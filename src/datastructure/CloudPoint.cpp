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
#include "xpcf/core/helpers.h"

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::CloudPoint);

namespace SolAR {
namespace datastructure {

CloudPoint::~CloudPoint(){
		
}

CloudPoint::CloudPoint(const Point3Df& point, float r, float g, float b, float nx, float ny, float nz, double reproj_error) :
    Point3Df(point), m_rgb(r, g, b), m_viewDirection(nx, ny, nz), m_reproj_error(reproj_error)
{
    m_cloudPointSupportedTypes = CloudPointType::Color | CloudPointType::ViewDirection | CloudPointType::ReprojectionError;
}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, double reproj_error) :
    Point3Df(x, y, z), m_rgb(r, g, b), m_viewDirection(nx, ny, nz), m_reproj_error(reproj_error)
{
    m_cloudPointSupportedTypes = CloudPointType::Color | CloudPointType::ViewDirection | CloudPointType::ReprojectionError;
}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, double reproj_error, const std::map<unsigned int, unsigned int>& visibility) :
    Point3Df(x, y, z), m_visibility(visibility), m_rgb(r, g, b), m_reproj_error(reproj_error)
{
    m_cloudPointSupportedTypes = CloudPointType::Color | CloudPointType::ViewDirection | CloudPointType::Visibility;
}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, double reproj_error, const std::map<unsigned int, unsigned int>& visibility) :
    Point3Df(x, y, z), m_visibility(visibility), m_rgb(r, g, b), m_viewDirection(nx, ny, nz), m_reproj_error(reproj_error)
{
    m_cloudPointSupportedTypes = CloudPointType::Color | CloudPointType::ViewDirection | CloudPointType::ReprojectionError | CloudPointType::Visibility ;
}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, double reproj_error, const std::map<unsigned int, unsigned int>& visibility, SRef<DescriptorBuffer> descriptor) :
    Point3Df(x, y, z), m_descriptor(descriptor), m_visibility(visibility), m_rgb(r, g, b), m_reproj_error(reproj_error)
{
    m_cloudPointSupportedTypes = CloudPointType::Color | CloudPointType::ReprojectionError | CloudPointType::Visibility;
    if (descriptor != nullptr)
        m_cloudPointSupportedTypes = m_cloudPointSupportedTypes | CloudPointType::Descriptor;
}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, double reproj_error, const std::map<unsigned int, unsigned int>& visibility, SRef<DescriptorBuffer> descriptor) :
    Point3Df(x, y, z), m_descriptor(descriptor), m_visibility(visibility), m_rgb(r, g, b), m_viewDirection(nx, ny, nz), m_reproj_error(reproj_error)
{
    m_cloudPointSupportedTypes = CloudPointType::Color | CloudPointType::ViewDirection | CloudPointType::ReprojectionError | CloudPointType::Visibility;
    if (descriptor != nullptr)
        m_cloudPointSupportedTypes = m_cloudPointSupportedTypes | CloudPointType::Descriptor;
}

const uint32_t& CloudPoint::getId() const{
	return m_id;
}

void CloudPoint::setId(const uint32_t& id) {
	m_id = id;
}

const SRef<DescriptorBuffer>& CloudPoint::getDescriptor() const{
	return m_descriptor;
}

void CloudPoint::setDescriptor(const SRef<DescriptorBuffer> &descriptor) {
    if (descriptor != nullptr)
    {
        m_descriptor = descriptor;
        m_cloudPointSupportedTypes = m_cloudPointSupportedTypes | CloudPointType::Descriptor;
    }
}

void CloudPoint::addNewDescriptor(const DescriptorView & descriptor)
{
	DescriptorBuffer newDescriptor(descriptor);
	DescriptorBuffer newDescriptorCP = ((*m_descriptor * m_visibility.size()) + newDescriptor) / (m_visibility.size() + 1);
	DescriptorBuffer newDescriptorCPConvertedType = newDescriptorCP.convertTo(m_descriptor->getDescriptorDataType());
	*m_descriptor = newDescriptorCPConvertedType;
    m_cloudPointSupportedTypes = m_cloudPointSupportedTypes | CloudPointType::Descriptor;
}

const Vector3f& CloudPoint::getRGB() const{
	return m_rgb;
}

const float& CloudPoint::getR() const { 
	return m_rgb[0]; 
}

const float& CloudPoint::getG() const {
	return m_rgb[1]; 
}

const float& CloudPoint::getB() const {
	return m_rgb[2]; 
}

void CloudPoint::setRGB(const Vector3f &rgb) {
	m_rgb = rgb;
    m_cloudPointSupportedTypes = m_cloudPointSupportedTypes | CloudPointType::Color;
}

const Vector3f & CloudPoint::getViewDirection() const
{
	return m_viewDirection;
}

void CloudPoint::setViewDirection(const Vector3f & viewDirection)
{
	m_viewDirection = viewDirection.normalized();
    m_cloudPointSupportedTypes = m_cloudPointSupportedTypes | CloudPointType::ViewDirection;
}

void CloudPoint::addNewViewDirection(const Vector3f & viewDirection)
{
	m_viewDirection = ((m_viewDirection * m_visibility.size() + viewDirection) / (m_visibility.size() + 1)).normalized();
    m_cloudPointSupportedTypes = m_cloudPointSupportedTypes | CloudPointType::ViewDirection;
}

void CloudPoint::setReprojError(const double & error)
{
	m_reproj_error = error;
    m_cloudPointSupportedTypes = m_cloudPointSupportedTypes | CloudPointType::ReprojectionError;
}

const double& CloudPoint::getReprojError() const
{
	return m_reproj_error;
}

const std::map<uint32_t, uint32_t>& CloudPoint::getVisibility() const {
	return m_visibility;
}

void CloudPoint::addVisibility(const uint32_t& keyframe_id, const uint32_t& keypoint_id) {
    m_visibility[keyframe_id] = keypoint_id;
    m_cloudPointSupportedTypes = m_cloudPointSupportedTypes | CloudPointType::Visibility;
}

bool CloudPoint::removeVisibility(const uint32_t& keyframe_id)
{
	if (m_visibility.find(keyframe_id) == m_visibility.end())
		return false;
	else {
		m_visibility.erase(keyframe_id);
		return true;
	}
}

template <typename Archive>
void CloudPoint::serialize(Archive &ar, const unsigned int /* version */)
{
    ar.template register_type<CloudPoint>();
    ar & m_cloudPointSupportedTypes;

    ar & boost::serialization::base_object<Point3Df>(*this);
    ar & boost::serialization::base_object<PrimitiveInformation>(*this);

    ar & m_id;
    if (m_cloudPointSupportedTypes & CloudPointType::Descriptor)
        ar & m_descriptor;
    if (m_cloudPointSupportedTypes & CloudPointType::Visibility)
        ar & m_visibility;
    if (m_cloudPointSupportedTypes & CloudPointType::Color)
        ar & boost::serialization::make_array(m_rgb.data(), 3);
    if (m_cloudPointSupportedTypes & CloudPointType::ViewDirection)
        ar & boost::serialization::make_array(m_viewDirection.data(), 3);
    if (m_cloudPointSupportedTypes & CloudPointType::ReprojectionError)
        ar & m_reproj_error;
}

IMPLEMENTSERIALIZE(CloudPoint);

} // namespace datastructure
} // namespace SolAR

