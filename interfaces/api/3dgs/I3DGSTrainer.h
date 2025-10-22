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

#ifndef I3DGSTRAINER_H
#define I3DGSTRAINER_H

#include "datastructure/GeometryDefinitions.h"
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/Map.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace gs {


/**
 * @class I3DGSTrainer
 * @brief <B>Train 3DGS representation.</B>
 * <TT>UUID: 92a32628-53c4-4ddc-956c-ca8a4cecd90f</TT>
 */

class XPCF_IGNORE I3DGSTrainer :
                                          virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief I3DGSTrainer default constructor.
    I3DGSTrainer() = default;

    ///@brief I3DGSTrainer default destructor.
    virtual ~I3DGSTrainer() = default;

    /// @brief Perform 2D instance segmentation
    /// @param[in] image The input image (SRef<const Image> is not used here in order to give more freedom to the implementations, e.g. torch::from_blob only accepts a non-const data buffer as input).
    /// @param[out] boxes The bounding boxes of each detected object.
    /// @return FrameworkReturnCode::_SUCCESS if the segmentation succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode train(SRef<Map>sfmMap, std::string&outputPly) = 0;
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::gs::I3DGSTrainer,
                             "92a32628-53c4-4ddc-956c-ca8a4cecd90f",
                             "I3DGSTrainer",
                             "Interface SolAR::api::3dgs::I3DGSTrainer");

#endif // ID3GSTRAINER_H
