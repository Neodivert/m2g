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

#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include "../drawables/sprite.hpp"
#include <SDL2/SDL_ttf.h>
#include <map>

enum class TextAlign
{
    LEFT,
    CENTER,
    RIGHT
};

namespace m2g {

class TextRenderer
{
    public:
        /***
         * 1. Initialization and destruction
         ***/
        TextRenderer( SDL_Renderer* renderer );
        ~TextRenderer();


        /***
         * 2. Fonts management
         ***/
        unsigned int loadFont( const char* fontPath,
                               int fontSize );


        /***
         * 3. Drawing
         ***/
        SpritePtr drawText( const char* text, unsigned int fontIndex, const SDL_Color& color, TextAlign textAlign = TextAlign::LEFT );


        /***
         * 4. Auxiliar methods
         ***/
    private:
        void getTextDimensions( TTF_Font* font, const char* text, int& textWidth, int& textHeight, std::vector< std::string >& lines );

        SDL_Renderer *renderer_;
        std::map< unsigned int, TTF_Font* > fonts_;
        unsigned int nextFontID_;
};

} // namespace m2g

#endif // TEXT_RENDERER_HPP
