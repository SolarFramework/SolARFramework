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
class SOLARFRAMEWORK_API Keyframe : public Frame {
    ///
    /// @brief ~Keyframe
    public:

    Keyframe(SRef<Frame> frame) : Frame(frame), m_idx(m_keyframeIdx++) {};

    Keyframe(const std::vector<Keypoint> & keypoints,
             SRef<DescriptorBuffer> descriptors,
             SRef<Image> view,
             SRef<Keyframe> refKeyframe,
             Transform3Df pose = Transform3Df::Identity()): Frame(keypoints, descriptors, view, refKeyframe, pose), m_idx(m_keyframeIdx++){};

    Keyframe(const std::vector<Keypoint> & keypoints,
             SRef<DescriptorBuffer> descriptors,
             SRef<Image> view,
             Transform3Df pose = Transform3Df::Identity()): Frame(keypoints, descriptors, view, pose), m_idx(m_keyframeIdx++){};

    ~Keyframe() = default;	

	// @brief: Get all neighbor keyframes
	const std::map<unsigned int, unsigned int> & getNeighborKeyframes();

	// @brief: Get best neighbor keyframes
	// return id of the best neighbors
	std::vector<unsigned int> getBestNeighborKeyframes(int nbKeyframes);

	// @brief: Add a neighbor keyframe with the weight
	void addNeighborKeyframe(unsigned int idxKeyframe, unsigned int weight);

    static void resetFirstIdKeyframe(){ m_keyframeIdx = 0; };

    int m_idx;

private:
    static int m_keyframeIdx;    

	// @brief: A map storing the neighboring keyframes, where the first element corresponds to the index of a neighboring keyframe, and the second element to the corresponding the weight which is number of common points visble between two keyframes.
	std::map<unsigned int, unsigned int> m_neighborKeyframes;

	std::mutex m_mutexNeighbor;
};

}
}

#endif //SOLAR_POSE_H
