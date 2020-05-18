#ifndef FRAME_H
#define FRAME_H


#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/CloudPoint.h"

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
    Frame(const SRef<Frame> frame);
	
	Frame(const SRef<Keyframe> keyframe);

    Frame(const std::vector<Keypoint> & keypoints,
          const SRef<DescriptorBuffer> descriptors,
          const SRef<Image> view,
          const SRef<Keyframe> refKeyframe,
          const Transform3Df pose = Transform3Df::Identity());

    Frame(const std::vector<Keypoint> & keypoints,
          const SRef<DescriptorBuffer> descriptors,
          const SRef<Image> view,
          const Transform3Df pose = Transform3Df::Identity());

    /// @brief ~Frame
    ~Frame() = default;

	///
	/// @brief return view image
	///
    SRef<Image> getView();

	///
	/// @brief return camera pose
	///
    Transform3Df getPose();

	///
	/// @brief set pose
	/// @param[in] pose: camera pose
	///
    void setPose(const Transform3Df & pose);

	///
	/// @brief return keypoints
	///
	const std::vector<Keypoint> & getKeypoints();

	///
	/// @brief set keypoints
	/// @param[in] kpts: keypoints
	///
    void setKeypoints(const std::vector<Keypoint>& kpts);

	///
	/// @brief set reference keyframe
	/// @param[in] keyframe: reference keyframe
	///
    void setReferenceKeyframe(SRef<Keyframe> keyframe);

	///
	/// @brief return reference keyframe
	///
    SRef<Keyframe> getReferenceKeyframe();


	///
	/// @brief return descriptors
	///
    SRef<DescriptorBuffer> getDescriptors();

	///
	/// @brief set descriptors
	/// @param[in] descriptors: descriptors
	///
	void setDescriptors(SRef<DescriptorBuffer> &descriptors);

	///
	/// @brief Get all cloud point visibilities
	///
	const std::map<uint32_t, uint32_t> & getVisibility();

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
	void addVisibility(uint32_t id_keypoint, uint32_t id_cloudPoint);

	///
	/// @brief Remove a visibility
	/// @param[in] id_keypoint: id of keypoint
	/// @param[in] id_cloudPoint: id of cloud point
	/// @return true if remove successfully
	///
	bool removeVisibility(uint32_t id_keypoint, uint32_t id_cloudPoint);

protected:
    Transform3Df                    m_pose;    
    SRef<Image>                     m_view;
    SRef<Keyframe>                  m_referenceKeyFrame ;
    SRef<DescriptorBuffer>          m_descriptors;
    std::vector<Keypoint>			m_keypoints ;

	//A map storing the 3D points visibility, where the first element corresponds to the index of the keypoint of the frame, and the second element to the index of the corresponding cloudPoint.
	std::map<uint32_t, uint32_t>	m_mapVisibility;

	std::mutex						m_mutexPose;
	std::mutex						m_mutexKeypoint;
	std::mutex						m_mutexReferenceKeyframe;
	std::mutex						m_mutexDescriptors;
	std::mutex						m_mutexVisibility;

};

}
}
#endif // FRAME_H
