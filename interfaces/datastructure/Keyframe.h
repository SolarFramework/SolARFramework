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
#include <utility>

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

    explicit Keyframe(const SRef<Frame>& frame) : Frame(frame), m_idx(m_keyframeIdx++) {}

    Keyframe(const std::vector<Keypoint> & keypoints,
             SRef<DescriptorBuffer> descriptors,
             SRef<Image> view,
             SRef<Keyframe> refKeyframe,
             const Transform3Df& pose = Transform3Df::Identity()): Frame(keypoints, std::move(descriptors), std::move(view), std::move(refKeyframe), pose), m_idx(m_keyframeIdx++){}

    Keyframe(const std::vector<Keypoint> & keypoints,
             SRef<DescriptorBuffer> descriptors,
             SRef<Image> view,
             const Transform3Df& pose = Transform3Df::Identity()): Frame(keypoints, std::move(descriptors), std::move(view), pose), m_idx(m_keyframeIdx++){}

    ~Keyframe() = default;

    //void addVisibleMapPoints(const std::vector<SRef<CloudPoint>>& mapPoints);
    void addVisibleMapPoints(const std::map<unsigned int, CloudPoint>& mapPoints);

    const std::map<unsigned int, CloudPoint> & getVisibleMapPoints();

    int m_idx;

private:
    static int m_keyframeIdx;

    // @brief: A map storing the 3D points visibility, where the first element corresponds to the index of the keypoint of the keyframe, and the second element to the corresponding cloudPoint.
    std::map<unsigned int, CloudPoint> m_mapVisibility;
    //std::vector<SRef<CloudPoint>> m_mapPoints;
};

}
}

#endif //SOLAR_POSE_H
