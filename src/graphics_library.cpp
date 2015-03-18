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

// TODO: Remove duplicated code in loading methods.

/***
 * 1. Construction
 ***/

GraphicsLibrary::GraphicsLibrary( const std::string &libraryPath ) :
    libraryPath_( libraryPath )
{}


/***
 * 2. Loading
 ***/

TilesetPtr GraphicsLibrary::loadTilesetByName( const std::string& tilesetName )
{
    TilesetPtr tileset = nullptr;
    tinyxml2::XMLDocument libraryFile;
    libraryFile.LoadFile( libraryPath_.c_str() );

    tinyxml2::XMLElement* rootElement =
            libraryFile.FirstChildElement( "library" );
    tinyxml2::XMLElement* xmlElement =
            rootElement->FirstChildElement( "tileset" );

    while( xmlElement != nullptr ){
        std::string name, path;
        loadNameAndPath( xmlElement, name, path ); // TODO: Don't use path.

        if( name == tilesetName ){
            return loadTilesetFromXML( xmlElement );
        }
        xmlElement = xmlElement->NextSiblingElement( "tileset" );
    }

    return tileset;
}


AnimationDataPtr GraphicsLibrary::loadAnimationDataByName( const std::string& animDataName )
{
    tinyxml2::XMLDocument libraryFile;
    libraryFile.LoadFile( libraryPath_.c_str() );

    tinyxml2::XMLElement* rootElement =
            libraryFile.FirstChildElement( "library" );
    tinyxml2::XMLElement* xmlElement =
            rootElement->FirstChildElement( "animation" );

    while( xmlElement != nullptr ){
        std::string name, path;
        loadNameAndPath( xmlElement->FirstChildElement( "tileset" ), name, path ); // TODO: Don't use path.

        if( name == animDataName ){
            return loadAnimationDataFromXML( xmlElement );
        }
        xmlElement = xmlElement->NextSiblingElement( "animation" );
    }

    return nullptr;
}


AnimationDataList GraphicsLibrary::loadAnimationDataByPrefix( const std::string &animDataName )
{
    AnimationDataList animDataList;

    tinyxml2::XMLDocument libraryFile;
    libraryFile.LoadFile( libraryPath_.c_str() );

    tinyxml2::XMLElement* rootElement =
            libraryFile.FirstChildElement( "library" );
    tinyxml2::XMLElement* xmlElement =
            rootElement->FirstChildElement( "animation" );

    while( xmlElement != nullptr ){
        std::string name, path;
        loadNameAndPath( xmlElement->FirstChildElement( "tileset" ), name, path ); // TODO: Don't use path.

        if( name.substr( 0, animDataName.size() ) == animDataName ){
            animDataList.push_back( loadAnimationDataFromXML( xmlElement ) );
        }
        xmlElement = xmlElement->NextSiblingElement( "animation" );
    }

    return animDataList;
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


TilesetPtr GraphicsLibrary::loadTilesetFromXML( tinyxml2::XMLElement *tilesetXML )
{
    std::string name, path;
    loadNameAndPath( tilesetXML, name, path );
    const std::string libraryDirPath = getDirPath( libraryPath_ );
    path = libraryDirPath + '/' + path;

    const tinyxml2::XMLElement* dimensionsElement =
            tilesetXML->FirstChildElement( "tile_dimensions" );
    const unsigned int width =
            dimensionsElement->UnsignedAttribute( "width" );
    const unsigned int height =
            dimensionsElement->UnsignedAttribute( "height" );

    TilesetPtr newTileset( new Tileset( path, width, height ) );

    loadCollisionRects( *newTileset, tilesetXML->FirstChildElement( "collision_rects" ) );

    return newTileset;
}

AnimationDataPtr GraphicsLibrary::loadAnimationDataFromXML( tinyxml2::XMLElement *animDataXML )
{
    TilesetPtr tileset =
            loadTilesetFromXML( animDataXML->FirstChildElement( "tileset" ) );
    const unsigned int REFRESH_RATE = animDataXML->UnsignedAttribute( "fps" );

    AnimationDataPtr animData( new AnimationData( *tileset, REFRESH_RATE ) );
    auxiliarTilesets_.push_back( std::move( tileset ) );

    loadAnimationDataStates( *animData,
                             animDataXML->FirstChildElement( "animation_states" ) );

    return animData;
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


void GraphicsLibrary::loadAnimationDataStates( AnimationData &animData,
                                               tinyxml2::XMLElement *statesNode )
{
    if( statesNode != nullptr ){
        tinyxml2::XMLElement* stateNode =
                statesNode->FirstChildElement( "animation_state" );

        while( stateNode != nullptr ){
            AnimationState animState(
                        stateNode->UnsignedAttribute( "first_frame" ),
                        stateNode->UnsignedAttribute( "last_frame" ),
                        stateNode->UnsignedAttribute( "back_frame" )
                        );
            animData.addState( animState );

            stateNode = stateNode->NextSiblingElement( "animation_state" );
        }
    }
}

} // namespace m2g
