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

#ifndef ISEMANTICSEGMENTATION_H
#define ISEMANTICSEGMENTATION_H

#include <xpcf/core/helpers.h>
#include "datastructure/Image.h"
#include "datastructure/GeometryDefinitions.h"
#include "core/Messages.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace segm {


/**
 * @class ISemanticSegmentation
 * @brief <B>Perform 2D semantic segmentation.</B>
 * <TT>UUID: 2fd30b7c-c6e4-4af7-a711-0b69964e68c2</TT>
 */

class XPCF_IGNORE ISemanticSegmentation :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief ISemanticSegmentation default constructor.
    ISemanticSegmentation() = default;

    ///@brief ISemanticSegmentation default destructor.
    virtual ~ISemanticSegmentation() = default;

    /// @brief Perform 2D semantic segmentation
    /// @param[in] image The input image (SRef<const Image> is not used here in order to give more freedom to the implementations, e.g. torch::from_blob only accepts a non-const data buffer as input).
    /// @param[out] mask The mask has same size as the input image, in which the value of each pixel is corresponding to the class id.
    /// @return FrameworkReturnCode::_SUCCESS if the segmentation succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode segment(SRef<Image> image, SRef<Image> &mask) = 0;

    /// @brief Perform 2D semantic segmentation
    /// @param[in] images List of input images.
    /// @param[out] masks List of output masks (mask has same size as the input image, in which the value of each pixel is corresponding to the class id).
    /// @return FrameworkReturnCode::_SUCCESS if the segmentation succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode segment(const std::vector<SRef<Image>>& images, std::vector<SRef<Image>>& masks);
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::segm::ISemanticSegmentation,
                             "2fd30b7c-c6e4-4af7-a711-0b69964e68c2",
                             "ISemanticSegmentation",
                             "Interface SolAR::api::segm::ISemanticSegmentation");

#endif // ISEMANTICSEGMENTATION_H
