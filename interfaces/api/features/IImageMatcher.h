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

#ifndef IIMAGEMATCHER_H
#define IIMAGEMATCHER_H


#include <xpcf/api/IComponentIntrospect.h>
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/DescriptorMatch.h"
#include "core/Messages.h"


namespace SolAR {
namespace api {
namespace features {

/**
 * @class IImageMatcher
 * @brief <B>Matches keypoint between two input images.</B>
 * <TT>UUID: 157ec340-0682-4e6c-bf69-e4d95fa760d3</TT>
 *
 * This class provides a keypoint matching method between directly from two images.
 */


class IImageMatcher: virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    /// @brief IDescriptorsExtractorFromImage default constructor
    IImageMatcher() = default;

    virtual ~IImageMatcher() {};

    /// @brief match keypoints between two input images.
    /// @param[in] image1, the first image.
    /// @param[in] image2, the second image.
    /// @param[out] keypoints1, The keypoints detected in the first image.
    /// @param[out] keypoints2, The keypoints detected in the second image.
    /// @param[out] descriptors1, The descriptors of keypoint of image1.
    /// @param[out] descriptors2, The descriptors of keypoint of image1.
    /// @param[out] matches, the keypoint matches between the first and second image
    /// @return FrameworkReturnCode::_SUCCESS_ if images are well matched, else FrameworkReturnCode::_ERROR
    virtual FrameworkReturnCode match( const SRef<SolAR::datastructure::Image> image1,
                                       const SRef<SolAR::datastructure::Image> image2,
                                       std::vector<SolAR::datastructure::Keypoint> & keypoints1,
                                       std::vector<SolAR::datastructure::Keypoint> & keypoints2,
                                       SRef<SolAR::datastructure::DescriptorBuffer> descriptors1,
                                       SRef<SolAR::datastructure::DescriptorBuffer> descriptors2,
                                       std::vector<SolAR::datastructure::DescriptorMatch> & matches) = 0;
};

}
}
}  // end of namespace SolAR

template <> struct org::bcom::xpcf::InterfaceTraits<SolAR::api::features::IImageMatcher>
{
    static constexpr const char * UUID = "{157ec340-0682-4e6c-bf69-e4d95fa760d3}";
    static constexpr const char * NAME = "IImageMatcher";
    static constexpr const char * DESCRIPTION = "IImageMatcher interface description";
};

#endif // IIMAGEMATCHER_H
