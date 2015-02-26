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

#include <gmock/gmock.h>
#include "../../drawables/tileset.hpp"

#ifndef MOCK_TILESET_HPP
#define MOCK_TILESET_HPP

class MockTileset : public m2g::Tileset
{
    public:
        MockTileset( const std::string &imagePath, unsigned int tileWidth, unsigned int tileHeight ) :
            Tileset( imagePath, tileWidth, tileHeight ){}

        MOCK_CONST_METHOD1( tileRect, sf::IntRect( unsigned int tile ) );
};

#endif // MOCK_TILESET
