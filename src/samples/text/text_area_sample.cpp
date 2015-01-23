#include "../m2g.hpp"
#include "../text/text_area.hpp"
#include <iostream>
#include <list>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void xmlTestAreasSample( const m2g::TextRenderer& textRenderer,
                         unsigned int fontIndex );


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
        "Hello\nawesome world!\nPress arrows to change text alignment\nPress [ENTER] to follow with next sample",
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

    }while( ( event.type != SDL_QUIT ) &&
            ( ( event.type != SDL_KEYDOWN ) ||
              ( event.key.keysym.sym != SDLK_RETURN ) ) );

    if( event.type != SDL_QUIT ){
        xmlTestAreasSample( textRenderer, fontIndex );
    }
}


void xmlTestAreasSample( const m2g::TextRenderer& textRenderer, unsigned int fontIndex )
{
    SDL_Event event;
    const SDL_Color fontColor = { 0, 0, 255, 255 };
    std::list< m2g::TextAreaPtr > textAreas;

    tinyxml2::XMLDocument xmlDocument;
    xmlDocument.LoadFile( "data/text_areas.xml" );

    tinyxml2::XMLElement* xmlRootElement =
            xmlDocument.FirstChildElement();

    tinyxml2::XMLElement* xmlElement =
            xmlRootElement->FirstChildElement( "text_area" );
    while( xmlElement ){
        textAreas.push_back(
                    m2g::TextAreaPtr(
                        new m2g::TextArea( xmlElement,
                                           &textRenderer,
                                           fontIndex,
                                           fontColor ) ) );

        xmlElement = xmlElement->NextSiblingElement( "text_area" );
    }

    do{
        SDL_RenderClear( textRenderer.renderer() );
        for( const m2g::TextAreaPtr& textArea : textAreas ){
            textArea->draw();
        }
        SDL_RenderPresent( textRenderer.renderer() );

        SDL_WaitEvent( &event );
    }while( ( event.type != SDL_QUIT ) &&
            ( ( event.type != SDL_KEYDOWN ) ||
              ( event.key.keysym.sym != SDLK_RETURN ) ) );
}
