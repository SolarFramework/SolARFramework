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

#ifndef SOLAR_IHOMOGRAPHYESTIMATION_H
#define SOLAR_IHOMOGRAPHYESTIMATION_H

#include "IComponentIntrospect.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"


namespace SolAR {
	using namespace datastructure;
	namespace api {
		namespace solver {
			namespace pose {

				namespace HomographyEstimation {

					///
                    /// @brief The HomographyEstimation return codes
					///
					enum  RetCode {
						HOMOGRAPHY_ESTIMATION_OK = 0, /**< the default OK code*/
						HOMOGRAPHY_EMPTY,			  /**< Homgraphy matrix is empty*/
					};

				}    // end of namespace HomographyEstimation
                /// @class IHomographyEstimation
				class IHomographyEstimation : public virtual org::bcom::xpcf::IComponentIntrospect {
				public:
					IHomographyEstimation() = default;
					virtual ~IHomographyEstimation() = default;

                    /// @brief find a Homography from 2 sets of 2D points.
                    /// @param[in] Set of 2d_points in the template view.
                    /// @param[in] Set of 2d_points in the current view.
                    /// @param[out] Estimated homography matrix.
					virtual HomographyEstimation::RetCode findHomography(const std::vector<SRef<Point2Df> >& srcPoints,
						const std::vector< SRef<Point2Df> >& dstPoints,
						Transform2Df & homography) = 0;

					static constexpr const char * UUID = "188e4ca3-3dff-4dde-a381-c1724b3e312f";
				};

			}
		}
	}
}

#endif // SOLAR_IHOMOGRAPHYESTIMATION_H
