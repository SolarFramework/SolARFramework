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

#ifndef SOLAR_IIMU_H
#define SOLAR_IIMU_H

#include "IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/MathDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace input {
namespace devices {

/**
 * @class IIMU
 * @brief Specify the IIMU interface class.
 *
 * This class describes the interface of an Inertial Measurement Unit capture device.
 */
class IIMU : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IIMU default constructor
    IIMU() = default;

    /// @brief IIMU default destructor
    virtual ~IIMU() = default;

    /// @brief Start the acquisition device
    /// @return FrameworkReturnCode to track sucessful or failing event
    virtual FrameworkReturnCode start() = 0;

    /// @brief Get gyroscope data
    /// @param[in,out] gyroData The vector in which the gyroscope data will be stored (in radian per second)
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getGyroscopeData(Vector3f & gyroData) = 0;

    /// @brief Get accelerometer data
    /// @param[in,out] accelData The vector in which the accelerometer data will be stored (in metre per second squared)
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getAccelerometerData(Vector3f & accelData) = 0;

    /// @brief Get magnetometer data
    /// @param[in,out] magData The vector in which the magnetometer data will be stored (in gauss)
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getMagnetometerData(Vector3f & magData) = 0;

    /// @brief Get gyroscope, accelerometer and magnetometer data
    /// @param[in,out] gyroData The vector in which the gyroscope data will be stored (in radian per second)
    /// @param[in,out] accelData accelData The vector in which the accelerometer data will be stored (in metre per second squared)
    /// @param[in,out] magData The vector in which the magnetometer data will be stored (in gauss)
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getAllSensorsData(Vector3f & gyroData, Vector3f & accelData, Vector3f & magData) = 0;

    /// @brief Get gyroscope sensor availability
    /// @return bool Whether the IMU can produce gyroscope data or not
    virtual bool isGyroscopeAvailable() = 0;

    /// @brief Get accelerometer sensor availability
    /// @return bool Whether the IMU can produce accelerometer data or not
    virtual bool isAccelerometerAvailable() = 0;

    /// @brief Get magnetometer sensor availability
    /// @return bool Whether the IMU can produce magnetometer data or not
    virtual bool isMagnetometerAvailable() = 0;

	 

};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::IIMU,
                         "9940fa48-10cf-11e8-b642-0ed5f89f718b",
                         "SolAR::api::input::devices::IIMU Interface");

#endif // SOLAR_IIMU_H

