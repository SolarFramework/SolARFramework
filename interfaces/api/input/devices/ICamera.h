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

#ifndef SOLAR_ICAMERA_H
#define SOLAR_ICAMERA_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "core/Messages.h"
#include "datastructure/MathDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace input {
namespace devices {

/**
 * @class ICamera
 * @brief Specify the ICamera interface class.
 *
 * This class describes the interface of a camera capture device.
 */
class ICamera : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief Specify the ICamera constructor class
    ICamera() = default;

    /// @brief Specify the ICamera destructor class
    virtual ~ICamera() = default;

    /// @brief Fill the SRef img buffer with a new image captured by the camera device.
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getNextImage(SRef<Image> & img) const = 0;
    
    /// @brief Start the acquisition device reference by its device_id
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode start()=0;
        
    /// @brief Set the acquisition device image resolution
    virtual void setResolution(Sizei resolution) = 0;

    /// @brief Set the intrinsic camera parameters
    virtual void setIntrinsicParameters(const CamCalibration & intrinsic_parameters) =0;
    
    /// @brief Set the distorsion intrinsic camera parameters
    virtual void setDistorsionParameters(const CamDistortion & distorsion_parameters) =0;

    /// @brief Get the acquisition device image resolution
    virtual Sizei getResolution() = 0;

    /// @return Return the intrinsic camera parameters
    virtual const CamCalibration& getIntrinsicsParameters() const = 0;
    
    /// @return Return the distorsion camera lens parameters
    virtual const CamDistortion& getDistorsionParameters() const = 0;

    //virtual params getCameraIntrinsics() = 0;
    //Frame : image + timestamp image + depth + timestamp depth ...

};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::ICamera,
                             "5DDC7DF0-8377-437F-9C81-3643F7676A5B",
                             "ICamera",
                             "SolAR::ICamera interface");

#endif // SOLAR_ICAMERA_H

