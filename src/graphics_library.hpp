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

class GraphicsLibrary
{
    public:
        /***
         * 1. Loading
         ***/
        void load( const std::string& libraryPath );


        /***
         * 2. Getters
         ***/
        const Tileset& getTilesetByName( const std::string& name ) const;
        const AnimationData& getAnimationDataByName( const std::string& name ) const;
        std::list< std::reference_wrapper< const AnimationData > > getAnimationDataByPrefix( const std::string& namePrefix );

    private:
        /***
         * 3. Auxiliar loading methods
         ***/
        void loadNameAndPath( tinyxml2::XMLElement* tileSetXML,
                              std::string& name,
                              std::string& path );
        void loadCollisionRects( Tileset& tileset, tinyxml2::XMLElement* xmlElement );
        std::string getDirPath( const std::string& path );
        std::string loadTileset( tinyxml2::XMLElement* tilesetXML,
                                 const std::string& libraryDirPath );
        void loadAnimationData( tinyxml2::XMLElement* animationDataXML,
                                const std::string& libraryDirPath );
        void loadAnimationDataStates( AnimationData& animData,
                                      tinyxml2::XMLElement* statesNode );


        /***
         * Attributes
         ***/
        std::map< std::string, std::unique_ptr< Tileset > > tilesets_;
        std::map< std::string, std::unique_ptr< AnimationData > > animData_;
};

} // namespace m2g

#endif // GRAPHICS_LIBRARY_HPP
