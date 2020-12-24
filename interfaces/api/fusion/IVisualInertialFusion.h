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

#include "core/Log.h"
#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/MathDefinitions.h"

namespace SolAR {
namespace api {
namespace fusion {

// TODO move into datastructure
struct InertialData {
    std::chrono::high_resolution_clock::time_point timestamp;

    datastructure::Vector3f accelData;
    datastructure::Vector3f gyroData;
    datastructure::Vector3f magData;
};

// TODO move into datastructure
// TODO remove isPoseValid
struct VisionData {
    std::chrono::high_resolution_clock::time_point timestamp;

    datastructure::Transform3Df pose;
    bool isPoseValid;
};

/**
 * @class IVisualInertialFusion
 * @brief <B>Fuses data captured by inertial sensors with the pose estimated from visual sensors.</B>
 * <TT>UUID: 3efaa1c6-85e4-11e8-adc0-fa7ae01bbebc</TT>
 *
 * This class provides a fusion method to process inputs from both visual and inertial sensors.
 */
class IVisualInertialFusion : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IVisualInertialFusion default constructor
    IVisualInertialFusion() = default;

    /// @brief IVisualInertialFusion default destructor
    virtual ~IVisualInertialFusion() = default;

    /// @brief Initialize the fusion process with an initial pose
    /// @param[in] initialVisionData the initial pose
    virtual void init(const VisionData & initialVisionData) = 0;

    /// @brief Add inertial data to be processed
    /// @param[in] inertialData the timestamped inertial data
    virtual void addInertialData(const InertialData & inertialData) = 0;

    /// @brief Add vision data to be processed
    /// @param[in] visionData the timestamped vision data
    virtual void addVisionData(const VisionData & visionData) = 0;

    /// @brief Carry out one step of the fusion process to estimate a pose
    /// @param[out] outputData the estimated pose
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR
    virtual FrameworkReturnCode process(datastructure::Transform3Df & outputData) = 0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::fusion::IVisualInertialFusion,
                         "3efaa1c6-85e4-11e8-adc0-fa7ae01bbebc",
                         "IVisualInertialFusion",
                         "SolAR::api::fusion::IVisualInertialFusion Interface");

namespace boost { namespace serialization {

template<class Archive>
inline void serialize(Archive & ar,
                      SolAR::api::fusion::InertialData & data,
                      const unsigned int version)
{
  ar & boost::serialization::make_binary_object(&data.timestamp, sizeof(data.timestamp));
  ar & data.accelData;
  ar & data.gyroData;
  ar & data.magData;
}

template<class Archive>
inline void serialize(Archive & ar,
                      SolAR::api::fusion::VisionData & data,
                      const unsigned int version)
{
  ar & boost::serialization::make_binary_object(&data.timestamp, sizeof(data.timestamp));
  ar & data.pose;
  ar & data.isPoseValid;
}

}}

#endif // SOLAR_IVISUALINERTIALFUSION_H

