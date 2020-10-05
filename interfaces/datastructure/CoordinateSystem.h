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

#ifndef SOLAR_COORDINATESYSTEM_H
#define SOLAR_COORDINATESYSTEM_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <core/SerializationDefinitions.h>
#include "GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include <chrono>
#include <mutex>

namespace SolAR {
namespace datastructure {

/**
    * @class CoordinateSystem
	* @brief <B>This component includes coordinate systems of a map. It can be a floating coordinate system or be related to other coordinate systems.</B>
	*/
class SOLARFRAMEWORK_API CoordinateSystem
{
public:
	///
	/// @brief Identification constructor
	///
	CoordinateSystem();

	///
	/// \brief ~Identification
	///
	~CoordinateSystem() = default;

	/// 
	/// @brief Set the absolute position of this map in the earth coordinate
	/// @param[in] position: the absolute position
	/// 
	void setAbsolutePosition(const Vector3f& position);

	/// 
	/// @brief Get the absolute position of this map in the earth coordinate
	/// @return the position
	/// 
	const Vector3f& getAbsolutePosition() const;

	/// 
	/// @brief Set the absolute euler rotation of this map in the earth coordinate
	/// @param[in] euler: the absolute euler rotation
	/// 
	void setAbsoluteRotation(const Vector3f& euler);

	/// 
	/// @brief Get the absolute euler rotation of this map in the earth coordinate
	/// @return the rotation
	/// 
	const Vector3f& getAbsoluteRotation() const;

	/// 
	/// @brief Set the uuid of parent map that this map belongs to
	/// @param[in] parent_uuid: the parent uuid
	/// 
	void setParentId(const boost::uuids::uuid& parent_uuid);

	/// 
	/// @brief Get the uuid of parent map that this map belongs to
	/// @return the parent uuid
	/// 
	const boost::uuids::uuid& getParentId() const;

	/// 
	/// @brief Set the transformation matrix from this map to its parent map
	/// @param[in] parent_transform: the transformation matrix
	/// 
	void setParentTransform(const Transform3Df& parent_transform);

	/// 
	/// @brief Get the transformation matrix from this map to its parent map
	/// @return the transformation matrix
	/// 
	const Transform3Df& getParentTransform() const;

private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version);

private:
	bool										m_isFloating;
	Vector3f									m_absolutePosition;	// absolute position in the earth.
	Vector3f									m_absoluteRotation;	// absolute euler rotation in the earth.
	boost::uuids::uuid							m_parentId;
	Transform3Df								m_parentTransform;
};

DECLARESERIALIZE(CoordinateSystem);

}
}

#endif //SOLAR_DESCRIPTORMATCH_H
