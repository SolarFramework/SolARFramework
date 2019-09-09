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

#include "datastructure/Frame.h"
#include "datastructure/Keyframe.h"

namespace SolAR {
namespace datastructure {

Frame::Frame(const SRef<Frame> frame) : m_keypoints(frame->getKeypoints()), m_descriptors(frame->getDescriptors()), m_view(frame->getView()), m_referenceKeyFrame(frame->getReferenceKeyframe()), m_pose(frame->getPose()), m_kpVisibility(frame->getVisibleKeypoints()), m_mapVisibility(frame->getVisibleMapPoints()){}

Frame::Frame(const SRef<Keyframe> keyframe) : m_keypoints(keyframe->getKeypoints()), m_descriptors(keyframe->getDescriptors()), m_view(keyframe->getView()), m_referenceKeyFrame(keyframe->getReferenceKeyframe()), m_pose(keyframe->getPose()), m_mapVisibility(keyframe->getVisibleMapPoints()) {
	int nKeypoints = keyframe->getKeypoints().size();
	for (int i = 0; i < nKeypoints; i++)
		m_kpVisibility[i] = i;
}

Frame::Frame(const std::vector<Keypoint> & keypoints, const SRef<DescriptorBuffer> descriptors, const SRef<Image> view, SRef<Keyframe> refKeyframe, const Transform3Df pose): m_keypoints(keypoints), m_descriptors(descriptors), m_view(view), m_referenceKeyFrame(refKeyframe), m_pose(pose){}

Frame::Frame(const std::vector<Keypoint> & keypoints, const SRef<DescriptorBuffer> descriptors, const SRef<Image> view,  const Transform3Df pose): m_keypoints(keypoints), m_descriptors(descriptors), m_view(view), m_pose(pose){}

SRef<Image>  Frame::getView()
{
    return m_view;
}

Transform3Df Frame::getPose()
{
    return m_pose;
}

void Frame::setPose(const Transform3Df & pose)
{
    m_pose = pose;
}

void Frame::setKeypoints(const std::vector<Keypoint> & kpts){
    m_keypoints  = kpts;
}

SRef<DescriptorBuffer> Frame::getDescriptors() const
{
    return m_descriptors;
}

const std::vector<Keypoint> & Frame::getKeypoints() const
{
    return m_keypoints;
}

void Frame::setReferenceKeyframe(SRef<Keyframe> keyframe)
{
    m_referenceKeyFrame = keyframe;
}

SRef<Keyframe> Frame::getReferenceKeyframe()
{
    return m_referenceKeyFrame;
}

const std::map<unsigned int, unsigned int> & Frame::getVisibleKeypoints()
{
	return m_kpVisibility;
}

void Frame::addVisibleKeypoints(const std::map<unsigned int, unsigned int>& kpVisibility)
{
	m_kpVisibility.insert(kpVisibility.begin(), kpVisibility.end());
}

void Frame::addVisibleMapPoints(const std::map<unsigned int, unsigned int>& mapPoints)
{
	m_mapVisibility.insert(mapPoints.begin(), mapPoints.end());
}

void Frame::addVisibleMapPoint(unsigned int id_keypoint, unsigned int id_cloudPoint)
{
	m_mapVisibility[id_keypoint] = id_cloudPoint;
}

const std::map<unsigned int, unsigned int> & Frame::getVisibleMapPoints()
{
	return m_mapVisibility;
}

}
}
