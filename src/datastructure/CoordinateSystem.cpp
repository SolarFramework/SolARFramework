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

#include <datastructure/CoordinateSystem.h>

namespace SolAR {
namespace datastructure {

CoordinateSystem::CoordinateSystem() {
	m_isFloating = true;
	m_parentId = boost::uuids::nil_uuid();
}

void CoordinateSystem::setAbsolutePosition(const Vector3f& position) {
	m_absolutePosition = position;
}

const Vector3f& CoordinateSystem::getAbsolutePosition() const {
	return m_absolutePosition;
}

void CoordinateSystem::setAbsoluteRotation(const Vector3f& euler) {
	m_absoluteRotation = euler;
}

const Vector3f& CoordinateSystem::getAbsoluteRotation() const {
	return m_absoluteRotation;
}

void CoordinateSystem::setParentId(const boost::uuids::uuid& parent_uuid) {
	m_parentId = parent_uuid;
}

const boost::uuids::uuid& CoordinateSystem::getParentId() const {
	return m_parentId;
}

void CoordinateSystem::setParentTransform(const Transform3Df& parent_transform) {
	m_parentTransform = parent_transform;
}

const Transform3Df& CoordinateSystem::getParentTransform() const {
	return m_parentTransform;
}

template<typename Archive>
void CoordinateSystem::serialize(Archive &ar, const unsigned int version) {
	ar & m_isFloating;
    /*ar & boost::serialization::make_array(m_absolutePosition.data(), 3);
	ar & boost::serialization::make_array(m_absoluteRotation.data(), 3);
	ar & m_parentId;
    ar & boost::serialization::make_array(m_parentTransform.data(), 12);*/
}

IMPLEMENTSERIALIZE(CoordinateSystem);
}
}

