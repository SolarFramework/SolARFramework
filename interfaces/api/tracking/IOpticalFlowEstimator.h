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

#ifndef SOLAR_IOPTICALFLOWESTIMATOR_H
#define SOLAR_IOPTICALFLOWESTIMATOR_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
namespace api {
namespace tracking {

/**
 * @class IOpticalFlowEstimator Estimator
 * @brief <B>Estimates the optical flow between two images.</B>
 * <TT>UUID: 3c74cd7f-950c-43ee-8886-9f4ddf763c27</TT>
 *
 * This interface is defined to implement components to estimate the optical flow between two images.
 */

class XPCF_IGNORE IOpticalFlowEstimator :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
   /// @brief IOpticalFlow default constructor
   IOpticalFlowEstimator() = default;

   /// @brief IContoursFilter default destructor
   virtual ~IOpticalFlowEstimator() = default;

   /// @brief estimate the optical flow between two images
   /// @param[in] previousImage: The previous image
   /// @param[in] currentImage: The current image for which we want to estimate the
   /// optical flow relative to the previous image
   /// @param[in] pointsToTrack: KEYPOINTS The pixels to track in the previous image
   /// @param[out] trackedPoints: The position of the pointsToTrack in the current image
   /// @param[out] status: Specify for each point; each element of the vector is set to 1
   /// if the flow for the corresponding features has been found, otherwise, it is set to 0.
   /// @param[out] error: Specify for each point the tracking error
   /// @return FrameworkReturnCode::_SUCCESS if the estimation is ok, otherwise frameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode estimate(const SRef<SolAR::datastructure::Image> previousImage,
                                        const SRef<SolAR::datastructure::Image> currentImage,
                                        const std::vector<SolAR::datastructure::Keypoint> & pointsToTrack,
                                        std::vector<SolAR::datastructure::Point2Df> & trackedPoints,
                                        std::vector<unsigned char> & status,
                                        std::vector<float> & error) = 0;

   /// @brief estimate the optical flow between two images
   /// @param[in] previousImage: The previous image
   /// @param[in] currentImage: The current image for which we want to estimate the optical
   /// flow relative to the previous image
   /// @param[in] pointsToTrack: POINT2DF The pixels to track in the previous image
   /// @param[out] trackedPoints: The position of the pointsToTrack in the current image
   /// @param[out] status: Specify for each point; each element of the vector is set to 1
   /// if the flow for the corresponding features has been found, otherwise, it is set to 0.
   /// @param[out] error: Specify for each point the tracking error
   /// @return FrameworkReturnCode::_SUCCESS if the estimation is ok, otherwise frameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode estimate(const SRef<SolAR::datastructure::Image> previousImage,
                                        const SRef<SolAR::datastructure::Image> currentImage,
                                        const std::vector<SolAR::datastructure::Point2Df> & pointsToTrack,
                                        std::vector<SolAR::datastructure::Point2Df> & trackedPoints,
                                        std::vector<unsigned char> & status,
                                        std::vector<float> & error) = 0;


};
}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::tracking::IOpticalFlowEstimator,
                             "3c74cd7f-950c-43ee-8886-9f4ddf763c27",
                             "IOpticalFlowEstimator",
                             "A interface for optical flow estimation between two images");

#endif // SOLAR_IOPTICALFLOWESTIMATOR_H
