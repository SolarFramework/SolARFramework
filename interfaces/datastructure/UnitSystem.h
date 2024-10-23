/**
 * @copyright Copyright (c) 2021-2022 B-com http://www.b-com.com/
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

#ifndef UNITSYSTEM_H
#define UNITSYSTEM_H

namespace SolAR {
namespace datastructure {

///
/// @brief Enumeration of all units of measurement used by the StorageWorldElements
///
enum class UnitSystem : char {

    //metric units

    /// millimeter
    MM,
    /// centimeter
    CM,
    /// decimeter
    DM,
    /// meter
    M,
    /// decameter
    DAM,
    /// hectometer
    HM,
    /// kilometer
    KM,

    //imperial units

    INCH,
    FOOT,
    YARD,
    MILE,
    INVALID

};



}
}
#endif // UNITSYSTEM_H
