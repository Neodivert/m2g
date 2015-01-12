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

#include "text_renderer.hpp"
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL_image.h>

namespace m2g {


/***
 * 1. Initialization
 ***/

TextRenderer::TextRenderer()
{
    GLint currentProgram;

    // Get the uniforms locations.
    glGetIntegerv( GL_CURRENT_PROGRAM, &currentProgram );

    mvpMatrixLocation = glGetUniformLocation( currentProgram, "mvpMatrix" );
    samplerLocation = glGetUniformLocation( currentProgram, "tex" );
    sliceLocation = glGetUniformLocation( currentProgram, "slice" );

    checkOpenGL( "TextRenderer - Getting uniform locations" );

    // Connect sampler to texture unit 0.
    glUniform1i( samplerLocation, 0 );
}

/***
 * 2. Loading
 ***/

unsigned int TextRenderer::loadFont( const char* file, const unsigned int size, const SDL_Color& color )
{
    std::shared_ptr< m2g::BitmapFont > bitmapFont = std::shared_ptr< m2g::BitmapFont >( new m2g::BitmapFont );

    // Generate the bitmap font from the TrueType one.
    bitmapFont->load( file, size, color );

    // Insert the new bitmap font in the bitmap fonts vector.
    bitmapFonts.push_back( bitmapFont );

    // Return the index of the just added font.
    return bitmapFonts.size() - 1;
}


/***
 * 3. Drawing
 ***/

void TextRenderer::drawText( const glm::mat4& projectionMatrix, const char* text, unsigned int fontIndex, GLuint x, GLuint y )
{
    unsigned int i = 0;
    glm::mat4 transformationMatrix;

    // Bind the bitmap font (its VAO, VBO and texture) as the active one.
    bitmapFonts[fontIndex]->bind();

    // Send current 0 index to shader.
    glUniform1ui( sliceLocation, 0 );

    for( ; i < strlen( text ); i++ ){
        // Set MVP matrix.
        transformationMatrix = projectionMatrix * glm::translate( glm::mat4( 1.0f ), glm::vec3( x, y, 0.0f ) );

        // Send the MVP matrix to the shader.
        glUniformMatrix4fv( mvpMatrixLocation, 1, GL_FALSE, &transformationMatrix[0][0] );

        // Draw the current character.
        glUniform1ui( sliceLocation, text[i]-' ' );
        bitmapFonts[fontIndex]->drawCharacter( text[i] );

        //std::cout << "Translating: " << bitmapFonts[fontIndex]->getCharacterWidth( text[i] - ' ' ) << std::endl;

        x += bitmapFonts[fontIndex]->getCharacterWidth( text[i] );

        //transformationMatrix = transformationMatrix * glm::translate( glm::mat4( 1.0f ), glm::vec3( bitmapFonts[fontIndex]->getCharacterWidth( text[i] - ' ' ) * 2, 0.0f, 0.0f ) );
    }
}


SpritePtr TextRenderer::drawText( const char* text, const char* fontPath, unsigned int fontSize, const SDL_Color& color, TextAlign textAlign )
{
    TTF_Font* font = nullptr;
    TilesetPtr textTileset;
    SpritePtr textSprite( new Sprite );
    SDL_Surface* lineSurface = nullptr;
    SDL_Surface* textSurface = nullptr;
    int textWidth, textHeight;
    int pow2;
    unsigned int i;
    std::vector< std::string > lines;
    SDL_Rect dstRect = { 0, 0, 0, 0 };

    // Load the required font.
    font = TTF_OpenFont( fontPath, fontSize );
    if( font == nullptr ){
        throw std::runtime_error( std::string( "ERROR opening font - " ) + TTF_GetError() );
    }

    // Set the RGBA mask for the text surface.
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const Uint32 rmask = 0xff000000;
        const Uint32 gmask = 0x00ff0000;
        const Uint32 bmask = 0x0000ff00;
        const Uint32 amask = 0x000000ff;
    #else
        const Uint32 rmask = 0x000000ff;
        const Uint32 gmask = 0x0000ff00;
        const Uint32 bmask = 0x00ff0000;
        const Uint32 amask = 0xff000000;
    #endif

    // Get the text dimensions.
    getTextDimensions( font, text, textWidth, textHeight, lines );

    std::cout << "Text dimensions: " << std::endl
              << "\twidth: " << textWidth << std::endl
              << "\theight: " << textHeight << std::endl
              << "\tnLines: " << lines.size() << std::endl;


    //auxTextSurface = SDL_ConvertSurface( auxTextSurface, textSurface->format, textSurface->flags );

    // Round text dimensions to nearest upper pow of two.
    pow2 = 1;
    while( pow2 < textWidth ){
        pow2 <<= 1;
    }
    textWidth = pow2;

    pow2 = 1;
    while( pow2 < textHeight ){
        pow2 <<= 1;
    }
    textHeight = pow2;

    std::cout << "Text dimensions - pow of two : (" << textWidth << ", " << textHeight << ")" << std::endl;

    // Create the final text surface with the power-of-two dimensions.
    textSurface = SDL_CreateRGBSurface( 0, textWidth, textHeight, 32, rmask, gmask, bmask, amask );

    // Prepare the final text surface for the blitting.
    SDL_FillRect( textSurface, nullptr, 0 );
    SDL_SetSurfaceBlendMode( lineSurface, SDL_BLENDMODE_NONE );

    // Render every line and blit it to the final surface.
    for( i = 0; i < lines.size(); i++ ){
        std::cout << "1" << std::endl;
        // Generate a surface with the text line.
        lineSurface = TTF_RenderText_Blended( font, lines[i].c_str(), color );
        std::cout << "2 (" << lineSurface << ")" << std::endl;

        // Give the text the given align.
        // TODO: Change so the switch is executed only once.
        switch( textAlign ){
            case TextAlign::LEFT:
                dstRect.x = 0;
            break;
            case TextAlign::CENTER:
                dstRect.x = (textWidth >> 1) - (lineSurface->w >> 1);
                std::cout << "textWidth >> 1: " << (textWidth >> 1) << std::endl;
                std::cout << "lineSurface->w >> 1: " << (lineSurface->w >> 1) << std::endl;
                std::cout << "dstRect.x: " << dstRect.x << std::endl;
            break;
            case TextAlign::RIGHT:
                dstRect.x = textWidth - lineSurface->w;
            break;
        }

        std::cout << "Blitting [" << lines[i] << "] to (" << dstRect.x << ", " << dstRect.y << ") ..." << std::endl;
        // Blit the line surface to its final surface.
        SDL_BlitSurface( lineSurface, nullptr, textSurface, &dstRect );
        std::cout << "Blitting [" << lines[i] << "] to (" << dstRect.x << ", " << dstRect.y << ") ...OK" << std::endl;

        //
        dstRect.y += TTF_FontHeight( font );

        std::cout << "3" << std::endl;

        // Free the line surface.
        SDL_FreeSurface( lineSurface );

        std::cout << "4" << std::endl;
    }

    std::cout << "5" << std::endl;

    IMG_SavePNG( textSurface, "text.png" );

    // Generate a tileset from the text surface.
    textTileset = TilesetPtr( new Tileset( textSurface, textWidth, textHeight ) );

    //std::cout << "Factors: (" << auxTextSurface->w / (GLfloat)textWidth << ", " << auxTextSurface->h / (GLfloat)textHeight << ")" << std::endl;
    //textTileset = TilesetPtr( new Tileset( auxTextSurface, auxTextSurface->w, auxTextSurface->h ) );

    // Create the final sprite from the previous tileset.
    textSprite->setTileset( textTileset );

    // Free resources.
    TTF_CloseFont( font );
    SDL_FreeSurface( textSurface );

    checkOpenGL( "TextRenderer::draw" );

    // Return the text sprite.
    return textSprite;
}


/***
 * 4. Auxiliar methods
 ***/

void TextRenderer::getTextDimensions( TTF_Font* font, const char* text, int& textWidth, int& textHeight, std::vector< std::string >& lines )
{
    char textLine[128];
    int lineWidth;
    unsigned int i;

    // Initialize the text dimensions to 0.
    textWidth = 0;
    textHeight = 0;
    lines.clear();

    // Iterate over the given text, extracting and getting the dimensions of
    // its lines.
    textWidth = 0;
    while( *text ){

        // Extract the next line and insert it in the vector of lines.
        i = 0;
        while( *text && ( *text != '\n' ) ){
            textLine[i] = *text;

            text++;
            i++;
        }
        textLine[i] = 0;
        lines.push_back( std::string( textLine ) );

        std::cout << "Text line: [" << lines.back() << "]" << std::endl;

        // Get the line dimensions.
        TTF_SizeText( font, textLine, &lineWidth, nullptr );

        // Set the maximum line width as the text one.
        if( lineWidth > textWidth ){
            textWidth = lineWidth;
        }

        // Go for next line.
        text++;
    }

    // Compute the text height by multiplying the font height by the numer of
    // lines in the text.
    textHeight = TTF_FontHeight( font ) * lines.size();
}

} // namespace m2g
