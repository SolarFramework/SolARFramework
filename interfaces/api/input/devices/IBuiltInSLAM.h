#ifndef SOLAR_IBUILTINSLAM_H
#define SOLAR_IBUILTINSLAM_H

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/Image.h"
#include "datastructure/CameraDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace input {
namespace devices {

/**
  * @class IBuiltInSLAM
  * @brief <B>Retrieve synchronized sensor images and poses from an external device (ie. HoloLens).</B>
  * <TT>UUID: 999085e6-1d11-41a5-8cca-3daf4e02e941 </TT>
  *
  * This class describes the interface for retrieving data from a device that has a built-in SLAM capability.
  */
class IBuiltInSLAM : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief Specify the IBuiltInSLAM constructor class
    IBuiltInSLAM() = default;

    /// @brief Specify the IBuiltInSLAM destructor class
    virtual ~IBuiltInSLAM() = default;

    /// @brief Start the connection to the device for sensors data streaming.
    /// @return FrameworkReturnCode::_SUCCESS if successful, eiher FrameworkReturnCode::_ERROR_.
    virtual FrameworkReturnCode start() = 0;

    /// @brief Stop the connection to the device.
    /// @return FrameworkReturnCode::_SUCCESS if successful, eiher FrameworkReturnCode::_ERROR_.
    virtual FrameworkReturnCode stop() = 0;

	/// @brief Notify to the server what sensors we want to use, so that they are ready when needed.
	/// @param[in] sensorList The names of the sensors to enable.
	/// @return FrameworkReturnCode to track successful or failing event.
	virtual FrameworkReturnCode EnableSensors(std::vector<std::string> sensorList) = 0;

    /// @brief Fill frames and poses vectors containing latest data from all sensors available on the device.
	/// @param[in,out] frames The vector that will store the frames for each sensor.
	/// @param[in,out] poses The vector that will store the poses for each sensor.
    /// @return FrameworkReturnCode to track successful or failing event.
    virtual FrameworkReturnCode getLastCapture(std::vector<SRef<Image>> & frames, std::vector<PoseMatrix> & poses) = 0;

    /// @brief Retrieve the sensor intrinsic parameters corresponding to the given name.
	/// @param[in] camera_name The name of the sensor.
	/// @param[in,out] camParams The CameraParameters object in which the parameters will be stored.
	/// @return FrameworkReturnCode to track successful or failing event.
	virtual FrameworkReturnCode getIntrinsics(const std::string & camera_name, CameraParameters & camParams) = 0;

	/// @brief Notify the server that we want to start streaming data from sensor <camera_name>.
	/// @param[in] camera_name The name of the sensor.
	/// @return FrameworkReturnCode to track successful or failing event.
	virtual FrameworkReturnCode RequestCapture(const std::string & camera_name) = 0;

	/// @brief Retrieve the frame and its associated pose from the previously requested sensor.
	/// @see RequestCapture
	/// @param[in,out] frame The Image object that will store the sensor frame.
	/// @param[in,out] pose The PoseMatrix object that will store the corresponding pose.
	/// @return FrameworkReturnCode to track successful or failing event.
	virtual FrameworkReturnCode ReadCapture(SRef<Image> & frame, PoseMatrix & pose) = 0;

    /// @brief Whether or not the device is simulated or online.
    /// @return True is the device is online, False is simulated.
    virtual bool isProxy() = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::IBuiltInSLAM,
                             "999085e6-1d11-41a5-8cca-3daf4e02e941",
                             "IBuiltInSLAM",
                             "SolAR::IBuiltInSLAM interface");

#endif // SOLAR_IBUILTINSLAM_H
