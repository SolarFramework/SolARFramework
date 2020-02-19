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

    /// @brief Fill frames and poses vectors containing latest sensors data from the device.
    /// @return FrameworkReturnCode to track successful or failing event.
    virtual FrameworkReturnCode getLastCapture(std::vector<SRef<Image>> & frames, std::vector<PoseMatrix> & poses) = 0;

    /// @brief Retrieve the sensors intrinsic parameters. (assuming all sensors are cameras, ie no IMU)
	/// @return FrameworkReturnCode to track successful or failing event.
	virtual FrameworkReturnCode getIntrinsics(const std::string & camera_name, CameraParameters & camParams) = 0;

	virtual FrameworkReturnCode RequestCapture(const std::string & camera_name) = 0;

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
