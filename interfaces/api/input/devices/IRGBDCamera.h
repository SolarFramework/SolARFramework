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

#ifndef SOLAR_IRGBDCAMERA_H
#define SOLAR_IRGBDCAMERA_H

#include "xpcf/api/IComponentIntrospect.h"
#include "api/input/devices/ICamera.h"
#include "api/input/devices/IDepthCamera.h"
#include "core/Messages.h"
#include "datastructure/MathDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace input {
namespace devices {

/**
 * @class IRGBDCamera
 * @brief Specify the IRGBDCamera interface class.
 *
 * This class describes the interface of a RGBD camera capture device.
 */
class IRGBDCamera : virtual public org::bcom::xpcf::IComponentIntrospect, public ICamera, public IDepthCamera {
public:
    /// @brief Specify the IRGBDCamera constructor class
    IRGBDCamera() = default;

    /// @brief Specify the IRGBDCamera destructor class
    virtual ~IRGBDCamera() = default;

    /// @brief Fill the SRef img buffer with a new RGB image captured by the camera device.
    /// @param img the image captured by the RGBD camera
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getNextImage(SRef<Image> & colorImg) const = 0;

    /// @brief Provides the last depth image and corresponding 3D point cloud.
    /// If output parameters are null (nullptr), it means that the implementation, or the requested mode does not provide this feature.
    /// @param depthImg the image captured by the RGBD camera
    /// @param pc the 3D point cloud reconstructed from the depth image. Points coordinates are defined according to the RGBD camera coordinate system.
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getNextDepthFrame(const SRef<Image>& depthImg, const SRef<PointCloud>& pc) const = 0;

    /// @brief Provides the last color image, depth image, corresponding 3D point cloud, and aligned images (RGB on depth and depth on RGB).
    /// If output parameters are null (nullptr), it means that the implementation, or the requested mode does not provide this feature.
    /// @param colorImg the RGB image captured by the RGBD camera
    /// @param depthImg the depth image captured by the RGBD camera
    /// @param pc the 3D point cloud reconstructed from the depth image. Points coordinates are defined according to the RGBD camera coordinate system.
    /// @param alignedColorImg the RGB image captured by the RGBD camera and aligned on the depth image
    /// @param alignedDepthImg the depth image captured by the RGBD camera and aligned on the color image
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getNextRGBDFrame(const SRef<Image>& colorImg, const SRef<Image>& depthImg, const SRef<PointCloud>& pc, const SRef<Image>& alignedColorImg, const SRef<Image>& alignedDepthImg) const = 0;

    /// @brief Start the acquisition device reference by its device_id
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode start()=0;

    /// @brief Set the color image resolution of the acquisition device
    virtual void setResolution(Sizei resolution) = 0;

    /// @brief Set the depth image resolution of the acquisition device
    virtual void setDepthResolution(Sizei resolution) = 0;

    /// @brief Set the intrinsic RGB camera parameters
    virtual void setIntrinsicParameters(const CamCalibration & intrinsic_parameters) =0;

    /// @brief Set the intrinsic parameters of the depth camera
    virtual void setIntrinsicDepthParameters(const CamCalibration & intrinsic_parameters) =0;

    /// @brief Set the distorsion intrinsic parameters of the RGB camera
    virtual void setDistorsionParameters(const CamDistortion & distorsion_parameters) =0;

    /// @brief Set the distorsion intrinsic parameters of the depth camera
    virtual void setDistorsionDepthParameters(const CamDistortion & distorsion_parameters) =0;

    /// @brief Get the image resolution of the RGB acquisition device
    virtual Sizei getResolution() = 0;

    /// @brief Get the image resolution of the depth acquisition device
    virtual Sizei getDepthResolution() = 0;

    /// @return Return the intrinsic RGB camera parameters
    virtual const CamCalibration& getIntrinsicsParameters() const = 0;

    /// @return Return the intrinsic depth camera parameters
    virtual const CamCalibration& getIntrinsicsDepthParameters() const = 0;

    /// @return Return the distorsion RGB camera lens parameters
    virtual const CamDistortion& getDistorsionParameters() const = 0;

    /// @return Return the distorsion depth camera lens parameters
    virtual const CamDistortion& getDistorsionDepthParameters() const = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::IRGBDCamera,
                             "5bf56174-94fd-4256-8eb7-b653ea3b8c34",
                             "IRGBDCamera",
                             "Interface for RGBD camera");


#endif // SOLAR_IRGBDCAMERA_H
