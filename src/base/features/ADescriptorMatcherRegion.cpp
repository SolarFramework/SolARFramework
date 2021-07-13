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

#include "base/features/ADescriptorMatcherRegion.h"

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace base {
namespace features {

ADescriptorMatcherRegion::ADescriptorMatcherRegion(std::map<std::string,std::string> componentInfosMap):xpcf::ConfigurableBase(componentInfosMap)
{
    declareInterface<SolAR::api::features::IDescriptorMatcherRegion>(this);
}

void ADescriptorMatcherRegion::unloadComponent ()
{
    // provide component cleanup strategy
    // default strategy is to delete self, uncomment following line in this case :
    delete this;
    return;
}

FrameworkReturnCode ADescriptorMatcherRegion::match(const std::vector<SolAR::datastructure::Point2Df>& points2D, const std::vector<SRef<SolAR::datastructure::DescriptorBuffer>>& descriptors, const SRef<SolAR::datastructure::Frame> frame, std::vector<SolAR::datastructure::DescriptorMatch>& matches, const float radius, const float matchingDistanceMax)
{
	SRef<datastructure::DescriptorBuffer> descBuff = xpcf::utils::make_shared<datastructure::DescriptorBuffer>(frame->getDescriptors()->getDescriptorType(), 0);
	for (const auto& it : descriptors)
		descBuff->append(it->getDescriptor(0));
	std::vector<datastructure::Point2Df> points2D2;
	const std::vector<datastructure::Keypoint>& keypoints = frame->getKeypoints();
	for (const auto& kp : keypoints)
		points2D2.push_back(kp);
	return match(descBuff, frame->getDescriptors(), points2D, points2D2, matches, radius, 
		matchingDistanceMax);
}

FrameworkReturnCode ADescriptorMatcherRegion::match(const SRef<SolAR::datastructure::Frame> currentFrame, const SRef<SolAR::datastructure::Frame> lastFrame, std::vector<SolAR::datastructure::DescriptorMatch>& matches, const float radius, const float matchingDistanceMax)
{
	std::vector<datastructure::Point2Df> points2D1, points2D2;
	const std::vector<datastructure::Keypoint>& keypoints1 = currentFrame->getKeypoints();
	const std::vector<datastructure::Keypoint>& keypoints2 = lastFrame->getKeypoints();
	for (const auto& kp : keypoints1)
		points2D1.push_back(kp);
	for (const auto& kp : keypoints2)
		points2D2.push_back(kp);
	return match(currentFrame->getDescriptors(), lastFrame->getDescriptors(), points2D1, points2D2, 
		matches, radius, matchingDistanceMax);
}



}
}
}  // end of namespace SolAR


