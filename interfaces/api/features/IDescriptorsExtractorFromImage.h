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

#ifndef IDescriptorsExtractorFromImageFROMIMAGE_H
#define IDescriptorsExtractorFromImageFROMIMAGE_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <vector>
#include "datastructure/Keypoint.h"
#include "datastructure/Image.h"
#include "datastructure/DescriptorBuffer.h"
#include "core/Messages.h"
#include <xpcf/core/helpers.h>


// Definition of IDescriptorsExtractorFromImage Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"

namespace SolAR {
namespace api {
namespace features {

/**
 * @class IDescriptorsExtractorFromImage
 * @brief <B>Detect keypoints and compute the descriptors from an image.</B>
 * <TT>UUID: 1cd4f5f1-6b74-413b-9725-69653aee48ef</TT>
 *
 * This class provides a method to extract descriptors directly from an image
 */
class XPCF_CLIENTUUID("6ed44a98-6743-414e-84de-970fab9b3507") XPCF_SERVERUUID("1df6caec-4032-48ae-9a46-72e40aadf0a5") IDescriptorsExtractorFromImage :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IDescriptorsExtractorFromImage default constructor
    IDescriptorsExtractorFromImage() = default;

    /// @brief IDescriptorsExtractorFromImage default destructor
    virtual ~IDescriptorsExtractorFromImage() {};

    /// @brief getType
    /// @return a string describing the type of descriptor used during extraction.
    virtual std::string  getTypeString() = 0;

    /// @brief detect keypoints and compute the descriptors.
    /// @param[in] image image on which the keypoint and their descriptor will be detected and extracted.
    /// @param[out] keypoints The keypoints detected in the input image.
    /// @param[out] descriptors The descriptors of keypoints of the input image.
    /// @return FrameworkReturnCode::_SUCCESS_ if images are well matched, else FrameworkReturnCode::_ERROR
    virtual FrameworkReturnCode extract(const SRef<SolAR::datastructure::Image> image,
                                        std::vector<SolAR::datastructure::Keypoint> &keypoints,
                                        SRef<SolAR::datastructure::DescriptorBuffer> & descriptors) = 0;

};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IDescriptorsExtractorFromImage,
                             "1cd4f5f1-6b74-413b-9725-69653aee48ef",
                             "IDescriptorsExtractorFromImage",
                             "SolAR::api::features::IDescriptorsExtractorFromImage");


#endif // IDescriptorsExtractorFromImageFROMIMAGE_H
