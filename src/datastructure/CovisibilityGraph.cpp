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

#include "datastructure/CovisibilityGraph.h"
#include "xpcf/core/helpers.h"
#include "core/Log.h"

namespace xpcf = org::bcom::xpcf;

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::CovisibilityGraph);

namespace SolAR {
namespace datastructure {

// join 2 vertex to make an edge
inline static uint64_t join(uint32_t a, uint32_t b) {
	if (a > b) std::swap(a, b);
	uint64_t a_b;
	uint32_t *_a_b_16 = (uint32_t*)&a_b;
	_a_b_16[0] = b;
	_a_b_16[1] = a;
	return a_b;
}

// divides a 64bit edge into its components
inline static std::pair<uint32_t, uint32_t> separe(uint64_t a_b) {
	uint32_t *_a_b_16 = (uint32_t*)&a_b;
	return std::make_pair(_a_b_16[1], _a_b_16[0]);
}

FrameworkReturnCode CovisibilityGraph::increaseEdge(const uint32_t node1_id, const uint32_t node2_id, const float weight)
{
	if (node1_id == node2_id)
		return FrameworkReturnCode::_ERROR_;

	// add nodes
	m_nodes.insert(node1_id);
	m_nodes.insert(node2_id);
	// add edge
	m_edges[node1_id].insert(node2_id);
	m_edges[node2_id].insert(node1_id);
	// add weight
	auto edge = join(node1_id, node2_id);
	m_weights[edge] += weight;
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CovisibilityGraph::decreaseEdge(const uint32_t node1_id, const uint32_t node2_id, const float weight)
{
	if (node1_id == node2_id)
		return FrameworkReturnCode::_ERROR_;
	auto edge = join(node1_id, node2_id);
	if (m_weights.count(edge) == 0)
		return FrameworkReturnCode::_ERROR_;
	// if m_weight > weight: decrease, else remove edge
	float &_weight = m_weights.at(edge);
	if (_weight > weight) {
		_weight -= weight;
	}
	else {
		m_weights.erase(edge);
		m_edges.at(node1_id).erase(node2_id);
		m_edges.at(node2_id).erase(node1_id);
	}
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CovisibilityGraph::removeEdge(const uint32_t node1_id, const uint32_t node2_id)
{
	auto edge = join(node1_id, node2_id);
	if (m_weights.count(edge) == 0)
		return FrameworkReturnCode::_ERROR_;
	// remove weight
	m_weights.erase(edge);
	// remove edges
	m_edges.at(node1_id).erase(node2_id);
	m_edges.at(node2_id).erase(node1_id);
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CovisibilityGraph::getEdge(const uint32_t node1_id, const uint32_t node2_id, float & weight) const
{
	auto edge = join(node1_id, node2_id);
	if (m_weights.count(edge) == 0)
		return FrameworkReturnCode::_ERROR_;
	weight = m_weights.at(edge);
	return FrameworkReturnCode::_SUCCESS;
}

bool CovisibilityGraph::isEdge(const uint32_t node1_id, const uint32_t node2_id) const
{
	return m_weights.count(join(node1_id, node2_id));
}

FrameworkReturnCode CovisibilityGraph::getAllNodes(std::set<uint32_t>& nodes_id) const
{
	nodes_id = m_nodes;
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CovisibilityGraph::suppressNode(const uint32_t node_id)
{
	if (m_nodes.find(node_id) == m_nodes.end())
		return FrameworkReturnCode::_ERROR_;
	// remove node
	m_nodes.erase(node_id);
	// get all weights to remove
	std::list<uint64_t> weightsToRemove;
	const std::set<uint32_t> &edges = m_edges.at(node_id);
	for (auto &e : edges)
		weightsToRemove.push_back(join(node_id, e));
	// remove edges
	m_edges.erase(node_id);
	// remove weights
	for (auto const &w : weightsToRemove)
		m_weights.erase(w);
	// remove all edges in other nodes
	for (auto &e : m_edges)
		e.second.erase(node_id);
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CovisibilityGraph::getNeighbors(const uint32_t node_id, const float minWeight, std::vector<uint32_t>& neighbors, const uint32_t maxNbNeighbors) const
{
	std::vector < std::pair<uint32_t, float> > neighbors_weights;
	auto it = m_edges.find(node_id);
	if (it == m_edges.end())
		return FrameworkReturnCode::_ERROR_;
	// get neighbors
	for (auto n : it->second) {
		auto edge = join(node_id, n);
		if (m_weights.at(edge) > minWeight)
			neighbors_weights.push_back(std::make_pair(n, m_weights.at(edge)));
	}
	if (neighbors_weights.size() == 0)
		return FrameworkReturnCode::_ERROR_;
	// sort
	std::sort(neighbors_weights.begin(), neighbors_weights.end(), [](const std::pair<uint32_t, float> &a, const std::pair<uint32_t, float> &b) {return a.second > b.second; });
	// get sorted neighbors
	uint32_t nbNeighbors = (maxNbNeighbors > 0) & (maxNbNeighbors < neighbors_weights.size()) ? maxNbNeighbors : neighbors_weights.size();
	for (auto const &it : neighbors_weights) {
		neighbors.push_back(it.first);
		if (neighbors.size() == nbNeighbors)
			break;
	}
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CovisibilityGraph::minimalSpanningTree(std::vector<std::tuple<uint32_t, uint32_t, float>> &edges_weights, float &minTotalWeights)
{
	if (m_nodes.size() == 0)
		return FrameworkReturnCode::_ERROR_;

	//first, add the elements to the  vector
	std::vector<std::pair<uint64_t, float>> edges;
	for (auto const& w : m_weights)
		edges.push_back(w);
	//sort in decreasing order
	std::sort(edges.begin(), edges.end(), [](const std::pair<uint64_t, float> &a, const std::pair<uint64_t, float>& b) {return a.second < b.second; });
	std::map<uint32_t, uint32_t> belongs;
	for (auto n : m_nodes)
		belongs.insert({ n,n });
	std::vector<uint64_t> mst_edges;//this is in fact the spanning tree
	size_t curEdge = 0;
	bool isspanning = false;
	while (curEdge < edges.size() && !isspanning) {
		auto edge = edges[curEdge++];
		//check that both do not belong to the same tree
		auto i_j = separe(edge.first);

		if (belongs[i_j.first] != belongs[i_j.second]) {
			//good, add the link, and set all nodes from belongs[i_j.second] to belong now to the first one
			mst_edges.push_back(edge.first);
			auto b1 = belongs[i_j.first];
			auto b2 = belongs[i_j.second];
			for (auto &b : belongs)
				if (b.second == b2) b.second = b1;
			//now check if there is only one connected component
			uint32_t cnn = belongs.begin()->second;
			isspanning = true;
			for (auto b : belongs)
				if (b.second != cnn) {
					isspanning = false;
					break;
				}
		}
	}

	assert(isspanning); //there are more than one connected components in the graph!!!!
	minTotalWeights = 0;
	for (auto const &m : mst_edges) {
		auto i_j = separe(m);
		edges_weights.push_back(std::make_tuple(i_j.first, i_j.second, m_weights.at(m)));
		minTotalWeights += m_weights.at(m);
	}
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CovisibilityGraph::maximalSpanningTree(std::vector<std::tuple<uint32_t, uint32_t, float>> &edges_weights, float &maxTotalWeights)
{
	if (m_nodes.size() == 0)
		return FrameworkReturnCode::_ERROR_;

	//first, add the elements to the  vector
	std::vector<std::pair<uint64_t, float>> edges;
	for (auto const& w : m_weights)
		edges.push_back(w);
	//sort in decreasing order
	std::sort(edges.begin(), edges.end(), [](const std::pair<uint64_t, float> &a, const std::pair<uint64_t, float>& b) {return a.second > b.second; });
	std::map<uint32_t, uint32_t> belongs;
	for (auto n : m_nodes)
		belongs.insert({ n,n });
	std::vector<uint64_t> mst_edges;//this is in fact the spanning tree
	size_t curEdge = 0;
	bool isspanning = false;
	while (curEdge < edges.size() && !isspanning) {
		auto edge = edges[curEdge++];
		//check that both do not belong to the same tree
		auto i_j = separe(edge.first);

		if (belongs[i_j.first] != belongs[i_j.second]) {
			//good, add the link, and set all nodes from belongs[i_j.second] to belong now to the first one
			mst_edges.push_back(edge.first);
			auto b1 = belongs[i_j.first];
			auto b2 = belongs[i_j.second];
			for (auto &b : belongs)
				if (b.second == b2) b.second = b1;
			//now check if there is only one connected component
			uint32_t cnn = belongs.begin()->second;
			isspanning = true;
			for (auto b : belongs)
				if (b.second != cnn) {
					isspanning = false;
					break;
				}
		}
	}

	assert(isspanning); //there are more than one connected components in the graph!!!!
	maxTotalWeights = 0;
	for (auto const &m : mst_edges) {
		auto i_j = separe(m);
		edges_weights.push_back(std::make_tuple(i_j.first, i_j.second, m_weights.at(m)));
		maxTotalWeights += m_weights.at(m);
	}
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CovisibilityGraph::getShortestPath(const uint32_t node1_id, const uint32_t node2_id, std::vector<uint32_t> &path)
{
	if (node1_id == node2_id)
		return FrameworkReturnCode::_ERROR_;
	//just need to start
	struct TreeNode {
		TreeNode(uint32_t n, uint32_t p) :node(n), parent(p) {}
		uint32_t node, parent;
	};

	std::vector<TreeNode> trees;
	trees.reserve(m_nodes.size() * 4);
	std::vector<bool> visited(*(m_nodes.rbegin()) + 1, false);
	trees.push_back({ node1_id,std::numeric_limits<uint32_t>::max() });
	size_t curNode = 0;
	bool found = false;
	while (curNode < trees.size() && !found) {
		//take current node
		const auto &tn = trees[curNode];
		//see ifs neighbors
        if (m_edges.find(tn.node) != m_edges.end()) {
            for (auto neigh : m_edges.at(tn.node)) {
                if (!visited[neigh]) {
                    visited[neigh] = true;
                    trees.push_back(TreeNode(neigh, static_cast<uint32_t>(curNode)));
                    if (neigh == node2_id) {
                        found = true;
                        break;
                    }
                }
            }
        }
		curNode++;
	}
	if (!found)//no path
		return FrameworkReturnCode::_ERROR_;

	//else ,reconstruct the path in inverse order
	int cnode = static_cast<int>(trees.size()) - 1;
	while (cnode != 0) {
		path.push_back(trees[cnode].node);
		cnode = trees[cnode].parent;
	}
	//add the starting node
	path.push_back(node1_id);
	//invert the node order
	std::reverse(path.rbegin(), path.rend());
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CovisibilityGraph::display() const
{
	// display vertices
	LOG_INFO("The vertices of the covisibility graph: ");
	for (auto const &it : m_nodes)
		std::cout << it << " ";
	std::cout << std::endl;
	LOG_INFO("The weighted edges of the covisibility graph: ");
	for (auto const &it : m_weights) {
		auto edge = it.first;
		auto weight = it.second;
		auto nodes = separe(edge);
		std::cout << nodes.first << " - " << nodes.second << " : " << weight << std::endl;
	}
	return FrameworkReturnCode::_SUCCESS;
}

template <typename Archive>
void CovisibilityGraph::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version)
{
	ar & m_nodes;
	ar & m_edges;
	ar & m_weights;
}

IMPLEMENTSERIALIZE(CovisibilityGraph);

} // end of namespace datastructure
} // end of namespace SolAR
