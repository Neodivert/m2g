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

#ifndef GRAPHICS_LIBRARY_HPP
#define GRAPHICS_LIBRARY_HPP

#include <tinyxml2.h>
#include <string>
#include <map>
#include "drawables/tileset.hpp"
#include "drawables/animation_data.hpp"

namespace m2g {

typedef std::list< AnimationDataPtr > AnimationDataList;

class GraphicsLibrary
{
    public:
        /***
         * 1. Construction
         ***/
        GraphicsLibrary( const std::string& libraryPath );


        /***
         * 2. Loading
         ***/
        TilesetPtr getTilesetByName( const std::string& tilesetName );
        AnimationDataPtr getAnimationDataByName( const std::string& animDataName );
        AnimationDataList getAnimationDataByPrefix( const std::string& animDataName );


    private:
        /***
         * 3. Auxiliar loading methods
         ***/
        void loadNameAndPath( tinyxml2::XMLElement* tileSetXML,
                              std::string& name,
                              std::string& path );
        TilesetPtr loadTilesetFromXML( tinyxml2::XMLElement* tilesetXML );
        AnimationDataPtr loadAnimationDataFromXML( tinyxml2::XMLElement* animDataXML );

        void loadCollisionRects( Tileset& tileset, tinyxml2::XMLElement* xmlElement );
        std::string getDirPath( const std::string& path );
        void loadAnimationDataStates( AnimationData& animData,
                                      tinyxml2::XMLElement* statesNode );


        /***
         * Attributes
         ***/
        std::map< std::string, std::unique_ptr< Tileset > > tilesets_;
        std::map< std::string, std::unique_ptr< AnimationData > > animData_;
        std::string libraryPath_;
};

} // namespace m2g

#endif // GRAPHICS_LIBRARY_HPP
