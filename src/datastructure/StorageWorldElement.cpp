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

    StorageWorldElement::StorageWorldElement(org::bcom::xpcf::uuids::uuid creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                                             Vector3d size, std::map<org::bcom::xpcf::uuids::uuid, std::pair<SRef<StorageWorldElement>, Transform3Df>> parents,
                                             std::map<org::bcom::xpcf::uuids::uuid, SRef<StorageWorldElement>> children, std::multimap<std::string, std::string> tags){
        m_id = org::bcom::xpcf::uuids::random_generator()();
        m_creatorId = creatorId;
        m_localCRS = localCRS;
        m_unitSystem = unitSystem;
        m_size = size;
        m_parents = parents;
        m_children = children;
        m_tags = tags;
        LOG_DEBUG("WorldElement constructor with id = ", org::bcom::xpcf::uuids::to_string(m_id));
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

    void StorageWorldElement::setUnitSystem(const UnitSystem newUnitSystem){
        m_unitSystem = newUnitSystem;
    }

    Vector3d StorageWorldElement::getSize() const{
        return m_size;
    }

    void StorageWorldElement::setSize(const Vector3d &newSize){
        m_size = newSize;
    }

    std::map<org::bcom::xpcf::uuids::uuid, std::pair<SRef<StorageWorldElement>, Transform3Df>> StorageWorldElement::getParents() const{
        return m_parents;
    }

    void StorageWorldElement::setParents(const std::map<org::bcom::xpcf::uuids::uuid, std::pair<SRef<StorageWorldElement>, Transform3Df>> parents){
        m_parents = parents;
    }

    std::map<org::bcom::xpcf::uuids::uuid, SRef<StorageWorldElement>> StorageWorldElement::getChildren() const{
        return m_children;
    }

    void StorageWorldElement::setChildren(const std::map<org::bcom::xpcf::uuids::uuid, SRef<StorageWorldElement>> newChildren){
        m_children = newChildren;
    }

    std::multimap<std::string, std::string> StorageWorldElement::getTags() const {
        return m_tags;
    }

    void StorageWorldElement::setTags(const std::multimap<std::string, std::string> tags) {
        m_tags = tags;
    }

    void StorageWorldElement::addTag(std::string dataType, std::string value){
        m_tags.insert({dataType, value});
    }

    void StorageWorldElement::addChild(SRef<StorageWorldElement> child){
        m_children.insert({child->getID(),child});
    }

    void StorageWorldElement::addParent(SRef<StorageWorldElement> parent, Transform3Df transform){
        m_parents.insert({parent->getID(), {parent, transform}});
    }

    bool StorageWorldElement::removeChild(org::bcom::xpcf::uuids::uuid childId){
        if (m_children.erase(childId) == 1){
            return true;
        }
        return false;
    }

    bool StorageWorldElement::removeParent(org::bcom::xpcf::uuids::uuid parentId){
        if (m_parents.erase(parentId) == 1){
            return true;
        }
        return false;
    }

    bool StorageWorldElement::hasChild(org::bcom::xpcf::uuids::uuid childId){
        auto it = m_children.find(childId);
        if(it != m_children.end()){
            return true;
        }
        return false;
    }

    bool StorageWorldElement::hasParent(org::bcom::xpcf::uuids::uuid parentId){
        auto it = m_parents.find(parentId);
        if(it != m_parents.end()){
            return true;
        }
        return false;
    }

    std::pair<SRef<StorageWorldElement>, Transform3Df> StorageWorldElement::getParentWithTransform(org::bcom::xpcf::uuids::uuid parentId){
        if (hasParent(parentId)){
            auto it = m_parents.find(parentId);
            return it->second;
        }
        return {SRef<StorageWorldElement>{nullptr}, Transform3Df()};
    }

    template<typename Archive>
    void StorageWorldElement::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
        ar & m_id;
        ar & m_creatorId;
        ar & m_localCRS;
        ar & m_unitSystem;
        ar & m_size;
        ar & m_parents;
        ar & m_children;
        ar & m_tags;
    }

    IMPLEMENTSERIALIZE(StorageWorldElement);

}
}
