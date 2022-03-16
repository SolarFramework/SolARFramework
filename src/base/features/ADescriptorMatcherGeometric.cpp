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

#include "base/features/ADescriptorMatcherGeometric.h"

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace base {
namespace features {

ADescriptorMatcherGeometric::ADescriptorMatcherGeometric(std::map<std::string,std::string> componentInfosMap):xpcf::ConfigurableBase(componentInfosMap)
{
    declareInterface<SolAR::api::features::IDescriptorMatcherGeometric>(this);
}

FrameworkReturnCode ADescriptorMatcherGeometric::match(const SRef<SolAR::datastructure::Frame> frame1,
                                                       const SRef<SolAR::datastructure::Frame> frame2,
                                                       const SolAR::datastructure::CameraParameters & camParams,
                                                       std::vector<SolAR::datastructure::DescriptorMatch> & matches,
                                                       const std::vector<uint32_t>& mask)
{	
    return match(frame1->getDescriptors(), frame2->getDescriptors(),
		frame1->getUndistortedKeypoints(), frame2->getUndistortedKeypoints(), frame1->getPose(), 
        frame2->getPose(), camParams, matches, mask);
}

}
}
}  // end of namespace SolAR


