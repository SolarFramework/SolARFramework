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

#include "datastructure/StorageWorldLink.h"
#include "core/Log.h"

#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {

    StorageWorldLink::StorageWorldLink(org::bcom::xpcf::uuids::uuid author, org::bcom::xpcf::uuids::uuid fromElement,
                                       org::bcom::xpcf::uuids::uuid toElement, Transform3Df transform,
                                       UnitSystem unitSystem, Vector3d scale,
                                       std::multimap<std::string, std::string> tags)
    {
        m_author = author;
        m_fromElement = fromElement;
        m_toElement = toElement;
        m_transform = transform;
        m_unitSystem = unitSystem;
        m_scale = scale;
        m_tags = tags;
    }

    const org::bcom::xpcf::uuids::uuid &StorageWorldLink::getAuthor() const
    {
        return m_author;
    }

    void StorageWorldLink::setAuthor(const org::bcom::xpcf::uuids::uuid &newAuthor){
        m_author = newAuthor;
    }

    const org::bcom::xpcf::uuids::uuid &StorageWorldLink::getFromElement() const
    {
        return m_fromElement;
    }

    void StorageWorldLink::setFromElement(const org::bcom::xpcf::uuids::uuid &newFromElement)
    {
        m_fromElement = newFromElement;
    }

    const org::bcom::xpcf::uuids::uuid &StorageWorldLink::getToElement() const
    {
        return m_toElement;
    }

    void StorageWorldLink::setToElement(const org::bcom::xpcf::uuids::uuid &newToElement)
    {
        m_toElement = newToElement;
    }

    const Transform3Df &StorageWorldLink::getTransform() const
    {
        return m_transform;
    }

    void StorageWorldLink::setTransform(const Transform3Df &newTransform)
    {
        m_transform = newTransform;
    }

    UnitSystem StorageWorldLink::getUnitSystem() const
    {
        return m_unitSystem;
    }

    void StorageWorldLink::setUnitSystem(UnitSystem newUnitSystem)
    {
        m_unitSystem = newUnitSystem;
    }

    const Vector3d &StorageWorldLink::getScale() const
    {
        return m_scale;
    }

    void StorageWorldLink::setScale(const Vector3d &newScale)
    {
        m_scale = newScale;
    }

    template<typename Archive>
    void StorageWorldLink::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {

        ar & boost::serialization::base_object<StorageWorldElement>(*this);
        ar & m_author;
        ar & m_fromElement;
        ar & m_toElement;
        ar & m_transform;
        ar & m_unitSystem;
        ar & m_scale;
    }

    bool StorageWorldLink::isWorldAnchor() {
        return false;
    }

    bool StorageWorldLink::isWorldLink() {
        return true;
    }

    bool StorageWorldLink::isTrackable() {
        return false;
    }

    IMPLEMENTSERIALIZE(StorageWorldLink);

}
}
