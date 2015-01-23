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

#include "text_texture.hpp"
#include <utility>

namespace m2g {

/***
 * 1. Construction and destruction
 ***/

TextTexture::TextTexture( SDL_Renderer *renderer,
                          SDL_Surface *surface,
                          const SDL_Rect &textRect ) :
    renderer( renderer ),
    textRect( textRect )
{
    texture = SDL_CreateTextureFromSurface( renderer, surface );
}


TextTexture::TextTexture( TextTexture&& b )
{
    *this = std::move( b );
}


TextTexture::~TextTexture()
{
    if( texture ){
        SDL_DestroyTexture( texture );
    }
}


/***
 * 2. Drawing
 ***/

void TextTexture::draw( SDL_Rect dstRect ) const
{
    SDL_RenderCopy( renderer, texture, &textRect, &dstRect );
}


/***
 * 3. Operators
 ***/

TextTexture& TextTexture::operator = ( TextTexture&& b )
{
    renderer = b.renderer;
    texture = b.texture;
    textRect = b.textRect;

    b.texture = nullptr;

    return *this;
}


} // namespace m2g
