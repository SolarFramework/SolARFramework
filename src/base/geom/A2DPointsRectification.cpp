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

#include "base/geom/A2DPointsRectification.h"

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace base {
namespace geom {

A2DPointsRectification::A2DPointsRectification(std::map<std::string,std::string> componentInfosMap):xpcf::ConfigurableBase(componentInfosMap)
{
    declareInterface<I2DPointsRectification>(this);
}

FrameworkReturnCode A2DPointsRectification::rectify(const std::vector<SolAR::datastructure::Keypoint>& keypoints,
													const SolAR::datastructure::CameraParameters& camParams,
													const SolAR::datastructure::RectificationParameters& rectParams,
													std::vector<SolAR::datastructure::Keypoint>& rectifiedKeypoints)
{
	std::vector<datastructure::Point2Df> pts, rectifiedPts;
	for (const auto& it : keypoints)
		pts.push_back(it);
	FrameworkReturnCode retCode = rectify(pts, camParams, rectParams, rectifiedPts);
	if (retCode == FrameworkReturnCode::_SUCCESS) {
		rectifiedKeypoints = keypoints;
		for (int i = 0; i < rectifiedKeypoints.size(); ++i) {
			rectifiedKeypoints[i].setX(rectifiedPts[i].getX());
			rectifiedKeypoints[i].setY(rectifiedPts[i].getY());
		}
	}
	return retCode;
}

}
}
}  // end of namespace SolAR


