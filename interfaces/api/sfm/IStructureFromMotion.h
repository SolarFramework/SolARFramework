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


#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"
#include "core/Messages.h"
#include "datastructure/Map.h"

namespace SolAR {
namespace api {
namespace sfm {

/**
 * @class IStructureFromMotion
 * @brief <B>???</B>
 * <TT>UUID: 3681e09b-1704-4a08-b1cd-42d5a7c961b4</TT>
 *
 * ???
 */

class IStructureFromMotion : virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    ///@brief IStructureFromMotion default constructor.
    IStructureFromMotion() = default;

    ///@brief IStructureFromMotion default destructor.
    virtual ~IStructureFromMotion() override = default;

    /// @brief Create map
    /// @param[in] keyframe: the keyframe to add to the bag of words
    /// @return FrameworkReturnCode::_SUCCESS if the keyfram adding succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(SRef<SolAR::datastructure::Map>& map) = 0;
};


} // namespace sfm
} // namespace api
} // namespace SolAR


template <> struct org::bcom::xpcf::InterfaceTraits<SolAR::api::sfm::IStructureFromMotion>
{
    static constexpr const char * UUID = "{3681e09b-1704-4a08-b1cd-42d5a7c961b4}";
    static constexpr const char * NAME = "IStructureFromMotion";
    static constexpr const char * DESCRIPTION = "IStructureFromMotion interface description";
};

#endif // ISTRUCTUREFROMMOTION_H
