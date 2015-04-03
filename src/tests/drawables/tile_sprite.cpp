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
#include <array>
#include <SFML/Graphics/RenderTexture.hpp>
using ::testing::AtLeast;

namespace m2g {

TEST_CASE( "TileSprite's constructor calls Tileset's convenient getters" )
{
    sf::Texture texture;
    texture.loadFromFile( "./data/tileset_w64_h64.png" );
    MockTileset tileset( "./data/tileset_w64_h64.png", 32, 32 );

    EXPECT_CALL( tileset, texture() ).WillOnce( testing::ReturnRef( texture ) );
    EXPECT_CALL( tileset, tileRect( 0 ) ).WillOnce( testing::Return( sf::IntRect() ) );

    m2g::TileSprite sprite( tileset );
}


TEST_CASE( "Tile sprite returns associated tileset" )
{
    m2g::TilesetPtr tileset( new m2g::Tileset( "./data/tileset_w64_h64.png", 32, 32 ) );
    Tileset* tilesetRawPtr = tileset.get();

    SECTION( "Tile sprite returns associated tileset (reference)" )
    {
        m2g::TileSprite sprite( *tileset );
        REQUIRE( &( sprite.tileset() ) == tilesetRawPtr );
    }

    SECTION( "Tile sprite returns associated tileset (ptr)" )
    {
        m2g::TileSprite sprite( std::move( tileset ) );
        REQUIRE( &( sprite.tileset() ) == tilesetRawPtr );
    }
}


TEST_CASE( "Calling TileSprite::setTile() references the given tile in the associated tile" )
{
    sf::Texture texture;
    texture.loadFromFile( "./data/tileset_w64_h64.png" );
    ::testing::NiceMock< MockTileset > tileset( "./data/tileset_w64_h64.png", 32, 32 );
    ON_CALL( tileset, texture() ).WillByDefault( testing::ReturnRef( texture ) );
    EXPECT_CALL( tileset, tileRect( 0 ) ).WillOnce( testing::Return( sf::IntRect() ) );
    EXPECT_CALL( tileset, tileRect( 1 ) ).WillOnce( testing::Return( sf::IntRect() ) );
    EXPECT_CALL( tileset, tileRect( 2 ) ).WillOnce( testing::Return( sf::IntRect() ) );
    EXPECT_CALL( tileset, tileRect( 3 ) ).WillOnce( testing::Return( sf::IntRect() ) );

    m2g::TileSprite sprite( tileset );
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


TEST_CASE( "Two unmoved sprites sharing the same tileset must collide" )
{
    m2g::Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    tileset.addCollisionRect( sf::IntRect( 0, 0, 15, 20 ) );

    m2g::TileSprite sprite1( tileset );
    m2g::TileSprite sprite2( tileset );

    REQUIRE( sprite1.collide( sprite2 ) == true );
}


TEST_CASE( "Two unmoved sprites with different tile collision rects must's collide" )
{
    m2g::Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    tileset.addCollisionRect( sf::IntRect( 0, 0, 15, 20 ), 0, 0 );

    m2g::TileSprite sprite1( tileset );
    sprite1.setTile( 1 );
    m2g::TileSprite sprite2( tileset );

    REQUIRE( sprite1.collide( sprite2 ) == false );
}


TEST_CASE( "Moving a sprite far from another prevents collision between them" )
{
    m2g::Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    tileset.addCollisionRect( sf::IntRect( 0, 0, 15, 20 ) );

    m2g::TileSprite sprite1( tileset );
    m2g::TileSprite sprite2( tileset );

    sprite1.move( 15, 20 );

    REQUIRE( sprite1.collide( sprite2 ) == false );
}


TEST_CASE( "Rotating one sprite next to another makes them both collide" )
{
    m2g::Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    tileset.addCollisionRect( sf::IntRect( 8, 0, 16, 32 ) );

    m2g::TileSprite sprite1( tileset );
    m2g::TileSprite sprite2( tileset );

    // Put sprite2 next to sprite1 without colliding.
    sprite2.move( 24, 0 );
    REQUIRE( sprite1.collide( sprite2 ) == false );
    REQUIRE( sprite2.collide( sprite1 ) == false );

    // Rotating sprite2 towards sprite1 makes them collide.
    sprite2.rotate( 45 );
    REQUIRE( sprite1.collide( sprite2 ) == true );
    REQUIRE( sprite2.collide( sprite1 ) == true );

    // Rotating sprite2 back to its original orientation prevents
    // sprites from colliding.
    sprite2.rotate( -45 );
    REQUIRE( sprite1.collide( sprite2 ) == false );
    REQUIRE( sprite2.collide( sprite1 ) == false );
}


TEST_CASE( "Moving sprite rendering" )
{
    const sf::Vector2u SPRITE_POS( 8, 16 );
    const sf::Vector2u SPRITE_SIZE( 32, 32 );
    const sf::Vector2u TEXTURE_SIZE( 64, 64 );

    const std::array< sf::Color, 4 > expectedColors =
    {
        sf::Color( 255, 0, 0, 255 ),
        sf::Color( 0, 255, 0, 255 ),
        sf::Color( 0, 0, 255, 255 ),
        sf::Color( 255, 255, 255, 255 )
    };

    m2g::Tileset tileset( "./data/tileset_w64_h64.png", SPRITE_SIZE.x, SPRITE_SIZE.y );
    m2g::TileSprite sprite( tileset );
    sprite.setPosition( SPRITE_POS.x, SPRITE_POS.y );

    sf::RenderTexture renderTexture;
    renderTexture.create( TEXTURE_SIZE.x, TEXTURE_SIZE.y );

    for( unsigned int i = 0; i < expectedColors.size(); i++ ){
        sprite.setTile( i );

        renderTexture.clear();
        renderTexture.draw( sprite );
        renderTexture.display();

        const sf::Image image = renderTexture.getTexture().copyToImage();
        REQUIRE( image.getSize() == TEXTURE_SIZE );

        sf::Vector2u pixelPos;
        for( pixelPos.x = 0; pixelPos.x < TEXTURE_SIZE.x; pixelPos.x++ ){
            for( pixelPos.y = 0; pixelPos.y < TEXTURE_SIZE.y; pixelPos.y++ ){
                if( ( pixelPos.y >= SPRITE_POS.y ) &&
                        ( pixelPos.x >= SPRITE_POS.x ) &&
                        ( pixelPos.x < SPRITE_POS.x + SPRITE_SIZE.x ) &&
                        ( pixelPos.y < SPRITE_POS.y + SPRITE_SIZE.y ) ){
                    REQUIRE( image.getPixel( pixelPos.x, pixelPos.y ) == expectedColors.at( i ) );
                }else{
                    REQUIRE( image.getPixel( pixelPos.x, pixelPos.y ) == sf::Color( 0, 0, 0, 255 ) );
                }
            }
        }
    }
}


TEST_CASE( "TileSprite::setTileset() changes the associated tileset" )
{
    m2g::Tileset srcTileset( "./data/tileset_w64_h64.png", 32, 32 );
    std::unique_ptr< m2g::Tileset > dstTileset(
                new m2g::Tileset(
                    "./data/test_tileset.png", 32, 32 ) );
    m2g::Tileset* TilesetRawPtr = dstTileset.get();
    m2g::TileSprite sprite( srcTileset );

    SECTION( "The associated tileset is effectively changed" )
    {
        REQUIRE( &( sprite.tileset() ) != TilesetRawPtr );

        SECTION( "TileSprite::setTileset( Tileset& )" )
        {
            sprite.setTileset( *dstTileset );
            REQUIRE( &( sprite.tileset() ) == TilesetRawPtr );
        }

        SECTION( "TileSprite::setTileset( TilesetPtr )" )
        {
            sprite.setTileset( std::move( dstTileset ) );
            REQUIRE( &( sprite.tileset() ) == TilesetRawPtr );
        }
    }

    SECTION( "Changing a tileset sets the current tile to zero" )
    {
        sprite.setTile( 2 );

        SECTION( "TileSprite::setTileset( Tileset& )" )
        {
            sprite.setTileset( *dstTileset );
            REQUIRE( sprite.currentTile() == 0 );
        }

        SECTION( "TileSprite::setTileset( TilesetPtr )" )
        {
            sprite.setTileset( std::move( dstTileset ) );
            REQUIRE( sprite.currentTile() == 0 );
        }
    }
}


TEST_CASE( "TileSprite::setTile() updates the current tile" )
{
    m2g::Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    m2g::TileSprite sprite( tileset );

    REQUIRE( sprite.currentTile() == 0 );

    for( unsigned int i = 0; i < 4; i++ ){
        sprite.setTile( i );
        REQUIRE( sprite.currentTile() == i );
    }
}

} // namespace m2g
