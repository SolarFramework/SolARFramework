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

#ifndef SOLAR_IVISIBILITYSTORAGE_H
#define SOLAR_IVISIBILITYSTORAGE_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace storage {

/**
 * @class IVisibilityStorage
 * @brief Allows to store a set of keyframes. This storage component can be accessed by processing components to share persistent data.

 */

class IVisibilityStorage : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IVisibilityStorage default constructor
    IVisibilityStorage() = default;

    /// @brief IVisibilityStorage default destructor
    virtual ~IVisibilityStorage() = default;

    /// @brief This method allow to add a visibility between a keypoint and the cooresponding 3D point
    /// @param[in] frame the frame to which the keypoint belongs
    /// @param[in] keypoint the keypoint seeing the 3D point
    /// @param[in] point the 3D point seen from the keypoint
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode AddVisibility(const SRef<frame> frame, const SRef<Keypoint> keypoint, const SRef<Point3Df> point) = 0;

    /// @brief This method allow to add visibilities between keypoints of a same frame and the corresponding 3D points
    /// @param[in] frame the frame to which the keypoints belongs
    /// @param[in] keypoints the keypoints seeing the 3D points
    /// @param[in] points the 3D points seen from the keypoints
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode AddVisibility(const SRef<frame> frame, const std::vector<SRef<Keypoint>>& keypoints, const std::vector<SRef<Point3Df>>& points) = 0;

    /// @brief This method allow to suppress all visibilities related to a 3D point
    /// @param[in] point the 3D point for which we want to suppress all the related visibilities
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode Suppress3DPoint(const SRef<Point3Df> point) = 0;

    /// @brief This method allow to suppress all visibilities related to a set of 3D points
    /// @param[in] points the set of 3D points for which we want to suppress all the related visibilities
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode Suppress3DPoints(const std::vector<SRef<Point3Df>>& points) = 0;

    /// @brief This method allow to suppress all visibilities related to a frame
    /// @param[in] frame the frame for which we want to remove the visibilities related to its keypoints
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode SuppressFrame(const SRef<Frame> frame) = 0;

    /// @brief This method allow to suppress all visibilities related to a keypoint
    /// @param[in] keypoint the keypoint for which we want to suppress all the related visibilities
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode SuppressKeypoint(const SRef<Keypoint> keypoint) = 0;

    /// @brief This method allow to suppress all visibilities related to a set of keypoints
    /// @param[in] keypoints the set of keypoints for which we want to suppress all the related visibilities
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode SuppressKeypoints(const std::vector<SRef<Keypoint>>& keypoints) = 0;

    /// @brief This method allows to get all the 3D points visible from a frame
    /// @param[in] frame the frame for which you want to get the visible 3D points
    /// @param[out] visiblePoints the set of 3D points visible from the frame
    /// @return FrameworkReturnCode::_SUCCESS_ if the access to visible 3D points succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode GetVisible3DPoints(const SRef<Frame> frame, std::vector<SRef<Point3Df>>& visiblePoints) = 0;

    /// @brief This method allows to get all the 3D points visible from a keypoint
    /// @param[in] frame the frame to which the keypoint belongs
    /// @param[in] keypoint the keypoint for wich we want to obtain the visible 3D point
    /// @param[out] visiblePoint the 3D points visible from the keypoint
    /// @return FrameworkReturnCode::_SUCCESS_ if the access to visible 3D points succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode GetVisible3DPoint(const SRef<Frame> frame, const SRef<Keypoint> keypoint, SRef<Point3Df> visiblePoint) = 0;

    /// @brief This method allows to get all the keypoints and corresponding keyframes seeing a given 3D point
    /// @param[in] frame the frame for which you want to get the visible 3D points
    /// @param[out] visiblePoints the set of 3D points visible from the frame
    /// @return FrameworkReturnCode::_SUCCESS_ if the access to visible 3D points succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode GetVisible3DPoints(const SRef<Point3Df> point, std::vector<SRef<Frame>>& frames, std::vector<SRef<Keypoint>>& keypoints) = 0;

    /// @brief This method allows to get all the keypoints and corresponding keyframes seeing a given 3D point
    /// @param[in] frame the frame for which you want to get the visible 3D points
    /// @param[out] visiblePoints the set of 3D points visible from the frame
    /// @return FrameworkReturnCode::_SUCCESS_ if the access to visible 3D points succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode GetVisible3DPoints(const std::vector<SRef<Point3Df>>& points, std::vector<SRef<Frame>>& frames, std::vector<SRef<Keypoint>>& keypoints) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IVisibilityStorage,
                             "2c147595-6c74-4f69-b63d-91e162c311ed",
                             "IVisibilityStorage",
                             "A component interface for storing a set of persistent keyframes accesisble by processing components.");


#endif //SOLAR_IVISIBILITYSTORAGE_H

