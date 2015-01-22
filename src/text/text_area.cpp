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

#include "text_area.hpp"

namespace m2g {

/***
 * 1. Construction
 ***/

TextArea::TextArea( const Rect &rect,
                    const std::string &text,
                    TextRenderer *textRenderer,
                    unsigned int fontIndex,
                    const SDL_Color &fontColor,
                    HorizontalAlign horizontalAlign,
                    VerticalAlign verticalAlign ) :
    Drawable( textRenderer->renderer() ),
    rect_( rect ),
    text_( text ),
    horizontalAlign_( horizontalAlign ),
    verticalAlign_( verticalAlign ),
    textRenderer_( textRenderer ),
    fontIndex_( fontIndex ),
    fontColor_( fontColor )
{}


TextArea::TextArea( SDL_Renderer *renderer,
                    tinyxml2::XMLElement* xmlElement,
                    TextRenderer* textRenderer,
                    unsigned int fontIndex,
                    const SDL_Color& fontColor ) :
    Drawable( renderer ),
    textRenderer_( textRenderer ),
    fontIndex_( fontIndex ),
    fontColor_( fontColor )
{
    loadFromXML( xmlElement );
    renderTextToTexture();
}


/***
 * 2. Loading
 ***/

void TextArea::loadFromXML( tinyxml2::XMLElement *xmlElement )
{
    name_ = xmlElement->Attribute( "name" );
    boundaryBox.loadFromXML( xmlElement->FirstChildElement( "rect" ) );
    horizontalAlign_ =
            readHorizontalAligmentFromXML( xmlElement->FirstChildElement( "horizontal_align" ) );
    verticalAlign_ =
            readVerticalAligmentFromXML( xmlElement->FirstChildElement( "vertical_align" ) );
    if( xmlElement->FirstChildElement( "text" ) ){
        text_ = xmlElement->FirstChildElement( "text" )->GetText();
    }
}


/***
 * 3. Drawing
 ***/

void TextArea::draw() const
{
    const SDL_Rect dstRect = boundaryBox.sdlRect();
    SDL_RenderCopy( renderer_, texture_, nullptr, &dstRect );
}


/***
 * 4. Text rendering
 ***/

void TextArea::renderTextToTexture()
{
    SDL_Surface* textSurface =
            textRenderer_->renderTextToSurface(
                text_.c_str(),
                fontIndex_,
                fontColor_,
                horizontalAlign_ );

    texture_ = SDL_CreateTextureFromSurface( renderer_, textSurface );

    SDL_FreeSurface( textSurface );
}

} // namespace m2g

