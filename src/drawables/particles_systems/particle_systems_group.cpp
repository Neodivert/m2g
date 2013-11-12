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

#include "particle_systems_group.hpp"
#include <boost/math/common_factor_rt.hpp>

namespace m2g {

/***
 * 1. Initialization and destruction.
 ***/

ParticleSystemsGroup::ParticleSystemsGroup( const char* file, const char* name )
{
    loadXML( file, name );
}


void ParticleSystemsGroup::loadXML( const char* file, const char* name )
{
    tinyxml2::XMLDocument xmlFile;
    tinyxml2::XMLElement* rootNode = nullptr;
    tinyxml2::XMLElement* xmlNode = nullptr;
    glm::vec2 refBaseLineOrigin;
    glm::vec2 currentBaseLineOrigin;
    unsigned int i;
    const Rect* refBoundaryBox;
    const Rect* currentBoundaryBox;

    // Try to open the requested XML file.
    xmlFile.LoadFile( file );
    if( !xmlFile.RootElement() ){
        throw std::runtime_error( std::string( "ERROR: Couldn't open file [" ) + file + "]" );
    }

    // Try to find the requested particle system group configuration.
    rootNode = xmlFile.RootElement()->FirstChildElement( "particle_systems_group" );
    while( rootNode && strcmp( name, rootNode->Attribute( "name" ) ) ){
        rootNode = rootNode->NextSiblingElement( "particle_systems_group" );
    }
    if( !rootNode ){
        throw std::runtime_error( std::string( "ERROR: Couldn't find particle systems group [" ) + name + "]" );
    }

    // Load every particle system in the group.
    xmlNode = rootNode->FirstChildElement( "particle_system" );
    while( xmlNode ){
        std::cout << "Loading [" << xmlNode->Attribute( "name" ) << "]" << std::endl;
        particleSystems_.emplace_back( file, xmlNode->Attribute( "name" ) );

        xmlNode = xmlNode->NextSiblingElement( "particle_system" );
    }

    // Make the origins of the different particle system's base lines match
    // each other.
    if( particleSystems_.size() ){
        // TODO: Change this so the reference particle system is defined in
        // the XML config file.
        refParticleSystem = &particleSystems_[0];
        refBaseLineOrigin = refParticleSystem->getBaseLineOrigin();
        boundaryBox = *refParticleSystem->getBoundaryBox();
        refBoundaryBox = refParticleSystem->getBoundaryBox();

        for( i=1; i<particleSystems_.size(); i++ ){
            currentBaseLineOrigin = particleSystems_[i].getBaseLineOrigin();
            currentBoundaryBox = particleSystems_[i].getBoundaryBox();

            std::cout << "refH: " << refBoundaryBox->height << ", currentY: " << currentBoundaryBox->height << std::endl;
            particleSystems_[i].moveBaseLine( refBaseLineOrigin.x - currentBaseLineOrigin.x, refBoundaryBox->height - currentBoundaryBox->height );
        }
    }
}


/***
 * 2. Transformations
 ***/

void ParticleSystemsGroup::translate( const float& tx, const float& ty )
{
    std::vector< ParticleSystem >::iterator it = particleSystems_.begin();

    for( ; it != particleSystems_.end(); it++ )
    {
        it->translate( tx, ty );
    }
}


void ParticleSystemsGroup::moveTo( const float& x, const float& y )
{
    std::vector< ParticleSystem >::iterator it = particleSystems_.begin();

    for( ; it != particleSystems_.end(); it++ )
    {
        it->moveTo( x, y );
    }
}


/***
 * 3. Collision test
 ***/

bool ParticleSystemsGroup::collide( const Drawable& b ) const
{
    return false;
}


const std::vector<Rect>* ParticleSystemsGroup::getCollisionRects() const
{
    return nullptr;
}


/***
 * 4. Drawing
 ***/

void ParticleSystemsGroup::draw( const glm::mat4& projectionMatrix ) const
{
    std::vector< ParticleSystem >::const_iterator it = particleSystems_.begin();

    for( ; it != particleSystems_.end(); it++ )
    {
        it->draw( projectionMatrix );
    }
}

void ParticleSystemsGroup::drawAndUpdate( const glm::mat4& projectionMatrix )
{
    std::vector< ParticleSystem >::iterator it = particleSystems_.begin();

    for( ; it != particleSystems_.end(); it++ )
    {
        it->drawAndUpdate( projectionMatrix );
    }
}


void ParticleSystemsGroup::generateTileset( const char* file, const glm::vec4& currentViewport )
{
    GLuint framebuffer;
    GLuint renderBuffer;
    GLsizei tileWidth, tileHeight;
    GLint maxRenderbufferSize;
    SDL_Surface* tileSurface = nullptr;
    SDL_Surface* tilesetSurface = nullptr;
    SDL_Rect dstRect = { 0, 0, 0, 0 };
    unsigned int i;
    unsigned int nTiles = 0;
    unsigned int nRows, nColumns;
    unsigned int row, column;

    // Round off the tile width to its nearest upper pow of two.
    tileWidth = 1;
    while( tileWidth < boundaryBox.width ){
        tileWidth <<= 1;
    }

    // Round off the tile height to its nearest upper pow of two.
    tileHeight = 1;
    while( tileHeight < boundaryBox.height ){
        tileHeight <<= 1;
    }

    // Compute the least common multiple of all the particle system's numbers
    // of generations. This will be the number of tiles in the tileset.
    switch( particleSystems_.size() ){
        case 0:
            return;
        break;
        case 1:
            nTiles = particleSystems_[0].getNGenerations();
        break;
        default:
            nTiles = boost::math::lcm( particleSystems_[0].getNGenerations(), particleSystems_[1].getNGenerations() );
            for( i=2; i<particleSystems_.size(); i++ ){
                nTiles = boost::math::lcm( nTiles, particleSystems_[i].getNGenerations() );
            }
    }

    // Compute the number of rows and columns in the tileset.
    // FIXME: Compute it better.
    nRows = 1;
    nColumns = nTiles;

    std::cout << "nTiles: " << nTiles << std::endl;
    std::cout << "Tileset dimensions (tiles): " << nRows << " x " << nColumns << std::endl;

    // Create a SDL surface for tiles.
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        Uint32 rmask = 0xff000000;
        Uint32 gmask = 0x00ff0000;
        Uint32 bmask = 0x0000ff00;
        Uint32 amask = 0x000000ff;
    #else
        Uint32 rmask = 0x000000ff;
        Uint32 gmask = 0x0000ff00;
        Uint32 bmask = 0x00ff0000;
        Uint32 amask = 0xff000000;
    #endif

    tileSurface = SDL_CreateRGBSurface( 0,          // flags
                                        tileWidth,  // width
                                        tileHeight, // height
                                        32,         // depth
                                        rmask,      // RGBA masks
                                        gmask,
                                        bmask,
                                        amask );

    if( !tileSurface ){
        throw std::runtime_error( std::string( "ERROR creating tile surface - " ) + SDL_GetError() );
    }
    SDL_FillRect( tileSurface, nullptr, 0 );

    std::cout << "Tile dimensions: (" << tileWidth << ", " << tileHeight << ")" << std::endl;
    std::cout << "Surface dimensions: (" << tileSurface->w << ", " << tileSurface->h << ")" << std::endl;

    glGetIntegerv( GL_MAX_RENDERBUFFER_SIZE_EXT, &maxRenderbufferSize );
    std::cout << "Max renderBuffer: " << maxRenderbufferSize << std::endl;

    checkOpenGL( "ParticleSystemsGroup::geenerateTileset() - 1" );

    // Generate and bind the render buffer.
    glGenRenderbuffersEXT( 1, &renderBuffer );
    glBindRenderbuffer( GL_RENDERBUFFER, renderBuffer );
    checkOpenGL( "ParticleSystemsGroup::geenerateTileset() - 3" );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA8, tileWidth, tileHeight  );

    // Generate a framebuffer and bind it for off-screen drawing.
    glGenFramebuffers( 1, &framebuffer );
    glBindFramebuffer( GL_FRAMEBUFFER, framebuffer );

    checkOpenGL( "ParticleSystemsGroup::geenerateTileset() - 2" );

    checkOpenGL( "ParticleSystemsGroup::geenerateTileset() - 4" );

    // Attach the previous render buffer and framebuffer.
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer );

    checkOpenGL( "ParticleSystemsGroup::geenerateTileset() - 5" );

    // Set the viewport to the dimensions of the off-screen framebuffer.
    glViewport( 0, 0, tileWidth, tileHeight );

    // RENDER
    glDisable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    // Create a SDL surface for the full tileset.
    tilesetSurface = SDL_CreateRGBSurface( 0,                       // flags
                                           tileWidth * nColumns,    // width
                                           tileHeight * nRows,      // height
                                           32,                      // depth
                                           rmask,                   // RGBA masks
                                           gmask,
                                           bmask,
                                           amask );
    if( !tilesetSurface ){
        throw std::runtime_error( std::string( "ERROR creating tileset surface - " ) + SDL_GetError() );
    }
    SDL_FillRect( tilesetSurface, nullptr, 0 );


    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    // Render every frame in the particle system animation and blit it to the
    // tileset surface.
    i = 0;
    for( row=0; row<nRows, i<nTiles; row++ ){
        dstRect.y = row * tileHeight;
        for( column=0; column<nColumns, i<nTiles; column++ ){
            dstRect.x = column * tileWidth;

            glClear( GL_COLOR_BUFFER_BIT );

            drawAndUpdate( glm::ortho( 0.0f, (float)tileWidth, 0.0f, (float)tileHeight, 1.0f, -1.0f ) /* glm::ortho( 0.0f, (float)tileWidth, (float)tileHeight, 0.0f, 1.0f, -1.0f ) */ );

            glReadBuffer( GL_COLOR_ATTACHMENT0 );

            checkOpenGL( "ParticleSystemsGroup::geenerateTileset() - 6" );

            glReadPixels( 0, 0, tileWidth, tileHeight, GL_RGBA, GL_UNSIGNED_BYTE, tileSurface->pixels );

            // Thanks to http://wiki.libsdl.org/SDL_CreateRGBSurface! :D
            SDL_SetSurfaceBlendMode( tileSurface , SDL_BLENDMODE_NONE );
            std::cout << "Blitting: " << SDL_BlitSurface( tileSurface, nullptr, tilesetSurface, &dstRect ) << std::endl;

            i++;
        }
    }

    //for( unsigned int i = 0; i<tileWidth*tileHeight; i++ ){
    //    std::cout << (int)( ( (char *)( tileSurface->pixels ) )[i] ) << ", ";
    //}

    checkOpenGL( "ParticleSystemsGroup::geenerateTileset() - 7" );

    std::cout << "SavePNG: " << SDL_SavePNG( tilesetSurface, file ) << std::endl;

    if( glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE ){
        std::cerr << "ERROR - Framebuffer not complete" << std::endl;
    }

    // Unbind the used framebuffer.
    glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

    // Restart the app viewport.
    glViewport( currentViewport[0], currentViewport[1], currentViewport[2], currentViewport[3] );

    // Delete the user framebuffer.
    // FIXME: Not declared.
    glDeleteFramebuffersEXT( 1, &framebuffer );
    glDeleteRenderbuffersEXT( 1, &renderBuffer );

    SDL_FreeSurface( tileSurface );
}

} // namespace m2g
