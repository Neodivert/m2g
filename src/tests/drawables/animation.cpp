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
    AnimationData animData( tileset );
    const AnimationState animState( 1, 1 );
    animData.addState( animState );

    Animation animation( animData );

    REQUIRE( animation.currentState() == 0 );
    REQUIRE( animation.currentFrame() == animState.firstFrame );
    REQUIRE( animation.refreshRate() == DEFAULT_ANIMATION_REFRESH_RATE );
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


TEST_CASE( "A different refresh rate can be specified when constructing an animation" )
{
    const Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset );
    const AnimationState animState( 2, 3, 0 );
    animData.addState( animState );

    Animation animation( animData, 3 );
    REQUIRE( animation.refreshRate() == 3 );
}

} // namespace m2g
