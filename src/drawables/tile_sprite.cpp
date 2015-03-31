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

#include "tile_sprite.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace m2g {

/***
 * 1. Construction
 ***/

TileSprite::TileSprite( const m2g::Tileset &tileset )
{
    setTileset( tileset );
}


TileSprite::TileSprite( TilesetPtr tileset )
{
    setTileset( std::move( tileset ) );
}


/***
 * 2. Getters
 ***/

const m2g::Tileset &m2g::TileSprite::tileset() const
{
    return *tileset_;
}


std::list<sf::FloatRect> TileSprite::collisionRects() const
{
    const std::list< sf::IntRect > tileCollisionRects =
            tileset_->collisionRects( currentTile_ );
    std::list< sf::FloatRect > collisionRects;

    for( const sf::IntRect& tileColRect : tileCollisionRects ){
        sf::FloatRect floatRect;
        floatRect.left = tileColRect.left;
        floatRect.top = tileColRect.top;
        floatRect.height = tileColRect.height;
        floatRect.width = tileColRect.width;

        collisionRects.push_back( getTransform().transformRect( floatRect ) );
    }

    return collisionRects;
}


sf::FloatRect TileSprite::getBoundaryBox() const
{
    return getTransform().transformRect( sprite_.getGlobalBounds() );
}


/***
 * 3. Setters
 ***/

void TileSprite::setTile( unsigned int tile )
{
    currentTile_ = tile;
    sprite_.setTextureRect( tileset_->tileRect( currentTile_ ) );
}


void TileSprite::setTileset( const Tileset &tileset )
{
    tileset_ = &tileset;
    sprite_.setTexture( tileset.texture() );
    TileSprite::setTile( 0 );
}


void TileSprite::setTileset( TilesetPtr tileset )
{
    ownTileset_ = std::move( tileset );
    setTileset( *ownTileset_ );
}


/***
 * 4. Collision detection
 ***/

bool TileSprite::collide( const TileSprite &sprite ) const
{
    std::list< sf::FloatRect > rectsA, rectsB;

    rectsA = collisionRects();
    rectsB = sprite.collisionRects();

    for( sf::FloatRect& rectA : rectsA ){
        for( sf::FloatRect& rectB : rectsB ){
            if( rectA.intersects( rectB ) ){
                return true;
            }
        }
    }

    return false;
}


/***
 * 5. Drawing
 ***/

void TileSprite::draw( sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform = getTransform();
    target.draw( sprite_, states );
}

} // namespace m2g
