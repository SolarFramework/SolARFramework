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

    SRef<Image> getView();

    Transform3Df getPose();

    void setPose(const Transform3Df & pose);
	void setKeylines(const std::vector<Keyline>& klines);
	void setKeypoints(const std::vector<Keypoint>& kpts);
    void setReferenceKeyframe(SRef<Keyframe> keyframe);

    SRef<Keyframe> getReferenceKeyframe();

    SRef<DescriptorBuffer> getDescriptors();

	SRef<DescriptorBuffer> getDescriptorsLine();

	const std::vector<Keypoint> & getKeypoints();

	const std::vector<Keyline> & getKeylines();

	// @brief: Get all visible keypoints of the refKeyframe
    const std::map<unsigned int, unsigned int> & getVisibleKeypoints();

	// @brief: Add visible keypoint of refKeyframe to frame
    void addVisibleKeypoints(const std::map<unsigned int, unsigned int> & kpVisibility);

	// @brief: Add visible cloud point to frame
	void addVisibleMapPoints(const std::map<unsigned int, unsigned int>& mapPoints);

	// @brief: Add visible of a cloud point to frame
	void addVisibleMapPoint(unsigned int id_keypoint, unsigned int id_cloudPoint);

	// @brief: Get all visible cloud point
	const std::map<unsigned int, unsigned int> & getVisibleMapPoints();

protected:
    ///@brief pose of current frame
    Transform3Df                    m_pose;    
    SRef<Image>                     m_view;
    SRef<Keyframe>                  m_referenceKeyFrame ;
	SRef<DescriptorBuffer>          m_descriptors;
	SRef<DescriptorBuffer>          m_descriptorsLine;
	std::vector<Keyline>			m_keylines;
	std::vector<Keypoint>			m_keypoints;

	/// @brief: A map storing the 3D points visibility, where the first element corresponds to the index of the keypoint of the frame, and the second element to the index of the corresponding cloudPoint.
	std::map<unsigned int, unsigned int> m_mapVisibility;

	/// @brief: A map storing the 3D points visibility, where the first element corresponds to the index of the keypoint of the frame, and the second element to the index of the keypoint of the reference keyframe.
	std::map<unsigned int, unsigned int > m_kpVisibility;

	std::mutex						m_mutexPose;
	std::mutex						m_mutexKeyline;
	std::mutex						m_mutexKeypoint;
	std::mutex						m_mutexReferenceKeyframe;
	std::mutex						m_mutexVisibleKeypoint;
	std::mutex						m_mutexVisibleMapPoint;

};

}
}
#endif // FRAME_H
