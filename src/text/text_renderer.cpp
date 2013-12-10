/***
 * Copyright 2013 Moises J. Bonilla Caraballo (Neodivert)
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


SpritePtr TextRenderer::drawText( const char* text, const char* fontPath, unsigned int fontSize, const SDL_Color& color )
{
    TTF_Font* font = nullptr;
    TilesetPtr textTileset;
    SpritePtr textSprite( new Sprite );
    SDL_Surface* auxTextSurface = nullptr;
    SDL_Surface* textSurface = nullptr;
    int textWidth, textHeight;
    int aux;

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

    // Render the text on an auxiliar surface.
    auxTextSurface = TTF_RenderText_Blended( font, text, color );
    //auxTextSurface = SDL_ConvertSurface( auxTextSurface, textSurface->format, textSurface->flags );

    // Round text dimensions to nearest upper pow of two.
    textWidth = 1;
    while( textWidth < auxTextSurface->w ){
        textWidth <<= 1;
    }

    textHeight = 1;
    while( textHeight < auxTextSurface->h ){
        textHeight <<= 1;
    }

    std::cout << "Aux text dimensions: (" << auxTextSurface->w << ", " << auxTextSurface->h << ")" << std::endl;
    std::cout << "Text dimensions: (" << textWidth << ", " << textHeight << ")" << std::endl;

    // Create the final text surface with the power-of-two dimensions.
    textSurface = SDL_CreateRGBSurface( 0, textWidth, textHeight, 32, rmask, gmask, bmask, amask );

    // Prepare the final text surface for the blitting.
    SDL_FillRect( textSurface, nullptr, 0 );
    SDL_SetSurfaceBlendMode( auxTextSurface, SDL_BLENDMODE_NONE );

    // Blit the text to its final surface.
    SDL_BlitSurface( auxTextSurface, nullptr, textSurface, nullptr );

    IMG_SavePNG( auxTextSurface, "foo1.png" );
    IMG_SavePNG( textSurface, "foo2.png" );

    // Generate a tileset from the text surface.
    //textTileset = TilesetPtr( new Tileset( textSurface, textWidth, textHeight, auxTextSurface->w / (GLfloat)textWidth, auxTextSurface->h / (GLfloat)textHeight ) );
    textTileset = TilesetPtr( new Tileset( textSurface, textWidth, textHeight ) );

    std::cout << "Factors: (" << auxTextSurface->w / (GLfloat)textWidth << ", " << auxTextSurface->h / (GLfloat)textHeight << ")" << std::endl;
    //textTileset = TilesetPtr( new Tileset( auxTextSurface, auxTextSurface->w, auxTextSurface->h ) );

    // Create the final sprite from the previous tileset.
    textSprite->setTileset( textTileset );

    // Free resources.
    TTF_CloseFont( font );
    SDL_FreeSurface( auxTextSurface );
    SDL_FreeSurface( textSurface );

    checkOpenGL( "TextRenderer::draw" );

    // Return the text sprite.
    return textSprite;
}

} // namespace m2g
