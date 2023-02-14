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

#ifndef SOLAR_MAP_H
#define SOLAR_MAP_H

#include <vector>
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Identification.h"
#include "datastructure/CameraParametersCollection.h"
#include "datastructure/CoordinateSystem.h"
#include "datastructure/PointCloud.h"
#include "datastructure/KeyframeCollection.h"
#include "datastructure/CovisibilityGraph.h"
#include "datastructure/KeyframeRetrieval.h"
#include "xpcf/core/refs.h"
#include <map>

// Definition of Map Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
* @class Map
* @brief <B>A generic map composed of an identification and a coordinate system.</B>
* This class provides a generic map.
*/
class  SOLARFRAMEWORK_API Map {
public:
	typedef enum {
		_PointCloud = 0x01,
		_Keyframe = 0x02,
		_CovisibilityGraph = 0x04,
        _KFRetriever = 0x08,
        _CameraParemeters = 0x10
	} MapType;

	///
    /// @brief Map constructor.
    ///
	Map();
    Map(const Map& other) = default;
    Map& operator=(const Map& other) = default;
	Map(MapType type) { m_mapSupportedTypes = type; };

	///
    /// @brief ~Map
	///
    ~Map() = default;

	///
	/// @brief This method is to check an element existed in the map
	/// @return true if this element exist
	///
	bool handles(MapType type) {
		return (type & m_mapSupportedTypes);
	}

	///
	/// @brief This method returns the identification
	/// @return the identification
	///
    const SRef<Identification> & getConstIdentification() const;

	///
	/// @brief This method returns the identification
    /// @param[out] identification the identification of map
	/// @return the identification
	///
	std::unique_lock<std::mutex> getIdentification(SRef<Identification>& identification);

	///
	/// @brief This method is to set the identification
	/// @param[in] identification the identification of map
	///
	void setIdentification(const SRef<Identification> identification);

	///
	/// @brief This method returns the coordinate system
	/// @return the coordinate system
	///
	const SRef<CoordinateSystem> & getConstCoordinateSystem() const;

	///
	/// @brief This method returns the coordinate system
	/// @param[out] coordinateSystem the coordinate system of map
	/// @return the coordinate system
	///
	std::unique_lock<std::mutex> getCoordinateSystem(SRef<CoordinateSystem>& coordinateSystem);

	///
	/// @brief This method is to set the coordinate system
	/// @param[in] coordinateSystem the coordinate system of map
	///
	void setCoordinateSystem(const SRef<CoordinateSystem> coordinateSystem);

	///
	/// @brief This method returns the point cloud
	/// @return the point cloud
	///
	const SRef<PointCloud> & getConstPointCloud() const;

	///
	/// @brief This method returns the point cloud
	/// @param[out] pointCloud the point cloud
	/// @return the point cloud
	///
	std::unique_lock<std::mutex> getPointCloud(SRef<PointCloud>& pointCloud);

	///
	/// @brief This method is to set the point cloud
	/// @param[in] pointCloud the point cloud
	///
	void setPointCloud(const SRef<PointCloud> pointCloud);

	///
	/// @brief This method returns the keyframe collection
	/// @return the keyframe collection
	///
	const SRef<KeyframeCollection> & getConstKeyframeCollection() const;

    ///
	/// @brief This method returns the keyframe collection
	/// @param[out] keyframeCollection the keyframe collection of map
	/// @return the keyframe collection
	///
	std::unique_lock<std::mutex> getKeyframeCollection(SRef<KeyframeCollection>& keyframeCollection);
    
	///
	/// @brief This method is to set the keyframe collection
	/// @param[in] keyframeCollection the keyframe collection of map
	///
	void setKeyframeCollection(const SRef<KeyframeCollection> keyframeCollection);

    ///
    /// @brief This method returns the camera parameters collection
    /// @return the camera parameters collection
    ///
    const SRef<CameraParametersCollection> & getConstCameraParametersCollection() const;

    ///
    /// @brief This method returns the camera parameters collection
    /// @param[out] keyframeCollection the camera parameters collection of map
    /// @return a mutex
    ///
    std::unique_lock<std::mutex> getCameraParametersCollection(SRef<CameraParametersCollection>& cameraParametersCollection);

    ///
    /// @brief This method is to set the camera parameters collection
    /// @param[in] cameraParametersCollection the camera parameters collection of map
    ///
    void setCameraParametersCollection(const SRef<CameraParametersCollection> cameraParametersCollection);

	///
	/// @brief This method returns the covisibility graph
	/// @return the covisibility graph
	///
	const SRef<CovisibilityGraph> & getConstCovisibilityGraph() const;

	///
	/// @brief This method returns the covisibility graph
	/// @param[out] covisibilityGraph the covisibility graph of map
	/// @return the covisibility graph
	///
	std::unique_lock<std::mutex> getCovisibilityGraph(SRef<CovisibilityGraph>& covisibilityGraph);

	///
	/// @brief This method is to set the covisibility graph
	/// @param[in] covisibilityGraph the covisibility graph of map
	///
	void setCovisibilityGraph(const SRef<CovisibilityGraph> covisibilityGraph);

	///
	/// @brief This method returns the keyframe retrieval
	/// @return the keyframe retrieval
	///
	const SRef<KeyframeRetrieval> & getConstKeyframeRetrieval() const;

	///
	/// @brief This method returns the keyframe retrieval
	/// @param[out] keyframeRetrieval the keyframe retrieval of map
	/// @return the keyframe retrieval
	///
	std::unique_lock<std::mutex> getKeyframeRetrieval(SRef<KeyframeRetrieval>& keyframeRetrieval);

	///
	/// @brief This method is to set the keyframe retrieval
	/// @param[in] keyframeRetrieval the keyframe retrieval of map
	///
	void setKeyframeRetrieval(const SRef<KeyframeRetrieval> keyframeRetrieval);

private:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    uint32_t                                            m_mapSupportedTypes;
    SRef<Identification>                                m_identification;
    SRef<CoordinateSystem>                              m_coordinateSystem;
    SRef<PointCloud>                                    m_pointCloud;
    SRef<KeyframeCollection>                            m_keyframeCollection;
    SRef<CovisibilityGraph>                             m_covisibilityGraph;
    SRef<KeyframeRetrieval>                             m_keyframeRetrieval;
    SRef<CameraParametersCollection>                    m_cameraParametersCollection;
};


DECLARESERIALIZE(Map);
}
}  // end of namespace SolAR
#endif // SOLAR_MAP_H
