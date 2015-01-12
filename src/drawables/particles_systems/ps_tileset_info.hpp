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

#ifndef PS_TILESET_INFO_H
#define PS_TILESET_INFO_H

#include "../drawable.hpp"
#include "../../dependencies/SDL_SavePNG/savepng.hpp"

namespace m2g {

class PSTilesetInfo
{
    private:
        // Tileset dimensions
        GLsizei tileWidth_;
        GLsizei tileHeight_;
        unsigned int nRows_;
        unsigned int nColumns_;
        unsigned int nTiles_;

        // SDL surfaces
        SDL_Surface* tileSurface_;
        SDL_Surface* tilesetSurface_;

        // Off-screen framebuffer
        GLuint framebuffer_;
        GLuint renderBuffer_;

    public:
        /***
         * 1. Initialization and destruction
         ***/
        PSTilesetInfo( unsigned int nTiles,
                       GLsizei tileWidth = 0,
                       GLsizei tileHeight = 0,
                       unsigned int nColumns = 0 );
        ~PSTilesetInfo();

    private:
        void computeTilesetDimensions();
        void generateSurfaces();
        void generateFrameBuffer();


        /***
         * 2. Getters
         ***/
    public:
        GLsizei getTileWidth() const ;
        GLsizei getTileHeight() const ;
        unsigned int getNRows() const ;
        unsigned int getNColumns() const ;
        unsigned int getNTiles() const ;
        SDL_Surface* getTileSurface() const ;
        SDL_Surface* getTilesetSurface() const ;


        /***
         * 3. Auxiliar methods
         ***/
        void bindFramebuffer() const ;
};

}

#endif // PS_TILESET_INFO_H
