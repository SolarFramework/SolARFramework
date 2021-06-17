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

#ifndef SOLAR_ISTEREODESCRIPTORMATCHER_H
#define SOLAR_ISTEREODESCRIPTORMATCHER_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/Keypoint.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/StereoCameraDefinitions.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace stereo {

/** @class IStereoDescriptorMatcher
* @brief <B>Matches two sets of descriptors from stereo images.</B>
* <TT>UUID: 272f1ef0-c269-4631-b75c-fc7316d10915</TT>
*/
class  IStereoDescriptorMatcher : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IStereoDescriptorMatcher constructor
	IStereoDescriptorMatcher() = default;

	/// @brief ~IStereoDescriptorMatcher
	virtual ~IStereoDescriptorMatcher() {};

	/// @brief Match two sets of descriptors from stereo images.
	/// @param[in] descriptors1 Descirptors of the first image.
	/// @param[in] descriptors2 Descirptors of the second image.
	/// @param[in] keypoints1 Keypoints of the first image.
	/// @param[in] keypoints2 Keypoints of the second image.
	/// @param[in] type Stereo type (horizontal or vertical).
	/// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
	/// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::DescriptorBuffer>& descriptors1,
									const SRef<SolAR::datastructure::DescriptorBuffer>& descriptors2,
									const std::vector<SolAR::datastructure::Keypoint>& keypoints1,
									const std::vector<SolAR::datastructure::Keypoint>& keypoints2,
									SolAR::datastructure::StereoType type,
									std::vector<SolAR::datastructure::DescriptorMatch> &matches) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::stereo::IStereoDescriptorMatcher,
							"272f1ef0-c269-4631-b75c-fc7316d10915",
							"IStereoDescriptorMatcher",
							"SolAR::api::stereo::IStereoDescriptorMatcher interface");

#endif // SOLAR_ISTEREODESCRIPTORMATCHER_H
