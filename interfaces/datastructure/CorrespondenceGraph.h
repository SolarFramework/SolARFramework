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

#ifndef CORRESPONDENCEGRAPH_H
#define CORRESPONDENCEGRAPH_H

#include "core/Messages.h"
#include "core/SerializationDefinitions.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/Lockable.h"
#include "datastructure/MathDefinitions.h"
#include <map>
#include <utility>
#include <vector>

using id_t = uint32_t;

namespace SolAR {
namespace datastructure {

/**
* @class CorrespondenceGraph
* @brief <B> A correspondence graph of keyframes. </B>
* This class provides a correspondence graph where each vertex is an id of a keyframe.
* Each edge connecting two vertices represents the correspondence between the two keyframes.
*/
class  SOLARFRAMEWORK_API CorrespondenceGraph : public Lockable {
public:
    /// @struct Vertex
    struct Vertex {
        bool enabled = true;
        size_t nbRegistrationTrials = 0;
        size_t nbLinkedEdges = 0;
        std::map<id_t, id_t> visibility; // keypoint ID -> cloud point ID
        /// @brief Serialization function
        friend class boost::serialization::access;
        template <typename Archive>
        void serialize(Archive &ar, const unsigned int version);
    };

    /// @struct Correspondence
    struct Correspondence {
        std::vector<DescriptorMatch> matches; // descriptor matches
        Transform3Df relativePose; // relative pose between the two keyframes 
        /// @brief Serialization function
        friend class boost::serialization::access;
        template <typename Archive>
        void serialize(Archive &ar, const unsigned int version);
    };

    /// @enum EdgeStatus
    enum class EdgeStatus {
        NOT_EXIST,
        INVALID,
        EXIST_ONE_DIRECTION,
        EXIST_ONE_DIRECTION_INVERSE,
        EXIST_DOUBLE_DIRECTION
    };

    /// @brief CorrespondenceGraph constructor.
    CorrespondenceGraph() = default;
    CorrespondenceGraph(const CorrespondenceGraph& other) = default;
    CorrespondenceGraph& operator=(const CorrespondenceGraph& other) = default;

    /// @brief CorrespondenceGraph destructor
    ~CorrespondenceGraph() = default;

    /// @brief Add edge
    /// @param[in] keyframeId1 first keyframe's Id
    /// @param[in] keyframeId2 second keyframe's Id
    /// @param[in] desMatches list of descriptor matches
    /// @param[in] relativePose pose from first to second keyframes
    /// @return FrameworkReturnCode::_SUCCESS if added successfully, otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode addEdge(id_t keyframeId1, id_t keyframeId2, const std::vector<DescriptorMatch>& desMatches, const Transform3Df& relativePose);

    /// @brief add keyframe visibility
    /// @param[in] vertexId ID of the vertex (keyframe)
    /// @param[in] vis visibility map
    /// @return FrameworkReturnCode::_SUCCESS if successfully added otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode addVisibility(id_t vertexId, const std::map<id_t, id_t>& vis);

    /// @brief Remove edge
    /// @param[in] keyframeId1 first keyframe's Id
    /// @param[in] keyframeId2 second keyframe's Id
    /// @return FrameworkReturnCode::_SUCCESS if successfully removed otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode removeEdge(id_t keyframeId1, id_t keyframeId2);

    /// @brief Remove all edges
    /// @return FrameworkReturnCode::_SUCCESS if successfully removed otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode removeAllEdges();

    /// @brief update number registration trials for the vertex
    /// @param[in] vertexId ID of the vertex (keyframe)
    /// @param[in] x update quantity of nb. reg. trials (nb_reg_trials = nb_reg_trials + x)
    /// @return FrameworkReturnCode::_SUCCESS if successfully updated otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode updateRegistrationTrials(id_t vertexId, int x);

    /// @brief enable or disable a vertex (keyframe)
    /// @param[in] vertexId ID of the vertex (keyframe)
    /// @param[in] enabled boolean indicating enabled or not
    /// @return FrameworkReturnCode::_SUCCESS if successfully set otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode setEnabled(id_t vertexId, bool enabled);

    /// @brief Get keyframes sorted by number of correspondences in decreasing order
    /// @return list of pairs of (keyframe Id, number of correspondences) sorted in decreasing order by number of correspondences
    std::vector<std::pair<id_t, size_t>> getAllSortedKeyframes() const;

    /// @brief Get keyframes linked to an input keyframe
    /// @param[in] keyframeId keyframe Id
    /// @param[in] onlyDisabled if true will get only disabled keyframes
    /// @return list of pairs of (keyframe Id, number of correspondences) sorted in decreasing order by number of correspondences
    std::vector<std::pair<id_t, size_t>> getLinkedKeyframes(id_t keyframeId, bool onlyDisabled = false) const;

    /// @brief Get descriptor matches between keyframes
    /// @param[in] keyframeId1 first keyframe's Id
    /// @param[in] keyframeId2 second keyframe's Id
    /// @return list of descriptor matches
    std::vector<DescriptorMatch> getDescriptorMatches(id_t keyframeId1, id_t keyframeId2) const;

    /// @brief Get relative pose
    /// @param[in] keyframeId1 first keyframe's Id
    /// @param[in] keyframeId2 second keyframe's Id
    /// @return relative pose. If no pose is available will return transform whose elements are all zero.
    Transform3Df getRelativePose(id_t keyframeId1, id_t keyframeId2) const;

    /// @brief get keyframe visibility
    /// @param[in] vertexId ID of the vertex (keyframe)
    /// @return visibility map (keypoint ID to cloud point ID)
    const std::map<id_t, id_t>& getVisibility(id_t vertexId) const;

    /// @brief get point's visibility
    /// @param[in] pointId ID of the cloud point
    /// @return visibility map 
    std::map<id_t, id_t> getPointVisibility(id_t pointId) const;

    /// @brief get visible keyframes sorted by number of visible 3D points
    /// @return list of visible keyframes (map from nbRegistrationTrials to list of (keyframeId, number of visible points)) 
    std::map<size_t, std::vector<std::pair<id_t, size_t>>> getVisibleKeyframes() const;

    /// @brief get matched keypoint IDs of a given keyframe
    /// @param keyframeId keyframe ID
    /// @return list of keypoint IDs
    std::vector<id_t> getActiveKeypoints(id_t keyframeId) const;

    /// @brief Print graph info
    void printInfo() const;

private:
    /// @brief  Serialization
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    /// @brief Check edge status 
    /// @param[in] keyframeId1 first keyframe's Id
    /// @param[in] keyframeId2 second keyframe's Id
    /// @return EdgeStatus 
    EdgeStatus checkEdge(id_t keyframeId1, id_t keyframeId2) const;

    /// @brief Delete edge
    /// @param[in] keyframeId1 first keyframe's Id
    /// @param[in] keyframeId2 second keyframe's Id
    /// @param[in] status edge status
    /// @return boolean true if deleted otherwise false  
    bool deleteEdge(id_t keyframeId1, id_t keyframeId2, const EdgeStatus& status);

    /// @brief Set edge
    /// @param[in] keyframeId1 first keyframe's Id
    /// @param[in] keyframeId2 second keyframe's Id
    /// @param[in] desMatches list of descriptor matches
    /// @param[in] relativePose pose from first to second keyframes
    void setEdge(id_t keyframeId1, id_t keyframeId2, const std::vector<DescriptorMatch>& desMatches, const Transform3Df& relativePose);

    /// @brief Inverse descriptor matches (e.g., from A-B to B-A)
    /// @param[in] desMatches list of descriptor matches
    /// @return list of descriptor matches
    std::vector<DescriptorMatch> inverseMatches(const std::vector<DescriptorMatch>& desMatches) const;

    /// @brief Get correspondence
    /// @param[in] keyframeId1 first keyframe's Id
    /// @param[in] keyframeId2 second keyframe's Id
    /// @param[out] corres correspondence between keyframes 
    /// @param[out] inverseOrder boolean indicating if the correspondence is in inverse order
    /// @return boolean true if found correspondence otherwise false
    bool getCorrespondence(id_t keyframeId1, id_t keyframeId2, Correspondence& corres, bool& inverseOrder) const;

    std::map<id_t, std::map<id_t, Correspondence>> m_edges; // keyframe Id, keyframe Id -> Correspondence
    std::map<id_t, Vertex> m_vertices; //  keyframe Id -> vertex info
};

DECLARESERIALIZE(CorrespondenceGraph::Correspondence);
DECLARESERIALIZE(CorrespondenceGraph::Vertex);
DECLARESERIALIZE(CorrespondenceGraph);

} // datastructure
} // SolAR
BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::CorrespondenceGraph);

#endif // CORRESPONDENCEGRAPH_H