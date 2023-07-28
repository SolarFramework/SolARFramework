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

#ifndef SOLAR_IDESCRIPTORSEXTRACTORSBPATTERN_H
#define SOLAR_IDESCRIPTORSEXTRACTORSBPATTERN_H

#include "xpcf/api/IComponentIntrospect.h"
#include <xpcf/core/helpers.h>
#include "datastructure/Image.h"
#include "datastructure/SquaredBinaryPattern.h"
#include "datastructure/DescriptorBuffer.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
namespace api {
namespace features {
/**
 * @class IDescriptorsExtractorSBPattern
 * @brief <B>Extracts descriptors from a squared binary pattern or from an image of a squared binary pattern.</B>
 * <TT>UUID: 2e2bde18-ce39-11e7-abc4-cec278b6b50a</TT>
 *
 * This class provides a method to extract descriptors of a squared binary pattern by simply concatenating pattern rows in a single vector.
 */
class XPCF_CLIENTUUID("c2a230ae-6fb0-4e30-b06c-05c29c6feb9b") XPCF_SERVERUUID("b79db157-da75-4e58-be04-f82a7c54dc7c") IDescriptorsExtractorSBPattern :
    virtual public org::bcom::xpcf::IComponentIntrospect {

public:
   /// @brief IDescriptorsExtractorSBPattern default constructor
   IDescriptorsExtractorSBPattern() = default;

   /// @brief IDescriptorsExtractorSBPattern default destructor
   virtual ~IDescriptorsExtractorSBPattern() = default;

   /// @brief Extracts the descriptors of a set of images of squared binary patterns
   /// @param[in] images The set of images on which we want to extract descriptors. These images have to be exactly aligned on the squared binary patterns including the borders of the marker.
   /// @param[in] inContours The contours in the original image of candidates for squared binary pattern. The nth contour corresponds to the nth image of the first attribute representing a candidate of a squared binary pattern extracted from the original image.
   /// @param[out] descriptors The descriptors of the squared binary pattern recognized in the images.
   /// @param[out] outContours The contours in the original image of recognized squared binary pattern. The nth contour corresponds to the nth descriptors of the third attribute representing a recognized squared binary pattern extracted from the original image.
   /// @return FrameworkReturnCode::_SUCCESS_ if the extraction succeed, else FrameworkReturnCode::_ERROR.
   virtual FrameworkReturnCode extract(const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                       const std::vector<SolAR::datastructure::Contour2Df> & inContours,
                                       SRef<SolAR::datastructure::DescriptorBuffer> & descriptors,
                                       std::vector<SolAR::datastructure::Contour2Df> & outContours) = 0;

   /// @brief Extracts the descriptors of a squared binary patterns
   /// @param[in] pattern The squared binary pattern for which we want to extract its descriptor
   /// @param[out] descriptor The descriptor extracted from the squared binary pattern. The descriptor of a squared binary pattern is simply the concatenation of the rows of the pattern matrix.
   /// @return FrameworkReturnCode::_SUCCESS_ if the extraction succeed, else FrameworkReturnCode::_ERROR.
   virtual FrameworkReturnCode extract(const SolAR::datastructure::SquaredBinaryPattern & pattern,
                                       SRef<SolAR::datastructure::DescriptorBuffer> & descriptor) = 0;

};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IDescriptorsExtractorSBPattern,
                             "2e2bde18-ce39-11e7-abc4-cec278b6b50a",
                             "IDescriptorsExtractorSBPattern",
                             "SolAR::api::features::IDescriptorsExtractorSBPattern");

#endif // SOLAR_IDESCRIPTORSEXTRACTORSBPATTERN_H
