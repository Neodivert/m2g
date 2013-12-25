/***
 * Copyright 2013 Moises J. Bonilla Caraballo (Neodivert)
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
 * 1. Drawables management
 ***/

DrawablePtr DrawablesSet::addDrawable( DrawablePtr newDrawable, float x, float y )
{
    // Move the given drawable to its final position.
    newDrawable->moveTo( x, y );

    // Add the given drawable to the container.
    drawables_.push_back( newDrawable );

    // Return the recently added newDrawable.
    return newDrawable;
}


SpritePtr DrawablesSet::addSprite( TilesetPtr tileset, float x, float y )
{
    // Add the given sprite to the container.
    return std::dynamic_pointer_cast<Sprite>(
                addDrawable( DrawablePtr( new Sprite( tileset ) ),
                             x,
                             y )
                );
}


/***
 * 2. Drawing
 **/

void DrawablesSet::drawAll( const glm::mat4& projectionMatrix ) const
{
    DrawablesContainer::const_iterator currentDrawable;

    // Draw all the drawables in the container.
    for( currentDrawable = drawables_.begin(); currentDrawable != drawables_.end(); currentDrawable++ ){
        (*currentDrawable)->draw( projectionMatrix );
    }
}


} // namespace m2g
