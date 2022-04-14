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

#include <xpcf/core/helpers.h>

#include "core/Log.h"
#include "datastructure/Trackable.h"

namespace SolAR {
namespace datastructure {

    StorageTrackable::StorageTrackable(const std::string & url) : m_url(url) {
    }

    StorageTrackable::StorageTrackable(const org::bcom::xpcf::uuids::uuid &creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                                       Vector3d size, const std::map<org::bcom::xpcf::uuids::uuid, std::pair<SRef<StorageWorldElement>, Transform3Df>> &parents,
                                       const std::map<org::bcom::xpcf::uuids::uuid, SRef<StorageWorldElement>> &children, const std::multimap<std::string, std::string> &tags,
                                       StorageTrackableType type, EncodingInfo encodingInfo, const std::vector<std::byte> &payload) : StorageWorldElement(creatorId, localCRS, unitSystem,
                                                                                                                                                   size, parents,
                                                                                                                                                   children, tags)
    {
        m_type = type;
        m_encodingInfo = encodingInfo;
        m_payload = payload;
        //TODO extraction des features et les mettre dans m_url?
    }

    std::string StorageTrackable::getURL() const {
        return m_url;
    }

    void StorageTrackable::setURL(const std::string & url) {
        m_url = url;
    }

    const datastructure::EncodingInfo &StorageTrackable::getEncodingInfo() const
    {
        return m_encodingInfo;
    }

    void StorageTrackable::setEncodingInfo(const datastructure::EncodingInfo &newEncodingInfo)
    {
        m_encodingInfo = newEncodingInfo;
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
        ar & m_type;
        ar & m_encodingInfo;
        ar & m_payload;
    }

    ElementKind StorageTrackable::getKind()
    {
        return ElementKind::TRACKABLE;
    }

    IMPLEMENTSERIALIZE(StorageTrackable);

}
}
