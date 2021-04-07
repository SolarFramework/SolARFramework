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

#ifndef SOLAR_MAP_H
#define SOLAR_MAP_H

#include <vector>
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Identification.h"
#include "datastructure/CoordinateSystem.h"
#include "xpcf/core/refs.h"
#include <map>

// Definition of Map Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
* @class Map
* @brief <B>A generic map composed of an identification and a coordinate system.</B>
* This class provides a generic map.
*/
class  SOLARFRAMEWORK_API Map {
public:
	///
    /// @brief Map constructor.
    ///
	Map() = default;
    Map(const Map& other) = default;
    Map& operator=(const Map& other) = default;

	///
    /// @brief ~Map
	///
    ~Map() = default;

	///
	/// @brief This method returns the identification
	/// @return the identification
	///
    const SRef<Identification> & getConstIdentification() const;

	///
	/// @brief This method returns the identification
    /// @param[out] identification the identification of map
	/// @return the identification
	///
	std::unique_lock<std::mutex> getIdentification(SRef<Identification>& identification);

	///
	/// @brief This method is to set the identification
	/// @param[in] identification the identification of map
	///
	void setIdentification(const SRef<Identification> identification);

	///
	/// @brief This method returns the coordinate system
	/// @return the coordinate system
	///
	const SRef<CoordinateSystem> & getConstCoordinateSystem() const;

	///
	/// @brief This method returns the coordinate system
	/// @param[out] coordinateSystem the coordinate system of map
	/// @return the coordinate system
	///
	std::unique_lock<std::mutex> getCoordinateSystem(SRef<CoordinateSystem>& coordinateSystem);

	///
	/// @brief This method is to set the coordinate system
	/// @param[in] coordinateSystem the coordinate system of map
	///
	void setCoordinateSystem(const SRef<CoordinateSystem> coordinateSystem);

private:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

	SRef<Identification>	m_identification;
	SRef<CoordinateSystem>	m_coordinateSystem;
};

DECLARESERIALIZE(Map);
}
}  // end of namespace SolAR
#endif // SOLAR_MAP_H
