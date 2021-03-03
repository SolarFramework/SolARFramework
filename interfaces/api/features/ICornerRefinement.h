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

#ifndef SOLAR_ICORNERREFINEMENT_H
#define SOLAR_ICORNERREFINEMENT_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <vector>
#include "core/Messages.h"
#include "datastructure/Image.h"
#include "datastructure/GeometryDefinitions.h"

// Definition of ICornerRefinement Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"

namespace SolAR {
namespace api {
namespace features {

/**
 * @class ICornerRefinement
 * @brief <B>Refine the corner locations.</B>
 * <TT>UUID: 6ed0413a-751e-4c33-b91b-97b3ea949bc2</TT>
 *
 * This class provides a method to refine the corner locations.
 */
class ICornerRefinement : virtual public org::bcom::xpcf::IComponentIntrospect {

public:    
    /// @brief ICornerRefinement default constructor
    ICornerRefinement() = default;

    /// @brief ICornerRefinement default destructor
    virtual ~ICornerRefinement() = default;

    /// @brief This method refines the corner locations
    /// @param[in] image Input image on which we are extracting keypoints.
    /// @param[in,out] corners Initial coordinates of the input corners and refined coordinates provided for output.
    virtual void refine(const SRef<datastructure::Image> image, std::vector<datastructure::Point2Df> & corners) = 0;

};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::ICornerRefinement,
                             "6ed0413a-751e-4c33-b91b-97b3ea949bc2",
                             "ICornerRefinement",
                             "SolAR::api::features::ICornerRefinement");

#endif // SOLAR_ICORNERREFINEMENT_H
