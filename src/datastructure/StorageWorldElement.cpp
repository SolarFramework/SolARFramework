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

#include "datastructure/StorageWorldElement.h"

#include <xpcf/core/helpers.h>

#include "core/Log.h"

namespace SolAR {
namespace datastructure {

    StorageWorldElement::StorageWorldElement(const org::bcom::xpcf::uuids::uuid &creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                                             Vector3d size, const std::multimap<std::string, std::string> &tags, std::string name){
        m_id = org::bcom::xpcf::uuids::random_generator()();
        m_name = name;
        m_creatorId = creatorId;
        m_localCRS = localCRS;
        m_unitSystem = unitSystem;
        m_size = size;
        m_tags = tags;
        //LOG_DEBUG("WorldElement constructor with id = {}", org::bcom::xpcf::uuids::to_string(m_id));
    }

    StorageWorldElement::StorageWorldElement(const org::bcom::xpcf::uuids::uuid &id,const org::bcom::xpcf::uuids::uuid &creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                                Vector3d size, const std::multimap<std::string, std::string> &tags, std::string name){
        m_id = id;
        m_name = name;
        m_creatorId = creatorId;
        m_localCRS = localCRS;
        m_unitSystem = unitSystem;
        m_size = size;
        m_tags = tags;
        LOG_DEBUG("WorldElement constructor with id = {}", org::bcom::xpcf::uuids::to_string(m_id));
    }

    org::bcom::xpcf::uuids::uuid StorageWorldElement::getID() const {
        return m_id;
    }

    void StorageWorldElement::setID(const org::bcom::xpcf::uuids::uuid & id) {
        m_id = id;
    }

    org::bcom::xpcf::uuids::uuid StorageWorldElement::getCreatorID() const {
        return m_creatorId;
    }

    void StorageWorldElement::setCreatorID(const org::bcom::xpcf::uuids::uuid & newCreator) {
        m_creatorId = newCreator;
    }

    Transform3Df StorageWorldElement::getLocalCrs() const{
        return m_localCRS;
    }

    void StorageWorldElement::setLocalCrs(const Transform3Df &newLocalCrs) {
        m_localCRS = newLocalCrs;
    }

    UnitSystem StorageWorldElement::getUnitSystem() const{
        return m_unitSystem;
    }

    void StorageWorldElement::setUnitSystem(const UnitSystem &newUnitSystem){
        m_unitSystem = newUnitSystem;
    }

    Vector3d StorageWorldElement::getSize() const{
        return m_size;
    }

    void StorageWorldElement::setSize(const Vector3d &newSize){
        m_size = newSize;
    }

    std::multimap<std::string, std::string> StorageWorldElement::getTags() const {
        return m_tags;
    }

    void StorageWorldElement::setTags(const std::multimap<std::string, std::string> &tags) {
        m_tags = tags;
    }

    void StorageWorldElement::addTag(const std::string &key, const std::string &value){
        m_tags.insert({key, value});
    }

    bool StorageWorldElement::removeTag(const std::string &key, const std::string &value){
        typedef std::multimap<std::string, std::string>::iterator iterator;
        std::pair<iterator, iterator> iterpair = m_tags.equal_range(key);

        iterator it = iterpair.first;
        for (; it != iterpair.second; ++it) {
            if (it->second == value) {
                m_tags.erase(it);
                return true;
            }
        }
        return false;
    }

    const std::string &StorageWorldElement::getName() const
    {
        return m_name;
    }

    void StorageWorldElement::setName(const std::string &newName)
    {
        m_name = newName;
    }

    template<typename Archive>
    void StorageWorldElement::serialize(Archive &ar, const unsigned int /* version */)
    {
        ar & boost::serialization::make_nvp("id", m_id);
        ar & boost::serialization::make_nvp("name", m_name);
        ar & boost::serialization::make_nvp("creatorId", m_creatorId);
        ar & boost::serialization::make_nvp("localCRS", m_localCRS);
        ar & boost::serialization::make_nvp("unitSystem", m_unitSystem);
        ar & boost::serialization::make_nvp("size", m_size);
        ar & boost::serialization::make_nvp("tags", m_tags);
    }

    IMPLEMENTSTORAGESERIALIZE(StorageWorldElement);

}
}
