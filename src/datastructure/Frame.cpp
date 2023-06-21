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

#include "xpcf/core/helpers.h"

std::mutex						m_mutexPose;
std::mutex						m_mutexKeypoint;
std::mutex						m_mutexReferenceKeyframe;
std::mutex						m_mutexDescriptors;
std::mutex						m_mutexVisibility;

namespace SolAR {
namespace datastructure {

Frame::Frame(const SRef<Frame> frame) : m_pose(frame->getPose()), m_view(frame->getView()), m_referenceKeyFrame(frame->getReferenceKeyframe()), m_descriptors(frame->getDescriptors()), m_keypoints(frame->getKeypoints()), m_keypointsUndistort(frame->getUndistortedKeypoints()), m_imageName(frame->getImageName()), m_camID(frame->getCameraID()), m_isFixedPose(frame->isFixedPose()), m_mapVisibility(frame->getVisibility()){}

Frame::Frame(const SRef<Keyframe> keyframe) : m_pose(keyframe->getPose()), m_view(keyframe->getView()), m_referenceKeyFrame(keyframe->getReferenceKeyframe()), m_descriptors(keyframe->getDescriptors()), m_keypoints(keyframe->getKeypoints()), m_keypointsUndistort(keyframe->getUndistortedKeypoints()), m_imageName(keyframe->getImageName()), m_camID(keyframe->getCameraID()), m_isFixedPose(keyframe->isFixedPose()), m_mapVisibility(keyframe->getVisibility()) {}

Frame::Frame(const std::vector<Keypoint>& keypoints, const SRef<DescriptorBuffer> descriptors, const SRef<Image> view, const uint32_t camID, const Transform3Df pose) : m_pose(pose), m_view(view), m_descriptors(descriptors), m_keypoints(keypoints), m_camID(camID) {}

Frame::Frame(const std::vector<Keypoint> & keypoints, const std::vector<Keypoint> & undistortedKeypoints, const SRef<DescriptorBuffer> descriptors, const SRef<Image> view, SRef<Keyframe> refKeyframe, const uint32_t camID, const Transform3Df pose): m_pose(pose), m_view(view), m_referenceKeyFrame(refKeyframe), m_descriptors(descriptors), m_keypoints(keypoints), m_keypointsUndistort(undistortedKeypoints), m_camID(camID){}

Frame::Frame(const std::vector<Keypoint> & keypoints, const std::vector<Keypoint> & undistortedKeypoints, const SRef<DescriptorBuffer> descriptors, const SRef<Image> view, const uint32_t camID, const Transform3Df pose): m_pose(pose), m_view(view), m_descriptors(descriptors), m_keypoints(keypoints), m_keypointsUndistort(undistortedKeypoints), m_camID(camID) {}

const SRef<Image>& Frame::getView() const
{
    return m_view;
}

void Frame::setView(const SRef<Image>& view)
{
	m_view = view;
}

const Transform3Df& Frame::getPose() const
{
	std::unique_lock<std::mutex> lock(m_mutexPose);
    return m_pose;
}

void Frame::setPose(const Transform3Df & pose)
{
	std::unique_lock<std::mutex> lock(m_mutexPose);
    m_pose = pose;
}

bool Frame::isFixedPose() const
{
    return m_isFixedPose;
}

void Frame::setFixedPose(bool value)
{
    m_isFixedPose = value;
}

void Frame::setKeypoints(const std::vector<Keypoint> & kpts){
	std::unique_lock<std::mutex> lock(m_mutexKeypoint);
    m_keypoints  = kpts;
}

bool Frame::updateKeypointClassId(int i, int classId) 
{
    if (i < 0 || i >= static_cast<int>(m_keypoints.size()) || i >= static_cast<int>(m_keypointsUndistort.size())) {
        std::cerr << "keypoint index " << i << " out of range" << std::endl;
        return false;
    }
    m_keypoints[i].setClassId(classId);
    m_keypointsUndistort[i].setClassId(classId);
    return true;
}

const std::vector<Keypoint>& Frame::getUndistortedKeypoints() const
{
	std::unique_lock<std::mutex> lock(m_mutexKeypoint);
	return m_keypointsUndistort;
}

const Keypoint & Frame::getUndistortedKeypoint(int i) const
{
	std::unique_lock<std::mutex> lock(m_mutexKeypoint);
	return m_keypointsUndistort[i];
}

void Frame::setUndistortedKeypoints(const std::vector<Keypoint>& kpts)
{
	std::unique_lock<std::mutex> lock(m_mutexKeypoint);
	m_keypointsUndistort = kpts;
}

const SRef<DescriptorBuffer>& Frame::getDescriptors() const
{
	std::unique_lock<std::mutex> lock(m_mutexDescriptors);
    return m_descriptors;
}

void Frame::setDescriptors(const SRef<DescriptorBuffer> &descriptors)
{
	std::unique_lock<std::mutex> lock(m_mutexDescriptors);
	m_descriptors = descriptors;
}

const std::map<uint32_t, uint32_t>& Frame::getVisibility() const
{
	std::unique_lock<std::mutex> lock(m_mutexVisibility);
	return m_mapVisibility;
}

void Frame::setVisibility(const std::map<uint32_t, uint32_t>& visibilities)
{
	std::unique_lock<std::mutex> lock(m_mutexVisibility);
	m_mapVisibility = visibilities;
}

void Frame::addVisibilities(const std::map<uint32_t, uint32_t>& visibilites)
{
	std::unique_lock<std::mutex> lock(m_mutexVisibility);
	m_mapVisibility.insert(visibilites.begin(), visibilites.end());
}

void Frame::addVisibility(const uint32_t& id_keypoint, const uint32_t& id_cloudPoint)
{
	std::unique_lock<std::mutex> lock(m_mutexVisibility);
	m_mapVisibility[id_keypoint] = id_cloudPoint;
}

bool Frame::removeVisibility(const uint32_t& id_keypoint, const uint32_t& /* id_cloudPoint */)
{
	std::unique_lock<std::mutex> lock(m_mutexVisibility);
	if (m_mapVisibility.find(id_keypoint) == m_mapVisibility.end())
		return false;
	else {
		m_mapVisibility.erase(id_keypoint);
		return true;
	}
}

const std::vector<Keypoint> & Frame::getKeypoints() const
{
	std::unique_lock<std::mutex> lock(m_mutexKeypoint);
    return m_keypoints;
}

const Keypoint& Frame::getKeypoint(int i) const
{
    std::unique_lock<std::mutex> lock(m_mutexKeypoint);
    return m_keypoints[i];
}

void Frame::setReferenceKeyframe(const SRef<Keyframe>& keyframe)
{
	std::unique_lock<std::mutex> lock(m_mutexReferenceKeyframe);
    m_referenceKeyFrame = keyframe;
}

const SRef<Keyframe>& Frame::getReferenceKeyframe() const
{
	std::unique_lock<std::mutex> lock(m_mutexReferenceKeyframe);
    return m_referenceKeyFrame;
}

void Frame::setCameraID(const uint32_t camID)
{
    m_camID = camID;
}

const uint32_t & Frame::getCameraID() const
{
    return m_camID;
}

void Frame::setImageName(const std::string &imageName)
{
    m_imageName = imageName;
}

const std::string& Frame::getImageName() const
{
    return m_imageName;
}

template<typename Archive>
void Frame::serialize(Archive &ar, const unsigned int /* version */) {
	ar & boost::serialization::make_array(m_pose.data(), 12);
	ar & m_view;
	ar & m_descriptors;
	ar & m_keypoints;
	ar & m_keypointsUndistort;	
	ar & m_imageName;
    ar & m_camID;
    ar & m_isFixedPose;
	ar & m_mapVisibility;	
}

IMPLEMENTSERIALIZE(Frame);

}
}
