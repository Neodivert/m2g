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

#include "alignment.hpp"
#include <stdexcept>

namespace m2g {


HorizontalAlign readHorizontalAligmentFromXML(tinyxml2::XMLElement *xmlElement)
{
    HorizontalAlign align = HorizontalAlign::LEFT;

    if( xmlElement != nullptr ){
        const char* alignStr = xmlElement->GetText();
        if( alignStr != nullptr ){
            if( !strcmp( alignStr, "left" ) ){
                align = HorizontalAlign::LEFT;
            }else if( !strcmp( alignStr, "center" ) ){
                align = HorizontalAlign::CENTER;
            }else if( !strcmp( alignStr, "right" ) ){
                align = HorizontalAlign::RIGHT;
            }else{
                throw std::runtime_error( "Unrecognized horizontal align in XML" );
            }
        }
    }

    return align;
}


VerticalAlign readVerticalAligmentFromXML(tinyxml2::XMLElement *xmlElement)
{
    VerticalAlign align = VerticalAlign::MIDDLE;

    if( xmlElement != nullptr ){
        const char* alignStr = xmlElement->GetText();
        if( alignStr != nullptr ){
            if( !strcmp( alignStr, "top" ) ){
                align = VerticalAlign::TOP;
            }else if( !strcmp( alignStr, "middle" ) ){
                align = VerticalAlign::MIDDLE;
            }else if( !strcmp( alignStr, "bottom" ) ){
                align = VerticalAlign::BOTTOM;
            }else{
                throw std::runtime_error( "Unrecognized vertical align in XML" );
            }
        }
    }

    return align;
}

} // namespace m2g
