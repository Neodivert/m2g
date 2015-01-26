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

#include "book.hpp"
#include <SDL2/SDL_image.h>

namespace m2g {

/***
 * 1. Construction
 ***/

Book::Book( const TextRenderer* textRenderer, const char* backgroundPath, unsigned int fontIndex ) :
    Drawable( textRenderer->renderer() ),
    Widget( textRenderer->renderer() ),
    textRenderer_( textRenderer ),
    bookNavigationText_(
        { 0, 0, 0, 0 },
        "< RePag / AvPag >",
        textRenderer_,
        fontIndex,
        { 0, 0, 0, 255 },
        HorizontalAlign::CENTER,
        VerticalAlign::BOTTOM ),
    currentPage_( pages_.begin() )
{
    setBackground( backgroundPath );
}


/***
 * 2. Setters
 ***/

void Book::setBackground( const char *backgroundPath )
{
    SDL_Surface* bgSurface = IMG_Load( backgroundPath );
    if( !bgSurface ){
        throw std::runtime_error( SDL_GetError() );
    }
    boundaryBox.width = bgSurface->w;
    boundaryBox.height = bgSurface->h;

    background_ =
            SDL_CreateTextureFromSurface( renderer_, bgSurface );
    if( !background_ ){
        throw std::runtime_error( SDL_GetError() );
    }

    bookNavigationText_.setArea( boundaryBox );

    SDL_FreeSurface( bgSurface );
}


/***
 * 3. Pages management
 ***/

void Book::addPage( const std::string& text )
{
    BookPage newPage( textRenderer_, boundaryBox, text );
    addPage( newPage );
}

void Book::addPage( BookPage page )
{
    pages_.push_back( page );

    if( currentPage_ == pages_.end() ){
        currentPage_ = pages_.begin();
    }
}


/***
 * 4. Pages navigation
 ***/

void Book::nextPage()
{
    if( currentPage_ != pages_.end() ){
        currentPage_++;
    }
}


void Book::previousPage()
{
    if( currentPage_ != pages_.begin() ){
        currentPage_--;
    }
}


/***
 * 5. EventListener interface
 ***/

bool Book::handleEvent( const SDL_Event &event )
{
    if( currentPage_ != pages_.end() ){
        if( event.type == SDL_KEYDOWN ){
            SDL_Keycode key = event.key.keysym.sym;
            if( key == SDLK_PAGEDOWN ){
                nextPage();
                return true;
            }else if( key == SDLK_PAGEUP ){
                previousPage();
                return true;
            }
        }
    }
    return false;
}


/***
 * 6. Drawawable interface
 ***/

void Book::translate( int tx, int ty )
{
    bookNavigationText_.translate( tx, ty );

    Drawable::translate( tx, ty );
}


void Book::moveTo( int x, int y )
{
    const int xRel = x - boundaryBox.x;
    const int yRel = y - boundaryBox.y;

    bookNavigationText_.translate( xRel, yRel );

    Drawable::moveTo( x, y );
}


void Book::draw() const
{
    if( currentPage_ != pages_.end() ){
        const SDL_Rect dstRect = boundaryBox.sdlRect();
        SDL_RenderCopy( renderer_, background_, nullptr, &dstRect );

        currentPage_->draw();

        bookNavigationText_.draw();
    }
}



} // namespace m2g
