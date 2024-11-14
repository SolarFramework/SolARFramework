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

#ifndef SOLAR_ADESCRIPTORMATCHER_H
#define SOLAR_ADESCRIPTORMATCHER_H

#include "core/SolARFrameworkDefinitions.h"
#include <xpcf/component/ConfigurableBase.h>
#include "api/features/IDescriptorMatcher.h"

namespace SolAR {
namespace base {
namespace features {

class XPCF_IGNORE SOLARFRAMEWORK_API ADescriptorMatcher : public org::bcom::xpcf::ConfigurableBase,
											virtual public SolAR::api::features::IDescriptorMatcher {
public:
    /// @brief ADescriptorMatcher constructor
	ADescriptorMatcher(std::map<std::string,std::string> componentInfosMap);


    virtual ~ADescriptorMatcher() override = default;    

    /// @brief Match two sets of descriptors together
    /// @param[in] descriptors1 The first set of descriptors organized in a dedicated buffer structure.
    /// @param[in] descriptors2 The second set of descriptors organized in a dedicated buffer structure.
    /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
    /// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::DescriptorBuffer> /*descriptors1*/,
                                      const SRef<SolAR::datastructure::DescriptorBuffer> /*descriptors2*/,
                                      std::vector<SolAR::datastructure::DescriptorMatch> & /*matches*/) override
    { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

	/// @brief Match two sets of descriptors together. The second set is organized in a vector of descriptors buffer and can be used if the descriptors have been extracted on subsets of an image.
	/// @param[in] descriptors1 The first set of descriptors organized in a dedicated buffer structure.
	/// @param[in] descriptors2 The second set of descriptors organized in a vector of dedicated buffer structure.
	/// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
	/// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::DescriptorBuffer> descriptors1,
                                      const std::vector<SRef<SolAR::datastructure::DescriptorBuffer>> & descriptors2,
                                      std::vector<SolAR::datastructure::DescriptorMatch> & matches) override;

    virtual FrameworkReturnCode match(const std::vector<SolAR::datastructure::Keypoint>& keypoints1,
                                      const std::vector<SolAR::datastructure::Keypoint>& keypoints2,
                                      const SRef<SolAR::datastructure::DescriptorBuffer> descriptors1,
                                      const SRef<SolAR::datastructure::DescriptorBuffer> descriptors2,
                                      std::vector<SolAR::datastructure::DescriptorMatch> & matches) override;


};
}
}
}  // end of namespace SolAR


#endif // SOLAR_ADESCRIPTORMATCHER_H
