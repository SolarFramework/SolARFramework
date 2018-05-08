#ifndef FRAME_H
#define FRAME_H


#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
#include "datastructure/Pose.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/Keyframe.h"

#include <memory>
namespace SolAR {
namespace datastructure {

/**
 * @class Frame
 * @brief Specifies the frame class.
 *
 * This class provides frame definition for slam utilities.
 */
class SOLARFRAMEWORK_API Frame {
    ///
    /// @brief ~Frame
    public:
    Frame();

    ~Frame();

    void                            InitKeyPointsAndDescriptors(std::vector<SRef<Keypoint>> keypoints, SRef<DescriptorBuffer> descriptors) ;

    void                            setReferenceKeyFrame(SRef<Keyframe> frame) ;

    SRef<Keyframe>                  getReferenceKeyFrame() ;

    SRef<DescriptorBuffer>          getDescriptors() ;

    std::vector<SRef<Keypoint>>     getKeyPoints() ;

    void                            setNumberOfFramesSinceLastKeyFrame(unsigned int nbFrames);

    unsigned int                    getNumberOfFramesSinceLastKeyFrame() const ;

    void                            setMatchesWithReferenceKeyFrame(std::vector<DescriptorMatch> & matches); // match not yet associated with map points

    std::vector<DescriptorMatch> &  getMatchesWithReferenceKeyFrame()  ; // match  not yet associated with map points


    void                            addCommonMapPointsWithReferenceKeyFrame(std::vector<SRef<CloudPoint>> & points) ;

    std::vector<SRef<CloudPoint>> & getCommonMapPointsWithReferenceKeyFrame()  ;


    ///@brief pose of current frame
    Transform3Df                    m_pose;



    private:
    SRef<Keyframe>                  m_refrenceKeyFrame ;
    SRef<DescriptorBuffer>          m_descriptor;
    std::vector<SRef<Keypoint>>     m_keypoints ;
    std::vector<DescriptorMatch>    m_matchesWithReferenceKeyFrame ;
    std::vector<SRef<CloudPoint>>   m_trackedPoints;
    unsigned int                    m_countOfFramesSinceLastKframe ;



};

}
}





#endif // FRAME_H
