/**
 * @copyright Copyright (c) 2024 B-com http://www.b-com.com/
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

#ifndef SOLAR_IMAGESEGMENTATIONPIPELINE_H
#define SOLAR_IMAGESEGMENTATIONPIPELINE_H

#include "api/pipeline/IPipeline.h"
#include "datastructure/Image.h"
#include <map>
#include <vector>
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace pipeline {

/**
 * @struct MaskValueInterpretation
 * @brief struct used to interpret pixel value in the segmentation mask
 * if classId < 0, it means that the current pixel is unsegmented
 * if instanceId < 0, it means that the current pixel belongs to a "stuff" class which is uncountable
 * if instanceId >= 0, it means that the current pixel belongs to a "thing" class
 * confidence is the confidence score of the pixel's segmentation (usually it has value between 0 and 1)
 * if confidence < 0, it simply means that the confidence score is not available for this pixel
 */
struct MaskValueInterpretation {
    int16_t classId = -1;
    int16_t instanceId = -1;
    float confidence = -1.f;
};

/**
 * @class IImageSegmentationPipeline
 * @brief <B>Defines an image segmentation pipeline.</B>
 * <TT>UUID: 0a897dee-74f1-42de-a6c1-f7855e0f0bbb</TT>
 *
 * This class provides the interface to define an image segmentation pipeline.
 */

class XPCF_CLIENTUUID("2215b6ef-e6fa-455c-84c6-820d95630eb5") XPCF_SERVERUUID("40aede65-0170-4384-9623-6a9d320ae56d")
    XPCF_GRPC_CLIENT_RECV_SIZE("-1") XPCF_GRPC_CLIENT_SEND_SIZE("-1")
    IImageSegmentationPipeline : virtual public IPipeline {
public:
    /// @brief default constructor
    IImageSegmentationPipeline() = default;

    /// @brief default destructor
    virtual ~IImageSegmentationPipeline() = default;

    /// @brief segmentation request
    /// @param[in] image pointer to image data to be segmented
    /// @param[out] mask output mask (pixel value of type uint8_t)
    /// @param[out] maskInterpretation mapping from mask pixel value to the MaskValueInterpretation
    /// @return FrameworkReturnCode::_SUCCESS (segmentation succeeded) or FrameworkReturnCode::_ERROR_ (segmentation failed)
    virtual FrameworkReturnCode segmentationRequest(SRef<const SolAR::datastructure::Image> image, 
                                                    SRef<SolAR::datastructure::Image>& mask, 
                                                    std::map<uint8_t, MaskValueInterpretation>& maskInterpretation) = 0;
    
    /// @brief segmentation request
    /// @param[in] images list of pointers to images to be segmented
    /// @param[out] masks list of output masks (pixel value of type uint8_t)
    /// @param[out] masksInterpretations list of mappings from mask pixel value to the MaskValueInterpretation
    /// @return FrameworkReturnCode::_SUCCESS (segmentation succeeded) or FrameworkReturnCode::_ERROR_ (segmentation failed)
    virtual FrameworkReturnCode segmentationRequest(const std::vector<SRef<SolAR::datastructure::Image>>& images, 
                                                    std::vector<SRef<SolAR::datastructure::Image>>& masks, 
                                                    std::vector<std::map<uint8_t, MaskValueInterpretation>>& masksInterpretations) = 0;
};
} // namespace pipeline
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IImageSegmentationPipeline,
                             "0a897dee-74f1-42de-a6c1-f7855e0f0bbb",
                             "IImageSegmentationPipeline",
                             "The interface to define an image segmentation pipeline")

#endif // SOLAR_IMAGESEGMENTATIONPIPELINE_H