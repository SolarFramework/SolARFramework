/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
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

#ifndef SOLAR_IPCFILTER_H
#define SOLAR_IPCFILTER_H

#include "xpcf/api/IComponentIntrospect.h"
#include <xpcf/core/helpers.h>
#include "datastructure/PointCloud.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace pointCloud {

/**
  * @class IPCFilter
  * @brief <B>Filters a point cloud</B>
  * <TT>UUID: 3e068943-5230-4e6c-abd7-959f293f9829</TT>
  */

class XPCF_CLIENTUUID("34192941-748e-4521-8d30-e12c06f5e226") XPCF_SERVERUUID("44842913-0e76-44bc-84ae-c8a0850ac97e") IPCFilter :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
   /// @brief IPCFilter default constructor
   IPCFilter() = default;

   /// @brief IPCFilter default destructor
   virtual ~IPCFilter() = default;

   /// @brief Filter a point cloud
   /// @param[in] inPointCloud: The point cloud to filter
   /// @param[out] outPointCloud: The resulting point cloud after filtering
   virtual FrameworkReturnCode filter(const SRef<SolAR::datastructure::PointCloud> inPointCloud,
                                      SRef<SolAR::datastructure::PointCloud> & outPointCloud) const = 0;

};
}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pointCloud::IPCFilter,
                             "3e068943-5230-4e6c-abd7-959f293f9829",
                             "IPCFilter",
                             "Interface for point cloud filtering");


#endif // SOLAR_IPCFILTER_H
