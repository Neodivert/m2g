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
}


/***
 * 2. Getters
 ***/

sf::Vector2u Tileset::tileDimensions() const
{
    return tileDimensions_;
}


} // Namespace m2g
