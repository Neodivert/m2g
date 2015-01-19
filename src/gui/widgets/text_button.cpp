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

#include "text_button.hpp"
#include <text/text_renderer.hpp>
#include <array>

namespace m2g {

/***
 * 1. Construction
 ***/

TextButton::TextButton( SDL_Renderer* renderer, const std::string& text ) :
    Sprite( renderer, generateTileset( renderer, text ) )
{
    setStatus( ButtonStatus::NORMAL );
}


/***
 * 2. Event handling
 ***/

bool TextButton::handleEvent( const SDL_Event &event )
{
    return false;
}


/***
 * 3. Initialization
 ***/

TilesetPtr TextButton::generateTileset( SDL_Renderer* renderer, const std::string &text )
{
    TextRenderer textRenderer( renderer );
    std::array< unsigned int, 3 > fontIndices;
    std::array< int, 3 > fontSize = { 30, 40, 40 };
    char fontPath[] = "/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf";
    unsigned int i = 0;
    SDL_Surface* textSurfaces[3];
    unsigned int maxWidth = 0, maxHeight = 0;
    unsigned int pow2width, pow2height;

    // Render the text associated to every button's state to its own surface
    // and compute the maximum width and height.
    for( i = 0; i < 3; i++ ){
        fontIndices[i] =
                textRenderer.loadFont(
                    fontPath,
                    fontSize[0] );

        const SDL_Color color =
        {
            static_cast< Uint8 >( 100 + 50 * i ),
            0,
            0,
            255
        };

        textSurfaces[i] =
                textRenderer.renderTextToSurface( text.c_str(),
                                                  fontIndices[i],
                                                  color,
                                                  TextAlign::CENTER );
        if( textSurfaces[i]->w > static_cast< int >( maxWidth ) ){
            maxWidth = textSurfaces[i]->w;
        }
        if( textSurfaces[i]->h > static_cast< int >( maxHeight ) ){
            maxHeight = textSurfaces[i]->h;
        }
    }

    // Round the maximum width and height to the maximum pow of two.
    pow2width = 1;
    while( pow2width < maxWidth ){
        pow2width <<= 1;
    }
    pow2height = 1;
    while( pow2height < maxHeight ){
        pow2height <<= 1;
    }

    // Set the RGBA mask for the text surface.
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const Uint32 rmask = 0xff000000;
        const Uint32 gmask = 0x00ff0000;
        const Uint32 bmask = 0x0000ff00;
        const Uint32 amask = 0x000000ff;
    #else
        const Uint32 rmask = 0x000000ff;
        const Uint32 gmask = 0x0000ff00;
        const Uint32 bmask = 0x00ff0000;
        const Uint32 amask = 0xff000000;
    #endif

    // Generate the button's surface.
    SDL_Surface* buttonSurface =
            SDL_CreateRGBSurface( 0,
                                  pow2width,
                                  pow2height * 3,
                                  32,
                                  rmask,
                                  gmask,
                                  bmask,
                                  amask );
    for( i = 0; i < 3; i++ ){
        SDL_Rect dstRect =
        {
            ( buttonSurface->w - textSurfaces[i]->w ) >> 1,
            static_cast< int >( buttonSurface->h * i + ( ( buttonSurface->h - textSurfaces[i]->h ) >> 1 ) ),
            textSurfaces[i]->w,
            textSurfaces[i]->h
        };
        SDL_BlitSurface( textSurfaces[i], nullptr, buttonSurface, &dstRect );
    }

    TilesetPtr buttonTileset(
                new Tileset( renderer,
                             buttonSurface,
                             buttonSurface->w,
                             buttonSurface->h ) );

    // Free resources.
    for( i = 0; i < 3; i++ ){
        SDL_FreeSurface( textSurfaces[i] );
    }
    SDL_FreeSurface( buttonSurface );

    return buttonTileset;
}


/***
 * 4. Private setters
 ***/

void TextButton::setStatus( ButtonStatus newStatus )
{
    status_ = newStatus;
}

} // namespace m2g
