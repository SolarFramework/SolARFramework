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

#ifndef SOLAR_IPCFILTERCENTROID_H
#define SOLAR_IPCFILTERCENTROID_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/PointCloud.h"
#include "datastructure/GeometryDefinitions.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace pointCloud {

/**
 * @class IPCFilterCentroid
 * @brief filters a point cloud according a given 3D point
 *
 * This class provides a filtering method to prune a point cloud according to a given 3D point.
 */

class  IPCFilterCentroid : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
   /// @brief IPCFilterCentroid default constructor
   IPCFilterCentroid() = default;

   /// @brief IPCFilterCentroid default destructor
   virtual ~IPCFilterCentroid() = default;

   /// @brief Filter a point cloud according to a given centroid
   /// @param[in] inPointCloud The point cloud to filter
   /// @param[in] centroid The 3D point of reference used to filter the point cloud.
   /// @param[out] outPointCloud The resulting point cloud after filtering
   virtual FrameworkReturnCode filter(const SRef<datastructure::PointCloud> inPointCloud, const SRef<datastructure::Point3Df> centroid, SRef<datastructure::PointCloud>& outPointCloud) const = 0;

};
}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pointCloud::IPCFilterCentroid,
                             "b293048a-1b04-4598-b2e5-7f485402acc0",
                             "IPCFilterCentroid",
                             "Interface for point cloud filtering according to a given 3D point");


#endif // SOLAR_IPCFILTERCENTROID_H
