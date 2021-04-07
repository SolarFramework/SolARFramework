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

#include "datastructure/FeatureCloudPoint.h"
#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {

FeatureCloudPoint::FeatureCloudPoint(float x, float y, float z, float r, float g, float b, double reproj_error, const std::map<unsigned int, unsigned int>& visibility) :
	CloudPoint(x, y, z, r, g, b, reproj_error), m_visibility(visibility) {}

FeatureCloudPoint::FeatureCloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, double reproj_error, const std::map<unsigned int, unsigned int>& visibility) :
	CloudPoint(x, y, z, r, g, b, nx, ny, nz, reproj_error), m_visibility(visibility) {}

FeatureCloudPoint::FeatureCloudPoint(float x, float y, float z, float r, float g, float b, double reproj_error, const std::map<unsigned int, unsigned int>& visibility, SRef<DescriptorBuffer> descriptor) :
	CloudPoint(x, y, z, r, g, b, reproj_error), m_visibility(visibility), m_descriptor(descriptor) {}

FeatureCloudPoint::FeatureCloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, double reproj_error, const std::map<unsigned int, unsigned int>& visibility, SRef<DescriptorBuffer> descriptor) :
	CloudPoint(x, y, z, r, g, b, nx, ny, nz, reproj_error), m_visibility(visibility), m_descriptor(descriptor) {}

const SRef<DescriptorBuffer>& FeatureCloudPoint::getDescriptor() const {
	return m_descriptor;
}

void FeatureCloudPoint::setDescriptor(const SRef<DescriptorBuffer> &descriptor) {
	m_descriptor = descriptor;
}

void FeatureCloudPoint::addNewDescriptor(const DescriptorView & descriptor)
{
	DescriptorBuffer newDescriptor(descriptor);
	DescriptorBuffer newDescriptorCP = ((*m_descriptor * m_visibility.size()) + newDescriptor) / (m_visibility.size() + 1);
	DescriptorBuffer newDescriptorCPConvertedType = newDescriptorCP.convertTo(m_descriptor->getDescriptorDataType());
	*m_descriptor = newDescriptorCPConvertedType;
}

const std::map<uint32_t, uint32_t>& FeatureCloudPoint::getVisibility() const {
	return m_visibility;
}

void FeatureCloudPoint::addVisibility(const uint32_t& keyframe_id, const uint32_t& keypoint_id) {
	m_visibility[keyframe_id] = keypoint_id;
}

bool FeatureCloudPoint::removeVisibility(const uint32_t& keyframe_id)
{
	if (m_visibility.find(keyframe_id) == m_visibility.end())
		return false;
	else {
		m_visibility.erase(keyframe_id);
		return true;
	}
}

template <typename Archive>
void FeatureCloudPoint::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version)
{
	ar & boost::serialization::base_object<CloudPoint>(*this);
	ar & m_descriptor;
	ar & m_visibility;
}

IMPLEMENTSERIALIZE(CloudPoint);

} // namespace datastructure
} // namespace SolAR
