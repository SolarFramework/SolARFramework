#ifndef KEYFRAMERETRIEVAL_H
#define KEYFRAMERETRIEVAL_H

#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Lockable.h"
#include "core/Messages.h"
#include "xpcf/core/refs.h"
#include <map>
#include "fbow.h"

// Definition of KeyframeRetrieval Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

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
	/// @param[in] fbowDesc fbow descriptor
	/// @param[in] fbow2Desc fbow2 descriptor
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode addDescriptor(uint32_t id, const fbow::fBow& fbowDesc, const fbow::fBow2& fbow2Desc);

	/// @brief This method allow to remove a keyframe descriptor in keyframe retrieval 
	/// @param[in] id the id of the keyframe
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode removeDescriptor(uint32_t id);

	/// @brief This method allow to get fbow descirptor
	/// @param[in] id the id of the keyframe
	/// @param[out] fbowDesc fbow descriptor
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode getFBow(uint32_t id, fbow::fBow& fbowDesc);

	/// @brief This method allow to get fbow2 descirptor
	/// @param[in] id the id of the keyframe
	/// @param[out] fbow2Desc fbow2 descriptor
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode getFBow2(uint32_t id, fbow::fBow2& fbow2Desc);

	/// @brief This method allow to get inverted index at each node
	/// @param[in] nodeId the id of node
	/// @param[out] invertedIndex inverted index at each node
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode getInvertedIndex(uint32_t nodeId, std::set<uint32_t>& invertedIndex);

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version);
	
	std::map<uint32_t, fbow::fBow> m_list_KFBoW;				// A map BoW descriptor of keyframes		
	std::map<uint32_t, fbow::fBow2> m_list_KFBoW2;				// A map BoW2 descriptor of keyframes which save index of feature at nodes of the expected level	
	std::map<uint32_t, std::set<uint32_t>> m_invertedIndexKfs;	// For each node at level m_level stores a set of frames that contain it
};

DECLARESERIALIZE(KeyframeRetrieval);

}
}  // end of namespace SolAR

#endif // KEYFRAMERETRIEVAL_H
