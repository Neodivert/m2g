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

#include "ps_tileset_info.hpp"

namespace m2g {

/***
 * 1. Initialization and destruction
 ***/

PSTilesetInfo::PSTilesetInfo( unsigned int nTiles,
                              GLsizei tileWidth,
                              GLsizei tileHeight,
                              unsigned int nColumns ) :
    tileWidth_( tileWidth ),
    tileHeight_( tileHeight ),
    nRows_( 0 ),
    nColumns_( nColumns ),
    nTiles_( nTiles )
{
    computeTilesetDimensions();

    generateSurfaces();

    generateFrameBuffer();
}


PSTilesetInfo::~PSTilesetInfo()
{
    // Free SDL surfaces
    SDL_FreeSurface( tileSurface_ );
    SDL_FreeSurface( tilesetSurface_ );

    // Delete the off-screen framebuffer.
    // FIXME: Not declared without the EXT prefix.
    glDeleteFramebuffersEXT( 1, &framebuffer_ );
    glDeleteRenderbuffersEXT( 1, &renderBuffer_ );
}


void PSTilesetInfo::computeTilesetDimensions()
{
    GLsizei pow2;

    // Check the validity of tile width and round it to the nearest upper power
    // of two.
    if( !tileWidth_ ){
        throw std::runtime_error( "ERROR: tile's width can't be zero" );
    }

    pow2 = 1;
    while( pow2 < tileWidth_ ){
        pow2 <<= 1;
    }
    tileWidth_ = pow2;

    // Check the validity of tile height and round it to the nearest upper
    // power of two.
    if( !tileHeight_ ){
        throw std::runtime_error( "ERROR: tile's height can't be zero" );
    }

    pow2 = 1;
    while( pow2 < tileHeight_ ){
        pow2 <<= 1;
    }
    tileHeight_ = pow2;

    // Compute the number of rows and columns in the tileset.
    // FIXME: Compute it better.

    // If caller defined a number of columns for the tileset, compute the
    // number of rows. Otherwise, compute both dimensions.
    if( nColumns_ ){
        if( !( nTiles_ % nColumns_ ) ){
            nRows_ = nTiles_ / nColumns_;
        }else{
            nRows_ = nTiles_ / nColumns_ + 1;
        }
    }else{
        nRows_ = 1;
        nColumns_ = nTiles_;
    }
}


void PSTilesetInfo::generateSurfaces()
{
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

    tileSurface_ = SDL_CreateRGBSurface( 0,             // flags
                                         tileWidth_,    // width
                                         tileHeight_,   // height
                                         32,            // depth
                                         rmask,         // RGBA masks
                                         gmask,
                                         bmask,
                                         amask );

    if( !tileSurface_ ){
        throw std::runtime_error( std::string( "ERROR creating tile surface - " ) + SDL_GetError() );
    }
    SDL_FillRect( tileSurface_, nullptr, 0 );

    // Create a SDL surface for the full tileset.
    tilesetSurface_ = SDL_CreateRGBSurface( 0,                      // flags
                                            tileWidth_ * nColumns_, // width
                                            tileHeight_ * nRows_,   // height
                                            32,                     // depth
                                            rmask,                  // RGBA masks
                                            gmask,
                                            bmask,
                                            amask );
    if( !tilesetSurface_ ){
        throw std::runtime_error( std::string( "ERROR creating tileset surface - " ) + SDL_GetError() );
    }
    SDL_FillRect( tilesetSurface_, nullptr, 0 );
}


void PSTilesetInfo::generateFrameBuffer()
{
    // Generate and bind the render buffer.
    glGenRenderbuffersEXT( 1, &renderBuffer_ );
    glBindRenderbuffer( GL_RENDERBUFFER, renderBuffer_ );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA8, tileWidth_, tileHeight_ );
    checkOpenGL( "PSTilesetInfo::generateFrameBuffer() - Generating render buffer" );

    // Generate a framebuffer and bind it for off-screen drawing.
    glGenFramebuffers( 1, &framebuffer_ );
    glBindFramebuffer( GL_FRAMEBUFFER, framebuffer_ );
    checkOpenGL( "PSTilesetInfo::generateFrameBuffer() - Generating frame buffer" );

    // Attach the previous render buffer and framebuffer.
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer_ );
    checkOpenGL( "PSTilesetInfo::generateFrameBuffer() - Attaching render buffer to frame buffer" );

    // Set the viewport to the dimensions of the off-screen framebuffer.
    glViewport( 0, 0, tileWidth_, tileHeight_ );

    // Set off-screen framebuffer's parameters.
    glDisable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
}


/***
 * 2. Getters
 ***/

GLsizei PSTilesetInfo::getTileWidth() const
{
    return tileWidth_;
}


GLsizei PSTilesetInfo::getTileHeight() const
{
    return tileHeight_;
}


unsigned int PSTilesetInfo::getNRows() const
{
    return nRows_;
}


unsigned int PSTilesetInfo::getNColumns() const
{
    return nColumns_;
}


unsigned int PSTilesetInfo::getNTiles() const
{
    return nTiles_;
}


SDL_Surface* PSTilesetInfo::getTileSurface() const
{
    return tileSurface_;
}


SDL_Surface* PSTilesetInfo::getTilesetSurface() const
{
    return tilesetSurface_;
}


/***
 * 3. Auxiliar methods
 ***/

void PSTilesetInfo::bindFramebuffer() const
{
    glBindFramebuffer( GL_FRAMEBUFFER, framebuffer_ );
}


} // namespace m2g
