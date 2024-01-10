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

#ifndef ISTRUCTUREFROMMOTION_H
#define ISTRUCTUREFROMMOTION_H


#include <xpcf/api/IComponentIntrospect.h>
#include "core/Messages.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/Keypoint.h"
#include "datastructure/Map.h"

namespace SolAR {
namespace api {
namespace sfm {

/**
 * @class IStructureFromMotion
 * @brief <B>Create a sparse point cloud and estimate camera poses from a set of images.</B>
 * <TT>UUID: 3681e09b-1704-4a08-b1cd-42d5a7c961b4</TT>
 *
 */

class XPCF_IGNORE IStructureFromMotion : virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    ///@brief IStructureFromMotion default constructor.
    IStructureFromMotion() = default;

    ///@brief IStructureFromMotion default destructor.
    virtual ~IStructureFromMotion() override = default;

    /// @brief Create map
    /// @param[in] keyframe: the keyframe to add to the bag of words
    /// @return FrameworkReturnCode::_SUCCESS if the keyfram adding succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(std::vector<SRef<SolAR::datastructure::Image>>& images,
                                          SRef<SolAR::datastructure::Map>& map) = 0; //last argument for test
};


} // namespace sfm
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::sfm::IStructureFromMotion,
                             "3681e09b-1704-4a08-b1cd-42d5a7c961b4",
                             "IStructureFromMotion",
                             "IStructureFromMotion interface description");

#endif // ISTRUCTUREFROMMOTION_H
