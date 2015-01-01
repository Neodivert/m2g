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
 * 1. Initialization and destruction
 ***/

Animation::Animation( AnimationDataPtr animationData ) :
    Sprite( animationData->tileset ),
    lastFrameTick_( 0 )
{
    setAnimationData( animationData );
}


/***
 * 2. Getters
 ***/

int Animation::getAnimationState() const
{
    return currentState;
}


GLuint Animation::getFrame() const
{
    return getCurrentTile();
}


bool Animation::finished() const
{
    return animationFinished_;
}


/***
 * 3. Setters
 ***/

void Animation::setAnimationData( AnimationDataPtr animationData )
{
    // Set static data.
    setTileset( animationData->tileset );
    this->animationData = animationData;

    // Reset current state.
    setAnimationState( 0 );
}


void Animation::setAnimationState( int newState )
{
    // Get the new animation state's info.
    std::array< int, 3 > state = animationData->states[ newState ];

    // Update the current animation state.
    currentState = newState;

    // Update the current tile / frame so it is now the first of the
    // new state.
    setTile( state[FIRST_FRAME] );

    animationFinished_ = false;
}


/***
 * 4. Updating
 ***/

void Animation::update()
{
    Uint32 t = SDL_GetTicks();

    if( ( t - lastFrameTick_ ) > animationData->refreshRate ){
        // Get the current animation state's info.
        std::array< int, 3 > state = animationData->states[ currentState ];

        // Get the current tile / frame.
        GLint currentTile = getCurrentTile();

        // Get the next tile / frame.
        if( currentTile < state[LAST_FRAME] ){
            currentTile++;
        }else{
            animationFinished_ = ( state[LAST_FRAME] == state[BACK_FRAME] );
            currentTile = state[BACK_FRAME];
        }

        // Update the current tile / frame.
        setTile( currentTile );

        lastFrameTick_ = t;
    }
}


} // namespace m2g
