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

#ifndef SOLAR_IHOMOGRAPHYVALIDATION_H
#define SOLAR_IHOMOGRAPHYVALIDATION_H

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"

namespace SolAR {
namespace api {
namespace solver {
namespace pose {

/**
  * @class IHomographyValidation
  * @brief <B>Tests if a homography is valid.</B>
  * <TT>UUID: e95e8f70-dd32-11e7-9296-cec278b6b50a</TT>
  */
class [[xpcf::clientUUID("55221e5e-67cc-487c-a277-1d56e3637e42")]] [[xpcf::serverUUID("ca9cda6e-6cf1-495d-a51d-da1286f4f3d3")]] IHomographyValidation :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IHomographyValidation default constructor
    IHomographyValidation() = default;

    /// @brief IHomographyValidation default destructor
    virtual ~IHomographyValidation() = default;

    /// @brief evaluate the homography according to the projection of the 4 corners of a 2D squared Marker
    /// @param[in] ref2DSquaredMarkerCorners set of 2d_points of the corners in the template view.
    /// @param[in] projected2DSquaredMarkerCorners set of 2d_points of the corners projected in the current view.
    /// @return true if succeed, else false
    virtual bool isValid(const std::vector<SolAR::datastructure::Point2Df> & ref2DSquaredMarkerCorners,
                         const std::vector<SolAR::datastructure::Point2Df> & projected2DSquaredMarkerCorners) = 0;
};

}
}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::IHomographyValidation,
                             "e95e8f70-dd32-11e7-9296-cec278b6b50a",
                             "IHomographyValidation",
                             "SolAR::api::solver::pose::IHomographyValidation");

#endif // SOLAR_IHOMOGRAPHYVALIDATION_H
