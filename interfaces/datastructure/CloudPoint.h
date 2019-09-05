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

// Definition of CloudPoint Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {
class Keyframe;

/**
 * @class CloudPoint
 * @brief <B>A 3D point stored in a cloud of points.</B>
 */
class  SOLARFRAMEWORK_API CloudPoint : public Point3Df {
public:
    CloudPoint() = default;

    /// @brief Cloudpoint constructor.
    /// @param[int] x-coordinate of the cloudpoint.
    /// @param[int] y-coordinate of the cloudpoint.
    /// @param[int] z-coordinate of the cloudpoint.
    /// @param[int] r-channel color value of the cloudpoint.
    /// @param[int] g-channel color value of the cloudpoint.
    /// @param[int] b-channel color value of the cloudpoint.
    /// @param[int] reprojection error of the cloudpoint.
    /// @param[int] visibility map of the cloudpoint.
    ///
    CloudPoint( float x,
                float y,
                float z,
                float r,
                float g,
                float b,
                double reproj_error,
                std::map<unsigned int, unsigned int> &visibility);

	CloudPoint(float x,
		float y,
		float z,
		float r,
		float g,
		float b,
		double reproj_error,
		std::map<unsigned int, unsigned int> &visibility,
		SRef<DescriptorBuffer> descriptor);

    ///
    /// \brief ~CloudPoint
    ///
    ~CloudPoint();

    ///
    /// \brief These methods returns the color components of the CloudPoint
    /// \return the color component of the CloudPoint (Red, Green or Blue)
    ///
    float getR() const {return m_r;}
    float getG() const {return m_g;}
    float getB() const {return m_b;}

    ///
    /// \brief This method returns reprojection error of the PointCloud
    /// \return teh reprojection error
    ///
    double getReprojError() const {return m_reproj_error;}
    std::map<unsigned int, unsigned int> getVisibility() const {return m_visibility;}

    /// @brief return the visibility map of the CloudPoint
    /// @return The visibility, a map where the key corresponds to the id of the keyframe, and the value to the id of the keypoint in this keyframe.
    std::map<unsigned int, unsigned int>& getVisibility() { return m_visibility; };

    /// @brief add a keypoint to the visibility map of the CloudPoint
    /// @param keyframe_id: the id of the keyframe to which the keypoint belong
    /// @param keypoint_id: the id of the keypoint of the keyframe
    void visibilityAddKeypoint(unsigned int keyframe_id, unsigned int keypoint_id) { m_visibility[keyframe_id] = keypoint_id; };

	SRef<DescriptorBuffer> getDescriptor() const { return m_descriptor; };

private:
    std::map<unsigned int, unsigned int>  m_visibility;
    float             m_r;
    float             m_g;
    float             m_b;

    double            m_reproj_error;

	SRef<DescriptorBuffer> m_descriptor;
};
}
}  // end of namespace SolAR

#endif // SolAR_KEYPOINT_H
