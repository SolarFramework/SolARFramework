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

#include "base/features/ADescriptorMatcher.h"

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace base {
namespace features {

ADescriptorMatcher::ADescriptorMatcher(std::map<std::string,std::string> componentInfosMap):xpcf::ConfigurableBase(componentInfosMap)
{
    declareInterface<IDescriptorMatcher>(this);
}

FrameworkReturnCode ADescriptorMatcher::match(const SRef<SolAR::datastructure::DescriptorBuffer> descriptors1, const std::vector<SRef<SolAR::datastructure::DescriptorBuffer>>& descriptors2, std::vector<SolAR::datastructure::DescriptorMatch>& matches)
{
	SRef<datastructure::DescriptorBuffer> buff2 = xpcf::utils::make_shared<datastructure::DescriptorBuffer>(descriptors1->getDescriptorType(), 0);
	for (const auto& it : descriptors2)
		buff2->append(it->getDescriptor(0));
    return match(descriptors1, buff2, matches);
}

FrameworkReturnCode  ADescriptorMatcher::match(const std::vector<SolAR::datastructure::Keypoint>& keypoints1,
                                  const std::vector<SolAR::datastructure::Keypoint>& keypoints2,
                                  const SRef<SolAR::datastructure::DescriptorBuffer> descriptors1,
                                  const SRef<SolAR::datastructure::DescriptorBuffer> descriptors2,
                                                                  std::vector<SolAR::datastructure::DescriptorMatch> & matches){

    return match(keypoints1, keypoints2, descriptors1, descriptors2, matches);
}


}
}
}  // end of namespace SolAR


