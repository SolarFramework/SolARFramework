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

#ifndef IPANOPTICSEGMENTATION_H
#define IPANOPTICSEGMENTATION_H

#include "datastructure/Image.h"
#include "datastructure/GeometryDefinitions.h"
#include "core/Messages.h"
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace segm {


/**
 * @class IPanopticSegmentation
 * @brief <B>Perform 2D Panoptic segmentation.</B>
 * <TT>UUID: 60701300-75e2-4215-a5e1-3a2b0aa3193a</TT>
 */

class XPCF_IGNORE IPanopticSegmentation :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief IPanopticSegmentation default constructor.
    IPanopticSegmentation() = default;

    ///@brief IPanopticSegmentation default destructor.
    virtual ~IPanopticSegmentation() = default;

    /// @brief Perform 2D Panoptic segmentation
    /// @param[in] image The input image (SRef<const Image> is not used here in order to give more freedom to the implementations, e.g. torch::from_blob only accepts a non-const data buffer as input)
    /// @param[out] labelMap The label map corresponding to the input image.
    /// @param[out] boxes The bounding boxes of each detected object.
    /// @param[out] classObjectIds The class id and object id of each bounding box.
    /// @param[out] scores The corresponding confidence scores.
    /// @return FrameworkReturnCode::_SUCCESS if the segmentation succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode segment(SRef<const SolAR::datastructure::Image> image,
                                        SRef<SolAR::datastructure::Image>& labelMap,
                                        std::vector<SolAR::datastructure::Rectanglei>& boxes,
                                        std::vector<std::pair<uint32_t, uint32_t>>& classObjectIds,
                                        std::vector<float>& scores) = 0;

    /// @brief Perform 2D Panoptic segmentation
    /// @param[in] image List of input images (SRef<const Image> is not used here in order to give more freedom to the implementations, e.g. torch::from_blob only accepts a non-const data buffer as input)
    /// @param[out] labelMap The label map corresponding to each input image.
    /// @param[out] boxes The bounding boxes of each detected object of each input image.
    /// @param[out] classObjectIds The class id and object id of each bounding box of each input image.
    /// @param[out] scores The corresponding confidence scores of each input image.
    /// @return FrameworkReturnCode::_SUCCESS if the segmentation succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode segment(const std::vector<SRef<SolAR::datastructure::Image>>& images,
                                        std::vector<SRef<SolAR::datastructure::Image>>& labelMaps,
                                        std::vector<std::vector<SolAR::datastructure::Rectanglei>>& boxes,
                                        std::vector<std::vector<std::pair<uint32_t, uint32_t>>>& classObjectIds,
                                        std::vector<std::vector<float>>& scores);
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::segm::IPanopticSegmentation,
                             "60701300-75e2-4215-a5e1-3a2b0aa3193a",
                             "IPanopticSegmentation",
                             "Interface SolAR::api::segm::IPanopticSegmentation");

#endif // IPANOPTICSEGMENTATION_H
