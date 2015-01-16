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

namespace m2g {


/***
 * 1. Initialization
 ***/

TextRenderer::TextRenderer( SDL_Renderer *renderer ) :
    renderer_( renderer )
{}


/***
 * 3. Drawing
 ***/

SpritePtr TextRenderer::drawText( const char* text, const char* fontPath, unsigned int fontSize, const SDL_Color& color, TextAlign textAlign )
{
    TTF_Font* font = nullptr;
    TilesetPtr textTileset;
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

    // Create the final text surface with the power-of-two dimensions.
    textSurface = SDL_CreateRGBSurface( 0, textWidth, textHeight, 32, rmask, gmask, bmask, amask );

    // Prepare the final text surface for the blitting.
    SDL_FillRect( textSurface, nullptr, 0 );
    SDL_SetSurfaceBlendMode( lineSurface, SDL_BLENDMODE_NONE );

    // Render every line and blit it to the final surface.
    for( i = 0; i < lines.size(); i++ ){
        // Generate a surface with the text line.
        lineSurface = TTF_RenderText_Blended( font, lines[i].c_str(), color );

        // Give the text the given align.
        // TODO: Change so the switch is executed only once.
        switch( textAlign ){
            case TextAlign::LEFT:
                dstRect.x = 0;
            break;
            case TextAlign::CENTER:
                dstRect.x = (textWidth >> 1) - (lineSurface->w >> 1);
            break;
            case TextAlign::RIGHT:
                dstRect.x = textWidth - lineSurface->w;
            break;
        }

        // Blit the line surface to its final surface.
        SDL_BlitSurface( lineSurface, nullptr, textSurface, &dstRect );

        //
        dstRect.y += TTF_FontHeight( font );

        // Free the line surface.
        SDL_FreeSurface( lineSurface );
    }

    // Generate a tileset from the text surface.
    textTileset = TilesetPtr( new Tileset( renderer_, textSurface, textWidth, textHeight ) );

    //textTileset = TilesetPtr( new Tileset( auxTextSurface, auxTextSurface->w, auxTextSurface->h ) );

    // Create the final sprite from the previous tileset.
    SpritePtr textSprite( new Sprite( renderer_, textTileset ) );

    // Free resources.
    TTF_CloseFont( font );
    SDL_FreeSurface( textSurface );

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
