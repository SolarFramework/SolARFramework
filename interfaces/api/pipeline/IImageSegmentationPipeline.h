/**
 * @copyright Copyright (c) 2025 B-com http://www.b-com.com/
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
#include "datastructure/Mask2DCollection.h"
#include <xpcf/core/helpers.h>

namespace SolAR {
using namespace datastructure;
namespace api {
namespace pipeline {

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

    /// Status of image segmentation processing
    enum class Status {
        UNINITIALIZED,    ///< processing not initialized
        INITIALIZED,      ///< processing correctly initialized, but not started
        IN_PROGRESS,      ///< processing in progress
        COMPLETED,        ///< processing completed
        ABORTED           ///< processing aborted before completion
    };

    /// @brief Return the text definition (string) of a Status object
    /// @param[in] status the Status type
    /// @return the text definition (string)
    static std::string toString(Status status)
    {
        switch (status) {
            case Status::UNINITIALIZED:
                return "UNINITIALIZED";
            case Status::INITIALIZED:
                return "INITIALIZED";
            case Status::IN_PROGRESS:
                return "IN_PROGRESS";
            case Status::COMPLETED:
                return "COMPLETED";
            case Status::ABORTED:
                return "ABORTED";
            default:
                return "Unknown value";
        }
    }

    /// @brief default constructor
    IImageSegmentationPipeline() = default;

    /// @brief default destructor
    virtual ~IImageSegmentationPipeline() = default;

    /// @brief segmentation request from an input image
    /// @param[in] image pointer to image
    /// @return FrameworkReturnCode::_SUCCESS (segmentation succeeded) or FrameworkReturnCode::_ERROR_ (segmentation failed)
    virtual FrameworkReturnCode segment(SRef<Image> image) = 0;

    /// @brief segmentation request from a number of input images
    /// @param[in] images list of pointers to images to be segmented
    /// @param[in] temporalConsistency flag indicating whether the images are temporally consistent (true) or not (false)
    /// @return FrameworkReturnCode::_SUCCESS (segmentation succeeded) or FrameworkReturnCode::_ERROR_ (segmentation failed)
    virtual FrameworkReturnCode segment(const std::vector<SRef<Image>>& images, bool temporalConsistency = false) = 0;

    /// @brief get status and progress percentage
    /// @param[out] status the current image segmentation processing status
    /// @param[out] progress the current progress percentage (valid value should be between 0 and 1)
    /// @return FrameworkReturnCode::_SUCCESS if the status and progress are successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getStatus(Status& status, float& progress) const = 0;

    /// @brief get output masks
    /// @param[out] mask output mask collection
    /// @return FrameworkReturnCode::_SUCCESS (get output mask succeeded) or FrameworkReturnCode::_ERROR_ (get output mask failed)
    virtual FrameworkReturnCode getOutputMask(SRef<Mask2DCollection>& mask) const = 0;

};

} // namespace pipeline
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IImageSegmentationPipeline,
                             "0a897dee-74f1-42de-a6c1-f7855e0f0bbb",
                             "IImageSegmentationPipeline",
                             "The interface to define an image segmentation pipeline")

#endif // SOLAR_IMAGESEGMENTATIONPIPELINE_H