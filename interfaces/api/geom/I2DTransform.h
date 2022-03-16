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

#ifndef SOLAR_I2DTRANSFORM_H
#define SOLAR_I2DTRANSFORM_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
namespace api {
namespace geom {

/**
 * @class I2DTransform
 * @brief <B>Applies a 2D transformation (e.g. an homography) to a set of 2D points.</B>
 * <TT>UUID: dbf5a8a1-cbcb-4a95-8dfd-4d9d5877e56f</TT>
 */

class [[xpcf::clientUUID("125ebd15-d7b2-4f20-98a9-572a48d477bf")]] [[xpcf::serverUUID("e59ed354-1ddc-4f89-b445-31001e0acc67")]] I2DTransform :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I2DTransform default constructor
    I2DTransform() = default;

    /// @brief I2DTransform default destructor
    virtual ~I2DTransform() = default;

    /// @brief This method applies a 2D transformation (3x3 float matrix) to a set of 2D points
    /// @param[in] inputPoints the set of 2D points to transform
    /// @param[in] transformation the 2D transformation to apply (a 3x3 float matrix)
    /// @param[out] outputPoints the resulting set of 2D points after transformation
    /// @return FrameworkReturnCode::_SUCCESS_ if 2D transformation succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode transform(const std::vector<SolAR::datastructure::Point2Df> & inputPoints,
                                          const SolAR::datastructure::Transform2Df & transformation,
                                          std::vector<SolAR::datastructure::Point2Df> & outputPoints) = 0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::I2DTransform,
                             "dbf5a8a1-cbcb-4a95-8dfd-4d9d5877e56f",
                             "I2DTransform",
                             "SolAR::api::geom::I2DTransform");


#endif //SOLAR_I2DTRANSFORM_H

