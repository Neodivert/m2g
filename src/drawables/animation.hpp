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

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "animation_data.hpp"
#include "tile_sprite.hpp"

namespace m2g {

class Animation : public TileSprite
{
    public:
        /***
         * 1. Construction
         ***/
        Animation( const AnimationData& animData );
        Animation( AnimationDataPtr animData ); // TODO: Test!


        /***
         * 2. Destruction
         ***/
        virtual ~Animation() = default;


        /***
         * 3. Getters
         ***/
        unsigned int currentState() const;
        unsigned int currentFrame() const;
        bool finished() const; // TODO: Test!
        const AnimationData& animationData() const;


        /***
         * 4. Setters
         ***/
        void setAnimationData( const AnimationData& animData ); // TODO: Test!
        void setState( unsigned int newState );
        virtual void setTile( unsigned int tile );


        /***
         * 5. Updating
         ***/
        void update( unsigned int ms );


    private:
        AnimationDataPtr ownAnimData_;
        AnimationData const* animData_;
        unsigned int currentState_;
        unsigned int currentFrame_;
};

typedef std::unique_ptr< Animation > AnimationPtr;

} // namespace m2g

#endif // ANIMATION_HPP
