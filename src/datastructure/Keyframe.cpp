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

#include "datastructure/Keyframe.h"
#include <cstddef> //TO DO: remove with a complete implementation

namespace SolAR {
namespace datastructure {
        Keyframe::Keyframe(){

        }

        Keyframe::Keyframe(SRef<Image>view,
                 SRef<DescriptorBuffer>desc,
                 int idx,
                 Transform3Df&pose,
                 std::vector<SRef<Keypoint>>kpts): m_view(view),
                                                   m_descriptor(desc),
                                                   m_idx(idx),
                                                   m_pose(pose),
                                                   m_keypoints(kpts){

        }

        void Keyframe::addVisibleMapPoints(const std::vector<SRef<CloudPoint>> & mapPoints)
        {
            m_mapPoints.insert(m_mapPoints.end(), mapPoints.begin(), mapPoints.end());
        }

        std::vector<SRef<CloudPoint>> & Keyframe::getVisibleMapPoints()
        {
            return m_mapPoints ;
        }


        SRef<DescriptorBuffer> Keyframe::getDescriptors()
        {
            return m_descriptor ;
        }

        std::vector<SRef<Keypoint>> Keyframe::getKeyPoints()
        {
            return m_keypoints ;
        }



        Keyframe::~Keyframe(){

        }
    }
}
