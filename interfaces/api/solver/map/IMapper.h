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

#ifndef IMAPPER_H
#define IMAPPER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of IMapper Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

#include "datastructure/Identification.h"
#include "datastructure/CoordinateSystem.h"
#include "api/storage/ICovisibilityGraph.h"
#include "api/storage/IKeyframesManager.h"
#include "api/storage/IPointCloudManager.h"
#include "api/reloc/IKeyframeRetriever.h"

namespace SolAR {
namespace api {
namespace solver {
namespace map {
/**
  * @class IMapper
  * @brief <B>Allow to manage all components of a map.</B>
  * <TT>UUID: 90075c1b-915b-469d-b92d-41c5d575bf15</TT>
  */

class  IMapper : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IMapper default constructor
	IMapper() = default;

	/// @brief IMapper default destructor
	virtual ~IMapper() {}

	/// @brief Set the mapper
	/// @return FrameworkReturnCode::_SUCCESS_ if all data structures successfully setted, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode set(const SRef<IMapper> mapper) = 0;

	/// @brief Get the mapper
	/// @return FrameworkReturnCode::_SUCCESS_ if successfully, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode get(SRef<IMapper> & mapper) = 0;

	/// @brief Set identification component.
	/// @param[in] an identification instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setIdentification (const SRef<datastructure::Identification> identification) = 0;

	/// @brief Get identification component.
	/// @param[out] an identification instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getIdentification(SRef<datastructure::Identification> & identification) const = 0;

	/// @brief Set coordinate system component.
	/// @param[in] a coordinate system instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCoordinateSystem(const SRef<datastructure::CoordinateSystem> coordinateSystem) = 0;

	/// @brief Get coordinate system component.
	/// @param[out] a coordinate system instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCoordinateSystem(SRef<datastructure::CoordinateSystem> & coordinateSystem) const = 0;

	/// @brief Set point cloud component.
	/// @param[in] a point cloud instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setPointCloudManager(const SRef<storage::IPointCloudManager> pointCloudManager) = 0;

	/// @brief Get point cloud component.
	/// @param[out] a point cloud instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getPointCloudManager(SRef<storage::IPointCloudManager> & pointCloudManager) const = 0;

	/// @brief Set keyframes manager component.
	/// @param[in] a keyframes manager instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setKeyframesManager(const SRef<storage::IKeyframesManager> keyframesManager) = 0;
	
	/// @brief Get keyframes manager component.
	/// @param[out] a keyframes manager instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getKeyframesManager(SRef<storage::IKeyframesManager> & keyframesManager) const = 0;

	/// @brief Set covisibility graph component.
	/// @param[in] a covisibility graph instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCovisibilityGraph(const SRef<storage::ICovisibilityGraph> covisibilityGraph) = 0;

	/// @brief Get covisibility graph component.
	/// @param[out] a covisibility graph instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCovisibilityGraph(SRef<storage::ICovisibilityGraph> & covisibilityGraph) const = 0;

	/// @brief Set keyframe retriever component.
	/// @param[in] a keyframe retriever instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setKeyframeRetriever(const SRef<reloc::IKeyframeRetriever> keyframeRetriever) = 0;

	/// @brief Get keyframe retriever component.
	/// @param[out] a keyframe retriever instance
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getKeyframeRetriever(SRef<reloc::IKeyframeRetriever> & keyframeRetriever) const = 0;

	/// @brief Get local point cloud seen from the keyframe and its neighbors
	/// @param[in] keyframe: the keyframe to get local point cloud
	/// @param[in] minWeightNeighbor: the weight to get keyframe neighbors
	/// @param[out] localPointCloud: the local point cloud
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getLocalPointCloud(const SRef<datastructure::Keyframe> keyframe, const float minWeightNeighbor, std::vector<SRef<datastructure::CloudPoint>> &localPointCloud) const = 0;

	/// @brief Add a point cloud to mapper and update visibility of keyframes and covisibility graph
	/// @param[in] cloudPoint: the cloud point to add to the mapper
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode addCloudPoint(const SRef<datastructure::CloudPoint> cloudPoint) = 0;

	/// @brief Remove a point cloud from mapper and update visibility of keyframes and covisibility graph
	/// @param[in] cloudPoint: the cloud point to remove to the mapper
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode removeCloudPoint(const SRef<datastructure::CloudPoint> cloudPoint) = 0;

	/// @brief Remove a keyframe from mapper and update visibility of point cloud and covisibility graph
	/// @param[in] cloudPoint: the cloud point to add to the mapper
	/// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode removeKeyframe(const SRef<datastructure::Keyframe> keyframe) = 0;

	/// @brief Prune cloud points and keyframes of a map
	/// @param[in] cloudPoints: the cloud points are checked to prune
    virtual void pruning(const std::vector<SRef<datastructure::CloudPoint>> & cloudPoints = {}) = 0;

	/// @brief Save the map to the external file
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode saveToFile() const = 0;

	/// @brief Load the map from the external file
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode loadFromFile() = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IMapper,
                             "90075c1b-915b-469d-b92d-41c5d575bf15",
                             "IMapper",
                             "SolAR::api::solver::map::IMapper defines the interface of a mapper that manages all components of a map such as point cloud, keyframes, retriever model, coordinate, identification.");

#endif // IMAPPER_H
