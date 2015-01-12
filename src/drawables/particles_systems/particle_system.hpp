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

#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include "particles_set.hpp"
#include <vector>

namespace m2g {

// Attributes per vertex = 12 = 2D pos + 2D vel + 4D color + 4D color variation.
const unsigned int N_ATTRIBUTES_PER_VERTEX = 2 + 2 + 4 + 4;

class ParticleSystem : public ParticlesSet
{
    private:
        // Vector with the current life of every generation of particles.
        std::vector< int > generationLife_;

        // Base line all the particles are generate from.
        glm::vec2 baseLine_[2];

        // Number of generations and particles per generation in the particle
        // system.
        unsigned int nParticlesPerGeneration_;

        // Particle size.
        unsigned int particleSize_;

        // Range of angles used to determine the initial velocity of every
        // particle in the system.
        float minAngle_, maxAngle_;

        // Range of speeds used to determine the initial velocity modulus
        // of every particle in the system.
        float minSpeed_, maxSpeed_;

        // Range of colors used to determine the initial color of every
        // particle in the system.
        glm::ivec4 minBaseColor_, maxBaseColor_;

        // Color variation applied to every particle in each step.
        glm::vec4 deltaColor_;

        // OpenGL's VAO and VBO used for this particle system.
        GLuint vao_;
        GLuint vbo_;

        // Size of the particle system's VBO (in bytes).
        unsigned int VBO_SIZE_;

        // Location of the uniform shader variables used during
        // drawing.
        static GLint mvpMatrixLocation;
        static GLint tLocation;

        // Bool for indicating whether the particle system is alive or not.
        bool alive_;

    public:
        /***
         * 1. Initialization
         ***/
        ParticleSystem( const char* file, const char*name );
        void loadXML( const char* file, const char*name );
        virtual void reset();


        /***
         * 2. Getters and setters
         ***/
        glm::vec2 getBaseLineOrigin() const ;
        unsigned int getNGenerations() const ;
        virtual bool isAlive() const ;
        virtual void setAlive( bool alive );


        /***
         * 3. Transformations
         ***/
        void moveBaseLine( const float& tx, const float& ty );


        /***
         * 4. Drawing
         ***/
        virtual void draw( const glm::mat4& projectionMatrix ) const ;
        virtual void drawAndUpdate( const glm::mat4& projectionMatrix );


        /***
         * 6. Auxiliar methods
         ***/
    private:
        void updateBoundaryBox( const float& x, const float& y );
};




} // namespace m2g

#endif // PARTICLESYSTEM_HPP
