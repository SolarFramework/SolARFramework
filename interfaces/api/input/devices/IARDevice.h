#ifndef SOLAR_IARDEVICE_H
#define SOLAR_IARDEVICE_H

#include "api/input/devices/IDevice.h"
#include "core/Messages.h"
#include "datastructure/Image.h"
#include "datastructure/CameraDefinitions.h"
#include <chrono>

namespace SolAR {
using namespace datastructure;
namespace api {
namespace input {
namespace devices {

/**
  * @class IARDevice
  * @brief <B>Retrieve synchronized sensor images and poses from an external device (ie. HoloLens).</B>
  * <TT>UUID: 999085e6-1d11-41a5-8cca-3daf4e02e941 </TT>
  *
  * This class describes the interface for retrieving data from a AR device that provides.
  */
class IARDevice : virtual public IDevice {
public:
    /// @brief Specify the IARDevice constructor class
	IARDevice() = default;

    /// @brief Specify the IARDevice destructor class
    virtual ~IARDevice() = default;

	/// @brief Get number of cameras of the device.
	/// @return the number of cameras.
	virtual int getNbCameras() = 0;

	/// @brief Retrieve a set of images and their associated poses from the sensors as well as timestamp.
	/// @param[out] images: the captured images.
	/// @param[out] poses: the associated poses.
	/// @param[out] timestamp: the timestamp.
	/// @return FrameworkReturnCode to track successful or failing event.
	virtual FrameworkReturnCode getData(std::vector<SRef<Image>> & images, std::vector<Transform3Df> & poses, std::chrono::system_clock::time_point &timestamp) = 0;

	/// @brief Get the distortion and intrinsic camera parameters
	/// @param[in] camera_id: The id of the camera.
	/// @return the camera parameters
	virtual const CameraParameters & getParameters(const int & camera_id) = 0;

	/// @brief Set the distortion and intrinsic camera parameters
	/// @param[in] camera_id: The id of the camera.
	/// @param[in] parameters: the camera parameters.
	virtual void setParameters(const int & camera_id, const CameraParameters & parameters) = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::IARDevice,
                             "999085e6-1d11-41a5-8cca-3daf4e02e941",
                             "IARDevice",
                             "SolAR::IARDevice interface");

#endif // SOLAR_IARDEVICE_H
