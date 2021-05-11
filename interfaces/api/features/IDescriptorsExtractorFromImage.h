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
#include "api/features/IDescriptorsExtractor.h"
#include "datastructure/Keypoint.h"
#include "datastructure/Image.h"
#include "datastructure/DescriptorBuffer.h"
#include "core/Messages.h"


// Definition of IDescriptorsExtractorFromImage Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"

namespace SolAR {
namespace api {
namespace features {



/**
 * @class IDescriptorsExtractorFromImage
 * @brief <B>Extracts descriptors from a set of keypoints.</B>
 * <TT>UUID: 1eab2c72-a1e0-11eb-bcbc-0242ac130002</TT>
 *
 * This class provides a method to extract descriptors directly from an image
 */
    class  IDescriptorsExtractorFromImage : virtual public org::bcom::xpcf::IComponentIntrospect {
    public:
        /// @brief IDescriptorsExtractorFromImage default constructor
        IDescriptorsExtractorFromImage() = default;

       /// @brief IDescriptorsExtractorFromImage default destructor
       virtual ~IDescriptorsExtractorFromImage() {};

       ///
       /// @brief getType
       /// @return a string describing the type of descriptor used during extraction.
       ///
       virtual std::string  getTypeString() = 0;

       ///
       /// @brief extract the descriptors directly from an image
       /// @param[in] image The image on which the keypoints have been detected
       /// @param[out] keypoints The set of keypoints on which the descriptors are extracted
       /// @param[out] descriptors The extracted descriptors. The nth descriptor corresponds to the nth keypoint of the second argument.
       ///
       virtual FrameworkReturnCode extract (const SRef<SolAR::datastructure::Image> image,
                                            std::vector<SolAR::datastructure::Keypoint> &keypoints,
                                            SRef<SolAR::datastructure::DescriptorBuffer> & descriptors) = 0;

    };

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IDescriptorsExtractorFromImage,
                             "c0e49ff1-0696-4fe6-85a8-9b2c1e155d2e",
                             "IDescriptorsExtractorFromImage",
                             "SolAR::api::features::IDescriptorsExtractorFromImage");


#endif // IDescriptorsExtractorFromImageFROMIMAGE_H
