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

FrameworkReturnCode CorrespondenceGraph::addEdge(id_t keyframeId1, id_t keyframeId2, const std::vector<DescriptorMatch>& desMatches, const Transform3Df& relativePose)
{
    if (desMatches.empty()) {
        LOG_ERROR("CorrespondenceGraph::addEdge - empty descriptor matches");
        return FrameworkReturnCode::_ERROR_;
    }
    if (relativePose.matrix().isZero()) {
        LOG_WARNING("CorrespondenceGraph::addEdge - zero pose matrix");
    }
    auto status = checkEdge(keyframeId1, keyframeId2);
    if (status == EdgeStatus::INVALID) {
        LOG_ERROR("CorrespondenceGraph::addEdge - cannot add edge between the same keyframes {}", keyframeId1);
        return FrameworkReturnCode::_ERROR_;
    }
    if (status == EdgeStatus::EXIST_ONE_DIRECTION || status == EdgeStatus::EXIST_ONE_DIRECTION_INVERSE || status == EdgeStatus::EXIST_DOUBLE_DIRECTION) {
        LOG_WARNING("CorrespondenceGraph::addEdge - edge between {} and {} exists, try to delete it first", keyframeId1, keyframeId2);
        if (!deleteEdge(keyframeId1, keyframeId2, status)) {
            LOG_ERROR("CorrespondenceGraph::addEdge - failed to delete existing edge");
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

bool CorrespondenceGraph::removeEdge(id_t keyframeId1, id_t keyframeId2)
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

std::vector<std::pair<id_t, size_t>> CorrespondenceGraph::getAllSortedKeyframes() const 
{
    LOG_DEBUG("CorrespondenceGraph::getAllSortedKeyframes - begin.");
    std::vector<std::pair<id_t, size_t>> keyframes;
    for (const auto& node : m_nodes) {
        LOG_DEBUG("CorrespondenceGraph::getAllSortedKeyframes - keyframe {}, nb linked edges {}", node.first, node.second.nbLinkedEdges);
        auto linkedKeyframes = getLinkedKeyframes(node.first);
        LOG_DEBUG("CorrespondenceGraph::getAllSortedKeyframes - nb linked keyframes {}", linkedKeyframes.size());
        size_t nbCorres = 0;
        std::for_each(linkedKeyframes.begin(), linkedKeyframes.end(), [&nbCorres](auto& item) {nbCorres += item.second;} );
        LOG_DEBUG("CorrespondenceGraph::getAllSortedKeyframes - nb of corres. {}", nbCorres);
        keyframes.push_back( {node.first, nbCorres} );
    }
    std::sort(keyframes.begin(), keyframes.end(), [](auto& x1, auto& x2) {return x1.second > x2.second;});
    return keyframes;
}

std::vector<std::pair<id_t, size_t>> CorrespondenceGraph::getLinkedKeyframes(id_t keyframeId, bool onlyDisabled) const
{
    LOG_DEBUG("CorrespondenceGraph::getLinkedKeyframes - begin.");
    std::vector<std::pair<id_t, size_t>> keyframes;
    // matched keyframes whose Id > keyframeId
    if (m_edges.find(keyframeId) != m_edges.end()) {
        for (const auto& kfMatch : m_edges.at(keyframeId)) {
            if (onlyDisabled && m_nodes.at(kfMatch.first).enabled) {
                continue;
            }
            keyframes.push_back( {kfMatch.first, kfMatch.second.matches.size()} );
        }
    }
    // matched keyframes whose Id < keyframeId
    auto itLast = m_edges.lower_bound(keyframeId); // 1st element >= keyframeId
    if (itLast != m_edges.begin()) {
        for (auto it = m_edges.begin(); it != itLast; ++it) { // it->first < keyframeId
            auto currentKfId = it->first;
            auto kfMatchResult = it->second;
            auto result = kfMatchResult.find(keyframeId);
            if (result != kfMatchResult.end()) {
                if (onlyDisabled && m_nodes.at(currentKfId).enabled) {
                    continue;
                }
                keyframes.push_back( {currentKfId, result->second.matches.size()} );
            }
        }
    }
    std::sort(keyframes.begin(), keyframes.end(), [](auto& x1, auto& x2) {return x1.second > x2.second;});
    LOG_DEBUG("CorrespondenceGraph::getLinkedKeyframes - end.");
    return keyframes;
}

std::vector<DescriptorMatch> CorrespondenceGraph::getDescriptorMatches(id_t keyframeId1, id_t keyframeId2) const
{
    Correspondence corres;
    bool inverseOrder = false;
    if (!getCorrespondence(keyframeId1, keyframeId2, corres, inverseOrder)) {
        LOG_WARNING("No correspondence found between keyframe {} and {}", keyframeId1, keyframeId2);
        return std::vector<DescriptorMatch>();
    }
    if (inverseOrder) {
        LOG_DEBUG("CorrespondenceGraph::getDescriptorMatches - inverse match idx order.");
        return inverseMatches(corres.matches);
    }
    else {
        LOG_DEBUG("CorrespondenceGraph::getDescriptorMatches - return matches.");
        return corres.matches;
    }
}

Transform3Df CorrespondenceGraph::getRelativePose(id_t keyframeId1, id_t keyframeId2) const
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
        LOG_DEBUG("CorrespondenceGraph::getRelativePose - inverse relative pose.");
        return corres.relativePose.inverse();
    }
    else {
        LOG_DEBUG("CorrespondenceGraph::getRelativePose - return relative pose.");
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

CorrespondenceGraph::EdgeStatus CorrespondenceGraph::checkEdge(id_t keyframeId1, id_t keyframeId2) const
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

bool CorrespondenceGraph::deleteEdge(id_t keyframeId1, id_t keyframeId2, const EdgeStatus& status)
{
    if (m_nodes.find(keyframeId1) == m_nodes.end()) {
        LOG_ERROR("CorrespondenceGraph::deleteEdge - node {} does not exist", keyframeId1);
        return false;
    }
    if (m_nodes.find(keyframeId2) == m_nodes.end()) {
        LOG_ERROR("CorrespondenceGraph::deleteEdge - node {} does not exist", keyframeId2);
        return false;
    }
    if (status == EdgeStatus::EXIST_ONE_DIRECTION) {
        m_edges[keyframeId1].erase( m_edges[keyframeId1].find(keyframeId2) );
        if (m_nodes[keyframeId1].nbLinkedEdges < 1) {
            LOG_WARNING("CorrespondenceGraph::deleteEdge - node {} nb linked edges is {}, cannot decrease.", keyframeId1, m_nodes[keyframeId1].nbLinkedEdges);
        }
        else {
            m_nodes[keyframeId1].nbLinkedEdges--;
        }
        if (m_nodes[keyframeId2].nbLinkedEdges < 1) {
            LOG_WARNING("CorrespondenceGraph::deleteEdge - node {} nb linked edges is {}, cannot decrease.", keyframeId2, m_nodes[keyframeId2].nbLinkedEdges);
        }
        else {
            m_nodes[keyframeId2].nbLinkedEdges--;
        }
    }
    else if (status == EdgeStatus::EXIST_ONE_DIRECTION_INVERSE) {
        m_edges[keyframeId2].erase( m_edges[keyframeId2].find(keyframeId1) );
        if (m_nodes[keyframeId1].nbLinkedEdges < 1) {
            LOG_WARNING("CorrespondenceGraph::deleteEdge - node {} nb linked edges is {}, cannot decrease.", keyframeId1, m_nodes[keyframeId1].nbLinkedEdges);
        }
        else {
            m_nodes[keyframeId1].nbLinkedEdges--;
        }
        if (m_nodes[keyframeId2].nbLinkedEdges < 1) {
            LOG_WARNING("CorrespondenceGraph::deleteEdge - node {} nb linked edges is {}, cannot decrease.", keyframeId2, m_nodes[keyframeId2].nbLinkedEdges);
        }
        else {
            m_nodes[keyframeId2].nbLinkedEdges--;
        }
    }
    else if (status == EdgeStatus::EXIST_DOUBLE_DIRECTION) {
        m_edges[keyframeId1].erase( m_edges[keyframeId1].find(keyframeId2) );
        m_edges[keyframeId2].erase( m_edges[keyframeId2].find(keyframeId1) );
        if (m_nodes[keyframeId1].nbLinkedEdges < 2) {
            LOG_WARNING("CorrespondenceGraph::deleteEdge - node {} nb linked edges is {}, cannot decrease.", keyframeId1, m_nodes[keyframeId1].nbLinkedEdges);
        }
        else {
            m_nodes[keyframeId1].nbLinkedEdges -= 2;
        }
        if (m_nodes[keyframeId2].nbLinkedEdges < 2) {
            LOG_WARNING("CorrespondenceGraph::deleteEdge - node {} nb linked edges is {}, cannot decrease.", keyframeId2, m_nodes[keyframeId2].nbLinkedEdges);
        }
        else {
            m_nodes[keyframeId2].nbLinkedEdges -= 2 ;
        }
    }
    else {
        return false;
    }
    if (m_nodes.at(keyframeId1).nbLinkedEdges == 0) {
        m_nodes.erase(m_nodes.find(keyframeId1));
    }
    if (m_nodes.at(keyframeId2).nbLinkedEdges == 0) {
        m_nodes.erase(m_nodes.find(keyframeId2));
    }
    return true;
}

void CorrespondenceGraph::setEdge(id_t keyframeId1, id_t keyframeId2, const std::vector<DescriptorMatch>& desMatches, const Transform3Df& relativePose)
{
    Correspondence corres;
    corres.matches = desMatches;
    corres.relativePose = relativePose;
    m_edges[keyframeId1][keyframeId2] = corres;
    m_nodes[keyframeId1].nbLinkedEdges++;
    m_nodes[keyframeId2].nbLinkedEdges++;
}

std::vector<DescriptorMatch> CorrespondenceGraph::inverseMatches(const std::vector<DescriptorMatch>& desMatches) const
{
    std::vector<DescriptorMatch> desMatches2;
    for (const auto& match : desMatches) {
        desMatches2.emplace_back(match.getIndexInDescriptorB(), match.getIndexInDescriptorA(), match.getMatchingScore());
    }
    return desMatches2;
}

bool CorrespondenceGraph::getCorrespondence(id_t keyframeId1, id_t keyframeId2, Correspondence& corres, bool& inverseOrder) const 
{
    if (keyframeId1 == keyframeId2) {
        return false;
    }
    if (keyframeId1 < keyframeId2) {
        if (m_edges.find(keyframeId1) != m_edges.end() && m_edges.at(keyframeId1).find(keyframeId2) != m_edges.at(keyframeId1).end()) {
            corres = m_edges.at(keyframeId1).at(keyframeId2);
            LOG_DEBUG("CorrespondenceGraph::getCorrespondence - corres. found");
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

void CorrespondenceGraph::printInfo() const
{
    size_t nbEdges = 0;
    std::for_each(m_edges.cbegin(), m_edges.cend(), [&nbEdges](const auto& item) {nbEdges += item.second.size();});
    LOG_INFO("CorrespondenceGraph::printInfo - \n nb of nodes {} \n nb of edges {}", m_nodes.size(), nbEdges);
    for (const auto& node : m_nodes) {
        LOG_INFO("[Node] keyframe {} - linked to other {} times", node.first, node.second.nbLinkedEdges);
    }
    for (const auto& edge : m_edges) {
        for (const auto& item : edge.second) {
            LOG_INFO("[Edge] keyframe {} <-> {} - nb of matched descriptors {}", edge.first, item.first, item.second.matches.size());
        }
    }
    auto allKeyframes = getAllSortedKeyframes();
    LOG_INFO("Sorted all the {} keyframes by number of correspondences", allKeyframes.size());
    for (const auto& item : allKeyframes) {
        LOG_INFO("keyframe {} - total number of descriptor correspondences: {}", item.first, item.second);
    }
}

bool CorrespondenceGraph::setEnabled(id_t nodeId, bool enabled)
{
    if (m_nodes.find(nodeId) == m_nodes.end()) {
        LOG_WARNING("CorrespondenceGraph::setNodeEnabled - node {} does not exist.", nodeId);
        return false;
    }
    m_nodes[nodeId].enabled = enabled;
    return true;
}

bool CorrespondenceGraph::addVisibility(id_t nodeId, const std::map<id_t, id_t>& vis)
{
    if (m_nodes.find(nodeId) == m_nodes.end()) {
        LOG_WARNING("CorrespondenceGraph::addVisibility - node {} does not exist.", nodeId);
        return false;
    }
    size_t nbNewVisAdded = 0;
    //std::vector<id_t> keyframeIdsExclude = {nodeId};
    auto& kfVis = m_nodes[nodeId].visibility;
    for (const auto& v : vis) {
        if (kfVis.find(v.first) == kfVis.end()) { // if does not exist then add 
            kfVis[v.first] = v.second;
            nbNewVisAdded++;
        }
    }
    // propagate visibilities to neighboring keyframes 
    auto linkedKfs = getLinkedKeyframes(nodeId);
    //std::vector<std::pair<id_t, std::map<id_t, id_t>>> linkedKfIds;  // id, newly added 2d-3d visibilities
    for (const auto& kf : linkedKfs) {
        auto kfId = kf.first;
        if (m_nodes.find(kfId) == m_nodes.end()) {
            LOG_WARNING("CorrespondenceGraph::addVisibility - keyframe {} is not found.", kfId);
            continue;
        }
        auto matches = getDescriptorMatches(nodeId, kfId);
        std::unordered_map<id_t, id_t> matchedKpt;
        for (const auto& m : matches) {
            matchedKpt[m.getIndexInDescriptorA()] = m.getIndexInDescriptorB();
        }
        auto& nbrKfvis = m_nodes[kfId].visibility;
        std::map<id_t, id_t> newVis;
        for (const auto& v : vis) {
            if (matchedKpt.find(v.first) == matchedKpt.end()) {
                continue;
            }
            auto nbrKfKptId = matchedKpt.at(v.first);
            if (nbrKfvis.find(nbrKfKptId) == nbrKfvis.end()) {
                nbrKfvis[nbrKfKptId] = v.second;
                nbNewVisAdded++;
                newVis[nbrKfKptId] = v.second;
            }
        }
        //linkedKfIds.push_back({kfId, newVis});
        //keyframeIdsExclude.push_back(kfId);
    }
    // find 2nd level neighbor
//    size_t nb2ndLevel = std::min<size_t>(2, linkedKfIds.size());
//    for (size_t i = 0; i < nb2ndLevel; ++i) {
//        auto lkf = linkedKfIds[i];
//        auto nbrId = lkf.first;
//        auto linkedKfs2 = getLinkedKeyframes(nbrId);
//        std::vector<id_t> linkedKfIds2;
//        for (const auto& lkf : linkedKfs2) {
//            auto id = lkf.first;
//            if (std::find(keyframeIdsExclude.cbegin(), keyframeIdsExclude.cend(), id) == keyframeIdsExclude.cend()) {
//                linkedKfIds2.push_back(id);
//            }
//        }
//        size_t nb3rdLevel = std::min<size_t>(2, linkedKfIds2.size());
//        for (size_t j = 0; j < nb3rdLevel; ++j) {
//            auto nbrId2 = linkedKfIds2[j];
//            // nodeId -> nbrId -> nbrId2
//            auto& vis = lkf.second;
//            auto matches2 = getDescriptorMatches(nbrId, nbrId2);
//            std::map<id_t, id_t> kptMap;
//            for (const auto& match : matches2) {
//                kptMap[match.getIndexInDescriptorA()] = match.getIndexInDescriptorB();
//            }
//            auto& nbr2vis = m_nodes[nbrId2].visibility;
//            for (const auto& v : vis) {
//                if (kptMap.find(v.first) == kptMap.end()) {
//                    continue;
//                }
//                auto nbr2KpId = kptMap.at(v.first);
//                if (nbr2vis.find(nbr2KpId) == nbr2vis.end()) {
//                    nbr2vis[nbr2KpId] = v.second;
//                    LOG_INFO("CorrespondenceGraph::addVisibility - (level 2) keyframe {} kpt {} cp {}", nbrId2, nbr2KpId, v.second);
//                }
//            }
//            keyframeIdsExclude.push_back(nbrId2);
//        }
//    }
    LOG_DEBUG("CorrespondenceGraph::addVisibility - keyframe {} propagated {} visibilities", nodeId, nbNewVisAdded);
    return nbNewVisAdded > 0;
}

std::map<size_t, std::vector<std::pair<id_t, size_t>>> CorrespondenceGraph::getVisibleKeyframes() const
{
    LOG_DEBUG("CorrespondenceGraph::getVisibleKeyframes - begin.");
    std::map<size_t, std::vector<std::pair<id_t, size_t>>> kfs;
    for (const auto& node : m_nodes) {
        if (!node.second.enabled) {
            continue;
        }
        size_t nbv = node.second.visibility.size();
        LOG_DEBUG("CorrespondenceGraph::getVisibleKeyframes - keyframe {} - nb vis. {}", node.first, nbv);
        if (nbv > 0) {
            kfs[node.second.nbRegistrationTrials].push_back({node.first, nbv});
        }
    }
    for (auto& item : kfs) {
        auto& listkfs = item.second;
        std::sort(listkfs.begin(), listkfs.end(), [](auto& x1, auto& x2) {return x1.second > x2.second;});
    }
    return kfs;
}

bool CorrespondenceGraph::updateRegistrationTrials(id_t nodeId, int x)
{
    if (m_nodes.find(nodeId) == m_nodes.end()) {
        LOG_WARNING("CorrespondenceGraph::updateRegistrationTrials - cannot find the node {}", nodeId);
        return false;
    }
    if (x >= 0) {
        m_nodes[nodeId].nbRegistrationTrials += static_cast<size_t>(x);
    }
    else {
        int newValue = static_cast<int>(m_nodes[nodeId].nbRegistrationTrials) + x;
        m_nodes[nodeId].nbRegistrationTrials = static_cast<size_t>(std::max<int>(0, newValue));
    }
    return true;
}

const std::map<id_t, id_t>& CorrespondenceGraph::getVisibility(id_t nodeId) const
{
    if (m_nodes.find(nodeId) == m_nodes.end()) {
        LOG_WARNING("CorrespondenceGraph::getVisibility - keyframe {} is not found.", nodeId);
        return std::map<id_t, id_t>();
    }
    return m_nodes.at(nodeId).visibility;
}

std::map<id_t, id_t> CorrespondenceGraph::getPointVisibility(id_t pointId) const
{
    std::map<id_t, id_t> visibility;
    for (const auto& node : m_nodes) {
        id_t keyframeId = node.first;
        auto& keyframeVis = node.second.visibility;
        for (const auto& vis : keyframeVis) {
            if (vis.second == pointId) {
                visibility[keyframeId] = vis.first;
                break;
            }
        }
    }
    return visibility;
}

std::vector<id_t> CorrespondenceGraph::getActiveKeypoints(id_t keyframeId) const
{
    auto linkedKfs = getLinkedKeyframes(keyframeId);
    std::vector<id_t> kptIds;
    for (const auto& kf : linkedKfs) {
        auto matches = getDescriptorMatches(keyframeId, kf.first);
        for (const auto& match : matches) {
            if (std::find(kptIds.begin(), kptIds.end(), match.getIndexInDescriptorA()) == kptIds.end()) {
                kptIds.push_back(match.getIndexInDescriptorA());
            }
        }
    }
    return kptIds;
}

template <typename Archive>
void CorrespondenceGraph::Correspondence::serialize(Archive &ar, const unsigned int /* version */)
{
    ar& matches;
    ar& relativePose;
}
IMPLEMENTSERIALIZE(CorrespondenceGraph::Correspondence);

template <typename Archive>
void CorrespondenceGraph::Node::serialize(Archive &ar, const unsigned int /* version */)
{
    ar& enabled;
    ar& nbRegistrationTrials;
    ar& nbLinkedEdges;
    ar& visibility;
}
IMPLEMENTSERIALIZE(CorrespondenceGraph::Node);

template <typename Archive>
void CorrespondenceGraph::serialize(Archive &ar, const unsigned int /* version */)
{
    ar & m_nodes;
    ar & m_edges;
}
IMPLEMENTSERIALIZE(CorrespondenceGraph);

} // datastructure
} // SolAR
