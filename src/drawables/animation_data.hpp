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
#include <vector>
#include <array>
#include <tinyxml2.h>

namespace m2g {

const unsigned int FIRST_FRAME = 0;
const unsigned int LAST_FRAME = 1;
const unsigned int BACK_FRAME = 2;

class AnimationData
{
    public:
        /***
         * 1. Initialization and destruction
         ***/
        AnimationData( SDL_Renderer* renderer, const tinyxml2::XMLNode* xmlNode, const char* folder = nullptr );


        /***
         * 2. Loading
         ***/
        void load( SDL_Renderer* renderer, const tinyxml2::XMLNode* xmlNode, const char* folder = nullptr );


        /***
         * 3. Getters
         ***/
        unsigned int refreshRate() const;
        std::array< int, 3 > state( unsigned int index ) const;

    private:
        // Tileset associated with this animation.
        TilesetPtr tileset_;

         // Refresh rate (ms).
        unsigned int refreshRate_;

        // Each state is a tuple (firstFrame, lastFrame, backFrame).
        // TODO: Create a new struct AnimationState and make a vector of them.
        std::vector< std::array< int, 3 > >  states_;
};

typedef std::shared_ptr< const AnimationData > AnimationDataPtr;

} // namespace m2g.

#endif // ANIMATION_DATA_HPP
