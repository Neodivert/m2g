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

namespace m2g {

class Book : public Drawable
{
    public:
        /***
         * 1. Construction
         ***/
        Book( SDL_Renderer* renderer, const char* backgroundPath );


        /***
         * 2. Setters
         ***/
        void setBackground( const char* backgroundPath );


        /***
         * 3. Drawing
         ***/
        virtual void draw() const;


    private:
        SDL_Texture* background_;
};

} // namespace m2g

#endif // BOOK_HPP
