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

#ifndef SOLAR_IDESCRIPTORSEXTRACTOR_H
#define SOLAR_IDESCRIPTORSEXTRACTOR_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <vector>
#include "datastructure/Keypoint.h"
//#include "IDescriptor.h"
#include "datastructure/Image.h"
#include "datastructure/DescriptorBuffer.h"


// Definition of IDescriptorsExtractor Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"

namespace SolAR {
namespace api {
namespace features {



/**
 * @class IDescriptorsExtractor
 * @brief <B>Extracts descriptors from a set of keypoints.</B>
 * <TT>UUID: c0e49ff1-0696-4fe6-85a8-9b2c1e155d2e</TT>
 *
 * This class provides a method to extract descriptors from a set of keypoints
 */
    class  IDescriptorsExtractor : virtual public org::bcom::xpcf::IComponentIntrospect {
	public:
        ///
        /// \brief The DescriptorsExtractorType enum
        ///
        enum class DescriptorsExtractorType {
            UNKNOWN_TYPE=-1,
            SURF,
            ORB,
            SIFT,
            DAISY,
            LATCH,
            AKAZE,
            AKAZEUP,
            BRISK,
            BRIEF,
        };

        /// @brief IDescriptorsExtractor default constructor
        IDescriptorsExtractor() = default;

       /// @brief IDescriptorsExtractor default destructor
       virtual ~IDescriptorsExtractor() {};

       ///
       /// @brief getType
       /// @return a string describing the type of descriptor used during extraction.
       ///
		virtual std::string  getTypeString() = 0;

       ///
       /// @brief extract the descriptors for a set of keypoints
       /// @param[in] image The image on which the keypoints have been detected
       /// @param[in] keypoints The set of keypoints on which the descriptors are extracted
       /// @param[out] descriptors The extracted descriptors. The nth descriptor corresponds to the nth keypoint of the second argument.
       ///
        virtual void extract (const SRef<SolAR::datastructure::Image> image,
                              const std::vector<SolAR::datastructure::Keypoint> &keypoints,
                              SRef<SolAR::datastructure::DescriptorBuffer> & descriptors) = 0;
	};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IDescriptorsExtractor,
                             "c0e49ff1-0696-4fe6-85a8-9b2c1e155d2e",
                             "IDescriptorsExtractor",
                             "SolAR::api::features::IDescriptorsExtractor");

#endif // SOLAR_IDESCRIPTORSEXTRACTOR_H
