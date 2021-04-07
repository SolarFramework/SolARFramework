#ifndef FEATURECLOUDPOINT_H
#define FEATURECLOUDPOINT_H

#include "xpcf/api/IComponentIntrospect.h"
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/CloudPoint.h"
#include <core/SerializationDefinitions.h>


// Definition of CloudPoint Class //
// part of SolAR namespace //
namespace SolAR {
namespace datastructure {

/**
	* @class CloudPoint
	* @brief <B>A 3D point stored in a cloud of points.</B>
	*/
class  SOLARFRAMEWORK_API FeatureCloudPoint : public CloudPoint {
public:
	FeatureCloudPoint() = default;

	/// @brief FeatureCloudPoint constructor.
	/// @param[in] x: x-coordinate of the cloudpoint.
	/// @param[in] y: y-coordinate of the cloudpoint.
	/// @param[in] z: z-coordinate of the cloudpoint.
	/// @param[in] r: r-channel color value of the cloudpoint.
	/// @param[in] g: g-channel color value of the cloudpoint.
	/// @param[in] b: b-channel color value of the cloudpoint.
	/// @param[in] visibility: visibility map of the cloudpoint.
	///
	explicit FeatureCloudPoint(float x,
							float y,
							float z,
							float r,
							float g,
							float b,
							double reproj_error,
							const std::map<uint32_t, uint32_t> & visibility);

	/// @brief FeatureCloudPoint constructor.
	/// @param[in] x: x-coordinate of the cloudpoint.
	/// @param[in] y: y-coordinate of the cloudpoint.
	/// @param[in] z: z-coordinate of the cloudpoint.
	/// @param[in] r: r-channel color value of the cloudpoint.
	/// @param[in] g: g-channel color value of the cloudpoint.
	/// @param[in] b: b-channel color value of the cloudpoint.
	/// @param[in] nx: x-coordinate of the view direction vector of the cloudpoint.
	/// @param[in] ny: y-coordinate of the view direction vector of the cloudpoint.
	/// @param[in] nz: z-coordinate of the view direction vector of the cloudpoint.
	/// @param[in] visibility: visibility map of the cloudpoint.
	///
	explicit FeatureCloudPoint(float x,
							float y,
							float z,
							float r,
							float g,
							float b,
							float nx,
							float ny,
							float nz,
							double reproj_error,
							const std::map<uint32_t, uint32_t> & visibility);

	/// @brief FeatureCloudPoint constructor.
	/// @param[in] x: x-coordinate of the cloudpoint.
	/// @param[in] y: y-coordinate of the cloudpoint.
	/// @param[in] z: z-coordinate of the cloudpoint.
	/// @param[in] r: r-channel color value of the cloudpoint.
	/// @param[in] g: g-channel color value of the cloudpoint.
	/// @param[in] b: b-channel color value of the cloudpoint.
	/// @param[in] visibility: visibility map of the cloudpoint.
	/// @param[in] descriptor: descriptor of the cloudpoint.
	///
	explicit FeatureCloudPoint(float x,
							float y,
							float z,
							float r,
							float g,
							float b,
							double reproj_error,
							const std::map<uint32_t, uint32_t> & visibility,
							SRef<DescriptorBuffer> descriptor);

	/// @brief FeatureCloudPoint constructor.
	/// @param[in] x: x-coordinate of the cloudpoint.
	/// @param[in] y: y-coordinate of the cloudpoint.
	/// @param[in] z: z-coordinate of the cloudpoint.
	/// @param[in] r: r-channel color value of the cloudpoint.
	/// @param[in] g: g-channel color value of the cloudpoint.
	/// @param[in] b: b-channel color value of the cloudpoint.
	/// @param[in] nx: x-coordinate of the view direction vector of the cloudpoint.
	/// @param[in] ny: y-coordinate of the view direction vector of the cloudpoint.
	/// @param[in] nz: z-coordinate of the view direction vector of the cloudpoint.
	/// @param[in] visibility: visibility map of the cloudpoint.
	/// @param[in] descriptor: descriptor of the cloudpoint.
	///
	explicit FeatureCloudPoint(float x,
							float y,
							float z,
							float r,
							float g,
							float b,
							float nx,
							float ny,
							float nz,
							double reproj_error,
							const std::map<uint32_t, uint32_t> & visibility,
							SRef<DescriptorBuffer> descriptor);

	///
	/// \brief ~FeatureCloudPoint
	///
	~FeatureCloudPoint() = default;

	///
	/// @brief This method returns the descriptor of the feature cloud point
	/// @return the descriptor
	///
	const SRef<DescriptorBuffer>& getDescriptor() const;

	///
	/// @brief This method sets the descriptor of the feature cloud point
	/// @param[in] descriptor: the descriptor
	///
	void setDescriptor(const SRef<DescriptorBuffer> &descriptor);

	/// @brief This method updates the descriptor of the feature cloud point by taking into account the descriptor of new keyframe
	/// @param[in] descriptor: the new descriptor
	void addNewDescriptor(const DescriptorView &descriptor);

	///
	/// @brief return the visibility map of the feature cloud point
	/// @return The visibility, a map where the key corresponds to the id of the keyframe, and the value to the id of the keypoint in this keyframe.
	///
	const std::map<uint32_t, uint32_t>& getVisibility() const;

	///
	/// @brief add a keypoint to the visibility map of the feature cloud point
	/// @param[in] keyframe_id: the id of the keyframe to which the keypoint belong
	/// @param[in] keypoint_id: the id of the keypoint of the keyframe
	///
	void addVisibility(const uint32_t& keyframe_id, const uint32_t& keypoint_id);

	///
	/// @brief remove a keypoint to the visibility map of the feature cloud point
	/// @param[in] keyframe_id: the id of the keyframe to which the keypoint belong
	/// @param[in] keypoint_id: the id of the keypoint of the keyframe
	/// @return true if remove successfully
	bool removeVisibility(const uint32_t& keyframe_id);

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version);

private:
	SRef<DescriptorBuffer>					m_descriptor = nullptr;
	std::map<unsigned int, unsigned int>	m_visibility = {};
};

DECLARESERIALIZE(FeatureCloudPoint);

}  // end of namespace datastructure
}  // end of namespace SolAR

#endif // FEATURECLOUDPOINT_H
