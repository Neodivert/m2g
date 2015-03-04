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

#ifndef ANIMATION_STATE_HPP
#define ANIMATION_STATE_HPP

namespace m2g {

class AnimationState {
    public:
        /***
         * 1. Construction
         ***/
        AnimationState();
        AnimationState( unsigned int firstFrame,
                        unsigned int lastFrame );
        AnimationState( unsigned int firstFrame,
                        unsigned int lastFrame,
                        unsigned int backFrame );


        /***
         * 2. Operators
         ***/
        bool operator == ( const AnimationState& b ) const;


        /***
         * Attributes
         ***/
        const unsigned int firstFrame;
        const unsigned int lastFrame;
        const unsigned int backFrame;





    private:
        /***
         * 3. Checking methods
         ***/
        void throwIfLastFrameGreaterThanFirstFrame() const;
};

} // namespace m2g

#endif // ANIMATION_STATE_HPP
