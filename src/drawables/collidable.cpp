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

#include "collidable.hpp"

namespace m2g {

/***
 * 1. Collision test
 ***/

bool Collidable::collide( const Collidable& b ) const
{
    const std::vector<Rect>* aRects = nullptr;
    const std::vector<Rect>* bRects = nullptr;

    const Rect aBoundaryBox = getBoundaryBox();
    const Rect bBoundaryBox = b.getBoundaryBox();

    if( !aBoundaryBox.collide( bBoundaryBox ) ){
        return false;
    }

    aRects = getCollisionRects();
    bRects = b.getCollisionRects();

    const glm::ivec2 bPosition = b.getPosition();

    Rect aRect, bRect;

    for( unsigned int i=0; i<aRects->size(); i++ ){
        aRect.x = ( (*aRects)[i] ).x + aBoundaryBox.x;
        aRect.y = ( (*aRects)[i] ).y + aBoundaryBox.y;
        aRect.width = ( (*aRects)[i] ).width;
        aRect.height = ( (*aRects)[i] ).height;

        for( unsigned int j=0; j<bRects->size(); j++ ){
            bRect.x = ( (*bRects)[j] ).x + bPosition.x;
            bRect.y = ( (*bRects)[j] ).y + bPosition.y;
            bRect.width = ( (*bRects)[j] ).width;
            bRect.height = ( (*bRects)[j] ).height;

            if( aRect.collide( bRect ) ){
                return true;
            }
        }
    }

    return false;
}


} // namespace m2g
