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

// Definition of Keypoint Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

///
/// \brief The Cloudpoint class
///
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
            /// @param[int] visibility graph of the cloudpoint.
            ///
        CloudPoint( double x,
                    double y,
                    double z,
                    float r,
                    float g,
                    float b,
                    double reproj_error,
                    std::vector<int>&visibility); ///
   ///
   /// \brief ~Keypoint
   ///
    ~CloudPoint();

    ///
    /// \brief This method returns the angle of an Keypoint
    /// \return angle
    ///
        inline float getR() const {return m_r;}
        inline float getG() const {return m_g;}
        inline float getB() const {return m_b;}

    ///
    /// \brief This method returns the size of an Keypoint
    /// \return size
    ///
        inline double getReprojError() const {return m_reproj_error;}

    ///
    /// \brief GetResponse
    /// \return
    ///
    std::vector<int>  m_visibility;
    private:     
        float             m_r;
        float             m_g;
        float             m_b;

        double            m_reproj_error;
	};
   }
}  // end of namespace SolAR

#endif // SolAR_KEYPOINT_H
