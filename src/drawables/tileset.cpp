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

#include "tileset.hpp"
#include <SDL2/SDL_image.h>

namespace m2g {


/***
 * 1. Initialization and destruction.
 ***/

Tileset::Tileset( SDL_Renderer* renderer, const tinyxml2::XMLNode* xmlNode, const char* folder ) :
    tileWidth( 0 ),
    tileHeight( 0 ),
    nRows( 0 ),
    nColumns( 0 ),
    nTiles( 0 ),
    renderer_( renderer ),
    texture_( nullptr )
{
    load( xmlNode, folder );
}


Tileset::Tileset( SDL_Renderer* renderer, SDL_Surface* surface, unsigned int tileWidth, unsigned int tileHeight ) :
    renderer_( renderer )
{
    load( surface, tileWidth, tileHeight );
}


Tileset::~Tileset()
{
    // Free the texture.
    SDL_DestroyTexture( texture_ );
}


/***
 * 2. Loading
 ***/

void Tileset::load( const tinyxml2::XMLNode* xmlNode, const char* folder )
{
    std::string tilesStr;
    unsigned int firstTile, lastTile;
    int separatorIndex;

    // Copy the tileset's name ().
    name = xmlNode->FirstChildElement( "src" )->GetText();

    // Read texture's source and frame dimensions from the given XML node.
    const char* imageFile = xmlNode->FirstChildElement( "src" )->GetText();
    const tinyxml2::XMLElement* tileDimensionsNode = xmlNode->FirstChildElement( "tile_dimensions" );
    tileWidth = (unsigned int)tileDimensionsNode->IntAttribute( "width" );
    tileHeight = (unsigned int)tileDimensionsNode->IntAttribute( "height" );
    const tinyxml2::XMLElement* collisionInfoNode = xmlNode->FirstChildElement( "collision_rects" );
    const tinyxml2::XMLElement* collisionRectNode;
    Rect colRect;

    SDL_Surface* image = NULL;

    // Load the texture image
    if( folder != nullptr ){
        image = IMG_Load( ( std::string( folder ) + std::string( imageFile ) ).c_str() );
    }else{
        image = IMG_Load( imageFile );
    }
    if( !image ){
        throw std::runtime_error( std::string( "ERROR: couldn't load texture image - " ) + std::string( IMG_GetError() ) );
    }

    // Validity condition: the tileset dimensions must be multiples
    // of the tile's dimensions.
    if( ( image->w % tileWidth ) || ( image->h % tileHeight ) ){
        throw std::runtime_error( "ERROR: Image's' dimensions are not multiples of tile's dimensions" );
    }

    // Read tileset general info.
    nRows = ( image->h / tileHeight );
    nColumns = ( image->w / tileWidth );
    nTiles = nRows * nColumns;

    // Load the texture
    texture_ = SDL_CreateTextureFromSurface( renderer_, image );

    // Free the image's surface.
    SDL_FreeSurface( image );

    // Create an empty vector of collision rects for each tile in the tileset.
    collisionRects.resize( nTiles );

    // Check if there is available collision info.
    if( collisionInfoNode ){

        // Get the first collision rect node.
        collisionRectNode = collisionInfoNode->FirstChildElement( "collision_rect" );

        // Process each collision rect in the tileset XML element.
        while( collisionRectNode ){

            // Get the current collision rect from the XML element.
            colRect.x = collisionRectNode->IntAttribute( "x" );
            colRect.y = collisionRectNode->IntAttribute( "y" );
            colRect.width = collisionRectNode->IntAttribute( "width" );
            colRect.height = collisionRectNode->IntAttribute( "height" );

            // The XML attribute "tiles" tells us in how many tiles is
            // the current collision rect present.
            tilesStr = collisionRectNode->Attribute( "tiles" );

            if( tilesStr == "all" ){
                // The collision rect is present in all the tiles
                // of the tileset.
                for( unsigned int i=0; i<nTiles; i++ ){
                    collisionRects[i].push_back( colRect );
                }
            }else{
                // The collision rect is present in a subset of
                // tiles.
                separatorIndex = tilesStr.find( '-' );
                if( separatorIndex != -1 ){
                    // The collision rect is present in a range
                    // of tiles [first-last].
                    firstTile = atoi( tilesStr.substr( 0, separatorIndex ).c_str() );
                    lastTile = atoi( tilesStr.substr( separatorIndex+1 ).c_str() );
                }else{
                    // The collision rect is present in an individual
                    // tile.
                    firstTile = atoi( tilesStr.c_str() );
                    lastTile = atoi( tilesStr.c_str() );
                }

                // Add the collision rect to the requested tiles' collision
                // info.
                for( unsigned int i=firstTile; i<=lastTile; i++ ){
                    collisionRects[i].push_back( colRect );
                }
            }

            // Get the next collision rect XML node.
            collisionRectNode = collisionRectNode->NextSiblingElement( "collision_rect" );
        }
    }
}


void Tileset::load( SDL_Surface* surface, unsigned int tileWidth, unsigned int tileHeight )
{
    // Load the tileset name.
    name = "SDL_Surface";

    // Load the tile dimensions.
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    // Validity condition: the tileset dimensions must be multiples
    // of the tile's dimensions.
    if( ( surface->w % tileWidth ) || ( surface->h % tileHeight ) ){
        throw std::runtime_error( "ERROR: Image's' dimensions are not multiples of tile's dimensions" );
    }

    // Read tileset general info.
    nRows = ( surface->h / tileHeight );
    nColumns = ( surface->w / tileWidth );
    nTiles = nRows * nColumns;

    // Load the texture
    texture_ = SDL_CreateTextureFromSurface( renderer_, surface );
}


/***
 * 3. Drawing
 ***/

void Tileset::drawTile( unsigned int tile, int x, int y ) const
{
    SDL_Rect srcRect =
    {
        static_cast< int >( tile % nColumns * tileWidth ),
        static_cast< int >( tile / nColumns * tileHeight ),
        static_cast< int >( tileWidth ),
        static_cast< int >( tileHeight )
    };
    SDL_Rect dstRect =
    {
        x,
        y,
        static_cast< int >( tileWidth ),
        static_cast< int >( tileHeight )
    };

    SDL_RenderCopy( renderer_, texture_, &srcRect, &dstRect );
}

} // Namespace m2g
