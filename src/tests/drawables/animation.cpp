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

} // namespace m2g
