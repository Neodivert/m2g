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

#include "graphics_library.hpp"

namespace m2g {

/***
 * 1. Loading
 ***/

void GraphicsLibrary::load( const std::string& libraryPath )
{
    tinyxml2::XMLDocument libraryFile;
    libraryFile.LoadFile( libraryPath.c_str() );

    const std::string libraryDirPath = getDirPath( libraryPath );

    tinyxml2::XMLElement* rootElement =
            libraryFile.FirstChildElement( "library" );
    tinyxml2::XMLElement* xmlElement =
            rootElement->FirstChildElement( "tileset" );

    while( xmlElement != nullptr ){
        std::string name, path;
        loadNameAndPath( xmlElement, name, path );
        path = libraryDirPath + '/' + path;

        const tinyxml2::XMLElement* dimensionsElement =
                xmlElement->FirstChildElement( "tile_dimensions" );
        const unsigned int width =
                dimensionsElement->UnsignedAttribute( "width" );
        const unsigned int height =
                dimensionsElement->UnsignedAttribute( "height" );

        std::unique_ptr< Tileset > newTileset( new Tileset( path, width, height ) );

        loadCollisionRects( *newTileset, xmlElement->FirstChildElement( "collision_rects" ) );

        tilesets_[std::string( name )] = std::move( newTileset );

        xmlElement = xmlElement->NextSiblingElement( "tileset" );
    }
}


/***
 * 2. Getters
 ***/

const Tileset &GraphicsLibrary::tileset( const std::string& name ) const
{
    return *( tilesets_.at( name ) );
}


/***
 * 3. Auxiliar loading methods
 ***/

void GraphicsLibrary::loadNameAndPath( tinyxml2::XMLElement *tileSetXML,
                                       std::string &name,
                                       std::string &path )
{
    path = tileSetXML->FirstChildElement( "src" )->GetText();

    if( tileSetXML->FirstChildElement( "name" ) != nullptr ){
        name = tileSetXML->FirstChildElement( "name" )->GetText();
    }else{
        // name = filename
        size_t slashPos = path.find_last_of( '/' );
        if( slashPos != std::string::npos ){
            name = path.substr( slashPos + 1, path.size() );
        }else{
            name = path;
        }
    }
}


void GraphicsLibrary::loadCollisionRects( Tileset& tileset, tinyxml2::XMLElement *xmlElement )
{
    if( xmlElement ){
        xmlElement = xmlElement->FirstChildElement( "collision_rect" );
        while( xmlElement ){
            unsigned int firstTile, lastTile;

            const std::string tilesStr = xmlElement->Attribute( "tiles" );

            if( tilesStr == "all" ){
                firstTile = 0;
                lastTile = tileset.nTiles();
            }else{
                std::size_t separatorPos = tilesStr.find( '-' );
                if( separatorPos != std::string::npos ){
                    firstTile = atoi( tilesStr.substr( 0, separatorPos ).c_str() );
                    lastTile = atoi( tilesStr.substr( separatorPos + 1, tilesStr.size() ).c_str() );
                }else{
                    firstTile = lastTile = xmlElement->UnsignedAttribute( "tiles" );
                }
            }

            sf::IntRect rect;
            rect.left = xmlElement->UnsignedAttribute( "x" );
            rect.top = xmlElement->UnsignedAttribute( "y" );
            rect.width = xmlElement->UnsignedAttribute( "width" );
            rect.height = xmlElement->UnsignedAttribute( "height" );

            tileset.addCollisionRect( rect, firstTile, lastTile );

            xmlElement = xmlElement->NextSiblingElement( "collision_rect" );
        }
    }
}


std::string GraphicsLibrary::getDirPath( const std::string& path )
{
    std::size_t slashPos = path.find_last_of( '/' );

    if( slashPos != std::string::npos ){
        return path.substr( 0, slashPos );
    }else{
        return ".";
    }
}

} // namespace m2g
