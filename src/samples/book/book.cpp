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

#include "../m2g.hpp"
#include "../gui/widgets/book.hpp"
#include "../graphics_library.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(){
    SDL_Event event;
    m2g::init();

    // Create main window
    SDL_Window* window = SDL_CreateWindow(
      "JDB",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
      0 );

    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, 0 );

    m2g::TextRenderer textRenderer( renderer );
    const unsigned int fontIndex = textRenderer.loadFont( "/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf", 30 );

    m2g::Book book( &textRenderer, "./data/book_background.png", fontIndex );
    book.moveTo( ( WINDOW_WIDTH - book.getWidth() ) >> 1,
                 ( WINDOW_HEIGHT - book.getHeight() ) >> 1 );

    m2g::GraphicsLibrary graphics( renderer );
    graphics.loadAll( "./data/graphics" );

    m2g::BookPage page( &textRenderer, { 0, 0, book.getWidth(), book.getHeight() }, "This is\nthe third\npage" );
    m2g::DrawablePtr fire = m2g::DrawablePtr( new m2g::Animation( renderer, graphics.getAnimationData( "fire.png" ) ) );
    page.addDrawable( fire, 0, 0 );

    book.addPage( "This is\nthe first\npage");
    book.addPage( "This is\nthe second\npage");
    book.addPage( page );

    do{
        if( SDL_PollEvent( &event ) ){
            book.handleEvent( event );
        }

        SDL_RenderClear( renderer );
        book.draw();
        SDL_RenderPresent( renderer );

    }while( ( event.type != SDL_QUIT ) &&
            ( ( event.type != SDL_KEYDOWN ) ||
              ( event.key.keysym.sym != SDLK_RETURN ) ) );
}
