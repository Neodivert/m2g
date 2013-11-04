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

#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include "../drawable.hpp"
#include "../../dependencies/dependencies.hpp"
#include "particles_generation.hpp"
#include <vector>

namespace m2g {

// Attributes per vertex = 12 = 2D pos + 2D vel + 4D color + 4D color variation.
const unsigned int N_ATTRIBUTES_PER_VERTEX = 2 + 2 + 4 + 4;

class ParticleSystem : public Drawable
{
    private:
        std::vector< ParticlesGeneration > particlesGenerations_;

        glm::vec2 baseLine_[2];

        unsigned int nGenerations_;
        unsigned int nParticlesPerGeneration_;
        float minAngle_, maxAngle_;
        glm::ivec4 minBaseColor_, maxBaseColor_;
        glm::vec4 deltaColor_;

        GLuint vao_;
        GLuint vbo_;

        unsigned int VBO_SIZE_;

        static GLint mvpMatrixLocation;
        static GLint tLocation;

    public:
        /***
         * 1. Initialization
         ***/
        ParticleSystem( const char* file, const char*name );
        void loadXML( const char* file, const char*name );


        /***
         * 2. Transformations
         ***/
        //virtual void translate( const float& tx, const float& ty );
        //virtual void moveTo( const float& x, const float& y );


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
};




} // namespace m2g

#endif // PARTICLESYSTEM_HPP
