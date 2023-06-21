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

#include <datastructure/Identification.h>

#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {


Identification::Identification() {
	m_uuid = boost::uuids::nil_uuid();
	m_name = "";
	m_author = "";
	m_createdTime = std::chrono::system_clock::now();
	m_lastUpdatedTime = m_createdTime;
	m_bbox.corner = Point3Df();
	m_bbox.width = 0.f; m_bbox.height = 0.f; m_bbox.depth = 0.f;
}

bool Identification::setUUID(const boost::uuids::uuid& uuid) {
	if (!m_uuid.is_nil()) {
		LOG_WARNING("The UUID has actually been set");
		return false;
	}
	m_uuid = uuid;
	return true;
}

bool Identification::setUUID(const std::string& uuid) {
	if (!m_uuid.is_nil()) {
		LOG_WARNING("The UUID has actually been set");
		return false;
	}
	try
	{
		m_uuid = boost::lexical_cast<boost::uuids::uuid>(uuid);
        return true;
	}
	catch (boost::bad_lexical_cast &e)
	{
		LOG_WARNING("{}",e.what());
        return false;
	}
}

const boost::uuids::uuid& Identification::getUUID() const{
	return m_uuid;
}

const std::string Identification::getUUIDString() const{
    return boost::lexical_cast<std::string>(m_uuid);
}

void Identification::setName(const std::string &name) {
	m_name = name;
}

const std::string& Identification::getName() const{
	return m_name;
}

void Identification::setAuthor(const std::string &author) {
	m_author = author;
}

const std::string& Identification::getAuthor() const{
	return m_author;
}

const std::chrono::system_clock::time_point& Identification::getCreatedTime() const{
	return m_createdTime;
}

void Identification::setCreatedTime(const std::chrono::system_clock::time_point& createdTime) {
	m_createdTime = createdTime;
}

const std::chrono::system_clock::time_point& Identification::getLastUpdateTime() const{
	return m_lastUpdatedTime;
}

void Identification::setLastUpdateTime(const std::chrono::system_clock::time_point& updateTime) {
	m_lastUpdatedTime = updateTime;
}

void Identification::setBBox3D(const BBox3Df& bbox) {
	m_bbox = bbox;
}

const BBox3Df& Identification::getBBox3D() const{
	return m_bbox;
}

template<typename Archive>
void Identification::serialize(Archive & ar, const unsigned int /* version */) {
    ar & m_uuid;
	ar & m_name;
    ar & m_author;
	char * ptr_createdTime = reinterpret_cast<char *>(&m_createdTime);
	ar & boost::serialization::make_array(ptr_createdTime, sizeof(m_createdTime));
	char * ptr_updatedTime = reinterpret_cast<char *>(&m_lastUpdatedTime);
	ar & boost::serialization::make_array(ptr_updatedTime, sizeof(m_lastUpdatedTime));
    ar & m_bbox;
}

IMPLEMENTSERIALIZE(Identification);

}
}
