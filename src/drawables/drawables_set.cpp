/***
<<<<<<< HEAD
 * Copyright 2013, 2014 Moises J. Bonilla Caraballo (Neodivert)
=======
 * Copyright 2013 - 2015 Moises J. Bonilla Caraballo (Neodivert)
>>>>>>> raw-opengl-removal
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

#include "drawables_set.hpp"

namespace m2g {

/***
 * 1. Construction
 ***/

DrawablesSet::DrawablesSet( SDL_Renderer *renderer ) :
    Drawable( renderer )
{}


/***
 * 2. Drawables management
 ***/

DrawablePtr DrawablesSet::addDrawable( DrawablePtr newDrawable, float x, float y )
{
    // Move the given drawable to its final position.
    newDrawable->moveTo( x, y );

    // Add the given drawable to the container.
    drawables_.push_back( newDrawable );

    // Update the set's boundary box so it contains the boundary box of the
    // recently added drawable.
    updateBoundaryBox( newDrawable->getBoundaryBox() );

    // Return the recently added newDrawable.
    return newDrawable;
}


/***
 * 3. Transformations
 ***/

void DrawablesSet::translate( const float& tx, const float& ty )
{
    for( DrawablePtr drawable : drawables_ ){
        drawable->translate( tx, ty );
    }
}


void DrawablesSet::moveTo( const float& x, const float& y )
{
    for( DrawablePtr drawable : drawables_ ){
        drawable->moveTo( x, y );
    }
}


/***
 * 4. Drawing
 ***/

void DrawablesSet::draw() const
{
    for( DrawablePtr drawable : drawables_ ){
        drawable->draw();
    }
}


/***
 * 5. Auxiliar methods.
 ***/

void DrawablesSet::updateBoundaryBox( const Rect& newBoundaryBox )
{
    if( newBoundaryBox.x < boundaryBox.x ){
        boundaryBox.x = newBoundaryBox.x;
    }
    if( newBoundaryBox.y < boundaryBox.y ){
        boundaryBox.y = newBoundaryBox.y;
    }
    if( newBoundaryBox.x + newBoundaryBox.width > boundaryBox.x + boundaryBox.width ){
        boundaryBox.width = newBoundaryBox.width;
    }
    if( newBoundaryBox.y + newBoundaryBox.height > boundaryBox.y + boundaryBox.height ){
        boundaryBox.height = newBoundaryBox.height;
    }
}

} // namespace m2g
