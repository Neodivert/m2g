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
#include "../graphics_library.hpp"

namespace m2g {

TEST_CASE( "Tileset dimensions are loaded correctly" )
{
    GraphicsLibrary graphicsLibrary;

    graphicsLibrary.load( "data/test_library_1_tileset.xml" );

    {
        const m2g::Tileset& tileset =
                graphicsLibrary.tileset( "Tileset64x64 - tile32x32" );
        REQUIRE( tileset.dimensions() == sf::Vector2u( 64, 64 ) );
        REQUIRE( tileset.tileDimensions() == sf::Vector2u( 32, 32 ) );
    }
    {
        const m2g::Tileset& tileset =
                graphicsLibrary.tileset( "Tileset64x64 - tile64x16" );
        REQUIRE( tileset.dimensions() == sf::Vector2u( 64, 64 ) );
        REQUIRE( tileset.tileDimensions() == sf::Vector2u( 64, 16 ) );
        const std::list< sf::IntRect > collisionRects0 = { { 15, 5, 25, 10 } };
        const std::list< sf::IntRect > collisionRects1 = { { 32, 0, 1, 3 } };

        REQUIRE( tileset.collisionRects( 0 ) == collisionRects0 );
        REQUIRE( tileset.collisionRects( 1 ) == collisionRects1 );
    }
}

} // namespace m2g
