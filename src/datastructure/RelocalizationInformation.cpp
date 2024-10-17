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

#include "datastructure/RelocalizationInformation.h"

#include <xpcf/core/helpers.h>

namespace SolAR {
namespace datastructure {

    RelocalizationInformation::RelocalizationInformation(const org::bcom::xpcf::uuids::uuid &rootUUID,const std::vector<RelocObject> relocObjects, const bool deviceToWorldAnchor) {
        m_rootUUID= rootUUID;
        m_relocObjects= relocObjects;
        m_deviceToWorldAnchor = deviceToWorldAnchor;
    }

    org::bcom::xpcf::uuids::uuid RelocalizationInformation::getRootUUID() const {
        return m_rootUUID;
    };

    void RelocalizationInformation::setRootUUID(org::bcom::xpcf::uuids::uuid uuid) {
        m_rootUUID = uuid;
    };

    const std::vector<RelocObject> RelocalizationInformation::getRelocObjects() const {
        return m_relocObjects;
    };

    void RelocalizationInformation::setRelocObjects(std::vector<RelocObject> NewRelocObjects){
        m_relocObjects = NewRelocObjects;
    };

    bool RelocalizationInformation::isDeviceToWorldAnchor() const{
      return m_deviceToWorldAnchor;
    };


    void RelocalizationInformation::setDeviceToWorldAnchor(bool newDeviceToWorldAnchor){
        m_deviceToWorldAnchor = newDeviceToWorldAnchor;
    };

    template<typename Archive>
    void RelocObject::serialize(Archive &ar, const unsigned int /* version */ )
    {
        ar & boost::serialization::make_nvp("trackable", m_trackable);
        ar & boost::serialization::make_nvp("transform", m_transform3D);
    }

    template<typename Archive>
    void RelocalizationInformation::serialize(Archive &ar, const unsigned int /* version */)
    {
        ar & boost::serialization::make_nvp("rootUUID", m_rootUUID);
        ar & boost::serialization::make_nvp("relocObjects", m_relocObjects);
        ar & boost::serialization::make_nvp("deviceToWorldAnchor", m_deviceToWorldAnchor);
    }

    IMPLEMENTSTORAGESERIALIZE(RelocObject);
    IMPLEMENTSTORAGESERIALIZE(RelocalizationInformation);

}

}
