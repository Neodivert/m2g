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
#include <list>

namespace m2g {

struct TilesetCollisionRect
{
    sf::IntRect rect;
    unsigned int firstTile;
    unsigned int lastTile;
};


class Tileset
{
    public:
        /***
         * 1. Initialization and destruction.
         ***/
        Tileset( const std::string& imagePath, unsigned int tileWidth, unsigned int tileHeight );
        virtual ~Tileset() = default;


        /***
         * 2. Getters
         ***/
        sf::Vector2u tileDimensions() const;
        sf::Vector2u dimensions() const;
        virtual sf::IntRect tileRect( unsigned int tile ) const;
        virtual const sf::Texture& texture() const;
        std::list< sf::IntRect > collisionRects( unsigned int tile ) const;
        unsigned int nTiles() const;


        /***
         * 3. Collision rects
         ***/
        void addCollisionRect( const sf::IntRect& rect );
        void addCollisionRect( const sf::IntRect& rect,
                               unsigned int firstTile,
                               unsigned int lastTile );


    private:
        sf::Texture texture_;
        sf::Vector2u tileDimensions_;
        std::list< TilesetCollisionRect > collisionRects_;
        unsigned int nRows_;
        unsigned int nColumns_;
};

typedef std::shared_ptr< const Tileset > TilesetPtr;

} // Namespace m2g

#endif // TILESET_HPP
