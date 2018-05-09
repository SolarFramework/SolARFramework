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
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/Pose.h"
#include "datastructure/DescriptorBuffer.h"

#include <memory>
namespace SolAR {
namespace datastructure {

/**
 * @class Keyframe
 * @brief Specifies the Keyframe class.
 *
 * This class provides Keyframe definition for slam utilities.
 */
class SOLARFRAMEWORK_API Keyframe {
    ///
    /// @brief ~Keyframe
    public:
    Keyframe();
    ~Keyframe();
    ///
    ///@brief constructs a Pose from a rotation matrix of size 3x3 and a translation vector of size 3
    /// @param rotation_matrix3x3, rotation matrix of size 3x3
    /// @param translation vector, translation vector of size 3
    Keyframe(SRef<Image>view,
             SRef<DescriptorBuffer>desc,
             int idx,
             Transform3Df&pose,
             std::vector<SRef<Keypoint>>kpts);


    void addVisibleMapPoints(const std::vector<SRef<CloudPoint>>  & mapPoints) ;

    std::vector<SRef<CloudPoint>> & getVisibleMapPoints() ; // give a pointer?


    SRef<DescriptorBuffer> getDescriptors() ;

    std::vector<SRef<Keypoint>> getKeyPoints() ;


    SRef<Image> m_view;
    int m_idx;
    Transform3Df m_pose;

    private:    
    SRef<DescriptorBuffer> m_descriptor;
    std::vector<SRef<Keypoint>> m_keypoints;
    std::vector<SRef<CloudPoint>> m_mapPoints ;

};

}
}

#endif //SOLAR_POSE_H
