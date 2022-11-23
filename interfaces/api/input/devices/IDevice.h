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


#ifndef IDEVICE_H
#define IDEVICE_H

#include <xpcf/api/IComponentIntrospect.h>
#include <core/Messages.h>

namespace SolAR {
namespace api {
namespace input {
namespace devices {

/**
 * @class IDevice
 * @brief <B>Manage any kind of device.</B>
 * <TT>UUID: d73c7b34-f6af-48f3-b65d-37a047929f4b</TT>
 *
 * This class describes the interface of a capture device.
 */
class [[xpcf::clientUUID("abd028ed-44a2-4ac0-831b-e0e9b939031c")]] [[xpcf::serverUUID("f20a4533-57e9-4a76-893a-3c031e267409")]] IDevice:
    virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    /// @brief Specify the IDevice constructor class
    IDevice() = default;

    /// @brief Specify the IDevice destructor class
    virtual ~IDevice() override = default;

    /// @brief Start the acquisition device referenced by its device_id
    /// @return FrameworkReturnCode::_SUCCESS if sucessful, eiher FrameworkRetunrnCode::_ERROR_.
    virtual FrameworkReturnCode start() = 0;

    /// @brief Stop the acquisition device
    /// @return FrameworkReturnCode::_SUCCESS if sucessful, eiher FrameworkRetunrnCode::_ERROR_.
    virtual FrameworkReturnCode stop() = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::IDevice,
                             "d73c7b34-f6af-48f3-b65d-37a047929f4b",
                             "IDevice",
                             "IDevice interface description");

#endif // IDEVICE_H
