/**
 * @copyright Copyright (c) 2020 B-com http://www.b-com.com/
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

#ifndef TRACKABLE_H
#define TRACKABLE_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "core/SolARFrameworkDefinitions.h"
#include <core/SerializationDefinitions.h>

// Definition of Trackable Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
    * @class Trackable
    * @brief <B>This abstract class defines the generic trackable datastructure.</B>
    */
class SOLARFRAMEWORK_API Trackable
{
    ///
    /// @brief Trackable default constructor
    /// Assign a unique ID to the instance
    ///
    Trackable() {
        // Assign a unique ID to the trackable object
        m_uuid = boost::uuids::random_generator()();
    }

    ///
    /// @brief Trackable default destructor
    ///
    virtual ~Trackable() = default;

    /// @brief Return the unique ID of the trackable object
    boost::uuids::uuid getUUID() {
        return m_uuid;
    }

    protected:
        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

    protected:
        boost::uuids::uuid m_uuid; // The unique id of the trackable object
};

DECLARESERIALIZE(Trackable);

}
} // end of namespace SolAR

#endif // TRACKABLE_H
