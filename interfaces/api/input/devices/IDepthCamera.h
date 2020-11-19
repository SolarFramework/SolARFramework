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

#ifndef SOLAR_IDEPTHCAMERA_H
#define SOLAR_IDEPTHCAMERA_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/PointCloud.h"
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "api/input/devices/IDevice.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace input {
namespace devices {

/**
 * @class IDepthCamera
 * @brief Specify the IDepthCamera interface class.
 *
 * This class describes the interface of a depth camera capture device.
 */
class IDepthCamera : virtual public IDevice {
public:
    /// @brief Specify the IDepthCamera constructor class
    IDepthCamera() = default;

    /// @brief Specify the IDepthCamera destructor class
    virtual ~IDepthCamera() = default;

    /// @brief Provides the last depth image.
    /// If output parameters are null (nullptr), it means that the implementation, or the requested mode does not provide this feature.
    /// @param img the image captured by the RGBD camera
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getNextDepthFrame(SRef<Image>& img) = 0;

    /// @brief Provides the corresponding 3D point cloud corresponding to last depth image aquiered (getNextDepthFrame())
    /// Should have no effect if the user didn't call getNextDepthFrame beforehand
    /// @param pc the 3D point cloud reconstructed from the depth image. Points coordinates are defined according to the RGBD camera coordinate system.
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getPointCloud(SRef<PointCloud>& pc) = 0;

    /// @brief Set the depth image resolution of the acquisition device
    virtual FrameworkReturnCode setDepthResolution(Sizei resolution) = 0;

    /// @brief Set the intrinsic parameters of the depth camera
    virtual FrameworkReturnCode setIntrinsicDepthParameters(const CamCalibration & intrinsic_parameters) =0;

    /// @brief Set the distortion intrinsic parameters of the depth camera
    virtual FrameworkReturnCode setDistortionDepthParameters(const CamDistortion & distortion_parameters) =0;

    /// @brief Get the image resolution of the depth acquisition device
    virtual Sizei getDepthResolution() = 0;

	/// @brief Get the min acquisition distance of the device
	virtual float getDepthMinDistance() = 0;

    /// @return Return the intrinsic depth camera parameters
    virtual const CamCalibration& getIntrinsicsDepthParameters() const = 0;

    /// @return Return the distortion depth camera lens parameters
    virtual const CamDistortion& getDistortionDepthParameters() const = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::IDepthCamera,
                             "6dfcb3c7-3432-418b-8f69-e66df55bbb67",
                             "IDepthCamera",
                             "Interface for Depth camera");

#endif // SOLAR_IDEPTHCAMERA_H
