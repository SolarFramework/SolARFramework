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

#ifndef WORLDANCHOR_H
#define WORLDANCHOR_H

#include <core/SolARFrameworkDefinitions.h>
#include <core/SerializationDefinitions.h>
#include <datastructure/WorldElement.h>

#include "core/Log.h"

// Definition of WorldAnchor Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {
/**
    * @class WorldAnchor
    * @brief <B>This class defines the generic WorldAnchor datastructure.</B>
    */
class SOLARFRAMEWORK_API WorldAnchor : virtual public WorldElement {
    public:
        ///
        /// @brief WorldAnchor default constructor
        ///
        WorldAnchor() = default;

        ///
        /// @brief WorldAnchor default destructor
        ///
        virtual ~WorldAnchor() = default;

    private:

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

    protected:
};

DECLARESERIALIZE(WorldAnchor);

}
} // end of namespace SolAR

#endif // WORLDANCHOR_H
