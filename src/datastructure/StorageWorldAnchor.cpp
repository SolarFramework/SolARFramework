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

#include "datastructure/StorageWorldAnchor.h"

#include <xpcf/core/helpers.h>

#include "core/Log.h"

namespace SolAR {
namespace datastructure {

    StorageWorldAnchor::StorageWorldAnchor(const org::bcom::xpcf::uuids::uuid &creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                                           Vector3d size, const std::multimap<std::string, std::string> &tags, std::string name) : StorageWorldElement(creatorId, localCRS, unitSystem, size, tags, name)
    {
    }

    template<typename Archive>
    void StorageWorldAnchor::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
        ar & boost::serialization::base_object<StorageWorldElement>(*this);
    }

    ElementKind StorageWorldAnchor::getKind()
    {
        return ElementKind::ANCHOR;
    }

    IMPLEMENTSERIALIZE(StorageWorldAnchor);

}
}

