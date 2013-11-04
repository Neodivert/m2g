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

#include "particle_systems_group.hpp"

namespace m2g {

/***
 * 1. Initialization and destruction.
 ***/

ParticleSystemsGroup::ParticleSystemsGroup( const char* file, const char* name )
{
    loadXML( file, name );
}


void ParticleSystemsGroup::loadXML( const char* file, const char* name )
{
    tinyxml2::XMLDocument xmlFile;
    tinyxml2::XMLElement* rootNode = nullptr;
    tinyxml2::XMLElement* xmlNode = nullptr;

    // Try to open the requested XML file.
    xmlFile.LoadFile( file );
    if( !xmlFile.RootElement() ){
        throw std::runtime_error( std::string( "ERROR: Couldn't open file [" ) + file + "]" );
    }

    // Try to find the requested particle system group configuration.
    rootNode = xmlFile.RootElement()->FirstChildElement( "particle_systems_group" );
    while( rootNode && strcmp( name, rootNode->Attribute( "name" ) ) ){
        rootNode = rootNode->NextSiblingElement( "particle_systems_group" );
    }
    if( !rootNode ){
        throw std::runtime_error( std::string( "ERROR: Couldn't find particle systems group [" ) + name + "]" );
    }

    xmlNode = rootNode->FirstChildElement( "particle_system" );
    while( xmlNode ){
        std::cout << "Loading [" << xmlNode->Attribute( "name" ) << "]" << std::endl;
        particleSystems_.emplace_back( file, xmlNode->Attribute( "name" ) );

        xmlNode = xmlNode->NextSiblingElement( "particle_system" );
    }
}


/***
 * 3. Collision test
 ***/

bool ParticleSystemsGroup::collide( const Drawable& b ) const
{
    return false;
}


const std::vector<Rect>* ParticleSystemsGroup::getCollisionRects() const
{
    return nullptr;
}


/***
 * 4. Drawing
 ***/

void ParticleSystemsGroup::draw( const glm::mat4& projectionMatrix ) const
{
    std::vector< ParticleSystem >::const_iterator it = particleSystems_.begin();

    for( ; it != particleSystems_.end(); it++ )
    {
        it->draw( projectionMatrix );
    }
}

void ParticleSystemsGroup::drawAndUpdate( const glm::mat4& projectionMatrix )
{
    std::vector< ParticleSystem >::iterator it = particleSystems_.begin();

    for( ; it != particleSystems_.end(); it++ )
    {
        it->drawAndUpdate( projectionMatrix );
    }
}

} // namespace m2g
