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
#include "mocks/mock_tileset.hpp"
#include "../drawables/tile_sprite.hpp"
#include <stdexcept>
using ::testing::AtLeast;


TEST_CASE( "Tile sprite returns associated tileset" )
{
    m2g::Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    m2g::TileSprite sprite( tileset );

    REQUIRE( &( sprite.tileset() ) == &tileset );
}


TEST_CASE( "Calling TileSprite::setTile() references the given tile in the associated tile" )
{
    MockTileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    EXPECT_CALL( tileset, tileRect( 0 ) ).WillOnce( testing::Return( sf::IntRect() ) );
    EXPECT_CALL( tileset, tileRect( 1 ) ).WillOnce( testing::Return( sf::IntRect() ) );
    EXPECT_CALL( tileset, tileRect( 2 ) ).WillOnce( testing::Return( sf::IntRect() ) );
    EXPECT_CALL( tileset, tileRect( 3 ) ).WillOnce( testing::Return( sf::IntRect() ) );

    m2g::TileSprite sprite( tileset );
    sprite.setTile( 0 );
    sprite.setTile( 1 );
    sprite.setTile( 2 );
    sprite.setTile( 3 );
}


TEST_CASE( "Calling TileSprite::setTile() with a invalid tile throws std::out_of_range" )
{
    m2g::Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    m2g::TileSprite sprite( tileset );

    REQUIRE_THROWS_AS( sprite.setTile( 5 ), std::out_of_range );
}
