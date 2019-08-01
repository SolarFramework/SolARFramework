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
    explicit Frame(const SRef<Frame>& frame);
	
	explicit Frame(const SRef<Keyframe>& keyframe);

    Frame(std::vector<Keypoint> keypoints,
          SRef<DescriptorBuffer>  descriptors,
          SRef<Image>  view,
          const SRef<Keyframe> refKeyframe,
          const Transform3Df& pose = Transform3Df::Identity());

    Frame(std::vector<Keypoint> keypoints,
          SRef<DescriptorBuffer>  descriptors,
          SRef<Image>  view,
          const Transform3Df& pose = Transform3Df::Identity());

    /// @brief ~Frame
    ~Frame() = default;

    SRef<Image> getView();

    Transform3Df getPose();

    void setPose(const Transform3Df & pose);
    void setKeypoints(const std::vector<Keypoint>& kpts);
    void setReferenceKeyframe(SRef<Keyframe> keyframe);

    SRef<Keyframe> getReferenceKeyframe();

    SRef<DescriptorBuffer> getDescriptors() const;

    const std::vector<Keypoint> & getKeypoints() const;

    const std::map<unsigned int, unsigned int> & getVisibleKeypoints();

    void addVisibleKeypoints(const std::map<unsigned int, unsigned int> & kpVisibility);

protected:
    ///@brief pose of current frame
    Transform3Df                    m_pose;    
    SRef<Image>                     m_view;
    SRef<Keyframe>                  m_referenceKeyFrame ;
    SRef<DescriptorBuffer>          m_descriptors;
    std::vector<Keypoint>     m_keypoints ;

	std::map<unsigned int, unsigned int > m_kpVisibility;

};

}
}
#endif // FRAME_H
