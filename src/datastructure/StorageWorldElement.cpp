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
                                             Vector3d size, SRef<StorageWorldElement> parent, Transform3Df transformFromParent,
                                             std::map<org::bcom::xpcf::uuids::uuid, SRef<StorageWorldElement>> children, std::multimap<std::string, std::string> tags){
        m_id = org::bcom::xpcf::uuids::random_generator()();
        m_creatorId = creatorId;
        m_localCRS = localCRS;
        m_unitSystem = unitSystem;
        m_size = size;
        m_parent = parent;
        m_transformFromParent = transformFromParent;
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

    SRef<StorageWorldElement> StorageWorldElement::getParent() const{
        return m_parent;
    }

    void StorageWorldElement::setParent(const SRef<StorageWorldElement> parent){
        m_parent = parent;
    }

    Transform3Df StorageWorldElement::getTransform() const{
        return m_transformFromParent;
    }

    void StorageWorldElement::setTransform(const Transform3Df newTransform){
        m_transformFromParent = newTransform;
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

    template<typename Archive>
    void StorageWorldElement::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
        ar & m_id;
        ar & m_creatorId;
        ar & m_localCRS;
        ar & m_unitSystem;
        ar & m_size;
        ar & m_parent;
        ar & m_transformFromParent;
        ar & m_children;
        ar & m_tags;
    }

    IMPLEMENTSERIALIZE(StorageWorldElement);

}
}
