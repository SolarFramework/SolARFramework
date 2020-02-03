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

#ifndef IKEYFRAMERETRIEVER_H
#define IKEYFRAMERETRIEVER_H

#include "datastructure/Keyframe.h"
#include "datastructure/Frame.h"
#include "datastructure/DescriptorMatch.h"
#include "core/Messages.h"
#include <set>

namespace SolAR {
using namespace datastructure;
namespace api {
namespace reloc {


/**
 * @class IKeyframeRetriever
 * @brief <B>Recovers a set of pre-recorded keyframes close to a given frame.</B>
 * <TT>UUID: f60980ce-bdbd-11e8-a355-529269fb1459</TT>
 *
 * This class provides a solution to retrieve a set of keyframes corresponding to a given frame.
 */

///@class IKeyframeRetriever
class IKeyframeRetriever : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief IKeyframeRetriever default constructor.
    IKeyframeRetriever() = default;
    ///@brief IKeyframeRetriever default destructor.
    virtual ~IKeyframeRetriever() = default;

    /// @brief Add a keyframe to the bag of words
    /// @param[in] keyframe: the keyframe to add to the bag of words
    /// @return FrameworkReturnCode::_SUCCESS if the keyfram adding succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode addKeyframe(const SRef<Keyframe> keyframe) = 0;


    /// @brief Retrieve a set of keyframes close to the frame pass in input.
    /// @param[in] frame: the frame for which we want to retrieve close keyframes.
    /// @param[out] keyframes: a set of keyframe which are close to the frame pass in input
    /// @return FrameworkReturnCode::_SUCCESS if the retrieve succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode retrieve(const SRef<Frame> frame, std::vector<SRef<Keyframe>> & keyframes) = 0;

	/// @brief Retrieve a set of keyframes close to the frame pass in input.
	/// @param[in] frame: the frame for which we want to retrieve close keyframes.
	/// @param[in] index: a set includes index of keyframe candidates
	/// @param[out] keyframes: a set of keyframe which are close to the frame pass in input
	/// @return FrameworkReturnCode::_SUCCESS if the retrieve succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode retrieve(const SRef<Frame> frame, std::set<unsigned int> &idxKfCandidates, std::vector<SRef<Keyframe>> & keyframes) = 0;

	/// @brief Match a frame with a keyframe
	/// @param[in] frame: the frame to match.
	/// @param[in] index: index of keyframe
	/// @param[out] matches: a set of matches between frame and keyframe
	/// @return FrameworkReturnCode::_SUCCESS if the retrieve succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode match(const SRef<Frame> frame, int index, std::vector<DescriptorMatch> &matches) = 0;

	/// @brief Match a set of descriptors with a keyframe
	/// @param[in] indexDescriptors: index of descriptors to match.
	/// @param[in] descriptors: a descriptor buffer contains all descriptors
	/// @param[in] indexKeyframe: index of keyframe
	/// @param[out] matches: a set of matches between frame and keyframe
	/// @return FrameworkReturnCode::_SUCCESS if the retrieve succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode match(const std::vector<int> &indexDescriptors, const SRef<DescriptorBuffer> &descriptors, int indexKeyframe, std::vector<DescriptorMatch> &matches) = 0;
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::reloc::IKeyframeRetriever,
                             "f60980ce-bdbd-11e8-a355-529269fb1459",
                             "IKeyframeRetriever",
                             "SolAR::api::reloc::IKeyframeRetriever describes the interface to retrieve a set of keyframes corresponding to a given frame.");

#endif // SOLAR_IKEYFRAMERETRIEVER_H
