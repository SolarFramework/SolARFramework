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

#ifndef SOLAR_ICOVISIBILITYGRAPHMANAGER_H
#define SOLAR_ICOVISIBILITYGRAPHMANAGER_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/CovisibilityGraph.h"

namespace SolAR {
namespace api {
namespace storage {

/**
 * @class ICovisibilityGraphManager
 * @brief Allows to store the covisibility graph between keyframes. This storage component can be accessed by processing components to share persistent data.
 * <TT>UUID: 15455f5a-0e99-49e5-a3fb-39de3eeb5b9b</TT>
 */

class ICovisibilityGraphManager : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief ICovisibilityGraphManager default constructor
	ICovisibilityGraphManager() = default;

    /// @brief ICovisibilityGraphManager default destructor
    virtual ~ICovisibilityGraphManager() = default;

    /// @brief This method allow to increase edge between 2 nodes
    /// @param[in] node1_id id of 1st node
    /// @param[in] node2_id id of 2nd node
    /// @param[in] weight weight to increase
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode increaseEdge(const uint32_t node1_id, const uint32_t node2_id, const float weight) = 0;

	/// @brief This method allow to decrease edge between 2 nodes
	/// @param[in] node1_id id of 1st node
	/// @param[in] node2_id id of 2nd node
	/// @param[in] weight weight to decrease
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode decreaseEdge(const uint32_t node1_id, const uint32_t node2_id, const float weight) = 0;

	/// @brief This method allow to remove an edge between 2 nodes
	/// @param[in] node1_id id of 1st node
	/// @param[in] node2_id id of 2nd node
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode removeEdge(const uint32_t node1_id, const uint32_t node2_id) = 0;

	/// @brief This method allow to get edge between 2 nodes
	/// @param[in] node1_id id of 1st node
	/// @param[in] node2_id id of 2nd node
	/// @param[out] weight weight of the edge
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getEdge(uint32_t node1_id, uint32_t node2_id, float & weight) const = 0;

	/// @brief This method allow to verify that exist an edge between 2 nodes
	/// @param[in] node1_id id of 1st node
	/// @param[in] node2_id id of 2nd node
	/// @return true if exist, else false
    virtual bool isEdge(const uint32_t node1_id, const uint32_t node2_id) const = 0;

	/// @brief This method allow to get all nodes of the graph
	/// @param[out] nodes_id ids of all nodes
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getAllNodes(std::set<uint32_t> & nodes_id) const = 0;

	/// @brief This method allow to suppress a node of the graph
	/// @param[in] node_id id of the node to suppress
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode suppressNode(const uint32_t node_id) = 0;

	/// @brief This method allow to get neighbors of a node in the graph
	/// @param[in] node_id id of the node to get neighbors
	/// @param[in] minWeight min value between this node and a neighbor to accept
	/// @param[out] neighbors a vector of neighbors sorted to greater weighted edge.
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getNeighbors(const uint32_t node_id, const float minWeight, std::vector<uint32_t> & neighbors) const = 0;

	/// @brief This method allow to get minimal spanning tree of the graph
	/// @param[out] edges_weights: the minimal spanning tree graph including edges with weights
	/// @param[out] minTotalWeights: cost of the minimal spanning tree graph
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode minimalSpanningTree(std::vector<std::tuple<uint32_t, uint32_t, float>> & edges_weights, float & minTotalWeights) = 0;

	/// @brief This method allow to get maximal spanning tree of the graph
	/// @param[out] edges_weights: the maximal spanning tree graph including edges with weights
	/// @param[out] maxTotalWeights: cost of the maximal spanning tree graph
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode maximalSpanningTree(std::vector<std::tuple<uint32_t, uint32_t, float>> & edges_weights, float & maxTotalWeights) = 0;

	/// @brief This method allow to get the shortest (by number of vertices) path between 2 nodes
	/// @param[in] node1_id id of 1st node
	/// @param[in] node2_id id of 2nd node
	/// @param[out] path the shortest path
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getShortestPath(uint32_t node1_id, uint32_t node2_id, std::vector<uint32_t> & path) = 0;

	/// @brief This method allow to display all vertices and weighted edges of the covisibility graph
    virtual FrameworkReturnCode display() const = 0;

	/// @brief This method allows to save the graph to the external file
	/// @param[in] file the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode saveToFile(const std::string & file) const = 0;

	/// @brief This method allows to load the graph from the external file
	/// @param[in] file the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode loadFromFile(const std::string & file) = 0;

	/// @brief This method returns the covisibility graph
	/// @return the covisibility graph
	virtual const SRef<datastructure::CovisibilityGraph> & getConstCovisibilityGraph() const = 0;

	/// @brief This method returns the covisibility graph
	/// @param[out] covisibilityGraph the covisibility graph of map
	/// @return the covisibility graph
	virtual std::unique_lock<std::mutex> getCovisibilityGraph(SRef<datastructure::CovisibilityGraph>& covisibilityGraph) = 0;

	/// @brief This method is to set the covisibility graph
	/// @param[in] covisibilityGraph the covisibility graph of map
	virtual void setCovisibilityGraph(const SRef<datastructure::CovisibilityGraph> covisibilityGraph) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::ICovisibilityGraphManager,
                             "15455f5a-0e99-49e5-a3fb-39de3eeb5b9b",
                             "ICovisibilityGraphManager",
                             "A component interface for storing a persistent covisibility graph between keyframes.");


#endif //SOLAR_ICOVISIBILITYGRAPHMANAGER_H

