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

#ifndef IMAPUPDATE_H
#define IMAPUPDATE_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Map.h"

namespace SolAR {
namespace api {
namespace solver {
namespace map {
/**
* @class IMapUpdate
* @brief <B>Allow to update the global map after merging a local map into the global map.</B>
* <TT>UUID: 943dd9a0-4889-489a-80a7-84be1a6c1650</TT>
*/

class [[xpcf::clientUUID("2c2b7702-6a34-4add-b645-547ef0185253")]] [[xpcf::serverUUID("4c496a20-693c-4729-93dc-7c2b06157604")]] IMapUpdate :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IMapUpdate default constructor
	IMapUpdate() = default;

	/// @brief IMapUpdate default destructor
	virtual ~IMapUpdate() = default;

	/// @brief Update the global map.
	/// @param[in,out] globalMap the global map
	/// @param[in] newKeyframeIds the ids of new keyframes.
	/// @return FrameworkReturnCode::_SUCCESS_ if the fusion succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode update(SRef<SolAR::datastructure::Map> globalMap,
									   const std::vector<uint32_t>& newKeyframeIds) = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IMapUpdate,
                             "943dd9a0-4889-489a-80a7-84be1a6c1650",
                             "IMapUpdate",
                             "SolAR::api::solver::map::IMapUpdate");

#endif // IMAPUPDATE_H
