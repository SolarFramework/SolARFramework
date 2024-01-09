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

#include "datastructure/StorageCapabilities.h"

#include <xpcf/core/helpers.h>
#include "datastructure/StorageTrackable.h"

namespace SolAR {
namespace datastructure {

    StorageCapabilities::StorageCapabilities(StorageTrackableType trackableType,EncodingInfo encodingInformation){
        m_trackableType = trackableType;
        m_encodingInformation = encodingInformation;
    }

    StorageTrackableType StorageCapabilities::getTrackableType() const {
        return m_trackableType;
    }

    void StorageCapabilities::setTrackableType(StorageTrackableType newTrackableType) {
         m_trackableType = newTrackableType;
    }

    EncodingInfo StorageCapabilities::getEncodingInformation() const {
         return m_encodingInformation;
    }

    void StorageCapabilities::setEncodingInformation(EncodingInfo newEncodingInformation) {
         m_encodingInformation = newEncodingInformation;
    }

    bool StorageCapabilities::equals(StorageCapabilities capability){
         if (m_trackableType != capability.m_trackableType) {
             return false;
         }
         bool dataformat = m_encodingInformation.getDataFormat() == capability.m_encodingInformation.getDataFormat();
         bool version = m_encodingInformation.getVersion() == capability.m_encodingInformation.getVersion();
         if (!(version && dataformat) ) {
             return false;
         }
         return true;
    }

}

}
