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

#include "base/features/ADescriptorMatcherStereo.h"

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace base {
namespace features {

ADescriptorMatcherStereo::ADescriptorMatcherStereo(std::map<std::string,std::string> componentInfosMap):xpcf::ConfigurableBase(componentInfosMap)
{
    declareInterface<SolAR::api::features::IDescriptorMatcherStereo>(this);
}

FrameworkReturnCode ADescriptorMatcherStereo::match(const SRef<SolAR::datastructure::Frame> frame1, const SRef<SolAR::datastructure::Frame> frame2, SolAR::datastructure::StereoType type, std::vector<SolAR::datastructure::DescriptorMatch>& matches)
{
	return match(frame1->getDescriptors(), frame2->getDescriptors(), frame1->getUndistortedKeypoints(),
		frame2->getUndistortedKeypoints(), type, matches);
}

}
}
}  // end of namespace SolAR


