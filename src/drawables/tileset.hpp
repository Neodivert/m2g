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

#include "drawable.hpp"
#include <memory>
#include <vector>
#include <tinyxml2.h>
#include <SDL2/SDL_ttf.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

namespace m2g {

class Tileset {

    public:
        // Tile dimensions.
        GLuint tileWidth;
        GLuint tileHeight;

        // Image dimensions.
        GLuint imageWidth;
        GLuint imageHeight;

        // Tileset number of elements.
        GLuint nRows;
        GLuint nColumns;
        GLuint nTiles;

        // Index of this tileset's vertex attributes in the tilesets buffer.
        unsigned int bufferIndex;

        // Name of the tileset's base image.
        std::string name;

        // We keep a vector of collision rects for each tile in the tileset.
        std::vector< std::vector< Rect > > collisionRects;


        /*** Methods ***/

        /***
         * 1. Initialization and destruction.
         ***/
        Tileset( SDL_Renderer* renderer, const tinyxml2::XMLNode* xmlNode, const char* folder );
        Tileset( SDL_Renderer* renderer, SDL_Surface* surface, GLuint tileWidth, GLuint tileHeight, GLfloat fx = 1.0f, GLfloat fy = 1.0f );
        ~Tileset();


        /***
         * 2. Loading
         ***/
        void load( const tinyxml2::XMLNode* xmlNode, const char* folder );
        void load( SDL_Surface* surface, GLuint tileWidth, GLuint tileHeight, GLfloat fx = 1.0f, GLfloat fy = 1.0f );


        /***
         * 3. Drawing
         ***/
        void drawTile( unsigned int tile, int x, int y ) const;


    protected:
        SDL_Renderer* renderer_;
        SDL_Texture* texture_;
};

typedef std::shared_ptr< const Tileset > TilesetPtr;

} // Namespace m2g

#endif // TILESET_HPP
