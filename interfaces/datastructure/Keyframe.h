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

#ifndef SOLAR_KEYFRAME_H
#define SOLAR_KEYFRAME_H

#include <core/SolARFrameworkDefinitions.h>
#include <core/SerializationDefinitions.h>
#include <datastructure/GeometryDefinitions.h>
#include <datastructure/Frame.h>


namespace SolAR {
namespace datastructure {

/**
 * @class Keyframe
 * @brief <B>A keyframe</B>.
 *
 * This class provides Keyframe definition.
 */
class SOLARFRAMEWORK_API Keyframe : public Frame, public PrimitiveInformation {
public:
    Keyframe() = default;

    explicit Keyframe(SRef<Frame> frame) : Frame(frame) {};

    explicit Keyframe(SRef<Keyframe> frame) : Frame(frame),
                                              m_id{frame->m_id},
                                              m_isKeypointMatched{frame->m_isKeypointMatched},
                                              m_isKeypointMatchedStatusFrozen{frame->m_isKeypointMatchedStatusFrozen} {};

	explicit Keyframe(const std::vector<Keypoint> & keypoints,
					  SRef<DescriptorBuffer> descriptors,
					  SRef<Image> view,
                      const uint32_t camID = 0,
                      Transform3Df pose = Transform3Df::Identity()) : Frame(keypoints, descriptors, view, camID, pose) {};

    explicit Keyframe(const std::vector<Keypoint> & keypoints,
					  const std::vector<Keypoint> & undistortedKeypoints,
                      SRef<DescriptorBuffer> descriptors,
                      SRef<Image> view,
                      SRef<Keyframe> refKeyframe,
                      const uint32_t camID = 0,
                      Transform3Df pose = Transform3Df::Identity()): Frame(keypoints, undistortedKeypoints, descriptors, view, refKeyframe, camID, pose) {};

	explicit Keyframe(const std::vector<Keypoint> & keypoints,
					  const std::vector<Keypoint> & undistortedKeypoints,
					  SRef<DescriptorBuffer> descriptors,
					  SRef<Image> view,
                      const uint32_t camID = 0,
                      Transform3Df pose = Transform3Df::Identity()): Frame(keypoints, undistortedKeypoints, descriptors, view, camID, pose) {};

    ~Keyframe() = default;	

	///
	/// @brief Return keyframe id
	///
	const uint32_t& getId() const;

	///
	/// @brief Set keyframe id
	/// @param[in] id_keyframe: keyframe id
	///
	void setId(const uint32_t& id_keyframe);

	///
	/// @brief Set keypoint matched
	/// @param[in] id_keypoint: keypoint id
	/// @return boolean 
	///
	bool setKeypointStatusToMatched(uint32_t id_keypoint);

	///
	/// @brief Freeze current keypoint matched status (modifications are no longer allowed) 
	///
	void freezeKeypointMatchedStatus();

	///
	/// @brief Unfreeze current keypoint matched status (modifications are allowed)
	///
	void unfreezeKeypointMatchedStatus();

    ///
    /// @brief Get keypoint matched map 
    /// @return list of boolean 
    ///
    const std::vector<bool>& getIsKeypointMatched() const;

private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version);

private:
    uint32_t	m_id{0}; // TODO: remove valid value for init: std::optional or force id to be passed in ctors,...?
    std::vector<bool> m_isKeypointMatched;  // boolean map true or false indicating if keypoint matched to other keyframes during mapping
    bool m_isKeypointMatchedStatusFrozen = false; // boolean true or false indicating if modifications on m_isKeypointMatched are forbidden or not
};

DECLARESERIALIZE(Keyframe);

}
}

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Keyframe);

#endif //SOLAR_POSE_H
