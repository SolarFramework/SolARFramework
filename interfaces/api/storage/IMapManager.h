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

#ifndef IMAPMANAGER_H
#define IMAPMANAGER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of IMapManager Class //
// part of SolAR namespace //

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Map.h"
#include "api/storage/ICameraParametersManager.h"
#include "api/storage/ICovisibilityGraphManager.h"
#include "api/storage/IKeyframesManager.h"
#include "api/storage/IPointCloudManager.h"
#include "api/reloc/IKeyframeRetriever.h"

namespace SolAR {
namespace api {
namespace storage {
/**
* @class IMapManager
* @brief <B>Allow to manage all components of a map.</B>
* <TT>UUID: 90075c1b-915b-469d-b92d-41c5d575bf15</TT>
*/

class XPCF_IGNORE IMapManager :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IMapManager default constructor
	IMapManager() = default;

	/// @brief IMapManager default destructor
	virtual ~IMapManager() {}

	/// @brief Set the map
	/// @param[in] map the data of map
	/// @return FrameworkReturnCode::_SUCCESS_ if all data structures successfully setted, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode setMap(const SRef<SolAR::datastructure::Map> map) = 0;

	/// @brief Get the map
	/// @param[out] map the data of map
	/// @return FrameworkReturnCode::_SUCCESS_ if successfully, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getMap(SRef<SolAR::datastructure::Map> & map) = 0;

	/// @brief Get the submap around a centered keyframe
	/// @param[in] idCenteredKeyframe the id of the centered keyframe
	/// @param[in] nbKeyframes the maximum number of keyframes of the submap
	/// @param[out] submap the submap
	/// @return FrameworkReturnCode::_SUCCESS_ if successfully, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode getSubmap(uint32_t idCenteredKeyframe,
										  uint32_t nbKeyframes,
										  SRef<SolAR::datastructure::Map> & submap) = 0;

    /// @brief Get local point cloud seen from the keyframes
    /// @param[in] keyframes the keyframes to get local point cloud
    /// @param[out] localPointCloud the local point cloud seen by the keyframes
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getLocalPointCloud(const std::vector<SRef<SolAR::datastructure::Keyframe>> &keyframes,
                                                   std::vector<SRef<SolAR::datastructure::CloudPoint>> &localPointCloud) const = 0;

	/// @brief Get local point cloud seen from the keyframe and its neighbors
	/// @param[in] keyframe the keyframe to get local point cloud
	/// @param[in] minWeightNeighbor the weight to get keyframe neighbors
	/// @param[out] localPointCloud the local point cloud
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getLocalPointCloud(const SRef<SolAR::datastructure::Keyframe> keyframe,
                                                   const float minWeightNeighbor,
                                                   std::vector<SRef<SolAR::datastructure::CloudPoint>> &localPointCloud) const = 0;

	/// @brief Add a point cloud to map manager and update visibility of keyframes and covisibility graph
	/// @param[in] cloudPoint the cloud point to add to the map manager
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode addCloudPoint(const SRef<SolAR::datastructure::CloudPoint> cloudPoint) = 0;

	/// @brief Remove a point cloud from map manager and update visibility of keyframes and covisibility graph
	/// @param[in] cloudPoint the cloud point to remove to the map manager
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode removeCloudPoint(const SRef<SolAR::datastructure::CloudPoint> cloudPoint) = 0;

	/// @brief Add a keyframe to map manager
	/// @param[in] keyframe the keyframe to add to the map manager
    /// @param[in] defineKeyframeId if true an id will be set for the added keyframe, if false the id of the keyframe will be used
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode addKeyframe(const SRef<SolAR::datastructure::Keyframe> keyframe, bool defineKeyframeId = true) = 0;

	/// @brief Remove a keyframe from map manager and update visibility of point cloud and covisibility graph
	/// @param[in] keyframe the keyframe to remove from the map manager
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode removeKeyframe(const SRef<SolAR::datastructure::Keyframe> keyframe) = 0;

    /// @brief Add camera parameters to map manager
    /// @param[in] cameraParameters the camera paramaters to add to the map manager
    /// @param[in] defineCameraParametersId if true an id will be set for the added CameraParameters, if false the id of the CameraParameters will be used
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode addCameraParameters(const SRef<SolAR::datastructure::CameraParameters> cameraParameters, bool defineCameraParametersId = true) = 0;

    /// @brief Remove camera parameters from map manager
    /// @param[in] cameraParameters the camera parameters to remove from the map manager
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode removeCameraParameters(const SRef<SolAR::datastructure::CameraParameters> cameraParameters) = 0;

    /// @brief Get camera parameters from map manager
    /// @param[in] id the id of the camera parameters
    /// @param[out] cameraParameters the camera parameters to get from the map manager
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCameraParameters(const uint32_t id, SRef<SolAR::datastructure::CameraParameters> & cameraParameters) = 0;

    /// @brief Get camera parameters from map manager
    /// @param[in] id the id of the camera parameters
    /// @param[out] cameraParameters the camera parameters to get from the map manager
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCameraParameters(const uint32_t id, SolAR::datastructure::CameraParameters & cameraParameters) = 0;

	/// @brief Prune cloud points of a map
	/// @param[in] cloudPoints: the cloud points are checked to prune
    virtual int pointCloudPruning(const std::vector<SRef<SolAR::datastructure::CloudPoint>> &cloudPoints = {}) = 0;

	/// @brief Prune keyframes of a map
	/// @param[in] keyframes: the keyframes are checked to prune
    virtual int keyframePruning(const std::vector<SRef<SolAR::datastructure::Keyframe>> &keyframes = {}) = 0;

    /// @brief Prune visibilities of a map 
    virtual FrameworkReturnCode visibilityPruning() = 0;   

	/// @brief Save the map to the external file
    /// @return FrameworkReturnCode::_SUCCESS_ if the backup succeeds, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode saveToFile() const = 0;

	/// @brief Load the map from the external file
    /// @return FrameworkReturnCode::_SUCCESS_ if the loading succeeds, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode loadFromFile() = 0;

    /// @brief Delete the map in external file
    /// @return FrameworkReturnCode::_SUCCESS_ if the deletion succeeds, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode deleteFile() = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IMapManager,
                             "90075c1b-915b-469d-b92d-41c5d575bf15",
                             "IMapManager",
                             "SolAR::api::storage::IMapManager defines the interface of a map manager that manages all components of a map such as point cloud, keyframes, retriever model, coordinate, identification.");

#endif // IMAPMANAGER_H
