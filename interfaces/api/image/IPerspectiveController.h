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

#ifndef SOLAR_IPERSPECTIVECONTROLLER_H
#define SOLAR_IPERSPECTIVECONTROLLER_H

#include "xpcf/api/IComponentIntrospect.h"

#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"

namespace SolAR {
namespace api {
namespace image {

/**
 * @class IPerspectiveController
 * @brief <B>Warps and crops an image given a contour defined with four 2D points.</B>
 * <TT>UUID: 4a7d5c34-cd6e-11e7-abc4-cec278b6b50a</TT>
 *
 */
class  IPerspectiveController : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IPerspectiveController default constructor
   IPerspectiveController() = default;

   /// @brief IPerspectiveController default destructor
   virtual ~IPerspectiveController() = default;

   /// @brief Warps and crops an image given a set of contour defined with four 2D points
   /// @param[in] inputImg: the original image on which we want to extract sub-images aligned on the set of 2D contours
   /// @param[in] contours: the set of contours each defined with four 2D points
   /// @param[out] patches: the set of sub-images or patches resulting from the warping and cropping of the original image according to the set of 2D contours
   /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
   virtual FrameworkReturnCode correct(const SRef<datastructure::Image> inputImg,
                                       const std::vector<datastructure::Contour2Df> & contours,
                                       std::vector<SRef<datastructure::Image>> & patches) = 0;

   /// @brief Warps and crops an image given a contour defined with four 2D points
   /// @param[in] inputImg: the original image on which we want to extract sub-image aligned on the 2D contour
   /// @param[in] contour: the contour defined with four 2D points
   /// @param[out] patch: the sub-image or patche resulting from the warping and cropping of the original image according to the 2D contour
   /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
   virtual FrameworkReturnCode correct(const SRef<datastructure::Image> inputImg,
                                       const datastructure::Contour2Df & contour,
                                       SRef<datastructure::Image> & patch) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::image::IPerspectiveController,
                             "4a7d5c34-cd6e-11e7-abc4-cec278b6b50a",
                             "IPerspectiveController",
                             "SolAR::api::image::IPerspectiveController");


#endif // SOLAR_IPERSPECTIVECONTROLLER_H
