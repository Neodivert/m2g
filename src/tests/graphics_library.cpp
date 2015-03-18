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
#include <array>
#include "../graphics_library.hpp"

namespace m2g {

TEST_CASE( "Tileset dimensions are loaded correctly" )
{
    GraphicsLibrary graphicsLibrary( "data/test_graphics_library.xml" );

    {
        TilesetPtr tileset =
                graphicsLibrary.getTilesetByName( "Tileset64x64 - tile32x32" );

        REQUIRE( tileset->dimensions() == sf::Vector2u( 64, 64 ) );
        REQUIRE( tileset->tileDimensions() == sf::Vector2u( 32, 32 ) );
    }
    {
        TilesetPtr tileset =
                graphicsLibrary.getTilesetByName( "Tileset64x64 - tile64x16" );

        REQUIRE( tileset->dimensions() == sf::Vector2u( 64, 64 ) );
        REQUIRE( tileset->tileDimensions() == sf::Vector2u( 64, 16 ) );
    }


    SECTION( "Tileset collision rects are loaded correctly" )
    {
        TilesetPtr tileset =
                graphicsLibrary.getTilesetByName( "Tileset64x64 - tile64x16" );

        const sf::IntRect commonRectForAllTiles( 14, 7, 5, 10 );
        const sf::IntRect commonRectForTiles2and3( 13, 5, 2, 5 );

        std::array< std::list< sf::IntRect >, 4 > collisionRects =
        {{
            {
                 commonRectForAllTiles,
                 { 15, 5, 25, 10 }
            },
            {
                 commonRectForAllTiles,
                 { 32, 0, 1, 3 }
            },
            {
                 commonRectForAllTiles,
                 commonRectForTiles2and3,
            },
            {
                 commonRectForAllTiles,
                 commonRectForTiles2and3
            }
        }};

        for( unsigned int tile = 0; tile < collisionRects.size(); tile++ ){
            REQUIRE( tileset->collisionRects( tile ) == collisionRects[tile] );
        }
    }
}


TEST_CASE( "Tileset without <name> is saved with name = <filename>" )
{
    GraphicsLibrary graphicsLibrary( "data/library_with_unnamed_tileset.xml" );

    REQUIRE( graphicsLibrary.getTilesetByName( "tileset_w64_h64.png" ) != nullptr );
}


TEST_CASE( "AnimationData is loaded from file" )
{
    GraphicsLibrary graphicsLibrary( "data/test_graphics_library.xml" );
    AnimationDataPtr animData =
            graphicsLibrary.getAnimationDataByName( "Animation 1" );

    SECTION( "AnimationData's refresh data is loaded from file" )
    {
        REQUIRE( animData->refreshRate() == 3 );
    }

    SECTION( "AnimationData's states are loaded from file" )
    {
        std::vector< AnimationState > EXPECTED_ANIM_STATES =
        {
            { 0, 3, 1 },
            { 1, 2, 0 }
        };

        REQUIRE( animData->nStates() == EXPECTED_ANIM_STATES.size() );
        for( unsigned int state = 0; state < EXPECTED_ANIM_STATES.size(); state++ ){
            REQUIRE( animData->state( state ) == EXPECTED_ANIM_STATES.at( state ) );
        }
    }
}


TEST_CASE( "AnimationData objects can be loaded from file by prefix" )
{
    GraphicsLibrary graphicsLibrary( "data/test_graphics_library.xml" );

    AnimationDataList animDataList =
            graphicsLibrary.getAnimationDataByPrefix( "animation_" );

    REQUIRE( animDataList.size() == 2 );

    SECTION( "AnimationData's refresh rates are loaded correctly" )
    {
        std::vector< unsigned int > EXPECTED_ANIM_REFRESH_RATES =
        {
            23, 34
        };

        unsigned int i = 0;
        for( AnimationDataPtr& animData : animDataList ){
            REQUIRE( animData->refreshRate() == EXPECTED_ANIM_REFRESH_RATES.at( i ) );
            i++;
        }
    }


    SECTION( "AnimationData's refresh rates are loaded correctly" )
    {
        std::vector< std::vector< AnimationState > > EXPECTED_ANIM_STATES =
        {
            { { 1, 2, 0 }, { 2, 3, 1 } },
            { { 0, 3, 0 } }
        };

        unsigned int animDataIndex = 0;

        for( AnimationDataPtr& animData : animDataList ){
            unsigned int animStateIndex = 0;
            for( animStateIndex = 0; animStateIndex < EXPECTED_ANIM_STATES.at( animDataIndex ).size(); animStateIndex++ ){
                REQUIRE( animData->state( animStateIndex ) == EXPECTED_ANIM_STATES.at( animDataIndex ).at( animStateIndex ) );
            }
            animDataIndex++;
        }
    }
}

} // namespace m2g
