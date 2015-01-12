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

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>

#include "particles_set.hpp"


namespace m2g {


/***
 * 1. Initialization
 ***/



/***
 * 2. Getters and setters
 ***/

unsigned int ParticlesSet::getNGenerations() const
{
    return nGenerations_;
}


/***
 * 3. Collision test
 ***/

bool ParticlesSet::collide( const Drawable& b ) const
{
    b.getX();
    // FIXME: Use the boundary box in future versions.
    return false;
}


const std::vector<Rect>* ParticlesSet::getCollisionRects() const
{
    // TODO: Make use of boundary box.
    return nullptr;
}


/***
 * 5. Tileset generation
 ***/

void ParticlesSet::generateTileset( const char* file,
                                    GLsizei tileWidth,
                                    GLsizei tileHeight,
                                    bool includeDeath,
                                    unsigned int nColumns )
{
    GLint oldViewport[4];
    unsigned int i;
    SDL_Rect dstRect = { 0, 0, 0, 0 };
    unsigned int row, column;
    unsigned int nTiles;

    // Save the current viewport dimensions for restoring it at the end.
    glGetIntegerv( GL_VIEWPORT, oldViewport );

    // Generate a struct with all the info needed for generating a tileset.
    if( !includeDeath ){
        nTiles = nGenerations_;
    }else{
        nTiles = nGenerations_ * 2;
    }

    if( !tileWidth ){
        tileWidth = getWidth();
    }
    if( !tileHeight ){
        tileHeight = getHeight();
    }

    PSTilesetInfo psTilesetInfo( nTiles, tileWidth, tileHeight, nColumns );

    // Thanks to http://wiki.libsdl.org/SDL_CreateRGBSurface! :D
    SDL_SetSurfaceBlendMode( psTilesetInfo.getTileSurface(), SDL_BLENDMODE_NONE );

    // Bind the off-screen framebuffer and check its status.
    psTilesetInfo.bindFramebuffer();
    if( glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE ){
        std::cerr << "ERROR - Framebuffer not complete" << std::endl;
    }
    checkOpenGL( "ParticleSystem::geenerateTileset() - Checking off-screen framebuffer status" );

    // Render every frame in the particle system animation and blit it to the
    // tileset surface.
    i = 0;

    for( row=0; ( ( row<psTilesetInfo.getNRows() ) && ( i<psTilesetInfo.getNTiles() ) ); row++ ){
        dstRect.y = row * psTilesetInfo.getTileHeight();
        for( column=0; (column<psTilesetInfo.getNColumns() && i<psTilesetInfo.getNTiles() ); column++ ){
            dstRect.x = column * psTilesetInfo.getTileWidth();

            // Clear framebuffer and draw the particles set.
            glClear( GL_COLOR_BUFFER_BIT );
            checkOpenGL( "Drawing particles set - Reading pixels -1" );
            drawAndUpdate( glm::ortho( 0.0f,
                                       (float)( psTilesetInfo.getTileWidth() ),
                                       0.0f,
                                       (float)( psTilesetInfo.getTileHeight() ),
                                       1.0f,
                                       -1.0f ) );

            // Read the contents of the framebuffer into the tile surface.
            glReadBuffer( GL_COLOR_ATTACHMENT0 );
            glReadPixels( 0, 0, psTilesetInfo.getTileWidth(), psTilesetInfo.getTileHeight(), GL_RGBA, GL_UNSIGNED_BYTE, ( psTilesetInfo.getTileSurface() )->pixels );
            checkOpenGL( "Drawing particles set - Reading pixels" );

            SDL_BlitSurface( psTilesetInfo.getTileSurface(), nullptr, psTilesetInfo.getTilesetSurface(), &dstRect );

            i++;
            if( includeDeath && ( i == psTilesetInfo.getNTiles() / 2 ) ){
                setAlive( false );
            }
        }
    }
    if( includeDeath ){
        reset();
    }

    // Save the tileset in a PNG file.
    SDL_SavePNG( psTilesetInfo.getTilesetSurface(), file );

    // Unbind the used framebuffer.
    glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

    // Restart the old viewport.
    glViewport( oldViewport[0], oldViewport[1], oldViewport[2], oldViewport[3] );
}


} // namespace m2g
