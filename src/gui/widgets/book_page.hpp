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

#ifndef BOOK_PAGE_HPP
#define BOOK_PAGE_HPP

#include "../../drawables/drawable.hpp"
#include "../../text/text_renderer.hpp"
#include "../../text/text_area.hpp"
#include <tinyxml2.h>

namespace m2g {

// TODO: Implement class TextDrawable and inherit it.
// TODO: Implement class DrawableParent or include an attribute
// Drawable::children_ for drawing drawables following a parentship hierarchy.
class BookPage : public Drawable
{
    public:
        /***
         * 1. Construction
         ***/
        BookPage( const TextRenderer* textRenderer,
                  const Rect& textArea,
                  const std::string& text,
                  const unsigned int fontIndex = 0 );
        BookPage( const TextRenderer* textRenderer,
                  const Rect& textArea,
                  tinyxml2::XMLElement* xmlElement,
                  const unsigned int fontIndex = 0 );


        /***
         * 2. Setters
         ***/
        void setTextArea( const Rect& textArea );


        /***
         * 3. Drawable interface
         ***/
        virtual void translate( int tx, int ty );
        virtual void moveTo( int x, int y );
        virtual void draw() const;


    private:
        const TextRenderer* textRenderer_;

        TextArea textArea_;
};

} // namespace m2g

#endif // BOOK_PAGE_HPP
