/**
 * @copyright Copyright (c) 2025 B-com http://www.b-com.com/
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

#ifndef SOLAR_OBJECT2DCOLLECTION_H
#define SOLAR_OBJECT2DCOLLECTION_H

#include "core/Messages.h"
#include "datastructure/Lockable.h"
#include "datastructure/Object2D.h"
#include <map>

namespace SolAR {
namespace datastructure {

/**
 * @class Object2DCollection
 * @brief <B>Object2DCollection used to store instance segmentation results</B>.
 *
 * This class provides Object2DCollection definition.
 */
class SOLARFRAMEWORK_API Object2DCollection : public Lockable {
public:
    /// @brief default constructor
    Object2DCollection() = default;

    /// @brief default destructor
    ~Object2DCollection() = default;

    /// @brief add 2D object
    /// @param[in] obj 2D object to to added
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addObject2D(const SRef<Object2D>& obj);

    /// @brief remove 2D object
    /// @param[in] id instance ID of the object
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode removeObject2D(const uint32_t& id);

    /// @brief get 2D object
    /// @param[in] id instance ID of the object
    /// @param[out] obj 2D object
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getObject2D(const uint32_t& id, SRef<Object2D>& obj);

private:
    /// @brief serialization
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    std::map<uint32_t, SRef<Object2D>> m_objects;
};

DECLARESERIALIZE(Object2DCollection);

} // namespace datastructure
} // namespace SolAR

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Object2DCollection);

#endif
