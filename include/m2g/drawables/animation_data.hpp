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

#ifndef ANIMATION_DATA_HPP
#define ANIMATION_DATA_HPP

#include "tileset.hpp"
#include "animation_state.hpp"

namespace m2g {

const unsigned int DEFAULT_ANIMATION_REFRESH_RATE = 25;

class AnimationData
{
    public:
        /***
         * 1. Construction
         ***/
        AnimationData( const Tileset& tileset, unsigned int refreshRate = DEFAULT_ANIMATION_REFRESH_RATE );
        AnimationData( TilesetPtr tileset, unsigned int refreshRate );

        /***
         * 2. Destruction
         ***/
        virtual ~AnimationData() = default;


        /***
         * 3. Getters
         ***/
        AnimationState state( unsigned int index ) const;
        unsigned int nStates() const;
        const Tileset& tileset() const;
        unsigned int refreshRate() const;


        /***
         * 4. States management
         ***/
        void addState( const AnimationState& newState );


    private:
        TilesetPtr ownTileset_;
        const Tileset* tileset_;
        unsigned int refreshRate_;
        std::vector< AnimationState > states_;
};

typedef std::unique_ptr< AnimationData > AnimationDataPtr;

} // namespace m2g.

#endif // ANIMATION_DATA_HPP
