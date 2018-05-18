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

#ifndef SOLAR_I2D3DCORRESPONDENCESFINDER_H
#define SOLAR_I2D3DCORRESPONDENCESFINDER_H

#include "IComponentIntrospect.h"

#include "core/Messages.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Pose.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/Keypoint.h"
#include "datastructure/DescriptorMatch.h"


namespace SolAR {
using namespace datastructure;
    namespace api {
        namespace solver {
            namespace pose {
            /**
             * @class I2D3DCorrespondencesFinder
             * @brief Decomposes 2D transform (ex Fundamental matrix) to 3D transform (ex camera pose).
             */
                class  I2D3DCorrespondencesFinder : public virtual org::bcom::xpcf::IComponentIntrospect {
                public:
                    /// @brief I2D3DCorrespondencesFinder default constructor.
                    I2D3DCorrespondencesFinder() = default;

                    /// @brief IFundamentalMatrixDecomposer default destructor.
                    virtual ~I2D3DCorrespondencesFinder() = default;
                    /// @brief .
                    /// @param[in].
                    /// @param[in].
                    /// @param[in].
                    /// @param[in].
                    /// @param[out].
                    /// @param[out].
                    virtual FrameworkReturnCode  find(const std::vector<SRef<CloudPoint>>&cloud,
                                                      const int keyframe_idx,
                                                      const std::vector<DescriptorMatch>&current_matches,
                                                      const std::vector<SRef<Keypoint>>&current_kpoints,
                                                      std::vector<SRef<CloudPoint>>&shared_mapPoint,
                                                      std::vector<SRef<Point3Df>>&shared_3dpoint,
                                                      std::vector<SRef<Point2Df>>&shared_2dpoint,
													  std::vector<DescriptorMatch> & found_matches , 
                                                      std::vector<DescriptorMatch> & remaining_matches)=0;
                    XPCF_DECLARE_UUID("0404e8b9-b824-4852-a34d-6eafa7563918");
                };
            }
        }
    }
}  // end of namespace Solar
#endif // SOLAR_IHOMOGRAPHYESTIMATION_H
