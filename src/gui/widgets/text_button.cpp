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

TextButton::TextButton( const std::string& text )
{
    (void)( text );

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
 * 3. Private setters
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
