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

#ifndef DRAWABLES_SET_HPP
#define DRAWABLES_SET_HPP

#include "drawable.hpp"
#include "sprite.hpp"
#include <list>

namespace m2g {

typedef std::list< DrawablePtr > DrawablesContainer;

class DrawablesSet : public Drawable
{
    private:
        // Drawables container.
        DrawablesContainer drawables_;

    public:
        /***
         * 1. Drawables management
         ***/
        DrawablePtr addDrawable( DrawablePtr newDrawable, float x = 0.0f, float y = 0.0f );
        SpritePtr addSprite( TilesetPtr tileset, float x = 0.0f, float y = 0.0f );


        /***
         * 2. Transformations
         ***/
        virtual void translate( const float& tx, const float& ty );
        virtual void moveTo( const float& x, const float& y );


        /***
         * 3. Drawing
         ***/
        virtual void draw( const glm::mat4& projectionMatrix ) const ;


        /***
         * 4. Auxiliar methods.
         ***/
        void updateBoundaryBox( const Rect* newBoundaryBox );
};

} // namespace m2g

#endif // DRAWABLES_SET_HPP
