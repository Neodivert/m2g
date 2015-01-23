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

#include "text_surface.hpp"
#include <utility>

namespace m2g {

/***
 * 1. Construction and destruction
 ***/

TextSurface::TextSurface( SDL_Surface *surface,
                          const SDL_Rect &textRect ) :
    surface( surface ),
    textRect_( textRect )
{}


TextSurface::TextSurface( TextSurface&& b )
{
    *this = std::move( b );
}


TextSurface::~TextSurface()
{
    if( surface ){
        SDL_FreeSurface( surface );
    }
}


/***
 * 2. Getters
 ***/

SDL_Rect TextSurface::textRect() const
{
    return textRect_;
}


/***
 * 3. Operators
 ***/

TextSurface& TextSurface::operator = ( TextSurface&& b )
{
    surface = b.surface;
    textRect_ = b.textRect_;

    b.surface = nullptr;

    return *this;
}


} // namespace m2g
