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

namespace SolAR {
namespace api {
namespace segm {


/**
 * @class IPanopticSegmentation
 * @brief <B>Perform 2D Panoptic segmentation.</B>
 * <TT>UUID: 60701300-75e2-4215-a5e1-3a2b0aa3193a</TT>
 */

class XPCF_CLIENTUUID("26e61305-b483-487a-8701-4a9612af5db6") XPCF_SERVERUUID("5c3e0d59-101c-40f8-8efe-0190c4816d81") IPanopticSegmentation :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief IPanopticSegmentation default constructor.
    IPanopticSegmentation() = default;

    ///@brief IPanopticSegmentation default destructor.
    virtual ~IPanopticSegmentation() = default;

    /// @brief Perform 2D Panoptic segmentation
    /// @param[in] image The input image.
    /// @param[out] labelMap The label map corresponding to the input image.
    /// @param[out] boxes The bounding boxes of each detected object.
    /// @param[out] classObjectIds The class id and object id of each bounding box.
    /// @param[out] scores The corresponding confidence scores.
    /// @return FrameworkReturnCode::_SUCCESS if the segmentation succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode segment(const SRef<SolAR::datastructure::Image> image,
                                        SRef<SolAR::datastructure::Image> &labelMap,
                                        std::vector<SolAR::datastructure::Rectanglei> &boxes,
                                        std::vector<std::pair<uint32_t, uint32_t>> &classObjectIds,
                                        std::vector<float> &scores) = 0;
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::segm::IPanopticSegmentation,
                             "60701300-75e2-4215-a5e1-3a2b0aa3193a",
                             "IPanopticSegmentation",
                             "Interface SolAR::api::segm::IPanopticSegmentation");

#endif // IPANOPTICSEGMENTATION_H
