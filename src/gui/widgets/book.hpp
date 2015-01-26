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

#ifndef BOOK_HPP
#define BOOK_HPP

#include "../../drawables/drawable.hpp"
#include "../../text/text_renderer.hpp"
#include "../../text/text_area.hpp"

namespace m2g {

class Book : public Drawable
{
    public:
        /***
         * 1. Construction
         ***/
        Book( const TextRenderer* textRenderer, const char* backgroundPath, unsigned int fontIndex = 0 );


        /***
         * 2. Setters
         ***/
        void setBackground( const char* backgroundPath );


        /***
         * 3. Drawawable interface
         ***/
        virtual void translate( int tx, int ty );
        virtual void moveTo( int x, int y );
        virtual void draw() const;


    private:
        const m2g::TextRenderer* textRenderer_;
        SDL_Texture* background_;

        // TODO: Use two text buttons instead.
        m2g::TextArea bookNavigationText_;
};

} // namespace m2g

#endif // BOOK_HPP