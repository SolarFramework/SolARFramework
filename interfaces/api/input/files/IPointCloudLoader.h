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

#ifndef SOLAR_IPOINTCLOUDLOADER_H
#define SOLAR_IPOINTCLOUDLOADER_H

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/PointCloud.h"

namespace SolAR {
namespace api {
namespace input {
namespace files {
/**
 * @class IPointCloudLoader
 * @brief <B>Loads a point cloud from a file.</B>
 * <TT>UUID: 1abd8117-87d3-4c6c-8fb6-c2fdb7359ee2</TT>
 *
 */
class XPCF_CLIENTUUID("dd80a6fa-db2f-4ba7-ba69-5207a68cfb03") XPCF_SERVERUUID("19780d21-e6a8-4f28-bf63-483f50b2af9d") IPointCloudLoader :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    IPointCloudLoader() = default;
    virtual ~IPointCloudLoader() = default;

	/// @brief Load a PointCloud from a filepath (.pcd or .ply)
    /// @param[out] pointCloud: the point cloud to fill
	/// @return FrameworkReturnCode::_SUCCESS if load succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode load(SRef<SolAR::datastructure::PointCloud> & pointCloud) = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::files::IPointCloudLoader,
                             "1abd8117-87d3-4c6c-8fb6-c2fdb7359ee2",
                             "IPointCloudLoader",
                             "Load a point cloud from a file");


#endif // SOLAR_IPOINTCLOUDLOADER_H
