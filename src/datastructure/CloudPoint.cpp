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

#include "datastructure/CloudPoint.h"
#include "datastructure/Keyframe.h"
#include <cstddef> //TO DO: remove with a complete implementation

std::mutex						m_mutex;

namespace SolAR {
    namespace datastructure {

    CloudPoint::~CloudPoint(){

    }

    CloudPoint::CloudPoint(const Point3Df& point) : Point3Df(point), m_r(0.0), m_g(0.0), m_b(0.0), m_reproj_error(0.0) {
    }

    CloudPoint::CloudPoint( float x,
                            float y,
                            float z,
                            float r,
                            float g,
                            float b,
                            double reproj_error,
                            std::map<unsigned int, unsigned int> &visibility): Point3Df(x,y,z),m_r(r),m_g(g),m_b(b), m_reproj_error(reproj_error),
                                                          m_visibility(visibility) {
    }
    CloudPoint::CloudPoint(float x,
                           float y,
                           float z,
                           float r,
                           float g,
                           float b,
                           double reproj_error,
                           std::map<unsigned int, unsigned int>& visibility,
                           SRef<DescriptorBuffer> descriptor) : Point3Df(x, y, z), m_r(r), m_g(g), m_b(b), m_reproj_error(reproj_error), m_visibility(visibility), m_descriptor(descriptor){
	}

	const std::map<unsigned int, unsigned int>& CloudPoint::getVisibility() const {
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_visibility;
	}

	void CloudPoint::visibilityAddKeypoint(unsigned int keyframe_id, unsigned int keypoint_id) { 
		std::unique_lock<std::mutex> lock(m_mutex);
		m_visibility[keyframe_id] = keypoint_id; 
	};
  }
}
