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
using namespace datastructure;
namespace api {
namespace storage {

/**
 * @class IKeyframesManager
 * @brief Allows to store a set of keyframes. This storage component can be accessed by processing components to share persistent data.

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
    virtual FrameworkReturnCode addKeyframe(const SRef<Keyframe>& keyframe) = 0;

	/// @brief This method allow to add a frame to the key frame manager component
	/// @param[in] frame the frame to add to the set of persistent keyframes
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode addKeyframe(const Keyframe &keyframe) = 0;

	/// @brief This method allows to get a keyframe by its id
	/// @param[in] id of the keyframe to get
	/// @param[out] a keyframe stored in the keyframes manager
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode getKeyframe(uint32_t id, SRef<Keyframe>& keyframe) = 0;

	/// @brief This method allows to get a set of keyframes by their ids
	/// @param[in] a vector of ids of the keyframes to get
	/// @param[out] a vector of keyframes stored in the keyframe manager
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode getKeyframes(std::vector<uint32_t> &ids, std::vector<SRef<Keyframe>>& keyframes) = 0;

	/// @brief This method allows to get all keyframes
	/// @param[out] the set of keyframes
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode getAllKeyframes(std::vector<SRef<Keyframe>>& keyframes) = 0;

	/// @brief This method allow to suppress a keyframe by its id
	/// @param[in] id of the keyframe to suppress
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode suppressKeyframe(uint32_t id) = 0;

	/// @brief This method allows to get the descriptor type used to extract descriptor for each keyframe
	/// @return Descriptor type
	virtual DescriptorType getDescriptorType() = 0;

	/// @brief This method allows to set the descriptor type used to extract descriptor for each keyframe
	/// @return Descriptor type
	virtual FrameworkReturnCode setDescriptorType(DescriptorType type) = 0;

	/// @brief This method allows to know if a keyframe is already stored in the component
	/// @param[in] Id of this keyframe
	/// @return true if exist, else false
	virtual bool isExistKeyframe(uint32_t id) = 0;

	/// @brief This method allows to get the number of keyframes stored in the point cloud
	/// @return The number of keyframes
	virtual int getNbKeyframes() = 0;

	/// @brief This method allows to save the keyframes to the external file
	/// @param[out] the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode saveToFile(std::string file) = 0;

	/// @brief This method allows to load the keyframes from the external file
	/// @param[in] the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode loadFromFile(std::string file) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IKeyframesManager,
                             "2c147595-6c74-4f69-b63d-91e162c311ed",
                             "IKeyframesManager",
                             "A component interface for storing a set of persistent keyframes accesisble by processing components.");


#endif //SOLAR_IKEYFRAMESMANAGER_H

