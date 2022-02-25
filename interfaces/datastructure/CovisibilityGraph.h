#ifndef COVISIBILITYGRAPH_H
#define COVISIBILITYGRAPH_H

#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Keyframe.h"
#include "datastructure/Lockable.h"
#include "core/Messages.h"
#include "xpcf/core/refs.h"
#include <map>

// Definition of CovisibilityGraph Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
* @class CovisibilityGraph
* @brief <B>A covisibility graph of keyframes.</B>
* This class provides a covisibility graph where each vertex is an id of a keyframe and each edge is weighted by the number of common cloud points between two keyframes.
*/
class  SOLARFRAMEWORK_API CovisibilityGraph : public Lockable {
public:

	///
	/// @brief CovisibilityGraph constructor.
	///
	CovisibilityGraph() = default;
	CovisibilityGraph(const CovisibilityGraph& other) = default;
	CovisibilityGraph& operator=(const CovisibilityGraph& other) = default;

	///
	/// \brief ~CovisibilityGraph
	///
	~CovisibilityGraph() = default;

	/// @brief This method allow to increase edge between 2 nodes
	/// @param[in] id of 1st node
	/// @param[in] id of 2nd node
	/// @param[in] weight to increase
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode increaseEdge(uint32_t node1_id, uint32_t node2_id, float weight);

	/// @brief This method allow to decrease edge between 2 nodes
	/// @param[in] id of 1st node
	/// @param[in] id of 2nd node
	/// @param[in] weight to decrease
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode decreaseEdge(uint32_t node1_id, uint32_t node2_id, float weight);

	/// @brief This method allow to remove an edge between 2 nodes
	/// @param[in] id of 1st node
	/// @param[in] id of 2nd node
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode removeEdge(uint32_t node1_id, uint32_t node2_id);

	/// @brief This method allow to get edge between 2 nodes
	/// @param[in] id of 1st node
	/// @param[in] id of 2nd node
	/// @param[out] weight of the edge
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode getEdge(uint32_t node1_id, uint32_t node2_id, float &weight) const;

	/// @brief This method allow to verify that exist an edge between 2 nodes
	/// @param[in] id of 1st node
	/// @param[in] id of 2nd node
	/// @return true if exist, else false
	bool isEdge(const uint32_t node1_id, const uint32_t node2_id) const;

	/// @brief This method allow to get all nodes of the graph
	/// @param[out] ids of all nodes
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode getAllNodes(std::set<uint32_t> & nodes_id) const;

	/// @brief This method allow to suppress a node of the graph
	/// @param[in] id of the node to suppress
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode suppressNode(const uint32_t node_id);

	/// @brief This method allow to get neighbors of a node in the graph
	/// @param[in] node_id id of the node to get neighbors
	/// @param[in] minWeight min value between this node and a neighbor to accept
	/// @param[out] neighbors a vector of neighbors sorted to greater weighted edge.
	/// @param[in] maxNbNeighbors the maximum number of neighbors. If it is zero, find all neighbors.
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode getNeighbors(const uint32_t node_id, 
									 const float minWeight, 
									 std::vector<uint32_t> &neighbors,
									 const uint32_t maxNbNeighbors = 0) const;

	/// @brief This method allow to get minimal spanning tree of the graph
	/// @param[out] edges_weights: the minimal spanning tree graph including edges with weights
	/// @param[out] minTotalWeights: cost of the minimal spanning tree graph
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode minimalSpanningTree(std::vector<std::tuple<uint32_t, uint32_t, float>> &edges_weights, float & minTotalWeights);

	/// @brief This method allow to get maximal spanning tree of the graph
	/// @param[out] edges_weights: the maximal spanning tree graph including edges with weights
	/// @param[out] maxTotalWeights: cost of the maximal spanning tree graph
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode maximalSpanningTree(std::vector<std::tuple<uint32_t, uint32_t, float>> &edges_weights, float & maxTotalWeights);

	/// @brief This method allow to get the shortest (by number of vertices) path between 2 nodes
	/// @param[in] id of 1st node
	/// @param[in] id of 2nd node
	/// @param[out] the shortest path
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode getShortestPath(const uint32_t node1_id, const uint32_t node2_id, std::vector<uint32_t> &path);

	/// @brief This method allow to display all vertices and weighted edges of the covisibility graph
	FrameworkReturnCode display() const;

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version);

	std::set<uint32_t>						m_nodes;
	std::map<uint32_t, std::set<uint32_t>>	m_edges;
	std::map<uint64_t, float>				m_weights;
};

DECLARESERIALIZE(CovisibilityGraph);

}
}  // end of namespace SolAR

#endif // COVISIBILITYGRAPH_H
