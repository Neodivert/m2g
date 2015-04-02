/***
 * Copyright 2013 - 2015 Moises J. Bonilla Caraballo (Neodivert)
 *
 * This file is part of M2G.
 *
 * M2G is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * M2G is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with M2G.  If not, see <http://www.gnu.org/licenses/>.
***/

#include <catch.hpp>
#include "../../drawables/animation.hpp"
#include <cstring>
#include <vector>

namespace m2g {

TEST_CASE( "An animation can't have no states" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    const AnimationData emptyAnimData( tileset );

    try{
        Animation animation( emptyAnimData );
        REQUIRE( false );
    }catch( std::invalid_argument& ex ){
        const std::string expectedMsgPrefix = "animData";
        REQUIRE( !strncmp( ex.what(),
                           expectedMsgPrefix.c_str(),
                           expectedMsgPrefix.size() ) );
    }
}


TEST_CASE( "Unless otherwise specified, an animation is initialized with state 0" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationDataPtr animData( new AnimationData( tileset ) );
    const AnimationState animState( 1, 1 );
    animData->addState( animState );

    SECTION( "Animation is constructed using a AnimationData&" )
    {
        Animation animation( *animData );

        REQUIRE( &( animation.animationData() ) == animData.get() );
        REQUIRE( animation.currentState() == 0 );
        REQUIRE( animation.currentFrame() == animState.firstFrame );
    }

    SECTION( "Animation is constructed using a AnimationDataPtr" )
    {
        AnimationData* rawAnimDataPointer = animData.get();
        Animation animation( std::move( animData ) );

        REQUIRE( &( animation.animationData() ) == rawAnimDataPointer );
        REQUIRE( animation.currentState() == 0 );
        REQUIRE( animation.currentFrame() == animState.firstFrame );
    }
}


TEST_CASE( "Animation constructed using AnimationData& or AnimationDataPtr returns the same AnimationData" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationDataPtr animData( new AnimationData( tileset ) );
    AnimationData* rawAnimDataPointer = animData.get();
    const AnimationState animState( 1, 1 );
    animData->addState( animState );

    SECTION( "Animation is constructed using a AnimationData&" )
    {
        Animation animation( *animData );

        REQUIRE( &( animation.animationData() ) == rawAnimDataPointer );
    }

    SECTION( "Animation is constructed using a AnimationDataPtr" )
    {
        Animation animation( std::move( animData ) );

        REQUIRE( &( animation.animationData() ) == rawAnimDataPointer );
    }
}


TEST_CASE( "Animation::finished() returns true when current state finishes" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset );
    const AnimationState animState( 0, 3, 1 );
    animData.addState( animState );
    Animation animation( animData );

    // The animation will be finished at frame 3 (lastFrame).
    REQUIRE( animation.finished() == false );

    animation.setTile( 1 );
    REQUIRE( animation.finished() == false );

    animation.setTile( 2 );
    REQUIRE( animation.finished() == false );

    animation.setTile( 3 );
    REQUIRE( animation.finished() == true );

    animation.setTile( 0 );
    REQUIRE( animation.finished() == false );
}


TEST_CASE( "Changing current state sets Animation::finished() to false if new state isn't finished" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset );
    animData.addState( AnimationState( 0, 1, 0 ) );
    animData.addState( AnimationState( 2, 3, 2 ) );
    Animation animation( animData );

    animation.setTile( 1 );
    REQUIRE( animation.finished() == true );

    animation.setState( 1 );
    REQUIRE( animation.finished() == false );
}


TEST_CASE( "Changing current state sets Animation::finished() to true if new state is finished" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset );
    animData.addState( AnimationState( 0, 1 ) );
    animData.addState( AnimationState( 2, 2 ) );
    Animation animation( animData );

    REQUIRE( animation.finished() == false );

    animation.setState( 1 );
    REQUIRE( animation.finished() == true );
}


TEST_CASE( "Changing the associated animationData changes the current frame and state" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );

    AnimationData srcAnimData( tileset );
    srcAnimData.addState( AnimationState( 0, 1 ) );
    srcAnimData.addState( AnimationState( 2, 2 ) );

    AnimationData dstAnimData( tileset );
    dstAnimData.addState( AnimationState( 1, 3 ) );

    Animation animation( srcAnimData );

    animation.setState( 1 );
    REQUIRE( animation.currentState() == 1 );
    REQUIRE( animation.currentFrame() == srcAnimData.state( 1 ).firstFrame );

    animation.setAnimationData( dstAnimData );
    REQUIRE( animation.currentState() == 0 );
    REQUIRE( animation.currentFrame() == dstAnimData.state( 0 ).firstFrame );
}


TEST_CASE( "The current animation state can be changed" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset );
    std::vector< AnimationState > animStates =
    {
        { 0, 3 },
        { 0, 1 },
        { 2, 2 },
        { 3, 3 }
    };

    for( const AnimationState& animState : animStates ){
        animData.addState( animState );
    }

    Animation animation( animData );
    for( unsigned int i = 0; i < animStates.size(); i++ ){
        animation.setState( i );
        REQUIRE( animation.currentState() == i );
        REQUIRE( animation.currentFrame() == animStates[i].firstFrame );
    }
}


TEST_CASE( "Trying to change to an non-existent state throws out_of_range" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset );
    std::vector< AnimationState > animStates =
    {
        { 0, 3 },
        { 0, 1 },
        { 2, 2 },
        { 3, 3 }
    };

    animData.addState( animStates[0] );
    Animation animation( animData );

    for( unsigned int i = 1; i < animStates.size(); i++ ){
        REQUIRE_THROWS_AS( animation.setState( i ), std::out_of_range );

        animData.addState( animStates.at( i ) );

        REQUIRE_NOTHROW( animation.setState( i ) );
    }
}


TEST_CASE( "User can change the current frame using TileSprite::setTile()" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset );
    const AnimationState animState( 2, 3, 1 );
    animData.addState( animState );

    Animation animation( animData );

    REQUIRE( animation.currentFrame() == 2 );

    animation.setTile( 1 );
    REQUIRE( animation.currentFrame() == 1 );

    animation.setTile( 2 );
    REQUIRE( animation.currentFrame() == 2 );

    animation.setTile( 3 );
    REQUIRE( animation.currentFrame() == 3 );
}


TEST_CASE( "An attempt to set a frame outside of the current state must throw" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset );
    const AnimationState animState( 2, 2, 1 );
    animData.addState( animState );

    Animation animation( animData );

    REQUIRE_THROWS_AS( animation.setTile( 0 ), std::out_of_range );
    REQUIRE( animation.currentFrame() == 2 );

    REQUIRE_THROWS_AS( animation.setTile( 3 ), std::out_of_range );
    REQUIRE( animation.currentFrame() == 2 );
}


TEST_CASE( "An animation can be time-updated" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset, 1 );
    const AnimationState animState( 1, 3, 0 );
    animData.addState( animState );

    Animation animation( animData );

    REQUIRE( animation.currentFrame() == 1 );

    animation.update( 50 );
    REQUIRE( animation.currentFrame() == 1 );

    animation.update( 949 );
    REQUIRE( animation.currentFrame() == 1 );

    animation.update( 1 );
    REQUIRE( animation.currentFrame() == 2 );

    animation.update( 1000 );
    REQUIRE( animation.currentFrame() == 3 );

    animation.update( 1000 );
    REQUIRE( animation.currentFrame() == 0 );

    animation.update( 4000 );
    REQUIRE( animation.currentFrame() == 0 );

    animation.update( 2000 );
    REQUIRE( animation.currentFrame() == 2 );
}


} // namespace m2g
