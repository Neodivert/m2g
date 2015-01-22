#include <m2g/m2g.hpp>
#include <m2g/text/text_area.hpp>

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
        "Helow\nworld!",
        &textRenderer,
        fontIndex,
        { 255, 0, 0, 255 } );

    do{
        SDL_PollEvent( &event );

        SDL_RenderClear( renderer );
        textArea.draw();
        SDL_RenderPresent( renderer );
    }while( event.type != SDL_QUIT );
}
