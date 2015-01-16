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

#include "sprite.hpp"

namespace m2g {

/***
 * 1. Initialization
 ***/

Sprite::Sprite( SDL_Renderer* renderer ) :
    Drawable( renderer ),
    currentTile( 0 )
{}

Sprite::Sprite( SDL_Renderer* renderer, TilesetPtr tileset_ ) :
    Drawable( renderer ),
    currentTile( 0 )
{
    // Share the tileset given as an argument.
    setTileset( tileset_ );
}


/***
 * 2. Getters
 ***/

TilesetPtr Sprite::getTileset()
{
    return tileset;
}


unsigned int Sprite::getCurrentTile() const
{
    return currentTile;
}


glm::ivec2 Sprite::getPosition() const
{
    return Drawable::getPosition();
}


Rect Sprite::getBoundaryBox() const
{
    return Drawable::getBoundaryBox();
}


/***
 * 3. Setters
 ***/

void Sprite::setTileset( TilesetPtr tileset )
{
    // Start sharing the new tileset.
    this->tileset = tileset;

    // Update the sprite's boundary box with the dimensions of a tile.
    glm::ivec2 tileDimensions = tileset->tileDimensions();
    boundaryBox.width = tileDimensions.x;
    boundaryBox.height = tileDimensions.y;

    // Restart current tile.
    currentTile = 0;
}


void Sprite::setTile( unsigned int tile )
{
    if( tile < tileset->nTiles() ){
        currentTile = tile;
    }else{
        throw std::runtime_error( "ERROR: tile index out of limits" );
    }
}


void Sprite::nextTile()
{
    if( currentTile < (tileset->nTiles() - 1) ){
        currentTile++;
    }else{
        currentTile = 0;
    }
}


void Sprite::previousTile()
{
    if( currentTile ){
        currentTile--;
    }else{
        currentTile = tileset->nTiles() - 1;
    }
}


/***
 * 4. Collision detection
 ***/

const std::vector<Rect>* Sprite::getCollisionRects() const
{
    return &( tileset->collisionRects( currentTile ) );
}


/***
 * 5. Drawing
 ***/

void Sprite::draw() const {
    const glm::ivec2 pos = getPosition();
    tileset->drawTile( currentTile, pos.x, pos.y );
}

} // Namespace m2g
