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

#ifndef PARTICLE_SYSTEMS_GROUP_HPP
#define PARTICLE_SYSTEMS_GROUP_HPP

#include "particle_system.hpp"
#include "../drawable.hpp"
#include "../../dependencies/SDL_SavePNG/savepng.hpp"
//#include "../../dependencies/SDL_SavePNG/savepng.h"

namespace m2g {

class ParticleSystemsGroup : public Drawable
{
    private:
        std::vector< ParticleSystem > particleSystems_;
        ParticleSystem* refParticleSystem;

    public:
        /***
         * 1. Initialization and destruction.
         ***/
        ParticleSystemsGroup( const char* file, const char* name );
        void loadXML( const char* file, const char* name );


        /***
         * 2. Transformations
         ***/
        virtual void translate( const float& tx, const float& ty );
        virtual void moveTo( const float& x, const float& y );


        /***
         * 3. Collision test
         ***/
        virtual bool collide( const Drawable& b ) const ;
        virtual const std::vector<Rect>* getCollisionRects() const ;


        /***
         * 4. Drawing
         ***/
        virtual void draw( const glm::mat4& projectionMatrix ) const ;
        virtual void drawAndUpdate( const glm::mat4& projectionMatrix );
        void generateTileset( const char* file, const glm::vec4& currentViewport );
};

} // namespace m2g

#endif // PARTICLE_SYSTEMS_GROUP_HPP
