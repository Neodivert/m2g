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

namespace m2g {

class TextArea : public Drawable
{
    public:
        /***
         * 1. Construction
         ***/
        TextArea( SDL_Renderer* renderer );


        /***
         * 3. Drawing
         ***/
        virtual void draw() const;


    private:
        std::string name_;
        std::string text_;
        Rect rect_;
        VerticalAlign verticalAlign_;
        HorizontalAlign horizontalAlign_;

        SDL_Texture* texture_;
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
