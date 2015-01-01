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

#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include "drawable.hpp"

namespace m2g {

class Collidable : public Drawable
{
    public:
        /***
         * 1. Collision test
         ***/
        virtual bool collide( const Collidable& b ) const ;
        virtual const std::vector<Rect>* getCollisionRects() const = 0;
};

} // namespace m2g

#endif // COLLIDABLE_HPP
