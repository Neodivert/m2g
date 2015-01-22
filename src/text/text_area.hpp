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

#ifndef TEXT_AREA
#define TEXT_AREA

#include <string>
#include "../utilities/rect.hpp"
#include "../utilities/alignment.hpp"
#include "../drawables/drawable.hpp"
#include "text_renderer.hpp"

namespace m2g {

class TextArea : public Drawable
{
    public:
        /***
         * 1. Construction
         ***/
        TextArea( SDL_Renderer* renderer,
                  tinyxml2::XMLElement* xmlElement,
                  TextRenderer* textRenderer,
                  unsigned int fontIndex,
                  const SDL_Color& fontColor );


        /***
         * 2. Loading
         ***/
        void loadFromXML( tinyxml2::XMLElement* xmlElement );


        /***
         * 3. Drawing
         ***/
        virtual void draw() const;


    private:
        /***
         * 4. Text rendering
         ***/
        void renderTextToTexture();


        /***
         * Attributes
         ***/
        std::string name_;
        std::string text_;
        VerticalAlign verticalAlign_;
        HorizontalAlign horizontalAlign_;

        SDL_Texture* texture_;

        TextRenderer* textRenderer_;
        unsigned int fontIndex_;
        SDL_Color fontColor_;
};

} // namespace m2g

#endif // TEXT_AREA

/*
<text_area name="">
        <rect x="" y="" w="" h="" />
        <vertical_align>middle</vertical_align>
        <horizontal_align>middle</horizontal_align>
        <text></text>
</text_area>
*/
