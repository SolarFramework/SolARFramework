#ifndef KEYFRAMERETRIEVAL_H
#define KEYFRAMERETRIEVAL_H

#include "core/SolARFrameworkDefinitions.h"
#include <core/SerializationDefinitions.h>
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Lockable.h"
#include "core/Messages.h"
#include "xpcf/core/refs.h"
#include <map>

// Definition of KeyframeRetrieval Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
 * @typedef BoW
 * @brief <B>Bag of words feature.</B>
 *
 */
typedef std::map<uint32_t, float> BoWFeature;

/**
 * @typedef BoWLevelFeature
 * @brief <B>Bag of words with augmented information.</B>
 *  For each word, keeps information about the indices of the elements that have been classified into the word it is computed at the desired level.
 */
typedef std::map<uint32_t, std::vector<uint32_t>> BoWLevelFeature;

/**
* @class KeyframeRetrieval
* @brief <B>A bag of word of keyframe.</B>
* This class provides a data structure of keyframe retrieval model (BoW).
*/
class  SOLARFRAMEWORK_API KeyframeRetrieval : public Lockable {
public:

	///
	/// @brief KeyframeRetrieval constructor.
	///
	KeyframeRetrieval() = default;
	KeyframeRetrieval(const KeyframeRetrieval& other) = default;
	KeyframeRetrieval& operator=(const KeyframeRetrieval& other) = default;

	///
	/// \brief ~KeyframeRetrieval
	///
	~KeyframeRetrieval() = default;

	/// @brief This method allow to add a keyframe descriptor to keyframe retrieval 
	/// @param[in] id the id of the keyframe
    /// @param[in] bowDesc fbow descriptor
    /// @param[in] bowLevelDesc fbow2 descriptor
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addDescriptor(uint32_t id, const SolAR::datastructure::BoWFeature& bowDesc, const SolAR::datastructure::BoWLevelFeature& bowLevelDesc);

	/// @brief This method allow to remove a keyframe descriptor in keyframe retrieval 
	/// @param[in] id the id of the keyframe
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode removeDescriptor(uint32_t id);

    /// @brief This method allow to get bow descirptor
	/// @param[in] id the id of the keyframe
    /// @param[out] bowDesc bow descriptor
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getBoWFeature(uint32_t id, SolAR::datastructure::BoWFeature& bowDesc);

    /// @brief This method allow to get bow descirptor at the desired level
	/// @param[in] id the id of the keyframe
    /// @param[out] bowLevelDesc bow level descriptor
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getBoWLevelFeature(uint32_t id, SolAR::datastructure::BoWLevelFeature& bowLevelDesc);

	/// @brief This method allow to get inverted index at each node
	/// @param[in] nodeId the id of node
	/// @param[out] invertedIndex inverted index at each node
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode getInvertedIndex(uint32_t nodeId, std::set<uint32_t>& invertedIndex);

    /// @brief This method allows to reset BoW features as well as inverted index map 
    void reset();

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version);
	
    std::map<uint32_t, SolAR::datastructure::BoWFeature> m_listBoWFeature;				// A map BoW descriptor of keyframes
    std::map<uint32_t, SolAR::datastructure::BoWLevelFeature> m_listBoWLevelFeature;    // A map BoW2 descriptor of keyframes which save index of feature at nodes of the expected level
    std::map<uint32_t, std::set<uint32_t>> m_invertedIndexKfs;                          // For each node at level m_level stores a set of frames that contain it
};

DECLARESERIALIZE(KeyframeRetrieval);

}
}  // end of namespace SolAR

#endif // KEYFRAMERETRIEVAL_H
