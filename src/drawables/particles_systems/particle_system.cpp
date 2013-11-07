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

#include "particle_system.hpp"

namespace m2g {


GLint ParticleSystem::mvpMatrixLocation = -1;
GLint ParticleSystem::tLocation = -1;

const float PI = 3.14159265;


/***
 * 1. Initialization
 ***/


ParticleSystem::ParticleSystem( const char* file, const char*name )
{
    loadXML( file, name );
}


void ParticleSystem::loadXML( const char* file, const char*name )
{
    tinyxml2::XMLDocument xmlFile;
    tinyxml2::XMLElement* rootNode = nullptr;
    tinyxml2::XMLElement* xmlNode = nullptr;
    const char colorComponents[][2] =
    {
        "r", "g", "b", "a"
    };
    float angle;
    std::string str;

    GLint currentProgram = 0;

    GLfloat* vertexData = nullptr;
    unsigned int i = 0;

    boundaryBox.x = 0.0f;
    boundaryBox.y = 0.0f;
    boundaryBox.height = 0.0f;
    boundaryBox.width = 0.0f;

    // Try to open the requested XML file.
    xmlFile.LoadFile( file );
    if( !xmlFile.RootElement() ){
        throw std::runtime_error( std::string( "ERROR: Couldn't open file [" ) + file + "]" );
    }

    // Try to find the requested particle system configuration.
    rootNode = xmlFile.RootElement()->FirstChildElement( "particle_system" );
    while( rootNode && strcmp( name, rootNode->Attribute( "name" ) ) ){
        rootNode = rootNode->NextSiblingElement( "particle_system" );
    }
    if( !rootNode ){
        throw std::runtime_error( std::string( "ERROR: Couldn't find particle system [" ) + name + "]" );
    }

    // Get the generations info.
    xmlNode = rootNode->FirstChildElement( "particles" );
    nGenerations_ = xmlNode->IntAttribute( "generations" );
    nParticlesPerGeneration_ = xmlNode->IntAttribute( "particles_per_generation" );
    particleSize_ = xmlNode->IntAttribute( "particle_size" );

    // Initialize the base line.
    xmlNode = rootNode->FirstChildElement( "base_line" );
    baseLine_[1].x = xmlNode->FloatAttribute( "x1" );
    baseLine_[1].y = xmlNode->FloatAttribute( "y1" );

    // Initialize the angle range.
    xmlNode = rootNode->FirstChildElement( "angle" );
    minAngle_ = xmlNode->FloatAttribute( "min" );
    maxAngle_ = xmlNode->FloatAttribute( "max" );

    // Initialize the base color range.
    xmlNode = rootNode->FirstChildElement( "base_color" );
    for( i=0; i<4; i++ ){
        str = xmlNode->Attribute( colorComponents[i] );
        if( str.find( '-' ) != std::string::npos ){
            minBaseColor_[i] = atoi( ( str.substr( 0, str.find( '-' ) ) ).c_str() );
            maxBaseColor_[i] = atoi( ( str.substr( str.find( '-' ) + 1 ) ).c_str() );
        }else{
            minBaseColor_[i] = atoi( str.c_str() );
            maxBaseColor_[i] = atoi( str.c_str() );
        }
    }


    // Initialize the color delta.
    xmlNode = rootNode->FirstChildElement( "delta_color" );
    for( i=0; i<4; i++ ){
        deltaColor_[i] = xmlNode->FloatAttribute( colorComponents[i] ) / 255.0f;
    }

    // Initializa the vector with the current life of every generation.
    generationLife_.reserve( nGenerations_ ) ;
    for( i = 0; i < nGenerations_; i++ ){
        generationLife_.push_back( i );
    }

    VBO_SIZE_ = N_ATTRIBUTES_PER_VERTEX * nGenerations_ * nParticlesPerGeneration_ * sizeof( GLfloat );

    // Generate the VAO associated with this particles system and bind it as
    // the active one.
    glGenVertexArrays( 1, &vao_ );
    glBindVertexArray( vao_ );

    // Generate the VBO asociated with this particles systen, bind it as the
    // active one and allocate the requested space.
    glGenBuffers( 1, &vbo_ );
    glBindBuffer( GL_ARRAY_BUFFER, vbo_ );
    glBufferData( GL_ARRAY_BUFFER, VBO_SIZE_, NULL, GL_STATIC_DRAW );

    // Set vertex attribute pointers.

    // We are sending 2D vertices to the vertex shader.
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, N_ATTRIBUTES_PER_VERTEX * sizeof(GLfloat), (GLvoid*)(0) );
    glEnableVertexAttribArray( 0 );

    // We are sending 2D velocity vectors to the shader.
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, N_ATTRIBUTES_PER_VERTEX * sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)) );
    glEnableVertexAttribArray( 1 );

    // We are sending RGBA colors to the shader.
    glVertexAttribPointer( 2, 4, GL_FLOAT, GL_FALSE, N_ATTRIBUTES_PER_VERTEX * sizeof(GLfloat), (GLvoid*)(4*sizeof(GLfloat)) );
    glEnableVertexAttribArray( 2 );

    // We are sending RGBA color variations to the shader.
    glVertexAttribPointer( 3, 4, GL_FLOAT, GL_FALSE, N_ATTRIBUTES_PER_VERTEX * sizeof(GLfloat), (GLvoid*)(8*sizeof(GLfloat)) );
    glEnableVertexAttribArray( 3 );

    // Map the VBO memory for writting.
    vertexData = reinterpret_cast< GLfloat* >( glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY ) );

    // Set the vertex data for every particle in the system.
    for( i = 0; i < N_ATTRIBUTES_PER_VERTEX * nGenerations_ * nParticlesPerGeneration_; i += N_ATTRIBUTES_PER_VERTEX ){
        // Position.
        vertexData[i] = rand() % ((int)(baseLine_[1].x) + 1);
        vertexData[i+1] = rand() % ((int)(baseLine_[1].y) + 1);

        // Velocity.
        angle = ( rand() % (int)( (maxAngle_-minAngle_)*10 ) + ( (int)minAngle_ * 10 ) ) * 0.1;
        //std::cout << "(" << minAngle_ << ", " << maxAngle_ << "): " << angle << std::endl;
        vertexData[i+2] = cos( angle * PI / 180.0f );
        vertexData[i+3] = -sin( angle * PI / 180.0f );

        // Compute the final position of this particle and use it to update
        // the particle system's boundary box.
        //std::cout << "y: " << -( vertexData[i+1] + vertexData[i+3] * nGenerations_ ) << ", ";
        updateBoundaryBox( vertexData[i] + vertexData[i+2] * nGenerations_, -( vertexData[i+1] + vertexData[i+3] * nGenerations_ ) );

        // Color.
        vertexData[i+4] = ( ( rand() % (maxBaseColor_.r - minBaseColor_.r + 1) + minBaseColor_.r ) / 255.0f );
        vertexData[i+5] = ( ( rand() % (maxBaseColor_.g - minBaseColor_.g + 1) + minBaseColor_.g ) / 255.0f );
        vertexData[i+6] = ( ( rand() % (maxBaseColor_.b - minBaseColor_.b + 1) + minBaseColor_.b ) / 255.0f );
        vertexData[i+7] = ( ( rand() % (maxBaseColor_.a - minBaseColor_.a + 1) + minBaseColor_.a ) / 255.0f );

        // DColor.
        vertexData[i+8] = deltaColor_[0];
        vertexData[i+9] = deltaColor_[1];
        vertexData[i+10] = deltaColor_[2];
        vertexData[i+11] = deltaColor_[3];
    }

    // Update the base line so its include an offset from the boundary box's
    // origin.
    baseLine_[0].x = -boundaryBox.x;
    baseLine_[0].y = -boundaryBox.y;
    baseLine_[1].x += -boundaryBox.x;
    baseLine_[1].y += -boundaryBox.y;

    // With the boundary box origin "moved to" the particle system's origin, we
    // set the boundary box origin as the transformed position of the
    // particle system.
    boundaryBox.x = 0.0f;
    boundaryBox.y = 0.0f;

    // Unmap the VBO memory.
    glUnmapBuffer( GL_ARRAY_BUFFER );

    // If unset, set the GPU uniforms' locations.
    if( mvpMatrixLocation == -1 ){
        glGetIntegerv( GL_CURRENT_PROGRAM, &currentProgram );

        mvpMatrixLocation = glGetUniformLocation( currentProgram, "mvpMatrix" );
        tLocation = glGetUniformLocation( currentProgram, "t" );

        checkOpenGL( "Particles system () - Setting uniform locations" );
    }

    std::cout << "Boundary box: (" << boundaryBox.x << ", " << boundaryBox.y << ", " << boundaryBox.width << ", " << boundaryBox.height << ")" << std::endl;
    std::cout << "Base line: (" << baseLine_[0].x << ", " << baseLine_[0].y << ") - (" << baseLine_[0].x << ", " << baseLine_[0].y << ")" << std::endl;

    checkOpenGL( "Particles System constructor" );
}


/***
 * 2. Getters and setters
 ***/

glm::vec2 ParticleSystem::getBaseLineOrigin() const
{
    return baseLine_[0];
}


/***
 * 3. Transformations
 ***/

void ParticleSystem::moveBaseLine( const float& tx, const float& ty )
{
    baseLine_[0].x += tx;
    baseLine_[0].y += ty;

    baseLine_[1].x += tx;
    baseLine_[1].y += ty;
}


/***
 * 4. Collision test
 ***/

bool ParticleSystem::collide( const Drawable& b ) const
{
    b.getX();
    // FIXME: Use the boundary box in future versions.
    return false;
}

const std::vector<Rect>* ParticleSystem::getCollisionRects() const
{
    return nullptr;
}


/***
 * 5. Drawing
 ***/

void ParticleSystem::draw( const glm::mat4& projectionMatrix ) const
{
    /*
    unsigned int i = 0, j = 0;

    // Bind the VAO and VBO of this particle system as the active ones.
    glBindVertexArray( vao_ );
    glBindBuffer( GL_ARRAY_BUFFER, vbo_ );

    // Send the MVP matrix to the shader.
    glUniformMatrix4fv( mvpMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0] );

    //glUniform4fv( dColorLocation, 1, &dColor[0] );
    std::cout << glGetError() << std::endl;

    for( i = 0; i < particlesGenerations_.size(); i++ ){
        if( particlesGenerations_[i].t >= 0 ){
            // Send the current generation's t to the shader.
            glUniform1i( tLocation, particlesGenerations_[i].t );

            for( j = 0; j < particlesGenerations_[i].particles.size(); j++ ){
                // Send the currents particle's t and dColor to the shader.
                //glUniform4fv( dColorLocation, 1, &dColor[0] /*&(particlesGenerations_[i].particles[j].dColor[0])* );

                // Draw every particle as a point.
                glDrawArrays( GL_POINTS, i * particlesGenerations_[0].particles.size() + j, 1 );
            }
        }
    }
    */
}


void ParticleSystem::drawAndUpdate( const glm::mat4& projectionMatrix )
{
    unsigned int i = 0;

    glm::mat4 transformationMatrix = projectionMatrix * glm::translate( glm::mat4( 1.0f ), glm::vec3( boundaryBox.x + baseLine_[0].x, boundaryBox.height + boundaryBox.y + baseLine_[0].y, 0.0f ) );

    glPointSize( particleSize_ );

    // Bind the VAO and VBO of this particle system as the active ones.
    glBindVertexArray( vao_ );
    glBindBuffer( GL_ARRAY_BUFFER, vbo_ );

    // Send the MVP matrix to the shader.
    glUniformMatrix4fv( mvpMatrixLocation, 1, GL_FALSE, &transformationMatrix[0][0] );

    for( i = 0; i < nGenerations_; i++ ){
        if( generationLife_[i] >= 0 ){
            // Send the current generation's life to the shader.
            glUniform1i( tLocation, generationLife_[i] );

            // Draw all the particles in the current generation.
            glDrawArrays( GL_POINTS, i * nParticlesPerGeneration_, nParticlesPerGeneration_ );
        }

        generationLife_[i]++;
        if( generationLife_[i] > nGenerations_){
            generationLife_[i] = 0;
        }
    }

    glPointSize( 1 );
}


/***
 * 6. Auxiliar methods
 ***/

void ParticleSystem::updateBoundaryBox( const float& x, const float& y )
{
    if( x < boundaryBox.x ){
        boundaryBox.x = x;
    }else if( x > (boundaryBox.x + boundaryBox.width) ){
        boundaryBox.width = x - boundaryBox.x;
    }

    if( y < boundaryBox.y ){
        boundaryBox.y = y;
    }else if( y > (boundaryBox.y + boundaryBox.height) ){  
        boundaryBox.height = y - boundaryBox.y;
        std::cout << "new Height: " << boundaryBox.height << std::endl;
    }
}


} // namespace m2g
