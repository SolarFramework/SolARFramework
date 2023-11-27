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
#include "xpcf/core/helpers.h"
#include <cstddef> //TO DO: remove with a complete implementation

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Keyframe);

namespace SolAR {
namespace datastructure {

const uint32_t& Keyframe::getId() const
{
	return m_id;
}

void Keyframe::setId(const uint32_t& id_keyframe)
{
	m_id = id_keyframe;
}

bool Keyframe::setKeypointStatusToMatched(uint32_t id_keypoint)
{
	if (m_isKeypointMatchedStatusFrozen)
		return false;
	if (m_isKeypointMatched.empty()) {
		if (m_keypoints.empty())
			return false;
		m_isKeypointMatched.resize(m_keypoints.size(), false);
	}
	if (id_keypoint >= m_isKeypointMatched.size())
		return false;
	m_isKeypointMatched[id_keypoint] = true;
	return true;
}

const std::vector<bool>& Keyframe::getIsKeypointMatched() const
{
    return m_isKeypointMatched;
}

void Keyframe::freezeKeypointMatchedStatus() {
	m_isKeypointMatchedStatusFrozen = true;
}

void Keyframe::unfreezeKeypointMatchedStatus() {
	m_isKeypointMatchedStatusFrozen = false;
}

template<typename Archive>
void Keyframe::serialize(Archive &ar, const unsigned int /* version */) {
	ar & boost::serialization::base_object<Frame>(*this);
	ar & boost::serialization::base_object<PrimitiveInformation>(*this);
	ar & m_id;
    ar & m_isKeypointMatched;
	ar & m_isKeypointMatchedStatusFrozen;
}

IMPLEMENTSERIALIZE(Keyframe);

}
}
