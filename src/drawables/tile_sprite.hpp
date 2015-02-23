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

#ifndef TILE_SPRITE
#define TILE_SPRITE

#include "tileset.hpp"
#include <SFML/Graphics/Sprite.hpp>

namespace m2g {

class TileSprite : public sf::Sprite
{
    public:
        /***
         * 1. Construction
         ***/
        TileSprite( const Tileset& tileset );


        /***
         * 2. Getters
         ***/
        const Tileset& tileset() const;


        /***
         * 3. Setters
         ***/
        void setTile( unsigned int tile );


    private:
        const Tileset* tileset_;
};

} // namespace m2g

#endif // TILE_SPRITE
