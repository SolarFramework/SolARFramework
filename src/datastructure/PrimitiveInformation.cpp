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

#include <datastructure/PrimitiveInformation.h>


namespace SolAR {
namespace datastructure {

PrimitiveInformation::PrimitiveInformation() {
	m_confidence = 1.0;
	m_usedTimes = 1;
	m_lastUpdateTime = std::chrono::system_clock::now();
	m_semanticId = -1;
}

void PrimitiveInformation::updateConfidence(bool isGood) {
	m_confidence = (m_usedTimes * m_confidence + (int)isGood) / (m_usedTimes + 1);
	m_usedTimes++;
}

const float& PrimitiveInformation::getConfidence() const {
	return m_confidence;
}

const uint32_t& PrimitiveInformation::getUsedTime() const {
	return m_usedTimes;
}

const std::chrono::system_clock::time_point& PrimitiveInformation::getLastUpdateTime() const {
	return m_lastUpdateTime;
}

void PrimitiveInformation::setLastUpdateTime(const std::chrono::system_clock::time_point& updateTime) {
	m_lastUpdateTime = updateTime;
}

const int& PrimitiveInformation::getSemanticId() const {
	return m_semanticId;
}

void PrimitiveInformation::setSemanticId(const int& semanticId) {
	m_semanticId = semanticId;
}

template<typename Archive>
void PrimitiveInformation::serialize(Archive &ar, const unsigned int version)
{
    ar & m_confidence;
    ar & m_usedTimes;
    char * ptr = reinterpret_cast<char *>(&m_lastUpdateTime);
	ar & boost::serialization::make_array(ptr, sizeof(m_lastUpdateTime));
    ar & m_semanticId;
}
IMPLEMENTSERIALIZE(PrimitiveInformation);

}
}
