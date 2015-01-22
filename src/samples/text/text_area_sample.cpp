#include "../m2g.hpp"
#include "../text/text_area.hpp"
#include <iostream>

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

    m2g::TextArea textArea(
        { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT },
        "Hello\nawesome world!\nPress arrows to change text alignment",
        &textRenderer,
        fontIndex,
        { 255, 0, 0, 255 } );

    do{
        if( SDL_PollEvent( &event ) ){
            if( event.type == SDL_KEYDOWN ){
                SDL_Keycode key = event.key.keysym.sym;
                if( key == SDLK_LEFT ){
                    if( textArea.horizontalAlign() == m2g::HorizontalAlign::RIGHT ){
                        textArea.setHorizontalAlign( m2g::HorizontalAlign::CENTER );
                    }else if( textArea.horizontalAlign() == m2g::HorizontalAlign::CENTER ){
                        textArea.setHorizontalAlign( m2g::HorizontalAlign::LEFT );
                    }
                }else if( key == SDLK_RIGHT ){
                    if( textArea.horizontalAlign() == m2g::HorizontalAlign::LEFT ){
                        textArea.setHorizontalAlign( m2g::HorizontalAlign::CENTER );
                    }else if( textArea.horizontalAlign() == m2g::HorizontalAlign::CENTER ){
                        textArea.setHorizontalAlign( m2g::HorizontalAlign::RIGHT );
                    }
                }else if( key == SDLK_UP ){
                    if( textArea.verticalAlign() == m2g::VerticalAlign::BOTTOM ){
                        textArea.setVerticalAlign( m2g::VerticalAlign::MIDDLE );
                    }else if( textArea.verticalAlign() == m2g::VerticalAlign::MIDDLE ){
                        textArea.setVerticalAlign( m2g::VerticalAlign::TOP );
                    }
                }else if( key == SDLK_DOWN ){
                    if( textArea.verticalAlign() == m2g::VerticalAlign::TOP ){
                        textArea.setVerticalAlign( m2g::VerticalAlign::MIDDLE );
                    }else if( textArea.verticalAlign() == m2g::VerticalAlign::MIDDLE ){
                        textArea.setVerticalAlign( m2g::VerticalAlign::BOTTOM );
                    }
                }
            }
        }

        SDL_RenderClear( renderer );
        textArea.draw();
        SDL_RenderPresent( renderer );

    }while( event.type != SDL_QUIT );
}
