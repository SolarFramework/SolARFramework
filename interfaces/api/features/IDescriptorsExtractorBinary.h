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

#ifndef SOLAR_IDESCRIPTORSEXTRACTORBINARY_H
#define SOLAR_IDESCRIPTORSEXTRACTORBINARY_H

#include "datastructure/Keyline.h"
#include "datastructure/Image.h"
#include "datastructure/DescriptorBuffer.h"

#include "xpcf/api/IComponentIntrospect.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace features {

/**
 * @class IDescriptorsExtractorBinary
 * @brief <B>Extracts descriptors from a set of keylines.</B>
 * <TT>UUID: 9171561b-e957-403b-8991-f84022672780</TT>
 *
 * This class provides a method to extract descriptors from a set of keylines
 */

class IDescriptorsExtractorBinary : virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    /// @brief IDescriptorsExtractorBinary default contructor
    IDescriptorsExtractorBinary() = default;

    /// @brief IDescriptorsExtractorBinary default destructor
    virtual ~IDescriptorsExtractorBinary() {};

    /// @brief Extracts the descriptors for a set of keylines
    /// @param[in] image The image on which the keylines have been detected
    /// @param[int] keylines The set of keylines on which the descriptors are extracted
    /// @param[out] descriptors The extracted descriptors. The nth descriptor corresponds to the nth keyline of the second argument.
    virtual void extract(const SRef<Image> image,
                         const std::vector<Keyline> & keylines,
                         SRef<DescriptorBuffer> & descriptors) = 0;

	/// @brief Detects keyliens and extracts the corresponding descriptors
	/// @param[in] image The image on which the keylines have been detected
	/// @param[out] keylines The set of detected keylines on which the descriptors are extracted
	/// @param[out] descriptors The extracted descriptors. The nth descriptor corresponds to the nth keyline of the second argument.
	virtual void compute(const SRef<Image> image,
						 std::vector<Keyline> & keylines,
						 SRef<DescriptorBuffer> & descriptors) = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IDescriptorsExtractorBinary,
                             "9171561b-e957-403b-8991-f84022672780",
                             "IDescriptorsExtractorBinary",
                             "SolAR::api::features::IDescriptorsExtractorBinary");

#endif // SOLAR_IDESCRIPTORSEXTRACTORBINARY_H
