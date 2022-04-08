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

#include "datastructure/StorageWorldAnchor.h"
#include "core/Log.h"

#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {

    StorageWorldAnchor::StorageWorldAnchor(org::bcom::xpcf::uuids::uuid creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                                           Vector3d size, std::map<org::bcom::xpcf::uuids::uuid, std::pair<SRef<StorageWorldElement>, Transform3Df>> parents,
                                           std::map<org::bcom::xpcf::uuids::uuid, SRef<StorageWorldElement>> children, std::multimap<std::string, std::string> tags) : StorageWorldElement(creatorId, localCRS, unitSystem,
                                                                                                                                                                                           size, parents,
                                                                                                                                                                                           children, tags)
    {
    }

    template<typename Archive>
    void StorageWorldAnchor::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {


        ar & boost::serialization::base_object<StorageWorldElement>(*this);
    }

    bool StorageWorldAnchor::isWorldAnchor() {
        return true;
    }
    bool StorageWorldAnchor::isTrackable() {
        return false;
    }

    IMPLEMENTSERIALIZE(StorageWorldAnchor);

}
}

