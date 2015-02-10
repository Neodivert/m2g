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

#ifndef TILESET_HPP
#define TILESET_HPP

#include <memory>
#include <SFML/Graphics/Texture.hpp>

namespace m2g {

class Tileset : public sf::Texture
{
    public:
        /***
         * 1. Initialization and destruction.
         ***/
        Tileset( const std::string& imagePath, unsigned int tileWidth, unsigned int tileHeight );


        /***
         * 2. Getters
         ***/
        sf::Vector2u tileDimensions() const;
        sf::Vector2u dimensions() const;


    private:
        sf::Vector2u tileDimensions_;
};

typedef std::shared_ptr< const Tileset > TilesetPtr;

} // Namespace m2g

#endif // TILESET_HPP
