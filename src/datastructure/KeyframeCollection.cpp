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

#include "datastructure/KeyframeCollection.h"
#include "xpcf/core/helpers.h"
#include "core/Log.h"

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

FrameworkReturnCode KeyframeCollection::addKeyframe(const SRef<Keyframe> keyframe)
{
	keyframe->setId(m_id);
	m_keyframes[m_id] = keyframe;
	m_id++;
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode KeyframeCollection::addKeyframe(const Keyframe & keyframe)
{
	SRef<Keyframe> keyframe_ptr = xpcf::utils::make_shared<Keyframe>(keyframe);
	keyframe_ptr->setId(m_id);
	m_keyframes[m_id] = keyframe_ptr;
	m_id++;
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode KeyframeCollection::getKeyframe(const uint32_t id, SRef<Keyframe> & keyframe) const
{
	std::map< uint32_t, SRef<Keyframe>>::const_iterator keyframeIt = m_keyframes.find(id);
	if (keyframeIt != m_keyframes.end()) {
		keyframe = keyframeIt->second;
		return FrameworkReturnCode::_SUCCESS;
	}
	else {
		LOG_ERROR("Cannot find keyframe with id {} to get", id);
		return FrameworkReturnCode::_ERROR_;
	}
}

FrameworkReturnCode KeyframeCollection::getKeyframes(const std::vector<uint32_t>& ids, std::vector<SRef<Keyframe>>& keyframes) const
{
	for (auto &it : ids) {
		std::map< uint32_t, SRef<Keyframe>>::const_iterator keyframeIt = m_keyframes.find(it);
		if (keyframeIt == m_keyframes.end()) {
			LOG_ERROR("Cannot find keyframe with id {} to get", it);
			return FrameworkReturnCode::_ERROR_;
		}
		keyframes.push_back(keyframeIt->second);
	}
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode KeyframeCollection::getAllKeyframes(std::vector<SRef<Keyframe>>& keyframes) const
{
	for (auto keyframeIt = m_keyframes.begin(); keyframeIt != m_keyframes.end(); keyframeIt++)
		keyframes.push_back(keyframeIt->second);
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode KeyframeCollection::suppressKeyframe(const uint32_t id)
{
	std::map< uint32_t, SRef<Keyframe>>::iterator keyframeIt = m_keyframes.find(id);
	if (keyframeIt != m_keyframes.end()) {
		m_keyframes.erase(keyframeIt);
		return FrameworkReturnCode::_SUCCESS;
	}
	else {
		LOG_ERROR("Cannot find keyframe with id {} to suppress", id);
		return FrameworkReturnCode::_ERROR_;
	}
}

DescriptorType KeyframeCollection::getDescriptorType() const
{
	return m_descriptorType;
}

FrameworkReturnCode KeyframeCollection::setDescriptorType(const DescriptorType & type)
{
	m_descriptorType = type;
	return FrameworkReturnCode::_SUCCESS;
}

bool KeyframeCollection::isExistKeyframe(const uint32_t id) const
{
	if (m_keyframes.find(id) != m_keyframes.end())
		return true;
	else
		return false;
}

int KeyframeCollection::getNbKeyframes() const
{
	return static_cast<int>(m_keyframes.size());
}

template <typename Archive>
void KeyframeCollection::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version)
{
	ar & m_id;
	ar & m_descriptorType;
	ar & m_keyframes;
}

IMPLEMENTSERIALIZE(KeyframeCollection);

} // end of namespace datastructure
} // end of namespace SolAR
