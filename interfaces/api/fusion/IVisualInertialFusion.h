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

#ifndef SOLAR_IVISUALINERTIALFUSION_H
#define SOLAR_IVISUALINERTIALFUSION_H

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/MathDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace fusion {

// TODO move into datastructure
struct InertialData {
    std::chrono::high_resolution_clock::time_point timestamp;

    Vector3f accelData;
    Vector3f gyroData;
    Vector3f magData;
};

// TODO move into datastructure
// TODO remove isPoseValid
struct VisionData {
    std::chrono::high_resolution_clock::time_point timestamp;

    Transform3Df pose;
    bool isPoseValid;
};

/**
 * @class IVisualInertialFusion
 * @brief Specify the IVisualInertialFusion interface class.
 *
 * This class provides a fusion method to process inputs from both visual and inertial sensors.
 */
class IVisualInertialFusion : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IVisualInertialFusion default constructor
    IVisualInertialFusion() = default;

    /// @brief IVisualInertialFusion default destructor
    virtual ~IVisualInertialFusion() = default;

    /// @brief Initialize the fusion process with an initial pose
    /// @param[in] initialVisionData the initial pose
    virtual void init(VisionData & initialVisionData) = 0;

    /// @brief Add inertial data to be processed
    /// @param[in] inertialData the timestamped inertial data
    virtual void addInertialData(InertialData & inertialData) = 0;

    /// @brief Add vision data to be processed
    /// @param[in] visionData the timestamped vision data
    virtual void addVisionData(VisionData & visionData) = 0;

    /// @brief Carry out one step of the fusion process to estimate a pose
    /// @param[out] outputData the estimated pose
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR
    virtual FrameworkReturnCode process(Transform3Df & outputData) = 0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::fusion::IVisualInertialFusion,
                         "3efaa1c6-85e4-11e8-adc0-fa7ae01bbebc",
                         "SolAR::api::fusion::IVisualInertialFusion Interface");

#endif // SOLAR_IVISUALINERTIALFUSION_H

