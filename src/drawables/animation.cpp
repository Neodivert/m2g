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
    animData_( &animData )
{
    if( animData.nStates() == 0 ){
        throw std::invalid_argument( "animData can't be empty (0 states)" );
    }
    setState( 0 );
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


unsigned int Animation::refreshRate() const
{
    return DEFAULT_ANIMATION_REFRESH_RATE;
}


/***
 * 4. Setters
 ***/

void Animation::setState( unsigned int newState )
{
    currentState_ = newState;
    currentFrame_ = animData_->state( currentState_ ).firstFrame;
}

} // namespace m2g
