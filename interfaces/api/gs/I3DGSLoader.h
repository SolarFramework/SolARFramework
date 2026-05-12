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

#ifndef I3DGSLOADER_H
#define I3DGSLOADER_H

#include <xpcf/api/IComponentIntrospect.h>
#include "core/Messages.h"
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace gs {


/**
 * @class I3DGSLOADER
 * @brief <B>Returns a camera pose giving a frame.</B>
 * <TT>UUID: bc05f240-4d34-11f1-acbe-325096b39f47</TT>
 *
 * This class provides a solution to get the pose given a frame.
 */

class XPCF_IGNORE I3DGSLoader :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief I3DGSLoader default constructor.
    I3DGSLoader() = default;

    ///@brief I3DGSLoader default destructor.
    virtual ~I3DGSLoader() = default;

    /// @brief Get the pose of the camera corresponding to the frame.
    /// @param[in] frame: the frame for which we want to retrieve close keyframes.
    /// @param[out] pose: the pose of the camera corresponding to the frame
    /// @return FrameworkReturnCode::_SUCCESS if the retrieve succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode loadData() = 0;
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::gs::I3DGSLoader,
                             "bc05f240-4d34-11f1-acbe-325096b39f47",
                             "I3DGSLoader",
                             "Interface SolAR::api::gs::I3DGSLoader allows to retrieve the pose for a given frame.");

#endif // I3DGSLOADER_H
