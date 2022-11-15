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

#ifndef SOLAR_I2DTRACKABLESDETECTOR_H
#define SOLAR_I2DTRACKABLESDETECTOR_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Trackable.h"
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Image.h"

namespace SolAR {
namespace api {
namespace features {
/**
 * @class I2DTrackablesDetector
 * @brief <B>Detect a set of given 2D trackables in an image.</B>
 * <TT>UUID: 607d0b0d-766d-4ff2-9b72-45c555f9726f</TT>
 */
class [[xpcf::clientUUID("b62759a5-069a-40b0-846e-71f6adc9cb5e")]] [[xpcf::serverUUID("b73bdd5a-aecb-4e63-b40f-cd05fa7b8490")]] I2DTrackablesDetector :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief I2DTrackablesDetector default constructor.
    I2DTrackablesDetector() = default;

    ///@brief I2DTrackablesDetector default destructor.
    virtual ~I2DTrackablesDetector() = default;

    /// @brief this method is used to set the set of 2D trackables.
    /// @param[in] trackables the set of 2D trackables.
    virtual FrameworkReturnCode setTrackables(const std::vector<SRef<SolAR::datastructure::Trackable>> trackables) =0;

    /// @brief Detect a set of trackables.
    /// @param[in] image input image.
    /// @param[out] corners a set of detected corners corresponding to the trackables (each trackable has a set of 4 corners).
    /// @return FrameworkReturnCode::_SUCCESS if the detection succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode detect(const SRef<SolAR::datastructure::Image> image,
                                       std::vector<std::vector<SolAR::datastructure::Point2Df>> & corners) =0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::I2DTrackablesDetector,
                             "607d0b0d-766d-4ff2-9b72-45c555f9726f",
                             "I2DTrackablesDetector",
                             "SolAR::api::features::I2DTrackablesDetector");
                            
#endif // SOLAR_I2DTRACKABLESDETECTOR_H
