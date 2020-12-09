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

#include "datastructure/CloudLine.h"

std::mutex						m_cloudLineMutex;

namespace SolAR {
namespace datastructure {

CloudLine::CloudLine(Edge3Df & line3D, double reproj_error, std::map<unsigned, unsigned>& visibilityMap) :
	Edge3Df(line3D.p1, line3D.p2),
	m_reproj_error(reproj_error),
	m_visibility(visibilityMap) { }

CloudLine::CloudLine(Edge3Df & line3D, double reproj_error, std::map<unsigned, unsigned>& visibilityMap, SRef<DescriptorBuffer> descriptor) :
	Edge3Df(line3D.p1, line3D.p2),
	m_reproj_error(reproj_error),
	m_visibility(visibilityMap),
	m_descriptor(descriptor) { }

const std::map<unsigned, unsigned>& CloudLine::getVisibility() const
{
	std::unique_lock<std::mutex> lock(m_cloudLineMutex);
	return m_visibility;
}

void CloudLine::visibilityAddKeypoint(unsigned keyframe_id, unsigned keyline_id)
{
	std::unique_lock<std::mutex> lock(m_cloudLineMutex);
	m_visibility[keyframe_id] = keyline_id;
}

}
}

