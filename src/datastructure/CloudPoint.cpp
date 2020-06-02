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

std::mutex m_mutex;

namespace SolAR {
namespace datastructure {

CloudPoint::~CloudPoint(){
		
}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, double reproj_error) :
    Point3Df(x, y, z), m_rgb(r, g, b), m_normal(nx, ny, nz), m_reproj_error(reproj_error) {}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, double reproj_error, std::map<unsigned int, unsigned int>& visibility) :
    Point3Df(x, y, z), m_rgb(r, g, b), m_reproj_error(reproj_error), m_visibility(visibility) {}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, double reproj_error, std::map<unsigned int, unsigned int>& visibility) :
	Point3Df(x, y, z), m_rgb(r, g, b), m_normal(nx, ny, nz), m_reproj_error(reproj_error), m_visibility(visibility) {}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, double reproj_error, std::map<unsigned int, unsigned int>& visibility, SRef<DescriptorBuffer> descriptor) :
    Point3Df(x, y, z), m_rgb(r, g, b), m_reproj_error(reproj_error), m_visibility(visibility), m_descriptor(descriptor){}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, double reproj_error, std::map<unsigned int, unsigned int>& visibility, SRef<DescriptorBuffer> descriptor) :
	Point3Df(x, y, z), m_rgb(r, g, b), m_normal(nx, ny, nz), m_reproj_error(reproj_error), m_visibility(visibility), m_descriptor(descriptor){}

const uint32_t& CloudPoint::getId() const{
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_id;
}

void CloudPoint::setId(const uint32_t& id) {
	std::unique_lock<std::mutex> lock(m_mutex);
	m_id = id;
}

const SRef<DescriptorBuffer>& CloudPoint::getDescriptor() const{
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_descriptor;
}

void CloudPoint::setDescriptor(const SRef<DescriptorBuffer> &descriptor) {
	std::unique_lock<std::mutex> lock(m_mutex);
	m_descriptor = descriptor;
}

const Vector3f& CloudPoint::getRGB() const{
	std::unique_lock<std::mutex> lock(m_mutex);
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
	std::unique_lock<std::mutex> lock(m_mutex);
	m_rgb = rgb;
}

const Vector3f& CloudPoint::getNormal() const{
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_normal;
}

void CloudPoint::setNormal(const Vector3f &normal) {
	std::unique_lock<std::mutex> lock(m_mutex);
	m_normal = normal;
}

void CloudPoint::setReprojError(const double & error)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_reproj_error = error;
}

const double& CloudPoint::getReprojError() const
{
	return m_reproj_error;
}

const std::map<uint32_t, uint32_t>& CloudPoint::getVisibility() const {
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_visibility;
}

void CloudPoint::addVisibility(const uint32_t& keyframe_id, const uint32_t& keypoint_id) {
	std::unique_lock<std::mutex> lock(m_mutex);
	m_visibility[keyframe_id] = keypoint_id; 
}

bool CloudPoint::removeVisibility(const uint32_t& keyframe_id, const uint32_t& keypoint_id)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_visibility.find(keyframe_id) == m_visibility.end())
		return false;
	else {
		m_visibility.erase(keyframe_id);
		return true;
	}
}
}
}
