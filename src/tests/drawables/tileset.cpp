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
#include "../../drawables/tileset.hpp"

/*
 * TODO: Add tests
 * - Loading a tileset with width > MAX_WIDTH must throw
 * - Loading a tileset with height > MAX_HEIGHT must throw
 * - Add tests for getter Tileset::nTiles().
 */

// TODO: Check exception's messages.

TEST_CASE( "Tileset is created properly" )
{
    REQUIRE_NOTHROW( m2g::Tileset( "./data/test_tileset.png" , 32, 64 ); );
}


TEST_CASE( "Tileset is not found on disk" )
{
    REQUIRE_THROWS( m2g::Tileset( "./data/not_found.png" , 32, 32 ); );
}


TEST_CASE( "Loading a tileset with tileWidth > texture's width must throw" )
{
    REQUIRE_THROWS_AS( m2g::Tileset( "./data/tileset_w64_h64.png", 65, 64 ), std::invalid_argument );
}


TEST_CASE( "Loading a tileset with tileHeight > texture's must throw" )
{
    REQUIRE_THROWS_AS( m2g::Tileset( "./data/tileset_w64_h64.png", 64, 65 ), std::invalid_argument );
}


TEST_CASE( "Loading a tileset with texture's width % tileWidth must throw" )
{
    REQUIRE_THROWS_AS( m2g::Tileset( "./data/tileset_w64_h64.png", 33, 64 ), std::invalid_argument );
}


TEST_CASE( "Loading a tileset with texture's height % tileHeight must throw" )
{
    REQUIRE_THROWS_AS( m2g::Tileset( "./data/tileset_w64_h64.png", 32, 33 ), std::invalid_argument );
}


TEST_CASE( "Tileset gives correct tile rect" )
{
    m2g::Tileset tileset( "./data/tileset_w64_h64.png" , 32, 32 );

    sf::IntRect tileRect = tileset.tileRect( 0 );
    REQUIRE( tileRect == sf::IntRect( 0, 0, 32, 32 ) );

    tileRect = tileset.tileRect( 1 );
    REQUIRE( tileRect == sf::IntRect( 32, 0, 32, 32 ) );

    tileRect = tileset.tileRect( 2 );
    REQUIRE( tileRect == sf::IntRect( 0, 32, 32, 32 ) );

    tileRect = tileset.tileRect( 3 );
    REQUIRE( tileRect == sf::IntRect( 32, 32, 32, 32 ) );
}


TEST_CASE( "Tileset throws when a invalid tile index is fetched" )
{
    m2g::Tileset tileset( "./data/tileset_w64_h64.png" , 32, 32 );

    REQUIRE_THROWS_AS( tileset.tileRect( 5 ), std::out_of_range );
}


TEST_CASE( "Tileset gives right image dimensions (different components)" )
{
    m2g::Tileset tileset( "./data/test_tileset.png" , 32, 64 );

    const sf::Vector2u dimensions = tileset.dimensions();

    REQUIRE( dimensions.x == 256 );
    REQUIRE( dimensions.y == 128 );
}


TEST_CASE( "Tileset gives right image dimensions (same components)" )
{
    m2g::Tileset tileset( "./data/tileset_w64_h64.png" , 32, 64 );

    const sf::Vector2u dimensions = tileset.dimensions();

    REQUIRE( dimensions.x == 64 );
    REQUIRE( dimensions.y == 64 );
}


TEST_CASE( "Tileset gives right tile dimensions (different components)" )
{
    m2g::Tileset tileset( "./data/test_tileset.png", 32, 64 );

    const sf::Vector2u tileDimensions = tileset.tileDimensions();

    REQUIRE( tileDimensions.x == 32 );
    REQUIRE( tileDimensions.y == 64 );
}


TEST_CASE( "Tileset gives right tile dimensions (equal components)" )
{
    m2g::Tileset tileset( "./data/test_tileset.png", 32, 32 );

    const sf::Vector2u tileDimensions = tileset.tileDimensions();

    REQUIRE( tileDimensions.x == 32 );
    REQUIRE( tileDimensions.y == 32 );
}


TEST_CASE( "Tileset::collisionRects() returns an empty list when called on a new Tileset" )
{
    m2g::Tileset tileset( "./data/test_tileset.png", 32, 32 );

    for( unsigned int i = 0; i < 4; i++ ){
        std::list< sf::IntRect > rects = tileset.collisionRects( i );

        REQUIRE( rects.size() == 0 );
    }
}


TEST_CASE( "Tileset::collisionRects() returns the collision rects added to a tileset" )
{
    m2g::Tileset tileset( "./data/test_tileset.png", 32, 32 );
    std::list< sf::IntRect > rects;
    rects.push_back( { 1, 0, 24, 15 } );
    rects.push_back( { 3, 0, 15, 17 } );
    rects.push_back( { 3, 6, 5, 9 } );

    for( const sf::IntRect& rect : rects ){
        tileset.addCollisionRect( rect );
    }

    for( unsigned int i = 0; i < 4; i++ ){
        REQUIRE( tileset.collisionRects( i ) == rects );
    }
}


TEST_CASE( "Tileset::collisionRects() returns the collision rects added to a range of tiles" )
{
    m2g::Tileset tileset( "./data/test_tileset.png", 32, 32 );
    std::list< sf::IntRect > rects;
    rects.push_back( { 1, 0, 24, 15 } );
    rects.push_back( { 3, 0, 15, 17 } );
    rects.push_back( { 3, 6, 5, 9 } );

    for( const sf::IntRect& rect : rects ){
        tileset.addCollisionRect( rect, 1, 2 );
    }

    REQUIRE( tileset.collisionRects( 0 ).size() == 0 );
    REQUIRE( tileset.collisionRects( 1 ) == rects );
    REQUIRE( tileset.collisionRects( 2 ) == rects );
    REQUIRE( tileset.collisionRects( 3 ).size() == 0 );
}
