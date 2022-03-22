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

#include "datastructure/StorageTrackable.h"
#include "datastructure/Trackable.h"
#include "core/Log.h"

#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {

    StorageTrackable::StorageTrackable(const std::string & url) : m_url(url) {
        LOG_DEBUG("StorageTrackable constructor with url = {}", url);
    }

    StorageTrackable::StorageTrackable(org::bcom::xpcf::uuids::uuid author, datastructure::StorageTrackableType type,
                         datastructure::EncodingInfo encodingInfo, std::vector<std::byte> payload, datastructure::Transform3Df localCrs,
                         datastructure::UnitSystem unitSystem, datastructure::Vector3d scale,
                         std::multimap<std::string, std::string> tags) : StorageWorldElement(tags)
    {
        m_author = author;
        m_type = type;
        m_encodingInfo = encodingInfo;
        m_payload = payload;
        m_LocalCrs = localCrs;
        m_unitSystem = unitSystem;
        m_scale = scale;
        //TODO extraction des features et les mettre dans m_url?
    }

    std::string StorageTrackable::getURL() const {
        return m_url;
    }

    void StorageTrackable::setURL(const std::string & url) {
        m_url = url;
    }

    const org::bcom::xpcf::uuids::uuid &StorageTrackable::getAuthor() const
    {
        return m_author;
    }

    void StorageTrackable::setAuthor(const org::bcom::xpcf::uuids::uuid &newAuthor)
    {
        m_author = newAuthor;
    }

    const datastructure::EncodingInfo &StorageTrackable::getEncodingInfo() const
    {
        return m_encodingInfo;
    }

    void StorageTrackable::setEncodingInfo(const datastructure::EncodingInfo &newEncodingInfo)
    {
        m_encodingInfo = newEncodingInfo;
    }

    const datastructure::Transform3Df &StorageTrackable::getLocalCrs() const
    {
        return m_LocalCrs;
    }

    void StorageTrackable::setLocalCrs(const datastructure::Transform3Df &newLocalCrs)
    {
        m_LocalCrs = newLocalCrs;
    }

    UnitSystem StorageTrackable::getUnitSystem() const
    {
        return m_unitSystem;
    }

    void StorageTrackable::setUnitSystem(UnitSystem newUnitSystem)
    {
        m_unitSystem = newUnitSystem;
    }

    const datastructure::Vector3d &StorageTrackable::getScale() const
    {
        return m_scale;
    }

    void StorageTrackable::setScale(const datastructure::Vector3d &newScale)
    {
        m_scale = newScale;
    }

    const std::vector<std::byte> &StorageTrackable::getPayload() const
    {
        return m_payload;
    }

    void StorageTrackable::setPayload(const std::vector<std::byte> &newPayload)
    {
        m_payload = newPayload;
    }

    StorageTrackableType StorageTrackable::getType() const{
        return m_type;
    }

    void StorageTrackable::setType(datastructure::StorageTrackableType newType)
    {
        m_type = newType;
    }

    template<typename Archive>
    void StorageTrackable::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {


        ar & boost::serialization::base_object<StorageWorldElement>(*this);
        ar & m_url;
        ar & m_author;
        ar & m_type;
        ar & m_encodingInfo;
        ar & m_payload;
        ar & m_LocalCrs;
        ar & m_unitSystem;
        ar & m_scale;
    }

    bool StorageTrackable::isWorldAnchor() {
        return false;
    }

    bool StorageTrackable::isWorldLink() {
        return false;
    }

    bool StorageTrackable::isTrackable() {
        return true;
    }

    IMPLEMENTSERIALIZE(StorageTrackable);

}
}
