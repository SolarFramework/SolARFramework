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

namespace SolAR {
namespace datastructure {

CloudPoint::~CloudPoint(){
		
}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, std::map<unsigned int, unsigned int>& visibility) :
	Point3Df(x, y, z), m_rgb(r, g, b), m_normal(nx, ny, nz), m_visibility(visibility) {}

CloudPoint::CloudPoint(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz, std::map<unsigned int, unsigned int>& visibility, SRef<DescriptorBuffer> descriptor) :
	Point3Df(x, y, z), m_rgb(r, g, b), m_normal(nx, ny, nz), m_visibility(visibility), m_descriptor(descriptor){}

uint32_t CloudPoint::getId() {
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_id;
}

void CloudPoint::setId(uint32_t id) {
	std::unique_lock<std::mutex> lock(m_mutex);
	m_id = id;
}

SRef<DescriptorBuffer> CloudPoint::getDescriptor() {
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_descriptor;
}

void CloudPoint::setDescriptor(const SRef<DescriptorBuffer> &descriptor) {
	std::unique_lock<std::mutex> lock(m_mutex);
	m_descriptor = descriptor;
}

Vector3f CloudPoint::getRGB() {
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_rgb;
}

void CloudPoint::setRGB(const Vector3f &rgb) {
	std::unique_lock<std::mutex> lock(m_mutex);
	m_rgb = rgb;
}

Vector3f CloudPoint::getNormal() {
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_normal;
}

void CloudPoint::setNormal(const Vector3f &normal) {
	std::unique_lock<std::mutex> lock(m_mutex);
	m_normal = normal;
}

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
}
}
