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

#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "../interfaces/event_listener.hpp"
#include "../../drawables/drawable.hpp"
#include <memory>

namespace m2g {

class Widget : public EventListener, public virtual Drawable
{
    public:
        /***
         * 1. Construction
         ***/
        Widget( SDL_Renderer* renderer );
};

typedef std::unique_ptr< Widget > WidgetPtr;

}

#endif // WIDGET_HPP
