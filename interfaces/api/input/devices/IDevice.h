#ifndef IDEVICE_H
#define IDEVICE_H


#include <xpcf/api/IComponentIntrospect.h>
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace input {
namespace devices {

/**
 * @class IDevice
 * @brief <B>Manage any kind of device.</B>
 * <TT>UUID: d73c7b34-f6af-48f3-b65d-37a047929f4b</TT>
 *
 * This class describes the interface of a camera capture device.
 */
class IDevice: virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    virtual ~IDevice() override = default;

    /// @brief Start the acquisition device referenced by its device_id
    /// @return FrameworkReturnCode::_SUCCESS if sucessful, eiher FrameworkRetunrnCode::_ERROR_.
    virtual FrameworkReturnCode start()=0;

    /// @brief Stop the acquisition device
    /// @return FrameworkReturnCode::_SUCCESS if sucessful, eiher FrameworkRetunrnCode::_ERROR_.
    virtual FrameworkReturnCode stop()=0;
};


}
}
}
}


template <> struct org::bcom::xpcf::InterfaceTraits<SolAR::api::input::devices::IDevice>
{
    static constexpr const char * UUID = "{d73c7b34-f6af-48f3-b65d-37a047929f4b}";
    static constexpr const char * NAME = "IDevice";
    static constexpr const char * DESCRIPTION = "IDevice interface description";
};


#endif // IDEVICE_H
