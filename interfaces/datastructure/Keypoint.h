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

#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"

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
    class  SOLARFRAMEWORK_API Keypoint final {
	public:
        Keypoint() = default;

        Keypoint::Keypoint( float x,
                            float y,
                            float size,
                            float angle,
                            float response,
                            int	octave,
                            int class_id ):
            m_position(x,y),
            m_size(size),
            m_angle(angle),
            m_response(response),
            m_octave(octave),
            m_class_id(class_id){
        }

    ///
    /// \brief This method returns the angle of an Keypoint
    /// \return angle
    ///
        inline float getAngle() const {return m_angle;}

    ///
    /// \brief This method returns the size of an Keypoint
    /// \return size
    ///
        inline float getSize() const {return m_size;}

    ///
    /// \brief GetResponse
    /// \return
    ///
        inline float getResponse() const {return m_response;}

    ///
    /// \brief This method returns the octave of an Keypoint
    /// \return octave
    ///
        inline int   getOctave() const {return m_octave;}

    ///
    /// \brief This method returns the classid of an Keypoint
    /// \return classid
    ///
        inline int   getClassId() const {return m_class_id;}

        const Point2Df &getPosition() const {return m_position;}
        float x() const {return m_position.x();}
        float y() const {return m_position.y();}

    private:     
        Point2Df        m_position;
        float           m_size{};
        float           m_angle{};
        float           m_response{};
        int             m_octave{};
        int             m_class_id{};
	};

}
}  // end of namespace SolAR

#endif // SolAR_KEYPOINT_H
