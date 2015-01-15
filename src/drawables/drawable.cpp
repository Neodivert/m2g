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

#include "drawable.hpp"
#include <GL/glu.h>

namespace m2g {


void Rect::loadFromXML( tinyxml2::XMLElement* xmlElement )
{
    x = xmlElement->FloatAttribute( "x" );
    y = xmlElement->FloatAttribute( "y" );
    width = xmlElement->FloatAttribute( "w" );
    height = xmlElement->FloatAttribute( "h" );
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


/***
 * 1. Initialization
 ***/

Drawable::Drawable( SDL_Renderer* renderer ) :
    renderer_( renderer )
{
    boundaryBox = { 0, 0, 0, 0 };
}


/***
 * 2. Getters and setters
 ***/

int Drawable::getX() const
{
    return boundaryBox.x;
}


glm::ivec2 Drawable::getPosition() const
{
    return glm::ivec2( boundaryBox.x, boundaryBox.y );
}


unsigned int Drawable::getWidth() const
{
    return boundaryBox.width;
}


unsigned int Drawable::getHeight() const
{
    return boundaryBox.height;
}


const Rect* Drawable::getBoundaryBox() const
{
    return &boundaryBox;
}


/***
 * 3. Transformations
 ***/

void Drawable::translate( int tx, int ty )
{
    // Update the Sprite's position.
    boundaryBox.x += tx;
    boundaryBox.y += ty;
}


void Drawable::moveTo( int x, int y )
{
    // Update the Sprite's position.
    boundaryBox.x = x;
    boundaryBox.y = y;
}

} // namespace m2g
