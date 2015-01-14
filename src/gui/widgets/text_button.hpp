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

#include "widget.hpp"
#include <drawables/animation.hpp>

namespace m2g {

enum class ButtonStatus
{
    NORMAL,
    HOVER,
    PRESSED
};

class TextButton : public Widget, public Drawable
{
    public:
        /***
         * 1. Construction
         ***/
        // TODO: Use UTF-8 / UTF-16 for text.
        TextButton( const std::string& text );


        /***
         * 2. Event handling
         ***/
        virtual bool handleEvent( const SDL_Event &event );


    private:
        /***
         * 3. Private setters
         ***/
        void setStatus( ButtonStatus newStatus );


        /***
         * Attributes
         ***/
        ButtonStatus status_;
        SDL_Texture* currentTexture_;

        SDL_Texture* normalTexture_;
        SDL_Texture* hoverTexture_;
        SDL_Texture* pressedTexture_;
};

} // namespace m2g
