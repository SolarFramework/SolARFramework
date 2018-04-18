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

#ifndef SOLAR_ITHIRDPARTYCONNECTOR_H
#define SOLAR_ITHIRDPARTYCONNECTOR_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of IThirdPartyConnector Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"
#include "datastructure/Pose.h"
#include "datastructure/Image.h"

namespace SolAR {
using namespace datastructure;

namespace api {
namespace sink {

///
/// \brief The IThirdPartyConnector class
///
class  IThirdPartyConnector : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
   IThirdPartyConnector() = default;

   ///
   /// \brief ~IThirdPartyConnector
   ///
   virtual ~IThirdPartyConnector() {};
   virtual void set( const SRef<Pose>& pose, const SRef<Image>& image ) = 0;
   virtual void get( SRef<Pose>& pose, SRef<Image>& image ) = 0;
   virtual bool tryGet( SRef<Pose>& pose, SRef<Image>& image ) = 0;

};

}
}
}  // end of namespace SolAR

template <> struct org::bcom::xpcf::InterfaceTraits<SolAR::api::sink::IThirdPartyConnector>
{
    static constexpr const char * UUID = "c0d9fee4-d7d7-4866-a6cd-3bacac23316a";
    static constexpr const char * DESCRIPTION = "SolAR::IThirdPartyConnector interface";
};

#endif // SOLAR_ITHIRDPARTYCONNECTOR_H
