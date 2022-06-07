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

#include "datastructure/StorageWorldLink.h"

#include <xpcf/core/helpers.h>

#include "core/Log.h"

namespace SolAR {
namespace datastructure {

    StorageWorldLink::StorageWorldLink(const org::bcom::xpcf::uuids::uuid &author, boost::uuids::uuid uuidFrom,
                                       boost::uuids::uuid uuidTo, ElementKind typeFrom, ElementKind typeTo, Transform3Df transform)
    {
        m_id = org::bcom::xpcf::uuids::random_generator()();
        m_author = author;
        m_uuidFrom = uuidFrom;
        m_uuidTo = uuidTo;
        m_typeFrom = typeFrom;
        m_typeTo = typeTo;
        m_transform = transform;
        LOG_DEBUG("Link constructor with id = {}", org::bcom::xpcf::uuids::to_string(m_id));
    }

    StorageWorldLink::StorageWorldLink(const org::bcom::xpcf::uuids::uuid &id, const org::bcom::xpcf::uuids::uuid &author, boost::uuids::uuid uuidFrom,
                                       boost::uuids::uuid uuidTo, ElementKind typeFrom, ElementKind typeTo, Transform3Df transform)
    {
        m_id = id;
        m_author = author;
        m_uuidFrom = uuidFrom;
        m_uuidTo = uuidTo;
        m_typeFrom = typeFrom;
        m_typeTo = typeTo;
        m_transform = transform;
        LOG_DEBUG("Link constructor with id = {}", org::bcom::xpcf::uuids::to_string(m_id));
    }

    const org::bcom::xpcf::uuids::uuid &StorageWorldLink::getId() const
    {
        return m_id;
    }

    const org::bcom::xpcf::uuids::uuid &StorageWorldLink::getAuthor() const
    {
        return m_author;
    }

    void StorageWorldLink::setAuthor(const org::bcom::xpcf::uuids::uuid &newAuthor){
        m_author = newAuthor;
    }

    const Transform3Df &StorageWorldLink::getTransform() const
    {
        return m_transform;
    }

    void StorageWorldLink::setTransform(const Transform3Df &newTransform)
    {
        m_transform = newTransform;
    }

    std::pair<org::bcom::xpcf::uuids::uuid, org::bcom::xpcf::uuids::uuid> StorageWorldLink::getAttachedIds() const
    {
        return {m_uuidFrom, m_uuidTo};
    }

    const boost::uuids::uuid &StorageWorldLink::getUuidFrom() const
    {
        return m_uuidFrom;
    }

    void StorageWorldLink::setUuidFrom(const boost::uuids::uuid &newUuidFrom)
    {
        m_uuidFrom = newUuidFrom;
    }

    const boost::uuids::uuid &StorageWorldLink::getUuidTo() const
    {
        return m_uuidTo;
    }

    void StorageWorldLink::setUuidTo(const boost::uuids::uuid &newUuidTo)
    {
        m_uuidTo = newUuidTo;
    }

    ElementKind StorageWorldLink::getTypeFrom() const
    {
        return m_typeFrom;
    }

    void StorageWorldLink::setTypeFrom(ElementKind newTypeFrom)
    {
        m_typeFrom = newTypeFrom;
    }

    ElementKind StorageWorldLink::getTypeTo() const
    {
        return m_typeTo;
    }

    void StorageWorldLink::setTypeTo(ElementKind newTypeTo)
    {
        m_typeTo = newTypeTo;
    }

    UnitSystem StorageWorldLink::unitSystem() const
    {
        return m_unitSystem;
    }

    void StorageWorldLink::setUnitSystem(UnitSystem newUnitSystem)
    {
        m_unitSystem = newUnitSystem;
    }

    const std::multimap<std::string, std::string> &StorageWorldLink::tags() const
    {
        return m_tags;
    }

    void StorageWorldLink::setTags(const std::multimap<std::string, std::string> &newTags)
    {
        m_tags = newTags;
    }

    template<typename Archive>
    void StorageWorldLink::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
        ar & m_id;
        ar & m_author;
        ar & m_uuidFrom;
        ar & m_uuidTo;
        ar & m_typeFrom;
        ar & m_typeTo;
        ar & m_transform;
    }

    IMPLEMENTSERIALIZE(StorageWorldLink);

}
}
