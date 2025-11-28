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
#include <xpcf/core/helpers.h>
#include "core/Log.h"

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::KeyframeCollection);

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

FrameworkReturnCode KeyframeCollection::addKeyframe(const SRef<Keyframe> keyframe, bool defineKeyframeId)
{
    if (defineKeyframeId) {
        keyframe->setId(m_id++);
    }
    m_keyframes[keyframe->getId()] = keyframe;
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode KeyframeCollection::addKeyframe(const Keyframe & keyframe, bool defineKeyframeId)
{
	SRef<Keyframe> keyframe_ptr = xpcf::utils::make_shared<Keyframe>(keyframe);
    return addKeyframe(keyframe_ptr, defineKeyframeId);
}

FrameworkReturnCode KeyframeCollection::getKeyframe(const uint32_t id, SRef<Keyframe> & keyframe) const
{
	std::map< uint32_t, SRef<Keyframe>>::const_iterator keyframeIt = m_keyframes.find(id);
	if (keyframeIt != m_keyframes.end()) {
		keyframe = keyframeIt->second;
		return FrameworkReturnCode::_SUCCESS;
	}
	else {
		LOG_DEBUG("Cannot find keyframe with id {} to get", id);
		return FrameworkReturnCode::_ERROR_;
	}
}

FrameworkReturnCode KeyframeCollection::getKeyframes(const std::vector<uint32_t>& ids, std::vector<SRef<Keyframe>>& keyframes) const
{
	for (auto &it : ids) {
		std::map< uint32_t, SRef<Keyframe>>::const_iterator keyframeIt = m_keyframes.find(it);
		if (keyframeIt == m_keyframes.end()) {
			LOG_DEBUG("Cannot find keyframe with id {} to get", it);
			return FrameworkReturnCode::_ERROR_;
		}
		keyframes.push_back(keyframeIt->second);
	}
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode KeyframeCollection::getAllKeyframes(std::vector<SRef<Keyframe>>& keyframes) const
{
    keyframes.clear();
    keyframes.reserve(m_keyframes.size());
    for (const auto & kf: m_keyframes) {
        keyframes.push_back(kf.second);
    }
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode KeyframeCollection::getAllKeyframesWithoutImages(std::vector<SRef<Keyframe>>& keyframes) const
{
    keyframes.clear();
    keyframes.reserve(m_keyframes.size());
    std::map<uint32_t, SRef<Keyframe>> newKeyframesMap;
    for (const auto& [id, kf]: m_keyframes) {
        SRef<Keyframe> keyframeWithoutImage = xpcf::utils::make_shared<Keyframe>(*kf);
        // Remove image
        keyframeWithoutImage->setView(nullptr);
        newKeyframesMap[id] = keyframeWithoutImage;
    }
    // Update the reference keyframe for each keyframe
    for (const auto& [id, kf]: newKeyframesMap) {
        // Retrieve reference keyframe in new keyframe map
        if (kf->getReferenceKeyframe()) {
            auto keyframeIt = newKeyframesMap.find(kf->getReferenceKeyframe()->getId());
            if (keyframeIt == newKeyframesMap.end()) {
                LOG_DEBUG("KeyframeCollection::getAllKeyframesWithoutImages - cannot find reference keyframe ({}) for keyframe id: {}", kf->getReferenceKeyframe()->getId(), id);
                kf->setReferenceKeyframe(nullptr);
            }
            else {
            	kf->setReferenceKeyframe(keyframeIt->second);
            }
        }
        // Add keyframe in result vector
        keyframes.push_back(kf);
    }

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
		LOG_DEBUG("Cannot find keyframe with id {} to suppress", id);
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

void KeyframeCollection::nextSerializationWithoutKeyframeImages()
{
    for (const auto& [id, kf]: m_keyframes) {
        kf->nextSerializationWithoutImage();
    }
}

template <typename Archive>
void KeyframeCollection::serialize(Archive &ar, const unsigned int /* version */)
{
	ar & m_id;
	ar & m_descriptorType;
	ar & m_keyframes;
}

IMPLEMENTSERIALIZE(KeyframeCollection);

} // end of namespace datastructure
} // end of namespace SolAR
