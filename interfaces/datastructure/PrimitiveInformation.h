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

#include <core/SerializationDefinitions.h>


namespace SolAR {
namespace datastructure {

/**
    * @class PrimitiveInformation
	* @brief <B>This component includes primitive informations such as confident score, semantic.</B>
	*/
class SOLARFRAMEWORK_API PrimitiveInformation
{
public:
	///
	/// @brief PrimitiveInformation constructor
	///
	PrimitiveInformation();

	///
	/// @brief This method updates the confident score of the primitive element
	/// @param[in] isGood: it is true if the primitive element is considered as an inlier for this use. It is false in the otherwise.
	///
	void updateConfidence(bool isGood);

	///
	/// @brief This method returns the confident score of the primitive element
	/// @return the confident score
	///
	float getConfidence() const;

	///
	/// @brief This method returns the number of used times of the primitive element
	/// @return the number of used times
	///
	uint32_t getUsedTime() const;

	///
	/// @brief This method returns the last updated time of the primitive element
	/// @return the last updated time
	///
	const std::chrono::system_clock::time_point& getLastUpdateTime() const;

	///
	/// @brief This method updates the last updated time of the primitive element
	/// @param[in] updateTime: the update time. You can get current time by using std::chrono::system_clock::now()
	///
	void setLastUpdateTime(const std::chrono::system_clock::time_point& updateTime);

	///
	/// @brief This method returns the semantic id of the primitive element
	/// @return the semantic id
	///
	int getSemanticId() const;

	///
	/// @brief This method sets the semantic id of the primitive element
	/// @param semanticId: the semantic id
	///
	void setSemanticId(const int& semanticId);
	

	///
	/// \brief ~PrimitiveInformation
	///
	~PrimitiveInformation() = default;

private:
	friend class boost::serialization::access;
	template<typename Archive>
    void serialize(Archive &ar, const unsigned int version);

private:
	float										m_confidence;
	uint32_t									m_usedTimes;
	std::chrono::system_clock::time_point		m_lastUpdateTime;
	int											m_semanticId;	
};

DECLARESERIALIZE(PrimitiveInformation);

}
}

#endif //SOLAR_DESCRIPTORMATCH_H
