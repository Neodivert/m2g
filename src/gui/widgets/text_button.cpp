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

namespace m2g {

/***
 * 1. Construction
 ***/

TextButton::TextButton( SDL_Renderer* renderer, const std::string& text )
{
    (void)( text );
    // TODO: Retrieve color and font from file.
    const SDL_Color color = { 255, 0, 0, 255 };
    TTF_Font* font =
            TTF_OpenFont( "/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf", 20 );
    if( font == nullptr ){
        throw std::runtime_error( TTF_GetError() );
    }

    setStatus( ButtonStatus::NORMAL );

    // Generate 3 different textures.
    SDL_Surface* surface = TTF_RenderText_Solid( font, text.c_str(), color );
    normalTexture_ = SDL_CreateTextureFromSurface( renderer, surface );
    hoverTexture_ = SDL_CreateTextureFromSurface( renderer, surface );
    pressedTexture_ = SDL_CreateTextureFromSurface( renderer, surface );
    SDL_FreeSurface( surface );

    TTF_CloseFont( font );
}


/***
 * 2. Destruction
 ***/

TextButton::~TextButton()
{
    SDL_DestroyTexture( normalTexture_ );
    SDL_DestroyTexture( hoverTexture_ );
    SDL_DestroyTexture( pressedTexture_ );
}


/***
 * 3. Event handling
 ***/

bool TextButton::handleEvent( const SDL_Event &event )
{
    return false;
}


/***
 * 4. Private setters
 ***/

void TextButton::setStatus( ButtonStatus newStatus )
{
    status_ = newStatus;
    switch( status_ ){
        case ButtonStatus::NORMAL:
            currentTexture_ = normalTexture_;
        break;
        case ButtonStatus::HOVER:
            currentTexture_ = hoverTexture_;
        break;
        case ButtonStatus::PRESSED:
            currentTexture_ = pressedTexture_;
        break;
    }
}

} // namespace m2g
