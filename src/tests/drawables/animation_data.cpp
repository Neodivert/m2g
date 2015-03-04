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
#include "../../drawables/animation_data.hpp"
#include <vector>

namespace m2g {

TEST_CASE( "We can retrieve multiple AnimationState added to an AnimationData" )
{
    std::vector< AnimationState > animStates =
    {
        { 0, 1, 0 },
        { 2, 2, 1 },
        { 1, 2, 2 }
    };
    Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset );
    AnimationState animState( 0, 1, 0 );

    for( const AnimationState& animState : animStates ){
        animData.addState( animState );
    }

    for( unsigned int i = 0; i < animStates.size(); i++ ){
        REQUIRE( animData.state( i ) == animStates[i] );
    }
}

} // namespace m2g
