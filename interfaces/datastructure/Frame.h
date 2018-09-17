#ifndef FRAME_H
#define FRAME_H


#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
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
    Frame(std::vector<SRef<Keypoint>> keypoints, SRef<DescriptorBuffer> descriptors, SRef<Image> view, Transform3Df pose);

    ~Frame();

//    void                            InitKeyPointsAndDescriptors(std::vector<SRef<Keypoint>> keypoints, SRef<DescriptorBuffer> descriptors) ;

    SRef<Image>                     getView() { return m_view; };

    void                            setReferenceKeyFrame(SRef<Keyframe> frame) ;

    SRef<Keyframe>                  getReferenceKeyFrame() ;

    SRef<DescriptorBuffer>          getDescriptors() ;

    std::vector<SRef<Keypoint>>     getKeyPoints() ;

    void                            setNumberOfFramesSinceLastKeyFrame(unsigned int nbFrames);

    unsigned int                    getNumberOfFramesSinceLastKeyFrame() const ;

    void                            setUnknownMatchesWithReferenceKeyFrame(std::vector<DescriptorMatch> & matches); // match not yet associated with map points

    std::vector<DescriptorMatch> &  getUnknownMatchesWithReferenceKeyFrame()  ; // match  not yet associated with map points

	void                            setKnownMatchesWithReferenceKeyFrame(std::vector<DescriptorMatch> & matches); // match not yet associated with map points

	std::vector<DescriptorMatch> &  getKnownMatchesWithReferenceKeyFrame(); // match  not yet associated with map points


    void                            addCommonMapPointsWithReferenceKeyFrame(std::vector<SRef<CloudPoint>> & points) ;

    std::vector<SRef<CloudPoint>> & getCommonMapPointsWithReferenceKeyFrame()  ;


    ///@brief pose of current frame
    Transform3Df                    m_pose;



    private:
    SRef<Image>                     m_view;
    SRef<Keyframe>                  m_referenceKeyFrame ;
    SRef<DescriptorBuffer>          m_descriptor;
    std::vector<SRef<Keypoint>>     m_keypoints ;
    std::vector<DescriptorMatch>    m_unknownMatchesWithReferenceKeyFrame ;
	std::vector<DescriptorMatch>    m_knownMatchesWithReferenceKeyFrame;
    std::vector<SRef<CloudPoint>>   m_trackedPoints;
    unsigned int                    m_countOfFramesSinceLastKframe ;



};

}
}





#endif // FRAME_H
