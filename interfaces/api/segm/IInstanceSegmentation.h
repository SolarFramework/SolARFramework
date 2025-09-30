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

#ifndef IINSTANCESEGMENTATION_H
#define IINSTANCESEGMENTATION_H

#include "datastructure/Image.h"
#include "datastructure/GeometryDefinitions.h"
#include <xpcf/core/helpers.h>
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace segm {


/**
 * @class IInstanceSegmentation
 * @brief <B>Perform 2D instance segmentation.</B>
 * <TT>UUID: 402aae34-bbec-43e3-8f36-3f201b6ca6d2</TT>
 */

class XPCF_IGNORE IInstanceSegmentation :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief IInstanceSegmentation default constructor.
    IInstanceSegmentation() = default;

    ///@brief IInstanceSegmentation default destructor.
    virtual ~IInstanceSegmentation() = default;

    /// @brief Perform 2D instance segmentation
    /// @param[in] image The input image (SRef<const Image> is not used here in order to give more freedom to the implementations, e.g. torch::from_blob only accepts a non-const data buffer as input).
    /// @param[out] boxes The bounding boxes of each detected object.
    /// @param[out] masks The binary masks corresponding to the bounding boxes. For each mask, regions with a value of 1 correspond to the object, otherwise the background.
    /// @param[out] classIds The id of each object in the bounding box.
    /// @param[out] scores The corresponding confidence scores.
    /// @return FrameworkReturnCode::_SUCCESS if the segmentation succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode segment(SRef<SolAR::datastructure::Image> image,
                                        std::vector<SolAR::datastructure::Rectanglei>& boxes,
                                        std::vector<SRef<SolAR::datastructure::Image>>& masks,
                                        std::vector<uint32_t>& classIds,
                                        std::vector<float>& scores) = 0;

    /// @brief Perform 2D instance segmentation
    /// @param[in] images List of input images (SRef<const Image> is not used here in order to give more freedom to the implementations, e.g. torch::from_blob only accepts a non-const data buffer as input).
    /// @param[out] boxes The bounding boxes of each detected object of each input image.
    /// @param[out] masks The binary masks corresponding to the bounding boxes of each input image. For each mask, regions with a value of 1 correspond to the object, otherwise the background.
    /// @param[out] classIds The id of each object in the bounding box of each input image.
    /// @param[out] scores The corresponding confidence scores of each input image.
    /// @return FrameworkReturnCode::_SUCCESS if the segmentation succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode segment(const std::vector<SRef<SolAR::datastructure::Image>>& images,
                                        std::vector<std::vector<SolAR::datastructure::Rectanglei>>& boxes,
                                        std::vector<std::vector<SRef<SolAR::datastructure::Image>>>& masks,
                                        std::vector<std::vector<uint32_t>>& classIds,
                                        std::vector<std::vector<float>>& scores);
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::segm::IInstanceSegmentation,
                             "402aae34-bbec-43e3-8f36-3f201b6ca6d2",
                             "IInstanceSegmentation",
                             "Interface SolAR::api::segm::IInstanceSegmentation");

#endif // IINSTANCESEGMENTATION_H
