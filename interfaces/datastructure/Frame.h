#ifndef FRAME_H
#define FRAME_H


#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Keyline.h"
#include "datastructure/Keypoint.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/CloudLine.h"
#include "datastructure/CloudPoint.h"
#include <core/SerializationDefinitions.h>

#include <memory>
namespace SolAR {
namespace datastructure {

class Keyframe;
/**
 * @class Frame
 * @brief <B>A frame.</B>
 *
 * This class provides frame definition.
 */
class SOLARFRAMEWORK_API Frame {
    ///

public:
	Frame() = default;
    Frame(const SRef<Frame> frame);
	
	Frame(const SRef<Keyframe> keyframe);

    explicit Frame(const std::vector<Keypoint> & keypoints,
                   const SRef<DescriptorBuffer> descriptors,
                   const SRef<Image> view,
                   const SRef<Keyframe> refKeyframe,
                   const Transform3Df pose = Transform3Df::Identity());

    explicit Frame(const std::vector<Keypoint> & keypoints,
                   const SRef<DescriptorBuffer> descriptors,
                   const SRef<Image> view,
                   const Transform3Df pose = Transform3Df::Identity());

	Frame(const std::vector<Keyline> & keylines,
		  const SRef<DescriptorBuffer> descriptors,
		  const SRef<Image> view,
		  const Transform3Df pose = Transform3Df::Identity());

	Frame(const std::vector<Keypoint> & keypoints,
		  const SRef<DescriptorBuffer> descriptorsPoint, 
		  const std::vector<Keyline> & keylines,
		  const SRef<DescriptorBuffer> descriptorsLine,
		  const SRef<Image> view,
		  const Transform3Df pose = Transform3Df::Identity());

    /// @brief ~Frame
    ~Frame() = default;

	///
	/// @brief return view image
	///
    const SRef<Image>& getView() const;

	///
	/// @brief return camera pose
	///
    const Transform3Df& getPose() const;

	///
	/// @brief set pose
	/// @param[in] pose: camera pose
	///
    void setPose(const Transform3Df & pose);

	///
	/// @brief return keylines
	///
	const std::vector<Keyline> & getKeylines() const;

	///
	/// @brief return keylines
	///
	const Keyline & getKeyline(int i) const;

	///
	/// @brief return keypoints
	///
	const std::vector<Keypoint> & getKeypoints() const;

    ///
    /// @brief return keypoints
    ///
    const Keypoint & getKeypoint(int i) const;

	///
	/// @brief set keylines
	/// @param[in] klines: keylines
	///
	void setKeylines(const std::vector<Keyline>& klines);

	///
	/// @brief set keypoints
	/// @param[in] kpts: keypoints
	///
    void setKeypoints(const std::vector<Keypoint>& kpts);

	///
	/// @brief set reference keyframe
	/// @param[in] keyframe: reference keyframe
	///
    void setReferenceKeyframe(const SRef<Keyframe>& keyframe);

	///
	/// @brief return reference keyframe
	///
	const SRef<Keyframe>& getReferenceKeyframe() const;


	///
	/// @brief return point descriptors
	///
    const SRef<DescriptorBuffer>& getDescriptors() const;

	///
	/// @brief return line descriptors
	///
	const SRef<DescriptorBuffer>& getDescriptorsLine() const;

	///
	/// @brief set descriptors
	/// @param[in] descriptors: descriptors
	///
	void setDescriptors(const SRef<DescriptorBuffer> &descriptors);

	///
	/// @brief Get all cloud point visibilities
	///
	const std::map<uint32_t, uint32_t> & getVisibility() const;

	///
	/// @brief set visibility
	/// @param[in] visibilities: a map of cloud pont visibilities, the first element is keypoint id, the second one is cloud point id
	///
	void setVisibility(const std::map<uint32_t, uint32_t> &visibilities);

	///
	/// @brief Add cloud point visibilities to frame
	/// @param[in] visibilites: a map of cloud pont visibilities, the first element is keypoint id, the second one is cloud point id
	void addVisibilities(const std::map<uint32_t, uint32_t>& visibilites);

	///
	/// @brief Add a cloud point visibility to frame
	/// @param[in] id_keypoint: id of keypoint
	/// @param[in] id_cloudPoint: id of cloud point
	///
	void addVisibility(const uint32_t& id_keypoint, const uint32_t& id_cloudPoint);

	///
	/// @brief Remove a visibility
	/// @param[in] id_keypoint: id of keypoint
	/// @param[in] id_cloudPoint: id of cloud point
	/// @return true if remove successfully
	///
	bool removeVisibility(const uint32_t& id_keypoint, const uint32_t& id_cloudPoint);

private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version);

protected:
    Transform3Df                    m_pose;    
    SRef<Image>                     m_view;
    SRef<Keyframe>                  m_referenceKeyFrame ;
	SRef<DescriptorBuffer>          m_descriptors;
	SRef<DescriptorBuffer>          m_descriptorsLine;
	std::vector<Keyline>			m_keylines;
	std::vector<Keypoint>			m_keypoints;

	//A map storing the 3D points visibility, where the first element corresponds to the index of the keypoint of the frame, and the second element to the index of the corresponding cloudPoint.
	std::map<uint32_t, uint32_t>	m_mapVisibility;
};

DECLARESERIALIZE(Frame);

}
}
#endif // FRAME_H
