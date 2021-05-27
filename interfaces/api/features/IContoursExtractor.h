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

#ifndef SOLAR_ICONTOURSEXTRACTOR_H
#define SOLAR_ICONTOURSEXTRACTOR_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
namespace api {
namespace features {
/**
 * @class IContoursExtractor
 * @brief <B>Extracts contours from an image.</B>
 * <TT>UUID: 42d82ab6-cc62-11e7-abc4-cec278b6b50a</TT>
 *
 * This class provides a contours extraction method from an image.
 */


class  IContoursExtractor : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IContoursExtractor default constructor
    IContoursExtractor() = default;

    /// @brief IContoursExtractor default destructor
    virtual ~IContoursExtractor() = default;

    /// @brief Extract the contours detected in a vector from a given input image
    /// @param[in] inputImg The image on which contours are extracted
    /// @param[out] contours The contours extracted from the image
    /// @return FrameworkReturnCode::_SUCCESS_ if contours ar well extracted, else FrameworkReturnCode::_ERROR
    virtual FrameworkReturnCode extract(const SRef<SolAR::datastructure::Image> inputImg, std::vector<SolAR::datastructure::Contour2Df> & contours) = 0;

};
}
}
}  // end of namespace SOLAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IContoursExtractor,
                             "42d82ab6-cc62-11e7-abc4-cec278b6b50a",
                             "IContoursExtractor",
                             "SolAR::api::features::IContoursExtractor");

#endif // SOLAR_ICONTOURSEXTRACTOR_H
