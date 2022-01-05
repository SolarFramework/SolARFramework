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

#include "datastructure/WorldElement.h"

#include "core/Log.h"

#include "xpcf/core/helpers.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace SolAR {
namespace datastructure {

WorldElement::WorldElement(std::multimap<std::string, std::string> tags){
    m_id = boost::uuids::random_generator()();
    m_tags = tags;
    LOG_DEBUG("WorldElement constructor with id = ", boost::uuids::to_string(m_id));
}

boost::uuids::uuid WorldElement::getID() const {
    return m_id;
}

void WorldElement::setID(const boost::uuids::uuid & id) {
    m_id = id;
}

std::multimap<std::string, std::string> WorldElement::getTags() const {
    return m_tags;
}

void WorldElement::setTags(std::multimap<std::string, std::string> tags) {
    this->m_tags = tags;
}

void WorldElement::addTag(std::string dataType, std::string value){
    m_tags.insert({dataType, value});
}

template<typename Archive>
void WorldElement::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
    ar & m_id;
    ar & m_tags;
}

IMPLEMENTSERIALIZE(WorldElement);

}
}
