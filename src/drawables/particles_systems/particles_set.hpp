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

#ifndef PARTICLES_SET_HPP
#define PARTICLES_SET_HPP

#include "../drawable.hpp"
#include "ps_tileset_info.hpp"


namespace m2g {


class ParticlesSet : public Drawable
{
    protected:
        unsigned int nGenerations_;

    public:
        /***
         * 1. Initialization
         ***/
        virtual void loadXML( const char* file, const char* name ) = 0;
        virtual void reset() = 0;


        /***
         * 2. Getters and setters
         ***/
        virtual unsigned int getNGenerations() const ;
        virtual bool isAlive() const = 0 ;
        virtual void setAlive( bool alive ) = 0 ;


        /***
         * 3. Collision test
         ***/
        virtual bool collide( const Drawable& b ) const ;
        virtual const std::vector<Rect>* getCollisionRects() const ;


        /***
         * 4. Drawing
         ***/
        virtual void draw( const glm::mat4& projectionMatrix ) const = 0;
        virtual void drawAndUpdate( const glm::mat4& projectionMatrix ) = 0;


        /***
         * 5. Tileset generation
         ***/
        virtual void generateTileset( const char* file,
                                      GLsizei tileWidth,
                                      GLsizei tileHeight,
                                      bool includeDeath = false,
                                      unsigned int nColumns = 0 );
};

} // namespace m2g

#endif // PARTICLES_SET_HPP
