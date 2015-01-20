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

#ifndef TEXT_BUTTON_HPP
#define TEXT_BUTTON_HPP

#include "widget.hpp"
#include "../../drawables/animation.hpp"
#include <functional>

namespace m2g {

enum class ButtonStatus
{
    NORMAL,
    HOVER,
    PRESSED
};

struct FontInfo
{
    std::string path;
    int size;
    SDL_Color color;
};

typedef std::function< void( void ) > ButtonCallback;

class TextButton : public Widget, public Sprite
{
    public:
        /***
         * 1. Construction
         ***/
        // TODO: Use UTF-8 / UTF-16 for text.
        TextButton( SDL_Renderer* renderer,
                    const std::string& text,
                    const std::array< FontInfo, 3 >& fontsInfo );


        /***
         * 2. Getters
         ***/
        ButtonStatus status() const;


        /***
         * 3. Setters
         ***/
        void setPressCallback( ButtonCallback onPressCallback );


        /***
         * 4. Event handling
         ***/
        virtual bool handleEvent( const SDL_Event &event );
        bool posHover( int x, int y ) const; // TODO: Move to a parent class.


    private:
        /***
         * 5. Initialization
         ***/
        static TilesetPtr generateTileset( SDL_Renderer* renderer,
                                           const std::string& text,
                                           const std::array< FontInfo, 3 >& fontsInfo );


        /***
         * 6. Private setters
         ***/
        void setStatus( ButtonStatus newStatus );


        /***
         * Attributes
         ***/
        ButtonStatus status_;
        ButtonCallback onPressCallback_;
};

typedef std::unique_ptr< TextButton > TextButtonPtr;

} // namespace m2g

#endif // TEXT_BUTTON_HPP
