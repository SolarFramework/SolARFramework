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

#ifndef SOLAR_CLOUDPOINT_H
#define SOLAR_CLOUDPOINT_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "xpcf/api/IComponentIntrospect.h"
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/PrimitiveInformation.h"
#include <core/SerializationDefinitions.h>

#include <Eigen/Dense>

// Definition of CloudPoint Class //
// part of SolAR namespace //
namespace SolAR {
namespace datastructure {
/**
 * @class CloudPoint
 * @brief <B>A 3D point stored in a cloud of points.</B>
 */
class  SOLARFRAMEWORK_API CloudPoint : public Point3Df, public PrimitiveInformation {
public:
    CloudPoint() = default;

	/// @brief CloudPoint constructor with a Point3Df.
	/// @param[in] point a Point3Df
	/// @param[in] r (optional): r-channel color value of the cloudpoint.
	/// @param[in] g (optional): g-channel color value of the cloudpoint.
	/// @param[in] b (optional): b-channel color value of the cloudpoint.
	/// @param[in] nx (optional): x-coordinate of the view direction vector of the cloudpoint.
	/// @param[in] ny (optional): y-coordinate of the view direction vector of the cloudpoint.
	/// @param[in] nz (optional): z-coordinate of the view direction vector of the cloudpoint.
    explicit CloudPoint( const Point3Df& point,
                         float r = 0.0f,
                         float g = 0.0f,
                         float b = 0.0f,
                         float nx = 0.0f,
                         float ny = 0.0f,
                         float nz = 0.0f,
                         double reproj_error = 0.0);

    /// @brief Cloudpoint constructor.
    /// @param[in] x: x-coordinate of the cloudpoint.
    /// @param[in] y: y-coordinate of the cloudpoint.
    /// @param[in] z: z-coordinate of the cloudpoint.
    /// @param[in] r (optional): r-channel color value of the cloudpoint.
    /// @param[in] g (optional): g-channel color value of the cloudpoint.
    /// @param[in] b (optional): b-channel color value of the cloudpoint.
    /// @param[in] nx (optional): x-coordinate of the view direction vector of the cloudpoint.
    /// @param[in] ny (optional): y-coordinate of the view direction vector of the cloudpoint.
    /// @param[in] nz (optional): z-coordinate of the view direction vector of the cloudpoint.
    ///
    explicit CloudPoint( float x,
                         float y,
                         float z,
                         float r = 0.0f,
                         float g = 0.0f,
                         float b = 0.0f,
                         float nx = 0.0f,
                         float ny = 0.0f,
                         float nz = 0.0f,
                         double reproj_error = 0.0);

    /// @brief Cloudpoint constructor.
    /// @param[in] x: x-coordinate of the cloudpoint.
    /// @param[in] y: y-coordinate of the cloudpoint.
    /// @param[in] z: z-coordinate of the cloudpoint.
    /// @param[in] r: r-channel color value of the cloudpoint.
    /// @param[in] g: g-channel color value of the cloudpoint.
    /// @param[in] b: b-channel color value of the cloudpoint.
    /// @param[in] visibility: visibility map of the cloudpoint.
    ///
    explicit CloudPoint( float x,
                         float y,
                         float z,
                         float r,
                         float g,
                         float b,
                         double reproj_error,
                         const std::map<unsigned int, unsigned int> & visibility);

    /// @brief Cloudpoint constructor.
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
    explicit CloudPoint( float x,
                         float y,
                         float z,
                         float r,
                         float g,
                         float b,
                         float nx,
                         float ny,
                         float nz,
                         double reproj_error,
                         const std::map<unsigned int, unsigned int> & visibility);

    /// @brief Cloudpoint constructor.
    /// @param[in] x: x-coordinate of the cloudpoint.
    /// @param[in] y: y-coordinate of the cloudpoint.
    /// @param[in] z: z-coordinate of the cloudpoint.
    /// @param[in] r: r-channel color value of the cloudpoint.
    /// @param[in] g: g-channel color value of the cloudpoint.
    /// @param[in] b: b-channel color value of the cloudpoint.
    /// @param[in] visibility: visibility map of the cloudpoint.
    /// @param[in] descriptor: descriptor of the cloudpoint.
    ///
    explicit CloudPoint( float x,
                         float y,
                         float z,
                         float r,
                         float g,
                         float b,
                         double reproj_error,
                         const std::map<unsigned int, unsigned int> & visibility,
                         SRef<DescriptorBuffer> descriptor);

    /// @brief Cloudpoint constructor.
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
    explicit CloudPoint( float x,
                         float y,
                         float z,
                         float r,
                         float g,
                         float b,
                         float nx,
                         float ny,
                         float nz,
                         double reproj_error,
                         const std::map<unsigned int, unsigned int> & visibility,
                         SRef<DescriptorBuffer> descriptor);

    ///
    /// \brief ~CloudPoint
    ///
    ~CloudPoint();

	///
	/// @brief This method returns the id of the cloud point
	/// @return the id
	///
	const uint32_t& getId() const;

	///
	/// @brief This method sets the id of the cloud point
	/// @param[in] id: id of cloud point
	///
	void setId(const uint32_t& id);

	///
	/// @brief This method returns the descriptor of the cloud point
	/// @return the descriptor
	///
	const SRef<DescriptorBuffer>& getDescriptor() const;

	///
	/// @brief This method sets the descriptor of the cloud point
	/// @param[in] descriptor: the descriptor
	///
	void setDescriptor(const SRef<DescriptorBuffer> &descriptor);

	/// @brief This method updates the descriptor of the cloud point by taking into account the descriptor of new keyframe
	/// @param[in] descriptor: the new descriptor
	void addNewDescriptor(const DescriptorView &descriptor);

    ///
    /// @brief These methods returns the color components of the CloudPoint
    /// @return the RGB color of the CloudPoint
    ///
	const Vector3f& getRGB() const;

	///
    /// @brief These methods returns the color components of the CloudPoint
    /// @return the color component of the CloudPoint (Red, Green or Blue)
	///
	const float& getR() const;
	const float& getG() const;
	const float& getB() const;


	///
	/// @brief This method sets the RGB color of the cloud point
	/// @param[in] rgb: rgb color
	///
	void setRGB(const Vector3f &rgb);

	///
	/// @brief This method returns the view direction of the cloud point
	/// @return view direction vector
	///
	const Vector3f& getViewDirection() const;

	///
	/// @brief This method sets the view direction of the cloud point
	/// @param[in] viewDirection: the view direction
	///
	void setViewDirection(const Vector3f &viewDirection);

	/// @brief This method updates the view direction of the cloud point by taking into account the view direction of new keyframe
	/// @param[in] viewDirection: the new view direction
	void addNewViewDirection(const Vector3f &viewDirection);
  
	/// @brief This method sets reprojection error of the PointCloud
	/// @param[in] error the reprojection error
	void setReprojError(const double &error);

	/// @brief This method returns reprojection error of the PointCloud
	/// @return the reprojection error
	const double& getReprojError() const;

	///
    /// @brief return the visibility map of the CloudPoint
    /// @return The visibility, a map where the key corresponds to the id of the keyframe, and the value to the id of the keypoint in this keyframe.
	///
	const std::map<uint32_t, uint32_t>& getVisibility() const;

	///
    /// @brief add a keypoint to the visibility map of the CloudPoint
    /// @param[in] keyframe_id: the id of the keyframe to which the keypoint belong
    /// @param[in] keypoint_id: the id of the keypoint of the keyframe
	///
    void addVisibility(const uint32_t& keyframe_id, const uint32_t& keypoint_id);

	///
	/// @brief remove a keypoint to the visibility map of the CloudPoint
	/// @param[in] keyframe_id: the id of the keyframe to which the keypoint belong
	/// @param[in] keypoint_id: the id of the keypoint of the keyframe
	/// @return true if remove successfully
	bool removeVisibility(const uint32_t& keyframe_id);


    //void updateSemanticVector(const SRef<Keyframe> &keyframe);

private:
	friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

private:	
	uint32_t								m_id = 0;
    SRef<DescriptorBuffer>					m_descriptor = nullptr;
    std::map<unsigned int, unsigned int>	m_visibility = {};
    Vector3f								m_rgb = {0.0, 0.0, 0.0};
    Vector3f								m_viewDirection = {0.0, 0.0, 0.0};
    double                                  m_reproj_error = 0.0;
	bool									m_isFeatureCP;

    Eigen::VectorXd                         m_probabilityVector;
    int                                                  m_class;



};

DECLARESERIALIZE(CloudPoint);

}  // end of namespace datastructure
}  // end of namespace SolAR

#endif // SolAR_KEYPOINT_H
