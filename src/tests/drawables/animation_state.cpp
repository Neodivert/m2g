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
#include "../../drawables/animation_state.hpp"

namespace m2g {

TEST_CASE( "AnimationState's empty constructor sets all attributes to 0" )
{
    AnimationState animState;

    REQUIRE( animState.firstFrame == 0 );
    REQUIRE( animState.lastFrame == 0 );
    REQUIRE( animState.backFrame == 0 );
}


TEST_CASE( "AnimationState's two-argument constructor sets firstFrame and backFrame equal" )
{
    AnimationState animState( 1, 3 );

    REQUIRE( animState.firstFrame == 1 );
    REQUIRE( animState.lastFrame == 3 );
    REQUIRE( animState.backFrame == animState.firstFrame );
}


TEST_CASE( "AnimationState's two-argument constructor must throw if lastFrame < firtFrame" )
{
    REQUIRE_THROWS_AS( AnimationState animState( 5, 4 ), std::invalid_argument );
}


TEST_CASE( "Animation's two-argument constructor must not throw if lastFrame == firstFrame" )
{
    REQUIRE_NOTHROW( AnimationState animationState( 5, 5 ) );
}


TEST_CASE( "AnimationState's three-argument constructor sets all attributes properly" )
{
    AnimationState animState( 3, 7, 5 );

    REQUIRE( animState.firstFrame == 3 );
    REQUIRE( animState.lastFrame == 7 );
    REQUIRE( animState.backFrame == 5 );
}


TEST_CASE( "AnimationState's three-argument constructor must throw if lastFrame < firtFrame" )
{
    REQUIRE_THROWS_AS( AnimationState animState( 5, 4, 2 ), std::invalid_argument );
}


TEST_CASE( "AnimationState's three-argument constructor must throw if backFrame > lastFrame" )
{
    REQUIRE_THROWS_AS( AnimationState animState( 2, 4, 5 ), std::invalid_argument );
}


TEST_CASE( "Equality tests" )
{
    AnimationState animStateA1( 3, 7, 5 );
    AnimationState animStateA2( 3, 7, 5 );
    AnimationState animStateB( 1, 7, 5 );
    AnimationState animStateC( 3, 15, 5 );
    AnimationState animStateD( 3, 7, 6 );

    REQUIRE( animStateA1 == animStateA1 );
    REQUIRE( animStateA1 == animStateA2 );
    REQUIRE( !( animStateA1 == animStateB ) );
    REQUIRE( !( animStateA1 == animStateC ) );
    REQUIRE( !( animStateA1 == animStateD ) );
}

} // namespace m2g
