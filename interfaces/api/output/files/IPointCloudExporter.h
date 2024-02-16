/**
 * @copyright Copyright (c) 2022 B-com http://www.b-com.com/
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

#ifndef SOLAR_IPOINTCLOUDEXPORTER_H
#define SOLAR_IPOINTCLOUDEXPORTER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>

#include "core/Messages.h"
#include "datastructure/PointCloud.h"

namespace SolAR::api::output::files 
{

/**
 * @class IPointCloudExporter
 * @brief <B>Exports a point cloud to a file.</B>
 * <TT>UUID: 8e2ec8f9-ed99-473d-84eb-7cb35eff6a1e</TT>
 *
 */
class XPCF_IGNORE IPointCloudExporter :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    IPointCloudExporter() = default;
    virtual ~IPointCloudExporter() = default;

    /// @brief Export a PointCloud to a file
    /// @param[in] pointCloud: the point cloud to export
    /// @return FrameworkReturnCode::_SUCCESS if export succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode exportPointCloud(const SRef<SolAR::datastructure::PointCloud> & pointCloud) = 0;
};

} // namespace SolAR::api::output::files 


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::output::files::IPointCloudExporter,
                             "8e2ec8f9-ed99-473d-84eb-7cb35eff6a1e",
                             "IPointCloudExporter",
                             "Export a point cloud to a file");


#endif // SOLAR_IPOINTCLOUDEXPORTER_H
