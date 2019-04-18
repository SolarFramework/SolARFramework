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

#ifndef SOLAR_IKEYFRAMESSTORAGE_H
#define SOLAR_IKEYFRAMESSTORAGE_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/Keyframe.h"

#include <vector>

namespace SolAR {
using namespace datastructure;
namespace api {
namespace storage {

/**
 * @class IKeyframesStorage
 * @brief Allows to store a set of keyframes. This storage component can be accessed by processing components to share persistent data.

 */

class IKeyframesStorage : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IKeyframesStorage default constructor
    IKeyframesStorage() = default;

    /// @brief IKeyframesStorage default destructor
    virtual ~IKeyframesStorage() = default;

    /// @brief This method allow to add a frame to the key frame storage component
    /// @param[in] frame the frame to add to the set of persistent keyframes
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode AddKeyframe(const SRef<Frame> frame) = 0;

    /// @brief This method allow to suppress a frame to the key frame storage component
    /// @param[in] frame the frame to suppress to the set of persistent keyframes
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode SuppressKeyframe(const SRef<Frame> frame) = 0;

    /// @brief This method allows to get all keyframes stored in the component
    /// @param[out] frames a vector storing all the keyframes
    /// /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode GetAllKeyframes(std::vector<SRef<Frame>>& frames) = 0;

    /// @brief This method allows to know if a keyframe is already stored in the component
    /// @return true if exist, else false
    virtual bool ExistKeyframe(SRef<Frame> frame) = 0;

    /// @brief This method allows to get the number of keyframes stored in the component frame storage component
    /// @return The number of keyframes
    virtual int GetNbKeyframes() = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IKeyframesStorage,
                             "2c147595-6c74-4f69-b63d-91e162c311ed",
                             "IKeyframesStorage",
                             "A component interface for storing a set of persistent keyframes accesisble by processing components.");


#endif //SOLAR_IKEYFRAMESSTORAGE_H

