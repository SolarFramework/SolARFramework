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

#include "datastructure/Trackable.h"

namespace SolAR {
namespace datastructure {

Trackable::Trackable() {
    // Assign a unique ID to the trackable object
    xpcf::uuids::random_generator gen;
    m_uuid = gen();
}

boost::uuids::uuid Trackable::getUUID() const {
    return m_uuid;
}

template<typename Archive>
void Trackable::serialize(Archive &ar, const unsigned int version) {
    ar & m_uuid;
}

IMPLEMENTSERIALIZE(Trackable);

}
}
