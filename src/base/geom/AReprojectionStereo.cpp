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

#include "base/geom/AReprojectionStereo.h"

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace base {
namespace geom {

AReprojectionStereo::AReprojectionStereo(std::map<std::string,std::string> componentInfosMap):xpcf::ConfigurableBase(componentInfosMap)
{
    declareInterface<IReprojectionStereo>(this);
}

FrameworkReturnCode AReprojectionStereo::reprojectToCloudPoints(SRef<SolAR::datastructure::Frame> frame, const SolAR::datastructure::CamCalibration & intrinsicParams, std::vector<SRef<SolAR::datastructure::CloudPoint>>& cloudPoints)
{
	return reprojectToCloudPoints(frame->getKeypoints(), frame->getPose(), intrinsicParams, cloudPoints);
}



}
}
}  // end of namespace SolAR


