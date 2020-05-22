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

#ifndef SOLAR_PRIMITIVEINFORMATION_H
#define SOLAR_PRIMITIVEINFORMATION_H

#include <cstdint>
#include <chrono>
#include <mutex>

namespace SolAR {
namespace datastructure {

/**
	* @class Primitive Information
	* @brief <B>This component includes primitive informations such as confident score, semantic.</B>
	*/
class PrimitiveInformation
{
public:
	///
	/// @brief PrimitiveInformation constructor
	///
	PrimitiveInformation() {
		m_confidence = 1.0;
		m_usedTimes = 1;
        m_lastUpdateTime = std::chrono::system_clock::now();
		m_semanticId = -1;
	}

	///
	/// @brief This method updates the confident score of the primitive element
	/// @param[in] isGood: it is true if the primitive element is considered as an inlier for this use. It is false in the otherwise.
	///
	void updateConfidence(bool isGood) {
		m_confidence = (m_usedTimes * m_confidence + (int)isGood) / (m_usedTimes + 1);
		m_usedTimes++;
	}

	///
	/// @brief This method returns the confident score of the primitive element
	/// @return the confident score
	///
	const float& getConfidence() const{ 
		return m_confidence; 
	}

	///
	/// @brief This method returns the number of used times of the primitive element
	/// @return the number of used times
	///
	const uint32_t& getUsedTime() const{ 
		return m_usedTimes; 
	}

	///
	/// @brief This method returns the last updated time of the primitive element
	/// @return the last updated time
	///
	const std::chrono::system_clock::time_point& getLastUpdateTime() const{ 
		return m_lastUpdateTime; 
	}

	///
	/// @brief This method updates the last updated time of the primitive element
	/// @param[in] updateTime: the update time. You can get current time by using std::chrono::system_clock::now()
	///
	void setLastUpdateTime(const std::chrono::system_clock::time_point& updateTime) {
		m_lastUpdateTime = updateTime;
	}

	///
	/// @brief This method returns the semantic id of the primitive element
	/// @return the semantic id
	///
	const int& getSemanticId() const{ 
		return m_semanticId; 
	}

	///
	/// @brief This method sets the semantic id of the primitive element
	/// @param semanticId: the semantic id
	///
	void setSemanticId(const int& semanticId) { 
		m_semanticId = semanticId; 
	}
	

	///
	/// \brief ~PrimitiveInformation
	///
	~PrimitiveInformation() = default;
private:
	float										m_confidence;
	uint32_t									m_usedTimes;
	std::chrono::system_clock::time_point		m_lastUpdateTime;
	int											m_semanticId;	
};

}
}

#endif //SOLAR_DESCRIPTORMATCH_H
