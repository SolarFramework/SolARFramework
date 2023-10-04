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

#ifndef IMESHING_H
#define IMESHING_H


#include <xpcf/api/IComponentIntrospect.h>
#include "datastructure/Map.h"
#include "datastructure/Mesh.h"

namespace SolAR {
namespace api {
namespace sfm {

/**
 * @class IMeshing
 * @brief <B>Create a 3D mesh from a 3D dense map.</B>
 * <TT>UUID: 7d810e96-fd9d-4029-a102-61fe3883a633</TT>
 */

class XPCF_IGNORE IMeshing : virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    ///@brief IStructureFromMotion default constructor.
    IMeshing() = default;

    ///@brief IMeshing default destructor.
    virtual ~IMeshing() override = default;

    /// @brief Create mesh from a dense 3D point cloud
    /// @param[in] densePointCloud: the dense poitn cloud to mesh with triangles
    /// @param[out] mesh: the resulting meshes
    /// @return FrameworkReturnCode::_SUCCESS if the meshing succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMesh(const SRef<SolAR::datastructure::PointCloud>& densePointCloud,
                                           SRef<SolAR::datastructure::Mesh>& mesh) = 0;
};


} // namespace sfm
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::sfm::IMeshing,
                             "7d810e96-fd9d-4029-a102-61fe3883a633",
                             "IMeshing",
                             "IMeshing interface description");

#endif // IMESHING_H
