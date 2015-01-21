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

#include "rect.hpp"

namespace m2g {

void Rect::loadFromXML( tinyxml2::XMLElement* xmlElement )
{
    x = xmlElement->IntAttribute( "x" );
    y = xmlElement->IntAttribute( "y" );
    width = xmlElement->IntAttribute( "w" );
    height = xmlElement->IntAttribute( "h" );
}


bool Rect::collide( const Rect& b ) const
{
    return  (
        ( x < ( b.x + static_cast< int >( b.width ) ) ) &&
        ( ( x + static_cast< int >( width ) ) > b.x ) &&
        ( y < ( b.y + static_cast< int >( b.height ) ) ) &&
        ( ( y + static_cast< int >( height ) ) > b.y )
                );
}


SDL_Rect Rect::sdlRect() const
{
    SDL_Rect rect =
    {
        x,
        y,
        static_cast<int>( width ),
        static_cast<int>( height )
    };
    return rect;
}

} // namespace m2g
