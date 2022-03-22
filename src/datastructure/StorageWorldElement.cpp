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

#include "datastructure/StorageWorldElement.h"

#include "core/Log.h"

#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {

    StorageWorldElement::StorageWorldElement(std::multimap<std::string, std::string> tags){
        m_id = org::bcom::xpcf::uuids::random_generator()();
        m_tags = tags;
        LOG_DEBUG("WorldElement constructor with id = ", org::bcom::xpcf::uuids::to_string(m_id));
    }

    org::bcom::xpcf::uuids::uuid StorageWorldElement::getID() const {
        return m_id;
    }

    void StorageWorldElement::setID(const org::bcom::xpcf::uuids::uuid & id) {
        m_id = id;
    }

    std::multimap<std::string, std::string> StorageWorldElement::getTags() const {
        return m_tags;
    }

    void StorageWorldElement::setTags(std::multimap<std::string, std::string> tags) {
        this->m_tags = tags;
    }

    void StorageWorldElement::addTag(std::string dataType, std::string value){
        m_tags.insert({dataType, value});
    }

    template<typename Archive>
    void StorageWorldElement::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
        ar & m_id;
        ar & m_tags;
    }

    IMPLEMENTSERIALIZE(StorageWorldElement);

}
}
