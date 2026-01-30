/**
 * @copyright Copyright (c) 2026 B-com http://www.b-com.com/
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

#ifndef SOLAR_IKEYFRAMELOADER_H
#define SOLAR_IKEYFRAMELOADER_H

#include "datastructure/CameraParametersCollection.h"
#include "datastructure/KeyframeCollection.h"
#include <optional>
#include <xpcf/api/IComponentIntrospect.h>

namespace SolAR {
namespace api {
namespace input {
namespace files {

/**
 * @enum keyframe file type
*/
enum class KeyframeFileType {
    TDF, /**< TDF format */
    UNDEFINED = 1000,
};

/// @brief Return the text definition (string) of a KeyframeFileType object
/// @param[in] keyframeFileType the keyframe file type
/// @return the text definition (string)
static std::string toString(const KeyframeFileType& keyframeFileType)
{
    switch (keyframeFileType) {
        case KeyframeFileType::TDF:
            return "TDF";
        case KeyframeFileType::UNDEFINED:
            return "UNDEFINED";
        default:
            return "Unknown value";
    }
}

/// @brief Return the KeyframeFileType object from a text definition (string)
/// @param[in] textDefinition the text definition (string)
/// @return the keyframe file type
static std::optional<KeyframeFileType> parseKeyframeFileType(const std::string& textDefinition)
{
    if (textDefinition == "TDF") 
        return KeyframeFileType::TDF;
    if (textDefinition == "UNDEFINED") 
        return KeyframeFileType::UNDEFINED;
    LOG_ERROR("Unknown keyframe file type: {}", textDefinition);
    return {};
}

/**
 * @class IKeyframeLoader
 * @brief <B>Load a keyframe collection from file.</B>
 * <TT>UUID: 2d1d125c-6bd2-4e2c-af76-f58910cb7791</TT>
 *
 */
class XPCF_IGNORE IKeyframeLoader : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief default constructor
    IKeyframeLoader() = default;

    /// @brief default destructor
    virtual ~IKeyframeLoader() = default;

    /// @brief Load a keyframe collection from file
    /// @param[out] keyframeCollection the loaded keyframe collection (camera ID is set to 0)
    /// @return FrameworkReturnCode::_SUCCESS if load succeeded, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode load(SRef<SolAR::datastructure::KeyframeCollection>& keyframeCollection) = 0;

    /// @brief Load a keyframe collection and a camera parameters collection from file
    /// @param[out] keyframeCollection the loaded keyframe collection
    /// @param[out] cameraParametersCollection the loaded camera parameters collection
    /// @return FrameworkReturnCode::_SUCCESS if load succeeded, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode load(SRef<SolAR::datastructure::KeyframeCollection>& keyframeCollection,
                                     SRef<SolAR::datastructure::CameraParametersCollection>& cameraParametersCollection) = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::files::IKeyframeLoader,
                             "2d1d125c-6bd2-4e2c-af76-f58910cb7791",
                             "IKeyframeLoader",
                             "Load a keyframe collection from file");


#endif // SOLAR_IKEYFRAMELOADER_H
