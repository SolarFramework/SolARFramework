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

#include "core/Log.h"
#include "datastructure/CorrespondenceGraph.h"
#include <xpcf/core/helpers.h>

namespace xpcf = org::bcom::xpcf;

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::CorrespondenceGraph);

namespace SolAR {
namespace datastructure {

FrameworkReturnCode CorrespondenceGraph::addEdge(uint32_t keyframeId1, uint32_t keyframeId2, const std::vector<DescriptorMatch>& desMatches, const Transform3Df& relativePose)
{
    if (desMatches.empty()) {
        LOG_ERROR("Empty descriptor matches");
        return FrameworkReturnCode::_ERROR_;
    }
    if (relativePose.matrix().isZero()) {
        LOG_ERROR("Zero pose matrix");
        return FrameworkReturnCode::_ERROR_;
    }
    auto status = checkEdge(keyframeId1, keyframeId2);
    if (status == EdgeStatus::INVALID) {
        LOG_ERROR("Cannot add edge between the same keyframes {}", keyframeId1);
        return FrameworkReturnCode::_ERROR_;
    }
    if (status == EdgeStatus::EXIST_ONE_DIRECTION || status == EdgeStatus::EXIST_ONE_DIRECTION_INVERSE || status == EdgeStatus::EXIST_DOUBLE_DIRECTION) {
        LOG_WARNING("Edge between {} and {} exists, try to delete it first", keyframeId1, keyframeId2);
        if (!deleteEdge(keyframeId1, keyframeId2, status)) {
            LOG_ERROR("Failed to delete existing edge");
            return FrameworkReturnCode::_ERROR_;
        }
    }
    // set edge for simplicity only set edge from smaller keyframe id to bigger keyframe id 
    // no need to set edge in double directions since information is redundant
    if (keyframeId1 < keyframeId2) {
        setEdge(keyframeId1, keyframeId2, desMatches, relativePose);        
    }
    else {
        setEdge(keyframeId2, keyframeId1, inverseMatches(desMatches), relativePose.inverse());
    }
    return FrameworkReturnCode::_SUCCESS;
}

bool CorrespondenceGraph::removeEdge(uint32_t keyframeId1, uint32_t keyframeId2)
{
    auto status = checkEdge(keyframeId1, keyframeId2);
    if (status == EdgeStatus::INVALID) {
        LOG_WARNING("Cannot remove edge between the same keyframes {}", keyframeId1);
        return false;
    }
    if (status == EdgeStatus::NOT_EXIST) {
        LOG_WARNING("Edge between {} and {} does not exist", keyframeId1, keyframeId2);
        return false;
    }
    return deleteEdge(keyframeId1, keyframeId2, status);
}

const std::vector<std::pair<uint32_t, size_t>>& CorrespondenceGraph::getAllSortedKeyframes() const 
{
    std::vector<std::pair<uint32_t, size_t>> keyframes;
    for (const auto& node : m_nodes) {
        auto linkedKeyframes = getLinkedKeyframes(node.first);
        size_t nbCorres = 0;
        std::for_each(linkedKeyframes.begin(), linkedKeyframes.end(), [&nbCorres](auto& item) {nbCorres += item.second;} );
        keyframes.push_back( {node.first, nbCorres} );
    }
    std::sort(keyframes.begin(), keyframes.end(), [](auto& x1, auto& x2) {return x1.second > x2.second;});
    return keyframes;
}

const std::vector<std::pair<uint32_t, size_t>>& CorrespondenceGraph::getLinkedKeyframes(uint32_t keyframeId) const
{
    std::vector<std::pair<uint32_t, size_t>> keyframes;
    // matched keyframes whose Id > keyframeId
    if (m_edges.find(keyframeId) != m_edges.end()) {
        for (const auto& kfMatch : m_edges.at(keyframeId)) {
            keyframes.push_back( {kfMatch.first, kfMatch.second.matches.size()} );
        }
    }
    // matched keyframes whose Id < keyframeId
    auto itLast = m_edges.lower_bound(keyframeId); // 1st element >= keyframeId
    for (auto it = m_edges.begin(); it != itLast; ++it) { // it->first < keyframeId
        auto currentKfId = it->first;
        auto kfMatchResult = it->second;
        auto result = kfMatchResult.find(keyframeId);
        if (result != kfMatchResult.end()) {
            keyframes.push_back( {currentKfId, result->second.matches.size()} );
        }
    }
    std::sort(keyframes.begin(), keyframes.end(), [](auto& x1, auto& x2) {return x1.second > x2.second;});
    return keyframes;
}

const std::vector<DescriptorMatch>& CorrespondenceGraph::getDescriptorMatches(uint32_t keyframeId1, uint32_t keyframeId2) const
{
    Correspondence corres;
    bool inverseOrder = false;
    if (!getCorrespondence(keyframeId1, keyframeId2, corres, inverseOrder)) {
        LOG_WARNING("No correspondence found between keyframe {} and {}", keyframeId1, keyframeId2);
        return std::vector<DescriptorMatch>();
    }
    if (inverseOrder) {
        return inverseMatches(corres.matches);
    }
    else {
        return corres.matches;
    }
}

const Transform3Df& CorrespondenceGraph::getRelativePose(uint32_t keyframeId1, uint32_t keyframeId2) const
{
    Transform3Df transform;
    transform.matrix().setZero();
    Correspondence corres;
    bool inverseOrder = false;
    if (!getCorrespondence(keyframeId1, keyframeId2, corres, inverseOrder)) {
        LOG_WARNING("No correspondence found between keyframe {} and {}", keyframeId1, keyframeId2);
        return transform;
    }
    if (inverseOrder) {
        return corres.relativePose.inverse();
    }
    else {
        return corres.relativePose;
    }
}

bool CorrespondenceGraph::removeAllEdges()
{
    if (m_edges.empty()) {
        if (!m_nodes.empty()) {
            LOG_WARNING("Graph does not have any edge but have non-empty set of nodes, remove all nodes.");
            m_nodes.clear();
        }
        return false;
    }
    m_edges.clear();
    m_nodes.clear();
    return true;
}

CorrespondenceGraph::EdgeStatus CorrespondenceGraph::checkEdge(uint32_t keyframeId1, uint32_t keyframeId2) const
{
    if (keyframeId1 == keyframeId2) {
        return EdgeStatus::INVALID;
    }
    bool edge_kf1_kf2 = m_edges.find(keyframeId1) != m_edges.end() && m_edges.at(keyframeId1).find(keyframeId2) != m_edges.at(keyframeId1).end();
    bool edge_kf2_kf1 = m_edges.find(keyframeId2) != m_edges.end() && m_edges.at(keyframeId2).find(keyframeId1) != m_edges.at(keyframeId2).end();
    if (edge_kf1_kf2) {
        if (edge_kf2_kf1) {
            return EdgeStatus::EXIST_DOUBLE_DIRECTION;
        }
        return EdgeStatus::EXIST_ONE_DIRECTION;
    }
    else {
        if (edge_kf2_kf1) {
            return EdgeStatus::EXIST_ONE_DIRECTION_INVERSE;
        }
        return EdgeStatus::NOT_EXIST;
    }
}

bool CorrespondenceGraph::deleteEdge(uint32_t keyframeId1, uint32_t keyframeId2, const EdgeStatus& status)
{
    if (status == EdgeStatus::EXIST_ONE_DIRECTION) {
        m_edges[keyframeId1].erase( m_edges[keyframeId1].find(keyframeId2) );
        m_nodes[keyframeId1]--;
        m_nodes[keyframeId2]--;
    }
    else if (status == EdgeStatus::EXIST_ONE_DIRECTION_INVERSE) {
        m_edges[keyframeId2].erase( m_edges[keyframeId2].find(keyframeId1) );
        m_nodes[keyframeId1]--;
        m_nodes[keyframeId2]--;
    }
    else if (status == EdgeStatus::EXIST_DOUBLE_DIRECTION) {
        m_edges[keyframeId1].erase( m_edges[keyframeId1].find(keyframeId2) );
        m_edges[keyframeId2].erase( m_edges[keyframeId2].find(keyframeId1) );
        m_nodes[keyframeId1] -= 2;
        m_nodes[keyframeId2] -= 2 ;
    }
    else {
        return false;
    }
    if (m_nodes.at(keyframeId1) == 0) {
        m_nodes.erase(m_nodes.find(keyframeId1));
    }
    if (m_nodes.at(keyframeId2) == 0) {
        m_nodes.erase(m_nodes.find(keyframeId2));
    }
    return true;
}

void CorrespondenceGraph::setEdge(uint32_t keyframeId1, uint32_t keyframeId2, const std::vector<DescriptorMatch>& desMatches, const Transform3Df& relativePose)
{
    Correspondence corres;
    corres.matches = desMatches;
    corres.relativePose = relativePose;
    m_edges[keyframeId1][keyframeId2] = corres;
    m_nodes[keyframeId1]++;
    m_nodes[keyframeId2]++;
}

std::vector<DescriptorMatch> CorrespondenceGraph::inverseMatches(const std::vector<DescriptorMatch>& desMatches) const
{
    std::vector<DescriptorMatch> desMatches2;
    for (const auto& match : desMatches) {
        desMatches2.emplace_back(match.getIndexInDescriptorB(), match.getIndexInDescriptorA(), match.getMatchingScore());
    }
    return desMatches2;
}

bool CorrespondenceGraph::getCorrespondence(uint32_t keyframeId1, uint32_t keyframeId2, Correspondence& corres, bool& inverseOrder) const 
{
    if (keyframeId1 == keyframeId2) {
        return false;
    }
    if (keyframeId1 < keyframeId2) {
        if (m_edges.find(keyframeId1) != m_edges.end() && m_edges.at(keyframeId1).find(keyframeId2) != m_edges.at(keyframeId1).end()) {
            corres = m_edges.at(keyframeId1).at(keyframeId2);
            inverseOrder = false;
            return true; // found 
        }
        LOG_WARNING("No correspondence from keyframe {} to {} found in the graph", keyframeId1, keyframeId2);
        return false; // not found 
    }
    // keyframeId1 > keyframeId2
    if (m_edges.find(keyframeId2) != m_edges.end() && m_edges.at(keyframeId2).find(keyframeId1) != m_edges.at(keyframeId2).end()) {
        corres = m_edges.at(keyframeId2).at(keyframeId1);
        inverseOrder = true;
        return true; // found 
    }
    LOG_WARNING("No correspondence from keyframe {} to {} found in the graph", keyframeId2, keyframeId1);
    return false; // not found 
}

} // datastructure
} // SolAR