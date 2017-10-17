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

#ifndef SolARKeypoint_H
#define SolARKeypoint_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "XPCF_definitions.h"
#include "SolARFrameworkDefinitions.h"


// Definition of SolARKeypoint Class //
// part of SolAR namespace //

namespace SolAR {


///
/// \brief The SolARKeypoint class
///
    class  SOLARFRAMEWORK_API SolARKeypoint  {
	public:
        SolARKeypoint() = default;


        SolARKeypoint( float x,
                    float  	y,
                    float  	size,
                    float  	angle,
                    float  	response,
                    int  	octave,
                    int  	class_id );
   ///
   /// \brief ~SolARKeypoint
   ///
    ~SolARKeypoint();
/// \brief This method initializes an SolARKeypoint object
    /// \param x: x-coordinate of the keypoint
    /// \param y: y-coordinate of the keypoint
    /// \param size: diameter of the meaningful keypoint neighborhood
    /// \param angle: orientation of the keypoint
    /// \param response: the response by which the most strong keypoints have been selected. Can be used for the further sorting or subsampling
    /// \param octave: octave (pyramid layer) from which the keypoint has been extracted
    /// \param class_id: object class (if the keypoints need to be clustered by an object they belong to)
    ///
     void init( float  x,
			float  	y,
			float  	size,
			float  	angle,
			float  	response,
			int  	octave,
            int  	class_id ) ;

    ///
    /// \brief This method returns the x-coordinate of an SolARKeypoint
    /// \return x-coordinate
    ///
        inline float getX() const { return m_x;}

    ///
    /// \brief This method returns the y-coordinate of an SolARKeypoint
    /// \return y-coordinate
    ///
        inline float getY() const { return m_y;}

    ///
    /// \brief This method returns the angle of an SolARKeypoint
    /// \return angle
    ///
        inline float getAngle() const {return m_angle;}

    ///
    /// \brief This method returns the size of an SolARKeypoint
    /// \return size
    ///
        inline float getSize() const {return m_size;}

    ///
    /// \brief GetResponse
    /// \return
    ///
        inline float getResponse() const {return m_response;}

    ///
    /// \brief This method returns the octave of an SolARKeypoint
    /// \return octave
    ///
        inline int   getOctave() const {return m_octave;}

    ///
    /// \brief This method returns the classid of an SolARKeypoint
    /// \return classid
    ///
        inline int   getClassId() const {return m_class_id;}

    private:

        float       m_x;
        float       m_y;
        float       m_size;
        float       m_angle;
        float       m_response;
        int         m_octave;
        int         m_class_id;
	};

}  // end of namespace SolAR

#endif // SolARKeypoint_H
