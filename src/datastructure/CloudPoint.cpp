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

namespace SolAR {
    namespace datastructure {

    CloudPoint::~CloudPoint(){
		
    }

	CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, std::map<unsigned int, unsigned int>& visibility) :
		Point3Df(x, y, z), m_rgb(r, g, b), m_normal(nx, ny, nz), m_visibility(visibility) {
	}

	CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, std::map<unsigned int, unsigned int>& visibility, SRef<DescriptorBuffer> descriptor) :
		Point3Df(x, y, z), m_rgb(r, g, b), m_normal(nx, ny, nz), m_visibility(visibility), m_descriptor(descriptor){}

	const std::map<uint32_t, uint32_t>& CloudPoint::getVisibility() {
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_visibility;
	}

	void CloudPoint::addVisibility(uint32_t keyframe_id, uint32_t keypoint_id) {
		std::unique_lock<std::mutex> lock(m_mutex);
		m_visibility[keyframe_id] = keypoint_id; 
	}
	bool CloudPoint::removeVisibility(uint32_t keyframe_id, uint32_t keypoint_id)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_visibility.find(keyframe_id) == m_visibility.end())
			return false;
		else {
			m_visibility.erase(keyframe_id);
			return true;
		}
	}
	;
  }
}
