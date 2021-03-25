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

#ifndef IMAPFUSION_H
#define IMAPFUSION_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "api/solver/map/IMapper.h"

namespace SolAR {
namespace api {
namespace solver {
namespace map {
/**
* @class IMapFusion
* @brief <B>Allow to merge local map or floating map in the global map.</B>
* <TT>UUID: eb9b9921-b063-42a8-8282-9ed53ee21d96</TT>
*/

class  IMapFusion : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IMapFusion default constructor
	IMapFusion() = default;

	/// @brief IMapFusion default destructor
	virtual ~IMapFusion() = default;

	/// @brief Merge a map in the global map. The map can be a local map (know transformation to the global map) or a floating map.
	/// @param[in,out] map: local map or floating map to merge
	/// @param[in,out] globalMap: the global map
	/// @param[in,out] transform: the transformation to the global map (null for floating map). It can be refined by fusion process.
	/// @param[out] nbMatches: the number of matched cloud points.
    /// @param[out] error: the error of fusion process that is the mean of error distances of the matched cloud points.
	/// @return FrameworkReturnCode::_SUCCESS_ if the fusion succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode merge(SRef<IMapper> map,
                                    SRef<IMapper> globalMap,
                                    SolAR::datastructure::Transform3Df &transform,
									uint32_t &nbMatches, 
									float &error) = 0;

	/// @brief Merge a map in the global map. The map can be a local map (know transformation to the global map) or a floating map.
	/// @param[in,out] map: local map or floating map to merge
	/// @param[in,out] globalMap: the global map	
	/// @param[in,out] transform: the transformation to the global map (null for floating map). It can be refined by fusion process.
	/// @param[in] cpOverlapIndices : pairs of detected overlap cloud points indices of floating map and global map.
	/// @param[in] isRefineTransform : refine the 3D transformation if it's true.
	/// @return FrameworkReturnCode::_SUCCESS_ if the fusion succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode merge(SRef<IMapper> map,
                                    SRef<IMapper> globalMap,
                                    SolAR::datastructure::Transform3Df &transform,
									const std::vector<std::pair<uint32_t, uint32_t>>&cpOverlapIndices,
                                    bool isRefineTransform = false) = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IMapFusion,
                             "eb9b9921-b063-42a8-8282-9ed53ee21d96",
                             "IMapFusion",
                             "SolAR::api::solver::map::IMapFusion");

#endif // IMAPFUSION_H
