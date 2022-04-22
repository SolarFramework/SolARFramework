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

    StorageWorldLink::StorageWorldLink(org::bcom::xpcf::uuids::uuid author, SRef<StorageWorldElement> fromElement,
                                       SRef<StorageWorldElement> toElement, Transform3Df transform)
    {
        m_id = org::bcom::xpcf::uuids::random_generator()();
        m_author = author;
        m_fromElement = fromElement;
        m_toElement = toElement;
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

    SRef<StorageWorldElement> StorageWorldLink::getFromElement() const
    {
        return m_fromElement;
    }

    void StorageWorldLink::setFromElement(const SRef<StorageWorldElement> &newFromElement)
    {
        m_fromElement = newFromElement;
    }

    SRef<StorageWorldElement> StorageWorldLink::getToElement() const
    {
        return m_toElement;
    }

    void StorageWorldLink::setToElement(const SRef<StorageWorldElement> &newToElement)
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

    std::pair<const StorageWorldElement&, const StorageWorldElement&> StorageWorldLink::getAttachedElements() const
    {
        return {*m_fromElement, *m_toElement};
    }

    std::pair<org::bcom::xpcf::uuids::uuid, org::bcom::xpcf::uuids::uuid> StorageWorldLink::getAttachedIds() const
    {
        return {m_fromElement->getID(), m_toElement->getID()};
    }

    template<typename Archive>
    void StorageWorldLink::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
        ar & m_id;
        ar & m_author;
        ar & m_fromElement;
        ar & m_toElement;
        ar & m_transform;
    }

    IMPLEMENTSERIALIZE(StorageWorldLink);

}
}
