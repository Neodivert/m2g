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

#include "book.hpp"
#include <SDL2/SDL_image.h>

namespace m2g {

/***
 * 1. Construction
 ***/

Book::Book( SDL_Renderer *renderer, const char* backgroundPath ) :
    Drawable( renderer )
{
    setBackground( backgroundPath );
}


/***
 * 2. Setters
 ***/

void Book::setBackground( const char *backgroundPath )
{
    SDL_Surface* bgSurface = IMG_Load( backgroundPath );
    if( !bgSurface ){
        throw std::runtime_error( SDL_GetError() );
    }
    boundaryBox.width = bgSurface->w;
    boundaryBox.height = bgSurface->h;

    background_ =
            SDL_CreateTextureFromSurface( renderer_, bgSurface );
    if( !background_ ){
        throw std::runtime_error( SDL_GetError() );
    }

    SDL_FreeSurface( bgSurface );
}


/***
 * 3. Drawing
 ***/

void Book::draw() const
{
    const SDL_Rect dstRect = boundaryBox.sdlRect();
    SDL_RenderCopy( renderer_, background_, nullptr, &dstRect );
}



} // namespace m2g
