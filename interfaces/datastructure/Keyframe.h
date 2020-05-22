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

#ifndef SOLAR_KEYFRAME_H
#define SOLAR_KEYFRAME_H

#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "Frame.h"
#include <map>

namespace SolAR {
namespace datastructure {

/**
 * @class Keyframe
 * @brief <B>A keyframe</B>.
 *
 * This class provides Keyframe definition.
 */
class SOLARFRAMEWORK_API Keyframe : public Frame, public PrimitiveInformation {
public:
    Keyframe() = default;

    Keyframe(SRef<Frame> frame) : Frame(frame) {};

    Keyframe(const std::vector<Keypoint> & keypoints,
             SRef<DescriptorBuffer> descriptors,
             SRef<Image> view,
             SRef<Keyframe> refKeyframe,
             Transform3Df pose = Transform3Df::Identity()): Frame(keypoints, descriptors, view, refKeyframe, pose){};

    Keyframe(const std::vector<Keypoint> & keypoints,
             SRef<DescriptorBuffer> descriptors,
             SRef<Image> view,
             Transform3Df pose = Transform3Df::Identity()): Frame(keypoints, descriptors, view, pose){};

    ~Keyframe() = default;	

	///
	/// @brief Return keyframe id
	///
	const uint32_t& getId() const;

	///
	/// @brief Set keyframe id
	/// @param[in] id_keyframe: keyframe id
	///
	void setId(const uint32_t& id_keyframe);

private:
    uint32_t	m_id;
};

}
}

#endif //SOLAR_POSE_H
