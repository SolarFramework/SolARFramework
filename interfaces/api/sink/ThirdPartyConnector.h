/**
 * @copyright Copyright (c) 2017 b<>com http://www.b-com.com/
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

#ifndef SOLAR_THIRDPARTYCONNECTOR_H
#define SOLAR_THIRDPARTYCONNECTOR_H

#include <string>
#include <utility>

#include "api/sink/IThirdPartyConnector.h"
// Definition of ThirdPartyConnector Class //
// part of SolAR namespace //

#include "ComponentBase.h"
#include "SharedCircularBuffer.hpp"

namespace SolAR {
using namespace datastructure;

class SOLARFRAMEWORK_API ThirdPartyConnector : public org::bcom::xpcf::ComponentBase,
        public SolAR::api::sink::IThirdPartyConnector {
public:
    ThirdPartyConnector();
    virtual ~ThirdPartyConnector();
    void unloadComponent () override final;


    void set( const SRef<Pose>& pose, const SRef<Image>& image ) override;
    void get( SRef<Pose>& pose, SRef<Image>& image ) override;
    bool tryGet( SRef<Pose>& pose, SRef<Image>& image ) override;

    XPCF_DECLARE_UUID("bb292de7-8f87-4a23-8b23-c4d9e8a64f8d");

protected:
    typedef std::pair<SRef<Pose>, SRef<Image>> connectorDataType;

    SharedCircularBuffer<connectorDataType> m_buffer;
private:
};

}  // end of namespace SolAR



#endif // SOLAR_THIRDPARTYCONNECTOR_H
