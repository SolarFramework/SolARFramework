/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SOLAR_IIMAGE2WORLDMAPPER_H
#define SOLAR_IIMAGE2WORLDMAPPER_H


#include "IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace geom {

/**
 * @class IImage2WorldMapper
 * @brief provides a method to map 2D points to a 3D world coordinate system. For example, this method can map the 4 corners of a marker to the world coordinate system.
 */

class IImage2WorldMapper : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IImage2WorldMapper default constructor
    IImage2WorldMapper() = default;

    /// @brief IImage2WorldMapper default destructor
    virtual ~IImage2WorldMapper() = default;

    /// @brief Set the digital size of the 2D marker (in pixels for a natural image marker, or in cells for a squared binary marker) as well as the real size of the marker in a user-defined coordinate system (in meter, centimeters, etc.).
    /// @param[in] digitalSize the size of the 2D marker in pixels for a natural image marker, or in cells for a squared binary marker.
    /// @param[in] worldSize the size of the marker in a user-defined world coordinate system (meters, cenimeters, etc.)
    virtual void setParameters(const Sizei digitalSize, const Sizef worldSize) = 0;

    /// @brief Map a set of 2D points to a 3D world coordinate system.
    /// @param[in] digitalPoints the 2D points we want to map in 3D world coordinate system.
    /// @param[out] worldPoints the resulting 3D poitns after 3D mapping
    /// @return FrameworkReturnCode::_SUCCESS_ if mapping succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode map(const std::vector<SRef<Point2Df>> & digitalPoints, std::vector<SRef<Point3Df>> & worldPoints) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::IImage2WorldMapper,
                             "67bcd080-258d-4b16-b693-cd30c013eb05",
                             "SolAR::api::geom::IImage2WorldMapper");


#endif // SOLAR_IIMAGE2WORLDMAPPER_H

