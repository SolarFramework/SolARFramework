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

#ifndef SOLAR_IMASKOVERLAY_H
#define SOLAR_IMASKOVERLAY_H

#include "xpcf/api/IComponentIntrospect.h"
#include <xpcf/core/helpers.h>
#include "datastructure/Image.h"
#include "datastructure/GeometryDefinitions.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace display {

/**
 * @class IMaskOverlay
 * @brief <B>Draws masks on top of an image.</B>
 * <TT>UUID: 35a2454a-cb09-44ac-b2ce-0b0732175f94</TT>
 */

class XPCF_CLIENTUUID("10d2d826-714e-4eb9-91d4-9c577585ddfe") XPCF_SERVERUUID("86974141-74a8-40a2-8150-c20eda855ed4") IMaskOverlay :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IMaskOverlay default constructor
    IMaskOverlay() = default;

    /// @brief IMaskOverlay default destructor
    virtual ~IMaskOverlay() = default;

    /// @brief Draw masks on an image.
    /// @param[in,out] image The image on which the masks will be drawn.
    /// @param[in] boxes The bounding boxes of each detected object.
    /// @param[in] masks The binary masks corresponding to the bounding boxes. For each mask, regions with a value of 1 correspond to the object, otherwise the background.
    /// @param[in] classIds The id of each object in the bounding box.
    /// @param[in] scores The corresponding confidence scores.
    /// @return FrameworkReturnCode::_SUCCESS if the draw succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode draw(SRef<SolAR::datastructure::Image> image,
                                     const std::vector<SolAR::datastructure::Rectanglei> &boxes,
                                     const std::vector<SRef<SolAR::datastructure::Image>> &masks,
                                     const std::vector<uint32_t> &classIds,
                                     const std::vector<float> &scores) = 0;

    /// @brief Draw masks on an image.
    /// @param[in,out] image The image on which the masks will be drawn.
    /// @param[in] mask The mask has same size as the input image, in which the value of each pixel is corresponding to the class id.
    /// @return FrameworkReturnCode::_SUCCESS if the draw succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode draw(SRef<SolAR::datastructure::Image> image,
                                     const SRef<SolAR::datastructure::Image> mask) = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::display::IMaskOverlay,
                             "35a2454a-cb09-44ac-b2ce-0b0732175f94",
                             "IMaskOverlay",
                             "SolAR::IMaskOverlay interface")

#endif // SOLAR_IMASKOVERLAY_H
