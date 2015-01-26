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

#include "book_page.hpp"

namespace m2g {

BookPage::BookPage( const TextRenderer *textRenderer,
                    const Rect &textArea,
                    const std::string &text,
                    const unsigned int fontIndex ) :
    DrawablesSet( textRenderer->renderer() ),
    textRenderer_( textRenderer ),
    textArea_( textArea, text, textRenderer, fontIndex, {0, 0, 0, 255 } )
{}


/***
 * 3. DrawablesSet interface
 ***/

void BookPage::translate( int tx, int ty )
{
    textArea_.translate( tx, ty );

    DrawablesSet::translate( tx, ty );
}


void BookPage::moveTo( int x, int y )
{
    const int xRel = x - boundaryBox.x;
    const int yRel = y - boundaryBox.y;

    textArea_.translate( xRel, yRel );

    DrawablesSet::translate( xRel, yRel );
}


void BookPage::draw() const
{
    textArea_.draw();

    DrawablesSet::draw();
}


} // namespace m2g
