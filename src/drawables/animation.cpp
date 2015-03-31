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

#include "animation.hpp"

namespace m2g {

/***
 * 1. Construction
 ***/

Animation::Animation( const AnimationData &animData ) :
    TileSprite( animData.tileset() ),
    ownAnimData_( nullptr )
{
    setAnimationData( animData );
}


Animation::Animation( AnimationDataPtr animData ) :
    Animation( *animData )
{
    ownAnimData_ = std::move( animData );
}


/***
 * 3. Getters
 ***/

unsigned int Animation::currentState() const
{
    return currentState_;
}


unsigned int Animation::currentFrame() const
{
    return currentFrame_;
}


bool Animation::finished() const
{
    return ( currentFrame_ == animData_->state( currentState_ ).backFrame );
}


void Animation::setAnimationData( const AnimationData &animData )
{
    if( animData.nStates() == 0 ){
        throw std::invalid_argument( "animData can't be empty (0 states)" );
    }
    animData_ = &animData;
    TileSprite::setTileset( animData_->tileset() );
    setState( 0 );
}


/***
 * 4. Setters
 ***/

void Animation::setState( unsigned int newState )
{
    currentState_ = newState;
    currentFrame_ = animData_->state( currentState_ ).firstFrame;
}


void Animation::setTile( unsigned int tile )
{
    if( ( tile < std::min( animData_->state( currentState_ ).backFrame,
                           animData_->state( currentState_ ).firstFrame ) ) ||
        ( tile > animData_->state( currentState_ ).lastFrame ) ){
        throw std::out_of_range( "tile" );
    }
    TileSprite::setTile( tile );
    currentFrame_ = tile;
}


/***
 * 5. Updating
 ***/

void Animation::update( unsigned int ms )
{
    static unsigned int frameTime = 0;
    const unsigned int MS_PER_FRAME = (1000 / animData_->refreshRate());

    const unsigned int N_FRAMES = ( frameTime + ms ) / MS_PER_FRAME;
    frameTime = ( frameTime + ms ) % MS_PER_FRAME;

    unsigned int dstFrame = currentFrame_;
    for( unsigned int i = 0; i < N_FRAMES; i++ ){
        if( dstFrame < animData_->state( currentState_ ).lastFrame ){
            dstFrame++;
        }else{
            dstFrame = animData_->state( currentState_ ).backFrame;
        }
    }
    setTile( dstFrame );
}


} // namespace m2g
