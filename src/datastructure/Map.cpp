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

#include <datastructure/Map.h>
#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {

const SRef<Identification>& Map::getConstIdentification() const
{
	return m_identification;
}

std::unique_lock<std::mutex> Map::getIdentification(SRef<Identification>& identification)
{
	identification = m_identification;
	return m_identification->acquireLock();
}

void Map::setIdentification(const SRef<Identification> identification)
{
	m_identification = identification;
}

const SRef<CoordinateSystem>& Map::getConstCoordinateSystem() const
{
	return m_coordinateSystem;
}

std::unique_lock<std::mutex> Map::getCoordinateSystem(SRef<CoordinateSystem>& coordinateSystem)
{
	coordinateSystem = m_coordinateSystem;
	return m_coordinateSystem->acquireLock();
}

void Map::setCoordinateSystem(const SRef<CoordinateSystem> coordinateSystem)
{
	m_coordinateSystem = coordinateSystem;
}

template<typename Archive>
void Identification::serialize(ATTRIBUTE(maybe_unused) Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
	ar & m_identification;
	ar & m_coordinateSystem;
}

IMPLEMENTSERIALIZE(Map);

}
}
