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

#ifndef SOLAR_IFUNDAMENTALMATRIXESTIMATION_H
#define SOLAR_IFUNDAMENTALMATRIXESTIMATION_H

#include "IComponentIntrospect.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"


namespace SolAR {
	using namespace datastructure;
	namespace api {
		namespace solver {
			namespace pose {

                namespace FundamentalMatrixEstimation {

					///
					/// \brief The HomographyEstimation return codes
					///
					enum  RetCode {
                        FUNDAMENTALMATRIX_ESTIMATION_OK = 0, /**< the default OK code*/
                        FUNDAMENTALMATRIX_EMPTY,			  /**< Homgraphy matrix is empty*/
					};

				}    // end of namespace HomographyEstimation

                class IFundamentalMatrixEstimation : public virtual org::bcom::xpcf::IComponentIntrospect {
				public:
                    IFundamentalMatrixEstimation() = default;
                    virtual ~IFundamentalMatrixEstimation() = default;

                    /// \brief find a epipolar fundamental matrix from 2 sets of 2D points
					/// \param srcPoints: set of points of first image
					/// \param dstPoints: set of points of second image
                    /// \param fundamental: output fundamental matrix
                    virtual FundamentalMatrixEstimation::RetCode findFundamental(const std::vector<SRef<Point2Df> >& srcPoints,
						const std::vector< SRef<Point2Df> >& dstPoints,
                        Transform2Df & fundamental) = 0;

                    static constexpr const char * UUID = "1c93e091-831f-4af7-a7a2-26bd06826391";
				};

			}
		}
	}
}

#endif // SOLAR_IHOMOGRAPHYESTIMATION_H
