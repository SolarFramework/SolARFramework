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
#include "datastructure/KeyframeRetrieval.h"
#include "datastructure/DescriptorMatch.h"
#include "core/Messages.h"
#include <set>
#include <utility>

namespace SolAR {
namespace api {
namespace reloc {


/**
 * @class IKeyframeRetriever
 * @brief <B>Recovers a set of pre-recorded keyframes close to a given frame.</B>
 * <TT>UUID: f60980ce-bdbd-11e8-a355-529269fb1459</TT>
 *
 * This class provides a solution to retrieve a set of keyframes corresponding to a given frame.
 */

class XPCF_IGNORE IKeyframeRetriever :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief IKeyframeRetriever default constructor.
    IKeyframeRetriever() = default;

    ///@brief IKeyframeRetriever default destructor.
    virtual ~IKeyframeRetriever() = default;

    /// @brief Add a keyframe to the retrieval model
    /// @param[in] keyframe: the keyframe to add to the retrieval model
    /// @param[in] useMatchedDescriptor: if true bow feature will be computed merely from descriptors which are matched to other frames, by default is set to false meaning that all descriptors will be used
    /// @return FrameworkReturnCode::_SUCCESS if the keyfram adding succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode addKeyframe(const SRef<SolAR::datastructure::Keyframe> keyframe, bool useMatchedDescriptor=false) = 0;

	/// @brief Suppress a keyframe from the retrieval model
	/// @param[in] keyframeId: the keyframe to supress from the retrieval model
	/// @return FrameworkReturnCode::_SUCCESS if the keyfram adding succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode suppressKeyframe(uint32_t keyframeId) = 0;


    /// @brief Retrieve a set of keyframes close to the frame pass in input.
    /// @param[in] frame: the frame for which we want to retrieve close keyframes.
    /// @param[out] retKeyframeId: a set of keyframe ids which are close to the frame pass in input
    /// @return FrameworkReturnCode::_SUCCESS if the retrieve succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode retrieve(const SRef<SolAR::datastructure::Frame> frame,
                                         std::vector<uint32_t> & retKeyframeId) = 0;

    /// @brief Retrieve a set of keyframes close to the frame passed in input.
    /// @param[in] frame: the frame for which we want to retrieve close keyframes.
    /// @param[out] retKeyframeIdScore: a set of pairs of keyframe id and the corresponding retrieval score (sorted by score in decreasing order)
    /// @return FrameworkReturnCode::_SUCCESS if the retrieve succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode retrieve(const SRef<SolAR::datastructure::Frame> frame,
                                         std::vector<std::pair<uint32_t, double>> & retKeyframeIdScore) = 0;

	/// @brief Retrieve a set of keyframes close to the frame pass in input.
	/// @param[in] frame: the frame for which we want to retrieve close keyframes.
    /// @param[in] canKeyframeId: a set including id of keyframe candidates
	/// @param[out] retKeyframeId: a set of keyframe ids which are close to the frame pass in input
	/// @return FrameworkReturnCode::_SUCCESS if the retrieve succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode retrieve(const SRef<SolAR::datastructure::Frame> frame,
                                         const std::set<unsigned int> & canKeyframeId,
                                         std::vector<uint32_t> & retKeyframeId) = 0;

	/// @brief This method allows to save the keyframe feature to the external file
    /// @param[in] file: the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode saveToFile(const std::string & file) const = 0;

	/// @brief This method allows to load the keyframe feature from the external file
    /// @param[in] file: the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode loadFromFile(const std::string & file) = 0;

	/// @brief Match a frame with a keyframe
	/// @param[in] frame: the frame to match
	/// @param[in] keyframe: id of keyframe to match
	/// @param[out] matches: a set of matches between frame and keyframe
	/// @return FrameworkReturnCode::_SUCCESS if the retrieve succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::Frame> frame,
                                      const SRef<SolAR::datastructure::Keyframe> keyframe,
                                      std::vector<SolAR::datastructure::DescriptorMatch> & matches) = 0;

	/// @brief Match a set of descriptors with a keyframe
	/// @param[in] indexDescriptors: index of descriptors to match.
	/// @param[in] descriptors: a descriptor buffer contains all descriptors
	/// @param[in] keyframe: id of keyframe to match
	/// @param[out] matches: a set of matches between frame and keyframe
	/// @return FrameworkReturnCode::_SUCCESS if the retrieve succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const std::vector<int> & indexDescriptors,
                                      const SRef<SolAR::datastructure::DescriptorBuffer> descriptors,
                                      const SRef<SolAR::datastructure::Keyframe> keyframe,
                                      std::vector<SolAR::datastructure::DescriptorMatch> & matches) = 0;

	/// @brief This method returns the keyframe retrieval
	/// @return the keyframe retrieval
	virtual const SRef<SolAR::datastructure::KeyframeRetrieval> & getConstKeyframeRetrieval() const = 0;

	/// @brief This method returns the keyframe retrieval
	/// @param[out] keyframeRetrieval the keyframe retrieval of map
	/// @return the keyframe retrieval
	virtual std::unique_lock<std::mutex> getKeyframeRetrieval(SRef<SolAR::datastructure::KeyframeRetrieval>& keyframeRetrieval) = 0;

	/// @brief This method is to set the keyframe retrieval
	/// @param[in] keyframeRetrieval the keyframe retrieval of map
	virtual void setKeyframeRetrieval(const SRef<SolAR::datastructure::KeyframeRetrieval> keyframeRetrieval) = 0;

    /// @brief This method is to reset the keyframe retrieval 
    virtual void resetKeyframeRetrieval() = 0;
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::reloc::IKeyframeRetriever,
                             "f60980ce-bdbd-11e8-a355-529269fb1459",
                             "IKeyframeRetriever",
                             "SolAR::api::reloc::IKeyframeRetriever describes the interface to retrieve a set of keyframes corresponding to a given frame.");

#endif // SOLAR_IKEYFRAMERETRIEVER_H
