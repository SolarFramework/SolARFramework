#ifndef SOLAR_IARDEVICE_H
#define SOLAR_IARDEVICE_H

#include "api/input/devices/IDevice.h"
#include "core/Messages.h"
#include "datastructure/Image.h"
#include "datastructure/CameraDefinitions.h"
#include <xpcf/core/helpers.h>
#include <chrono>

namespace SolAR {
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
class XPCF_IGNORE IARDevice :
    virtual public IDevice {
public:
    /// @brief Specify the IARDevice constructor class
	IARDevice() = default;

    /// @brief Specify the IARDevice destructor class
    virtual ~IARDevice() = default;

	/// @brief Retrieve a set of images and their associated poses from the sensors as well as timestamp.
    /// @param[out] images the captured images.
    /// @param[out] poses the associated poses.
    /// @param[out] timestamp the timestamp.
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getData(std::vector<SRef<SolAR::datastructure::Image>> & images,
                                        std::vector<SolAR::datastructure::Transform3Df> & poses,
                                        std::chrono::system_clock::time_point &timestamp) = 0;

	/// @brief Get parameters of a camera rig
	/// @return the camera rig parameters
    virtual const SolAR::datastructure::CameraRigParameters & getCameraParameters() const = 0;
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
