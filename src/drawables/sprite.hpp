/***
 * Copyright 2013 Moises J. Bonilla Caraballo (Neodivert)
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

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "tileset.hpp"
#include "../utilities/tilesets_buffer.hpp"
#include <memory>
#include <iostream>
#include <vector>

namespace m2g {

class Sprite : public Drawable
{
    private:
        static GLint mvpMatrixLocation;
        static GLint samplerLocation;
        static GLint sliceLocation;

        TilesetPtr tileset;
        GLuint currentTile;

    public:
        /***
         * 1. Initialization and destruction
         ***/
        Sprite();
        Sprite( TilesetPtr tileset );


        /***
         * 2. Getters
         ***/
        TilesetPtr getTileset();
        GLuint getCurrentTile() const ;


        /***
         * 3. Setters
         ***/
        virtual void setTileset( TilesetPtr tileset );
        virtual void setTile( const GLuint tile );
        virtual void nextTile();
        virtual void previousTile();


        /***
         * 4. Collision detection
         ***/
        virtual const std::vector<Rect>* getCollisionRects() const ;


        /***
         * 5. Drawing
         ***/
        virtual void draw( const glm::mat4& projectionMatrix ) const ;


        /***
         * 6. Auxiliar methods
         ***/
    private:
        virtual void sendMVPMatrixToShader( const glm::mat4& mvpMatrix ) const ;
};


} // Namespace m2g

#endif // SPRITE_HPP
