#include "datastructure/Frame.h"
namespace SolAR {
namespace datastructure {

    Frame::Frame()
    {
        m_countOfFramesSinceLastKframe = 0 ;
    }


    Frame::~Frame()
    {
    }


    void Frame::InitKeyPointsAndDescriptors(std::vector<SRef<Keypoint>> keypoints, SRef<DescriptorBuffer> descriptors)
    {
        m_keypoints = keypoints ;
        m_descriptor = descriptors ;
    }

    void Frame::setReferenceKeyFrame(SRef<Keyframe> kframe)
    {
        m_refrenceKeyFrame = kframe ;
    }

    SRef<Keyframe> Frame::getReferenceKeyFrame()
    {
        return m_refrenceKeyFrame ;
    }


    SRef<DescriptorBuffer> Frame::getDescriptors()
    {
        return m_descriptor ;
    }

    std::vector<SRef<Keypoint>> Frame::getKeyPoints()
    {
        return m_keypoints ;
    }

    void   Frame::setNumberOfFramesSinceLastKeyFrame(unsigned int nbFrames)
    {
       m_countOfFramesSinceLastKframe = nbFrames ;  ;
    }

    unsigned int Frame::getNumberOfFramesSinceLastKeyFrame() const
    {
        return m_countOfFramesSinceLastKframe ;
    }

    void  Frame::setMatchesWithReferenceKeyFrame(std::vector<DescriptorMatch> & matches)
    {
        m_matchesWithReferenceKeyFrame = matches ;
    }

    std::vector<DescriptorMatch>    Frame::getMatchesWithReferenceKeyFrame() const
    {
        return m_matchesWithReferenceKeyFrame ; //
    }

    unsigned int  Frame::getNumberOfMatchesWithReferenceKeyFrame() const
    {
        return static_cast<unsigned int>(m_matchesWithReferenceKeyFrame.size()) ;
    }
}
}
