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

#ifndef TEXT_TEXTURE_HPP
#define TEXT_TEXTURE_HPP

#include <SDL2/SDL.h>

namespace m2g {

struct TextTexture
{
    /***
     * 1. Construction and destruction
     ***/
    TextTexture( SDL_Renderer* renderer,
                 SDL_Surface* surface,
                 const SDL_Rect& textRect );
    TextTexture( const TextTexture& ) = delete;
    TextTexture( TextTexture&& );
    ~TextTexture();


    /***
     * 2. Drawing
     ***/
    void draw( SDL_Rect dstRect ) const;


    /***
     * 3. Operators
     ***/
    TextTexture& operator = ( const TextTexture& ) = delete;
    TextTexture& operator = ( TextTexture&& );


    /***
     * Attributes
     ***/
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    private:
        SDL_Rect textRect;
};

} // namespace m2g

#endif // TEXT_TEXTURE_HPP
