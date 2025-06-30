#ifndef FRAME_H
#define FRAME_H


#include <core/SolARFrameworkDefinitions.h>
#include <core/SerializationDefinitions.h>
#include <datastructure/GeometryDefinitions.h>
#include <datastructure/Image.h>
#include <datastructure/Keypoint.h>
#include <datastructure/DescriptorMatch.h>
#include <datastructure/CloudPoint.h>
#include <datastructure/CameraDefinitions.h>
#include <datastructure/GlobalDescriptor.h>
#include <datastructure/Object2DCollection.h>

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
                   const uint32_t camID = 0,
                   const Transform3Df pose = Transform3Df::Identity());

    explicit Frame(const std::vector<Keypoint> & keypoints,
				   const std::vector<Keypoint> & undistortedKeypoints,
                   const SRef<DescriptorBuffer> descriptors,
                   const SRef<Image> view,
                   const SRef<Keyframe> refKeyframe,
                   const uint32_t camID = 0,
                   const Transform3Df pose = Transform3Df::Identity());

    explicit Frame(const std::vector<Keypoint> & keypoints,
				   const std::vector<Keypoint> & undistortedKeypoints,
                   const SRef<DescriptorBuffer> descriptors,
                   const SRef<Image> view,
                   const uint32_t camID = 0,
                   const Transform3Df pose = Transform3Df::Identity());

    /// @brief ~Frame
    ~Frame() = default;

	/// @brief get view image
	/// @return view image
    const SRef<Image>& getView() const;

    /// @brief get mask
    /// @return mask
    const SRef<Image>& getMask() const;

    /// @brief get const 2D objects
    /// @return collection of 2D objects
    const SRef<Object2DCollection>& getConstObject2DCollection() const;

    /// @brief get 2D objects
    /// @param[out] objects 2D object collection
    /// @return std::unique_lock for protecting the access
    std::unique_lock<std::mutex> getObject2DCollection(SRef<Object2DCollection>& objects);

	/// @brief set view image
	/// @param[in] view: view image
	void setView(const SRef<Image> &view);

    /// @brief set mask
    /// @param[in] mask semantic segmentation mask
    void setMask(const SRef<Image>& mask);

    /// @brief set 2D objects
    /// @param[in] objects collection of 2D objects
    void setObject2DCollection(const SRef<Object2DCollection>& objects);

	/// @brief get camera pose
	/// @return camera pose
    const Transform3Df& getPose() const;

	/// @brief set pose
	/// @param[in] pose: camera pose
    void setPose(const Transform3Df & pose);

    /// @brief check if the pose of this frame is fixed and no need to optimize
    /// @return true if fixed pose, otherwise return false
    bool isFixedPose() const;

    /// @brief This method is to set this frame having a fixed pose.
	/// @param[in] value the value (true/false)
    void setFixedPose(bool value);

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
	
    /// @brief update keypoint class id
    /// @param[in] i index of keypoint
    /// @param[in] classId semantic class Id of this keypoint
    /// @return true if update class id successfully
    bool updateKeypointClassId(int i, int classId);

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

    /// @brief set camera parameters
    /// @param[in] camParams the camera parameters
    void setCameraID(const uint32_t camID);

    /// @brief get camera parameters
    /// @return the camera parameters
    const uint32_t& getCameraID() const;

    /// @brief set image name
    /// @param[in] imageName: image name
    void setImageName(const std::string &imageName);

    /// @brief get image name
    /// @return image name
    const std::string& getImageName() const;

    ///
    /// @brief Set global descriptor
    /// @param[in] gdescriptor global descriptor
    void setGlobalDescriptor(SRef<GlobalDescriptor> gdescriptor);

    ///
    /// @brief Get global descriptor
    /// @return reference to the global descriptor
    ///
    const SRef<GlobalDescriptor> getGlobalDescriptor() const;

private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version);

protected:
    Transform3Df                    m_pose;    
    SRef<Image>                     m_view;
    SRef<Image>                     m_mask; // semantic segmentation is stored as a mask
    SRef<Object2DCollection>        m_objects; // instance segmentation result is stored as a list of 2D objects
    SRef<Keyframe>                  m_referenceKeyFrame ;
    SRef<DescriptorBuffer>          m_descriptors;
    SRef<GlobalDescriptor>          m_globalDescriptor;
    std::vector<Keypoint>			m_keypoints;
    std::vector<Keypoint>			m_keypointsUndistort;
    std::string                     m_imageName;
    uint32_t                        m_camID;
    bool							m_isFixedPose = false;

	//A map storing the 3D points visibility, where the first element corresponds to the index of the keypoint of the frame, and the second element to the index of the corresponding cloudPoint.
	std::map<uint32_t, uint32_t>	m_mapVisibility;
};

DECLARESERIALIZE(Frame);

}
}

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Frame);

#endif // FRAME_H
