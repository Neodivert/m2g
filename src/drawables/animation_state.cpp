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

#include <m2g/drawables/animation_state.hpp>
#include <stdexcept>

namespace m2g {

/***
 * 1. Construction
 ***/

AnimationState::AnimationState() :
    firstFrame( 0 ),
    lastFrame( 0 ),
    backFrame( 0 )
{}


AnimationState::AnimationState( unsigned int firstFrame,
                                unsigned int lastFrame ) :
    firstFrame( firstFrame ),
    lastFrame( lastFrame ),
    backFrame( firstFrame )
{
    throwIfLastFrameGreaterThanFirstFrame();
}


AnimationState::AnimationState( unsigned int firstFrame,
                                unsigned int lastFrame,
                                unsigned int backFrame ) :
    firstFrame( firstFrame ),
    lastFrame( lastFrame ),
    backFrame( backFrame )
{
    throwIfLastFrameGreaterThanFirstFrame();

    if( backFrame > lastFrame ){
        throw std::invalid_argument( "backFrame mustn't be greater than lastFrame" );
    }
}


/***
 * 2. Operators
 ***/

bool AnimationState::operator ==(const AnimationState &b) const
{
    return ( firstFrame == b.firstFrame &&
             lastFrame == b.lastFrame &&
             backFrame == b.backFrame );
}


/***
 * 3. Checking methods
 ***/

void AnimationState::throwIfLastFrameGreaterThanFirstFrame() const
{
    if( lastFrame < firstFrame ){
        throw std::invalid_argument( "lastFrame mustn't be smaller that firstFrame" );
    }
}

} // namespace m2g

