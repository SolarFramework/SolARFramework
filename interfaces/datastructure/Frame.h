#ifndef FRAME_H
#define FRAME_H


#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/DescriptorMatch.h"
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
public:
	Frame() = default;
    Frame(const SRef<Frame> frame);
	
	Frame(const SRef<Keyframe> keyframe);

	explicit Frame(const std::vector<Keypoint> & keypoints,
				   const SRef<DescriptorBuffer> descriptors,
				   const SRef<Image> view,
				   const Transform3Df pose = Transform3Df::Identity());

    explicit Frame(const std::vector<Keypoint> & keypoints,
				   const std::vector<Keypoint> & undistortedKeypoints,
                   const SRef<DescriptorBuffer> descriptors,
                   const SRef<Image> view,
                   const SRef<Keyframe> refKeyframe,
                   const Transform3Df pose = Transform3Df::Identity());

    explicit Frame(const std::vector<Keypoint> & keypoints,
				   const std::vector<Keypoint> & undistortedKeypoints,
                   const SRef<DescriptorBuffer> descriptors,
                   const SRef<Image> view,
                   const Transform3Df pose = Transform3Df::Identity());

    /// @brief ~Frame
    ~Frame() = default;

	/// @brief get view image
	/// @return view image
    const SRef<Image>& getView() const;

	/// @brief set view image
	/// @param[in] view: view image
	void setView(const SRef<Image> &view);

	/// @brief get camera pose
	/// @return camera pose
    const Transform3Df& getPose() const;

	/// @brief set pose
	/// @param[in] pose: camera pose
    void setPose(const Transform3Df & pose);

	/// @brief get keypoints
	/// @return keypoints
	const std::vector<Keypoint> & getKeypoints() const;
	
    /// @brief get the i-th keypoint
	/// @param[in] i: index of keypoint
	/// @return i-th keypoint
    const Keypoint & getKeypoint(int i) const;

	/// @brief set keypoints
	/// @param[in] kpts: keypoints
    void setKeypoints(const std::vector<Keypoint>& kpts);

	/// @brief get undistorted keypoints
	/// @return undistorted keypoints
	const std::vector<Keypoint> & getUndistortedKeypoints() const;

	/// @brief get the i-th undistorted keypoint
	/// @param[in] i: index of undistorted keypoint
	/// @return i-th undistorted keypoint
	const Keypoint & getUndistortedKeypoint(int i) const;

	/// @brief set undistorted keypoints
	/// @param[in] kpts: undistorted keypoints
	void setUndistortedKeypoints(const std::vector<Keypoint>& kpts);

	/// @brief set reference keyframe
	/// @param[in] keyframe: reference keyframe
    void setReferenceKeyframe(const SRef<Keyframe>& keyframe);

	/// @brief get reference keyframe
	/// @return reference keyframe
	const SRef<Keyframe>& getReferenceKeyframe() const;

	/// @brief get descriptors
	/// @return descriptors
    const SRef<DescriptorBuffer>& getDescriptors() const;

	/// @brief set descriptors
	/// @param[in] descriptors: descriptors
	void setDescriptors(const SRef<DescriptorBuffer> &descriptors);

	///
	/// @brief Get all cloud point visibilities
	///
	const std::map<uint32_t, uint32_t> & getVisibility() const;

	/// @brief set visibility
	/// @param[in] visibilities: a map of cloud pont visibilities, the first element is keypoint id, the second one is cloud point id
	void setVisibility(const std::map<uint32_t, uint32_t> &visibilities);

	/// @brief Add cloud point visibilities to frame
	/// @param[in] visibilites: a map of cloud pont visibilities, the first element is keypoint id, the second one is cloud point id
	void addVisibilities(const std::map<uint32_t, uint32_t>& visibilites);

	/// @brief Add a cloud point visibility to frame
	/// @param[in] id_keypoint: id of keypoint
	/// @param[in] id_cloudPoint: id of cloud point
	void addVisibility(const uint32_t& id_keypoint, const uint32_t& id_cloudPoint);

	/// @brief Remove a visibility
	/// @param[in] id_keypoint: id of keypoint
	/// @param[in] id_cloudPoint: id of cloud point
	/// @return true if remove successfully
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
    std::vector<Keypoint>			m_keypoints;
    std::vector<Keypoint>			m_keypointsUndistort;

	//A map storing the 3D points visibility, where the first element corresponds to the index of the keypoint of the frame, and the second element to the index of the corresponding cloudPoint.
	std::map<uint32_t, uint32_t>	m_mapVisibility;
};

DECLARESERIALIZE(Frame);

}
}
#endif // FRAME_H
