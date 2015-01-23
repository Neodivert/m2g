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

#ifndef TEXT_SURFACE_HPP
#define TEXT_SURFACE_HPP

#include <SDL2/SDL.h>

namespace m2g {

struct TextSurface
{
    /***
     * 1. Construction and destruction
     ***/
    TextSurface( SDL_Surface* surface,
                 const SDL_Rect& textRect );
    TextSurface( const TextSurface& ) = delete;
    TextSurface( TextSurface&& );
    ~TextSurface();


    /***
     * 2. Getters
     ***/
    SDL_Rect textRect() const;


    /***
     * 2. Operators
     ***/
    TextSurface& operator = ( const TextSurface& ) = delete;
    TextSurface& operator = ( TextSurface&& );


    /***
     * Attributes
     ***/
    SDL_Surface* surface;

    private:
        SDL_Rect textRect_;
};

} // namespace m2g

#endif // TEXT_SURFACE_HPP
