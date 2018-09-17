#include "datastructure/Frame.h"
namespace SolAR {
namespace datastructure {

/*
    Frame::Frame()
    {
        m_countOfFramesSinceLastKframe = 0 ;
    }
*/
    Frame::Frame(std::vector<SRef<Keypoint>> keypoints, SRef<DescriptorBuffer> descriptors, SRef<Image> view, Transform3Df pose)
    {
        m_keypoints = keypoints ;
        m_descriptor = descriptors ;
        m_view = view;
        m_pose = pose;
        m_countOfFramesSinceLastKframe = 0 ;
    }

    Frame::~Frame()
    {
    }

    void Frame::setReferenceKeyFrame(SRef<Keyframe> kframe)
    {
        m_referenceKeyFrame = kframe ;
    }

    SRef<Keyframe> Frame::getReferenceKeyFrame()
    {
        return m_referenceKeyFrame ;
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

    void  Frame::setUnknownMatchesWithReferenceKeyFrame(std::vector<DescriptorMatch> & matches)
    {
        m_unknownMatchesWithReferenceKeyFrame = matches ;
    }

    std::vector<DescriptorMatch> &   Frame::getUnknownMatchesWithReferenceKeyFrame()
    {
        return m_unknownMatchesWithReferenceKeyFrame; //
    }

	void  Frame::setKnownMatchesWithReferenceKeyFrame(std::vector<DescriptorMatch> & matches)
	{
		m_knownMatchesWithReferenceKeyFrame = matches;
	}

	std::vector<DescriptorMatch> &   Frame::getKnownMatchesWithReferenceKeyFrame()
	{
		return m_knownMatchesWithReferenceKeyFrame; //
	}

    void Frame::addCommonMapPointsWithReferenceKeyFrame(std::vector<SRef<CloudPoint>> & points)
    {
        m_trackedPoints.insert(m_trackedPoints.end(), points.begin(), points.end());
    }

    std::vector<SRef<CloudPoint>> &  Frame::getCommonMapPointsWithReferenceKeyFrame()
    {
        return m_trackedPoints ;
    }


    /*unsigned int  Frame::getNumberOfMatchesWithReferenceKeyFrame()
    {
        return static_cast<unsigned int>(m_matchesWithReferenceKeyFrame.size()) ;
    }*/
}
}
