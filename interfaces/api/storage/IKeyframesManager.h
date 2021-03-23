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

#ifndef SOLAR_IKEYFRAMESMANAGER_H
#define SOLAR_IKEYFRAMESMANAGER_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/Keyframe.h"

#include <vector>

namespace SolAR {
namespace api {
namespace storage {

/**
 * @class IKeyframesManager
 * @brief Allows to store a set of keyframes. This storage component can be accessed by processing components to share persistent data.
 * <TT>UUID: 2c147595-6c74-4f69-b63d-91e162c311ed</TT>
 */

class IKeyframesManager : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IKeyframesStorage default constructor
    IKeyframesManager() = default;

    /// @brief IKeyframesStorage default destructor
    virtual ~IKeyframesManager() = default;

    /// @brief This method allow to add a frame to the keyframe manager component
    /// @param[in] frame the frame to add to the set of persistent keyframes
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode addKeyframe(const SRef<SolAR::datastructure::Keyframe> keyframe) = 0;

	/// @brief This method allow to add a frame to the key frame manager component
	/// @param[in] frame the frame to add to the set of persistent keyframes
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode addKeyframe(const SolAR::datastructure::Keyframe & keyframe) = 0;

	/// @brief This method allows to get a keyframe by its id
	/// @param[in] id id of the keyframe to get
	/// @param[out] keyframe a keyframe stored in the keyframes manager
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getKeyframe(const uint32_t id, SRef<SolAR::datastructure::Keyframe> & keyframe) const = 0;

	/// @brief This method allows to get a set of keyframes by their ids
	/// @param[in] ids a vector of ids of the keyframes to get
	/// @param[out] keyframes a vector of keyframes stored in the keyframe manager
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getKeyframes(const std::vector<uint32_t> & ids, std::vector<SRef<SolAR::datastructure::Keyframe>> & keyframes) const = 0;

	/// @brief This method allows to get all keyframes
	/// @param[out] keyframes the set of keyframes
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getAllKeyframes(std::vector<SRef<SolAR::datastructure::Keyframe>> & keyframes) const = 0;

	/// @brief This method allow to suppress a keyframe by its id
	/// @param[in] id id of the keyframe to suppress
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode suppressKeyframe(const uint32_t id) = 0;

	/// @brief This method allows to get the descriptor type used to extract descriptor for each keyframe
	/// @return Descriptor type
    virtual SolAR::datastructure::DescriptorType getDescriptorType() const = 0;

	/// @brief This method allows to set the descriptor type used to extract descriptor for each keyframe
	/// @param[in] type the descriptor type
	/// @return @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode setDescriptorType(const SolAR::datastructure::DescriptorType & type) = 0;

	/// @brief This method allows to know if a keyframe is already stored in the component
	/// @param[in] id id of this keyframe
	/// @return true if exist, else false
    virtual bool isExistKeyframe(const uint32_t id) const = 0;

	/// @brief This method allows to get the number of keyframes stored in the point cloud
	/// @return The number of keyframes
    virtual int getNbKeyframes() const = 0;

	/// @brief This method allows to save the keyframes to the external file
	/// @param[in] file the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode saveToFile(const std::string & file) const = 0;

	/// @brief This method allows to load the keyframes from the external file
	/// @param[in] file the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode loadFromFile(const std::string & file) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IKeyframesManager,
                             "2c147595-6c74-4f69-b63d-91e162c311ed",
                             "IKeyframesManager",
                             "A component interface for storing a set of persistent keyframes accesisble by processing components.");


#endif //SOLAR_IKEYFRAMESMANAGER_H

