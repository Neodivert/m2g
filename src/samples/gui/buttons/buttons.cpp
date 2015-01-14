#include <iostream>
#include <m2g/graphics_library.hpp>
#include <msl/shader_loader.hpp>
#include "../../kernel/sample_app.hpp"
#include <gui/gui.hpp>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

int main()
{
    m2g::SampleApp sampleApp( WINDOW_WIDTH, WINDOW_HEIGHT );

    // Display a string showing the GLSL version.
    std::cout << "GLSL Version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

    // Load and use shaders.
    //shaderLoader = msl::ShaderLoader::getInstance();
    //shaderLoader->loadMinimumShaderProgram( "data/shaders/particles_system.vertex", "data/shaders/particles_system.fragment" );
    //shaderLoader->destroy();

    // Initialize OpenGL.
    glDisable( GL_DEPTH_TEST );
    //glDepthFunc( GL_LEQUAL );
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    //glClearColor( 0xCE/255.0f, 0xE3/255.0f, 0xF6/255.0f, 1.0f );
    glClearColor( 0xF5/255.0f, 0xF6/255.0f, 0xCE/255.0f, 1.0f );

    // Main loop.
    bool quit = false;
    Uint32 t0, t1;
    SDL_Event event;
    const Uint32 REFRESH_TIME = 33;
    glClearColor( 0xF5/255.0f, 0xF6/255.0f, 0xCE/255.0f, 1.0f );
    m2g::GUI gui( "foo" );

    while( !quit ){
        t0 = t1 = SDL_GetTicks();
        while( (t1 - t0) < REFRESH_TIME ){
            if( SDL_PollEvent( &event ) != 0 ){
                switch( event.type ){
                    case SDL_QUIT:
                        // Player wants to exit the game.
                        quit = true;
                    break;
                    default:
                    break;
                }
            }
            t1 = SDL_GetTicks();
        }
        t0 = SDL_GetTicks();
        t1 = SDL_GetTicks();

        // Clear screen.
        glClear ( GL_COLOR_BUFFER_BIT );

        // Refresh screen.
        sampleApp.refreshWindow();
    }

    m2g::checkOpenGL( "constructor" );
}
