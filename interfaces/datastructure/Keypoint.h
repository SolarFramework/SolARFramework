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

#ifndef SOLAR_KEYPOINT_H
#define SOLAR_KEYPOINT_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <core/SolARFrameworkDefinitions.h>
#include <datastructure/GeometryDefinitions.h>
#include <core/SerializationDefinitions.h>

// Definition of Keypoint Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
 * @class Keypoint
 * @brief <B>A 2D Keypoint.</B>.
 *
 * This class provides Keypoint definition.
 */
class  SOLARFRAMEWORK_API Keypoint : public Point2Df {
public:
	/// @brief Keypoint constructor.
    Keypoint() = default;

	/// @brief Keypoint constructor.
    Keypoint( unsigned int id,
                float x,
                float y,
				float r,
				float g,
				float b,
                float size,
                float angle = -1.0f,
                float response = 0.0f,
                int   octave = 0,
                int   class_id = -1);

	/// @brief ~Keypoint
    ~Keypoint();

	/// @brief This method initializes an Keypoint object
    /// @param[in] x: x-coordinate of the keypoint
    /// @param[in] y: y-coordinate of the keypoint
	/// @param[in] r: r-channel color value of the keypoint.
	/// @param[in] g: g-channel color value of the keypoint.
	/// @param[in] b: b-channel color value of the keypoint.
    /// @param[in] size: diameter of the meaningful keypoint neighborhood
    /// @param[in] angle: orientation of the keypoint
    /// @param[in] response: the response by which the most strong keypoints have been selected. Can be used for the further sorting or subsampling
    /// @param[in] octave: octave (pyramid layer) from which the keypoint has been extracted
    /// @param[in] class_id: object class (if the keypoints need to be clustered by an object they belong to)
    void init( unsigned int id,
                float x,
                float y,
				float r,
				float g,
				float b,
                float size,
                float angle = -1.0f,
                float response = 0.0f,
                int   octave = 0,
                int   class_id = -1 ) ;

     /// @brief This method returns the id of the keypoint in its frame
     /// @return id
    inline float getId() const {return m_id;}

    /// @brief This method returns the angle of an Keypoint
    /// @return angle
    inline float getAngle() const {return m_angle;}

    /// @brief This method returns the size of an Keypoint
    /// @return size
    inline float getSize() const {return m_size;}

    /// @brief GetResponse
    /// @return
    inline float getResponse() const {return m_response;}

    /// @brief This method returns the octave of an Keypoint
    /// @return octave
    inline int   getOctave() const {return m_octave;}

    /// @brief This method returns the classid of an Keypoint
    /// @return classid
    inline int   getClassId() const {return m_class_id;}

	/// @brief These methods returns the color components of the CloudPoint
	/// @return the RGB color of the CloudPoint
	inline const Vector3f& getRGB() const { return m_rgb; };

	/// @brief These methods returns the color components of the CloudPoint
	/// @return the color component of the CloudPoint (Red, Green or Blue)
	inline const float& getR() const { return m_rgb[0]; };
	inline const float& getG() const { return m_rgb[1]; };
	inline const float& getB() const { return m_rgb[2]; };

    /// @brief This method returns the depth value of an Keypoint in the camera coordinate system
    /// @return depth value
    inline float getDepth() const {return m_depth;}

    /// @brief This method allows to set the depth value of an Keypoint in the camera coordinate system
    /// @param[in] depth  Depth value
    inline void setDepth(float depth) {m_depth = depth;}
	
    /// @brief This method allows to set the class Id of a Keypoint
    /// @param[in] classId  class id of the key point 
    inline void setClassId(int classId) {m_class_id = classId;}

    /// @brief This method allows to set the RGB values of a Keypoint
    /// @param[in] r  Red channel intensity level between 0 and 255
    /// @param[in] g  Green channel intensity level between 0 and 255
    /// @param[in] b  Blue channel intensity level between 0 and 255
    inline void setRGB(float r, float g, float b) {m_rgb(0)=r; m_rgb(1)=g; m_rgb(2)=b;}

private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version);

private:
    unsigned int    m_id; // The id of the keypoint in the current frame
    float           m_size;
    float           m_angle;
    float           m_response;
    int             m_octave;
    int             m_class_id = -1; // default value -1 meaning that no class is assigned
	Vector3f		m_rgb = { 0.0, 0.0, 0.0 };
    float           m_depth = -1.f;
};

DECLARESERIALIZE(Keypoint);

}
}  // end of namespace SolAR

#endif // SolAR_KEYPOINT_H
