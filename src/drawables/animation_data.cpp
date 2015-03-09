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

#include "animation_data.hpp"

namespace m2g {

/***
 * 1. Construction
 ***/

AnimationData::AnimationData( const Tileset& tileset ) :
    tileset_( &tileset )
{}


/***
 * 3. Getters
 ***/

AnimationState AnimationData::state( unsigned int index ) const
{
    return states_.at( index );
}


unsigned int AnimationData::nStates() const
{
    return states_.size();
}


const Tileset &AnimationData::tileset() const
{
    return *tileset_;
}


/***
 * 4. States management
 ***/

void AnimationData::addState( const AnimationState &newState )
{
    if( newState.lastFrame >= tileset_->nTiles() ){
        throw std::out_of_range( "lastFrame" );
    }
    states_.push_back( newState );
}

} // namespace m2g
