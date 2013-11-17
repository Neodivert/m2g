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
#include <boost/math/common_factor_rt.hpp>

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
    glm::vec2 refBaseLineOrigin;
    glm::vec2 currentBaseLineOrigin;
    unsigned int i;
    const Rect* refBoundaryBox;
    const Rect* currentBoundaryBox;

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

    // Load every particle system in the group.
    xmlNode = rootNode->FirstChildElement( "particle_system" );
    while( xmlNode ){
        particleSystems_.emplace_back( file, xmlNode->Attribute( "name" ) );

        xmlNode = xmlNode->NextSiblingElement( "particle_system" );
    }

    // Make the origins of the different particle system's base lines match
    // each other.
    if( particleSystems_.size() ){
        // TODO: Change this so the reference particle system is defined in
        // the XML config file.
        refParticleSystem = &particleSystems_[0];
        refBaseLineOrigin = refParticleSystem->getBaseLineOrigin();
        boundaryBox = *refParticleSystem->getBoundaryBox();
        refBoundaryBox = refParticleSystem->getBoundaryBox();

        for( i=1; i<particleSystems_.size(); i++ ){
            currentBaseLineOrigin = particleSystems_[i].getBaseLineOrigin();
            currentBoundaryBox = particleSystems_[i].getBoundaryBox();

            particleSystems_[i].moveBaseLine( refBaseLineOrigin.x - currentBaseLineOrigin.x, currentBoundaryBox->height - refBoundaryBox->height );
        }
    }

    // Compute the particle systems group's number of generations as the least
    // common multiple of all the particle system's numbers of generations.
    switch( particleSystems_.size() ){
        case 0:
            throw std::runtime_error( "ERROR - Particle system's group can't be empty" );
        break;
        case 1:
            nGenerations_ = particleSystems_[0].getNGenerations();
        break;
        default:
            nGenerations_ = boost::math::lcm( particleSystems_[0].getNGenerations(), particleSystems_[1].getNGenerations() );
            for( i=2; i<particleSystems_.size(); i++ ){
                nGenerations_ = boost::math::lcm( nGenerations_, particleSystems_[i].getNGenerations() );
            }
    }
}


/***
 * 2. Getters and setters
 ***/

bool ParticleSystemsGroup::isAlive() const
{
    return ( particleSystems_[0] ).isAlive();
}


void ParticleSystemsGroup::setAlive( bool alive )
{
    std::vector< ParticleSystem >::iterator it = particleSystems_.begin();

    for( ; it != particleSystems_.end(); it++ )
    {
        it->setAlive( alive );
    }
}


/***
 * 3. Transformations
 ***/

void ParticleSystemsGroup::translate( const float& tx, const float& ty )
{
    std::vector< ParticleSystem >::iterator it = particleSystems_.begin();

    for( ; it != particleSystems_.end(); it++ )
    {
        it->translate( tx, ty );
    }
}


void ParticleSystemsGroup::moveTo( const float& x, const float& y )
{
    std::vector< ParticleSystem >::iterator it = particleSystems_.begin();

    for( ; it != particleSystems_.end(); it++ )
    {
        it->moveTo( x, y );
    }
}


/***
 * 4. Collision test
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
 * 5. Drawing
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
