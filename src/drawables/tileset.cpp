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
#include <fstream>

namespace m2g {


/***
 * 1. Initialization and destruction.
 ***/

Tileset::Tileset( const std::string &imagePath, unsigned int tileWidth, unsigned int tileHeight ) :
    tileDimensions_( tileWidth, tileHeight )
{
    std::ifstream file( imagePath.c_str() );
    if( !file.is_open() ){
        throw std::runtime_error( "File not found" );
    }
    file.close();
    texture_.loadFromFile( imagePath );

    if( tileWidth > texture_.getSize().x ){
        throw std::invalid_argument( "Tileset constructor - tile width can't be greater thant tileset width" );
    }
    if( texture_.getSize().x % tileWidth ){
        throw std::invalid_argument( "Tileset constructor - tileset width must be dividable by tile width" );
    }
    if( tileHeight > texture_.getSize().y ){
        throw std::invalid_argument( "Tileset constructor - tile height can't be greater thant tileset height" );
    }
    if( texture_.getSize().y % tileHeight ){
        throw std::invalid_argument( "Tileset constructor - tileset height must be dividable by tile height" );
    }

    nRows_ = texture_.getSize().y / tileDimensions_.y;
    nColumns_ = texture_.getSize().x / tileDimensions_.x;
}


/***
 * 2. Getters
 ***/

sf::Vector2u Tileset::tileDimensions() const
{
    return tileDimensions_;
}


sf::Vector2u Tileset::dimensions() const
{
    return texture_.getSize();
}


sf::IntRect Tileset::tileRect( unsigned int tile ) const
{
    if( tile >= nRows_ * nColumns_ ){
        throw std::out_of_range( "tile " +
                                 std::to_string( tile ) +
                                 ") out of bounds (" +
                                 std::to_string( nRows_ * nColumns_ )
                                 + ")" );
    }

    const unsigned int row = tile / nRows_;
    const unsigned int column = tile % nRows_;

    return sf::IntRect( column * tileDimensions_.x,
                        row * tileDimensions_.y,
                        tileDimensions_.x,
                        tileDimensions_.y );
}


const sf::Texture &Tileset::texture() const
{
    return texture_;
}


std::list<sf::IntRect> Tileset::collisionRects( unsigned int tile ) const
{
    std::list<sf::IntRect> collisionRects;

    for( const TilesetCollisionRect& colRect : collisionRects_ ){
        if( tile >= colRect.firstTile && tile <= colRect.lastTile ){
            collisionRects.push_back( colRect.rect );
        }
    }

    return collisionRects;
}


unsigned int Tileset::nTiles() const
{
    return nRows_ * nColumns_;
}


/***
 * 3. Collision rects
 ***/

void Tileset::addCollisionRect( const sf::IntRect &rect )
{
    addCollisionRect( rect, 0, nRows_ * nColumns_ );
}


void Tileset::addCollisionRect( const sf::IntRect &rect,
                                unsigned int firstTile,
                                unsigned int lastTile )
{
    TilesetCollisionRect colRect = { rect, firstTile, lastTile };
    collisionRects_.push_back( colRect );
}

} // Namespace m2g
