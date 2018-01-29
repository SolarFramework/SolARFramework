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

#include "IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/SquaredBinaryPattern.h"
#include "datastructure/DescriptorBuffer.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace features {
/**
 * @class IDescriptorsExtractorSBPattern
 * @brief extracts descriptors from a squared binary pattern or from an image of a squared binary pattern
 *
 * This class provides a method to extract descriptors of a squared binary pattern by simply concatenating pattern rows in a single vector.
 */
class  IDescriptorsExtractorSBPattern : public virtual org::bcom::xpcf::IComponentIntrospect {

public:
   /// @brief IDescriptorsExtractorSBPattern default constructor
   IDescriptorsExtractorSBPattern() = default;

   /// @brief IDescriptorsExtractorSBPattern default destructor
   virtual ~IDescriptorsExtractorSBPattern() = default;

   /// @brief Set the squared binary pattern size corresponding to horizontal or vertical cells
   /// As this pattern is squared, it has the same number of vertical and horizontal cells (without marker borders)
   /// @param[in] patternSize The number of horizontal or vertical cells of the squared binary pattern.
   virtual void setParameters (const int patternSize) = 0;

   /// @brief Extracts the descriptors of a set of images of squared binary patterns
   /// @param[in] images The set of images on which we want to extract descriptors. These images have to be exactly aligned on the squared binary patterns including the borders of the marker.
   /// @param[in] inContours The contours in the original image of candidates for squared binary pattern. The nth contour corresponds to the nth image of the first attribute representing a candidate of a squared binary pattern extracted from the original image.
   /// @param[out] descriptors The descriptors of the squared binary pattern recognized in the images.
   /// @param[out] outContours The contours in the original image of recognized squared binary pattern. The nth contour corresponds to the nth descriptors of the third attribute representing a recognized squared binary pattern extracted from the original image.
   /// @return FrameworkReturnCode::_SUCCESS_ if the extraction succeed, else FrameworkReturnCode::_ERROR.
   virtual FrameworkReturnCode extract(const std::vector<SRef<Image>>& images, const std::vector<SRef<Contour2Df>>& inContours, SRef<DescriptorBuffer> & descriptors, std::vector<SRef<Contour2Df>> & outContours) = 0;

   /// @brief Extracts the descriptors of a squared binary patterns
   /// @param[in] pattern The squared binary pattern for which we want to extract its descriptor
   /// @param[out] descriptor The descriptor extracted from the squared binary pattern. The descriptor of a squared binary pattern is simply the concatenation of the rows of the pattern matrix.
   /// @return FrameworkReturnCode::_SUCCESS_ if the extraction succeed, else FrameworkReturnCode::_ERROR.
   virtual FrameworkReturnCode extract(const SRef<SquaredBinaryPattern> pattern, SRef<DescriptorBuffer> & descriptor) = 0;

   XPCF_DECLARE_UUID("2e2bde18-ce39-11e7-abc4-cec278b6b50a");

};

}
}
}  // end of namespace Solar

#endif // SOLAR_IDESCRIPTORSEXTRACTORSBPATTERN_H
