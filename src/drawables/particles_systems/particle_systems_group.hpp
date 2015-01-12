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

#ifndef PARTICLE_SYSTEMS_GROUP_HPP
#define PARTICLE_SYSTEMS_GROUP_HPP

#include "particle_system.hpp"
#include "../drawable.hpp"

namespace m2g {

class ParticleSystemsGroup : public ParticlesSet
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
        virtual void reset();


        /***
         * 2. Getters and setters
         ***/
        virtual bool isAlive() const ;
        virtual void setAlive( bool alive );


        /***
         * 3. Transformations
         ***/
        virtual void translate( const float& tx, const float& ty );
        virtual void moveTo( const float& x, const float& y );


        /***
         * 4. Collision test
         ***/
        virtual bool collide( const Drawable& b ) const ;
        virtual const std::vector<Rect>* getCollisionRects() const ;


        /***
         * 5. Drawing
         ***/
        virtual void draw( const glm::mat4& projectionMatrix ) const ;
        virtual void drawAndUpdate( const glm::mat4& projectionMatrix );
};

} // namespace m2g

#endif // PARTICLE_SYSTEMS_GROUP_HPP
