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
#include "datastructure/CameraDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace input {
namespace devices {

/**
 * @class ICamera
 * @brief <B>Grabs images captured in real-time by a video camera.</B>
 * <TT>UUID: 5ddc7df0-8377-437f-9c81-3643f7676a5b</TT>
 *
 * This class describes the interface of a camera capture device.
 */
class ICamera : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief Specify the ICamera constructor class
    ICamera() = default;

    /// @brief Specify the ICamera destructor class
    virtual ~ICamera() = default;

    /// @brief Fill the SRef img buffer with a new image captured by the camera device.
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getNextImage(SRef<Image> & img) = 0;
    
    /// @brief Start the acquisition device referenced by its device_id
    /// @return FrameworkReturnCode::_SUCCESS if sucessful, eiher FrameworkRetunrnCode::_ERROR_.
    virtual FrameworkReturnCode start()=0;

    /// @brief Stop the acquisition device
    /// @return FrameworkReturnCode::_SUCCESS if sucessful, eiher FrameworkRetunrnCode::_ERROR_.
    virtual FrameworkReturnCode stop()=0;
        
    /// @brief Set the acquisition device image resolution
    virtual void setResolution(const Sizei & resolution) = 0;

    /// @brief Set the intrinsic camera parameters
    virtual void setIntrinsicParameters(const CamCalibration & intrinsic_parameters) =0;
    
    /// @brief Set the distorsion intrinsic camera parameters
    virtual void setDistorsionParameters(const CamDistortion & distorsion_parameters) =0;

    /// @brief Set the distorsion intrinsic camera parameters
    virtual void setParameters(const CameraParameters & parameters) =0;

    /// @brief Get the acquisition device image resolution
    virtual Sizei getResolution() = 0;

    /// @return Return the intrinsic camera parameters
    virtual const CamCalibration & getIntrinsicsParameters() = 0;

    /// @return Return the camera parameters
    virtual const CameraParameters & getParameters() = 0;
    
    /// @return Return the distorsion camera lens parameters
    virtual const CamDistortion & getDistorsionParameters() = 0;

    //virtual params getCameraIntrinsics() = 0;
    //Frame : image + timestamp image + depth + timestamp depth ...

};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::ICamera,
                             "5ddc7df0-8377-437f-9c81-3643f7676a5b",
                             "ICamera",
                             "SolAR::ICamera interface");

#endif // SOLAR_ICAMERA_H

