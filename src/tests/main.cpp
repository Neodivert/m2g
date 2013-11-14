#include <iostream>
#include "../dependencies/GL3W/gl3w.h"
#include "../dependencies/dependencies.hpp"
#include "../drawables/particles_systems/particle_systems_group.hpp"
#include "../dependencies/msl/src/shader_loader.hpp"

using namespace std;

const float WINDOW_WIDTH = 800.0f;
const float WINDOW_HEIGHT = 600.0f;

void ParticlesSystemsTest( SDL_Window* window, SDL_Surface* screen );

int main()
{
    SDL_Window* window = nullptr;
    SDL_Surface* screen = nullptr;
    SDL_GLContext glContext;
    msl::ShaderLoader* shaderLoader;

    // Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        throw std::runtime_error( std::string( "ERROR initializing SDL: " ) + SDL_GetError() );
    }

    // Initialize SDL_image
    if( IMG_Init( IMG_INIT_PNG ) != IMG_INIT_PNG ){
        throw std::runtime_error( IMG_GetError() );
    }

    // Initialize some OpenGL attributes.
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );

    // Create main window
    window = SDL_CreateWindow(
      "JDB",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
      /*SDL_WINDOW_SHOWN |*/ SDL_WINDOW_OPENGL );

    if( window == NULL ){
        throw std::runtime_error( std::string( "ERROR creating window: " ) + std::string( SDL_GetError() ) );
    }

    // Retrieve the window's screen.
    screen = SDL_GetWindowSurface( window );

    // Create an OpenGL context.
    glContext = SDL_GL_CreateContext( window );

    // Initialize OpenGL and create a GL context.
    if( gl3wInit() ){
        throw std::runtime_error( "ERROR when using gl3wInit()" );
    }
    if (!gl3wIsSupported(4, 2)) {
        throw std::runtime_error( "OpenGL 4.2 not supported" );
    }

     std::cout << "OpenGL " << glGetString(GL_VERSION) << ", GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Retrieve and display the context's version.
    int majorVersion, minorVersion;
    SDL_GL_GetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, &majorVersion );
    SDL_GL_GetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, &minorVersion );
    std::cout << "Context version (SDL/OpenGL): " << majorVersion << "." << minorVersion << std::endl;


    // Display a string with the OpenGL version.
    const unsigned char* version = glGetString( GL_VERSION );
    if( version == NULL ){
        std::runtime_error( std::string( "ERROR retrieving OpenGL's version: " ) + std::string( (GLchar* )( gluErrorString( glGetError() ) ) ) );
    }else{
        std::cout << "Version: " << version << std::endl;
    }

    // Display a string showing the GLSL version.
    std::cout << "GLSL Version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

    // Load and use shaders.
    shaderLoader = msl::ShaderLoader::getInstance();
    shaderLoader->loadMinimumShaderProgram( "data/shaders/particles_system.vertex", "data/shaders/particles_system.fragment" );
    shaderLoader->destroy();

    // Initialize OpenGL.
    glDisable( GL_DEPTH_TEST );
    //glDepthFunc( GL_LEQUAL );
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glClearColor( 0xF5/255.0f, 0xF6/255.0f, 0xCE/255.0f, 1.0f );

    m2g::checkOpenGL( "constructor" );

    ParticlesSystemsTest( window, screen );
}


void ParticlesSystemsTest( SDL_Window* window, SDL_Surface* screen )
{
    const unsigned int REFRESH_TIME = 44;
    bool quit = false;
    SDL_Event event;
    Uint32 t0, t1;

    // Set projection mode.
    glm::mat4 projectionMatrix = glm::ortho( 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f, -1.0f );

    m2g::ParticleSystemsGroup fire( "data/config/particle_systems.xml", "fire" );
    fire.generateTileset( "data/img/fire.png", glm::vec4( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT ) );

    m2g::ParticleSystem foam( "data/config/particle_systems.xml", "foam" );
    foam.generateTileset( "data/img/foam.png", glm::vec4( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT ) );


    fire.moveTo( 250, 0 );
    foam.moveTo( 350, 350 );

    m2g::ParticleSystem smoke( "data/config/particle_systems.xml", "smoke" );
    /*
    m2g::ParticleSystem electricField( "data/config/particle_systems.xml", "electric_field" );
    m2g::ParticleSystem snow( "data/config/particle_systems.xml", "snow" );
    m2g::ParticleSystem fireCore( "data/config/particle_systems.xml", "fire_core" );
    */

    SDL_ShowCursor( SDL_DISABLE );

    /*
    electricField.moveTo( 200, 0 );
    snow.moveTo( 400, 0 );
    fireCore.moveTo( 300, 300 );
    */

    glClearColor( 0xF5/255.0f, 0xF6/255.0f, 0xCE/255.0f, 1.0f );
    while( !quit ){
        t0 = SDL_GetTicks();
        while( (t1 - t0) < REFRESH_TIME ){
            if( SDL_PollEvent( &event ) != 0 ){
                switch( event.type ){
                    case SDL_QUIT:
                        // Player wants to exit the game.
                        quit = true;
                    break;
                    //case SDL_MOUSEMOTION:
                    //    smoke.moveTo( event.motion.x, event.motion.y );
                    //break;
                }
            }
            t1 = SDL_GetTicks();
        }
        t0 = SDL_GetTicks();
        t1 = SDL_GetTicks();

        // Clear screen.
        glClear ( GL_COLOR_BUFFER_BIT );

        // Draw the particles system.
        fire.drawAndUpdate( projectionMatrix );
        smoke.drawAndUpdate( projectionMatrix );
        foam.drawAndUpdate( projectionMatrix );
        /*electricField.drawAndUpdate( projectionMatrix );
        fireCore.drawAndUpdate( projectionMatrix );
        snow.drawAndUpdate( projectionMatrix );*/

        // Refresh screen.
        SDL_GL_SwapWindow( window );
    }
}

