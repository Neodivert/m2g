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
                    const TextRenderer *textRenderer,
                    unsigned int fontIndex,
                    const SDL_Color &fontColor,
                    HorizontalAlign horizontalAlign,
                    VerticalAlign verticalAlign ) :
    Drawable( textRenderer->renderer() ),
    rect_( rect ),
    text_( text ),
    horizontalAlign_( horizontalAlign ),
    verticalAlign_( verticalAlign ),
    texture_( nullptr ),
    textRenderer_( textRenderer ),
    fontIndex_( fontIndex ),
    fontColor_( fontColor )
{
    renderTextToTexture();
}


TextArea::TextArea( SDL_Renderer *renderer,
                    tinyxml2::XMLElement* xmlElement,
                    const TextRenderer* textRenderer,
                    unsigned int fontIndex,
                    const SDL_Color& fontColor ) :
    Drawable( renderer ),
    texture_( nullptr ),
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
 * 3. Getters
 ***/

VerticalAlign TextArea::verticalAlign() const
{
    return verticalAlign_;
}


HorizontalAlign TextArea::horizontalAlign() const
{
    return horizontalAlign_;
}


std::string TextArea::text() const
{
    return text_;
}


/***
 * 4. Setters
 ***/

void TextArea::setVerticalAlign( VerticalAlign verticalAlign )
{
    verticalAlign_ = verticalAlign;
    renderTextToTexture();
}


void TextArea::setHorizontalAlign( HorizontalAlign horizontalAlign )
{
    horizontalAlign_ = horizontalAlign;
    renderTextToTexture();
}


void TextArea::setText( const std::string& text )
{
    text_ = text;
    renderTextToTexture();
}


/***
 * 5. Drawing
 ***/

void TextArea::draw() const
{
    const SDL_Rect dstRect = boundaryBox.sdlRect();
    SDL_RenderCopy( renderer_, texture_, nullptr, &dstRect );
}


/***
 * 6. Text rendering
 ***/

void TextArea::renderTextToTexture()
{
    SDL_Surface* textSurface =
            textRenderer_->renderTextToSurface(
                text_.c_str(),
                fontIndex_,
                fontColor_,
                horizontalAlign_ );

    if( texture_ != nullptr ){
        SDL_DestroyTexture( texture_ );
    }
    texture_ = SDL_CreateTextureFromSurface( renderer_, textSurface );

    // Set the text's boundary box according to its alignment.
    boundaryBox.x = rect_.x;
    if( horizontalAlign_ == HorizontalAlign::CENTER ){
        if( static_cast< int >( rect_.width ) > textSurface->w ){
            boundaryBox.x += (rect_.width - textSurface->w) / 2;
        }else{
            boundaryBox.x += (textSurface->w - rect_.width) / 2;
        }
    }else if( horizontalAlign_ == HorizontalAlign::RIGHT ){
        if( static_cast< int >( rect_.width ) > textSurface->w ){
            boundaryBox.x += rect_.width - textSurface->w;
        }else{
            boundaryBox.x += textSurface->w - rect_.width;
        }
    }

    boundaryBox.y = rect_.y;
    if( verticalAlign_ == VerticalAlign::MIDDLE ){
        if( static_cast< int >( rect_.height ) > textSurface->h ){
            boundaryBox.y += (rect_.height - textSurface->h) >> 1;
        }else{
            boundaryBox.y += (textSurface->h - rect_.height) >> 1;
        }
    }else if( verticalAlign_ == VerticalAlign::BOTTOM ){
        if( static_cast< int >( rect_.height ) > textSurface->h ){
            boundaryBox.y += rect_.height - textSurface->h;
        }else{
            boundaryBox.y += textSurface->h - rect_.height;
        }
    }

    boundaryBox.width = textSurface->w;
    boundaryBox.height = textSurface->h;

    SDL_FreeSurface( textSurface );
}

} // namespace m2g

