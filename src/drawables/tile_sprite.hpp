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

class TileSprite : public sf::Drawable, public sf::Transformable
{
    public:
        /***
         * 1. Construction
         ***/
        TileSprite( const Tileset& tileset );
        TileSprite( TilesetPtr tileset ); // TODO: Test!


        /***
         * 2. Getters
         ***/
        const Tileset& tileset() const;
        std::list< sf::FloatRect > collisionRects() const;
        sf::FloatRect getBoundaryBox() const; // TODO: Test!


        /***
         * 3. Setters
         ***/
        virtual void setTile( unsigned int tile );
        void setTileset( const Tileset& tileset );  // TODO: Test!
        void setTileset( TilesetPtr tileset );      // TODO: Test!


        /***
         * 4. Collision detection
         ***/
        bool collide( const TileSprite& sprite ) const;


        /***
         * 5. Drawing
         ***/
        virtual void draw( sf::RenderTarget &target, sf::RenderStates states ) const;


    private:
        sf::Sprite sprite_;
        TilesetPtr ownTileset_;
        const Tileset* tileset_;
        unsigned int currentTile_;
};

typedef std::unique_ptr< TileSprite > TileSpritePtr;

} // namespace m2g

#endif // TILE_SPRITE
