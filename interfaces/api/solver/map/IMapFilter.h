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

#ifndef IMAPFILTER_H
#define IMAPFILTER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of IMapFilter Class //
// part of SolAR namespace //

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/CloudPoint.h"

namespace SolAR {
namespace api {
namespace solver {
namespace map {
/**
* @class IMapFilter
* @brief <B>Filters a map of 3D points.</B>
* <TT>UUID: 68dc9152-5199-11ea-8d77-2e728ce88125</TT>
*/
class XPCF_IGNORE IMapFilter :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IMapFilter default constructor
    IMapFilter() = default;

    /// @brief IMapFilter default destructor
    virtual ~IMapFilter() {}

    /// @brief  Filter point cloud reconstructed from 2 viewpoints
    /// @param[in] pose1: the first pose used for building the point cloud.
    /// @param[in] pose2: the second pose used for building the point cloud.
    /// @param[in] input: The set of points to filter
    /// @param[out] output: the filtered point cloud
    virtual void  filter(const SolAR::datastructure::Transform3Df & pose1, const SolAR::datastructure::Transform3Df & pose2, const std::vector<SRef<SolAR::datastructure::CloudPoint>> & input,  std::vector<SRef<SolAR::datastructure::CloudPoint>> & output) = 0;

	/// @brief  Filter point cloud reconstructed from 2 viewpoints
	/// @param[in] pose1: the first pose used for building the point cloud.
	/// @param[in] pose2: the second pose used for building the point cloud.
	/// @param[in] input: The set of points to filter
	/// @param[out] output: the filtered point cloud
	/// @param[out] index: the index of filtered point cloud
	virtual void  filter(const SolAR::datastructure::Transform3Df & pose1, const SolAR::datastructure::Transform3Df & pose2, const std::vector<SRef<SolAR::datastructure::CloudPoint>>& input, std::vector<SRef<SolAR::datastructure::CloudPoint>>& output, std::vector<int> &index) = 0;
};
}

}
}
}
XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IMapFilter,
                             "68dc9152-5199-11ea-8d77-2e728ce88125",
                             "IMapFilter",
                             "SolAR::api::solver::map::IMapFilter interface defines how to filter a reconstructed point cloud from 2 viewpoints.");


#endif // IMapFilter_H
