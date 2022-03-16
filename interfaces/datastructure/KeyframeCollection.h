#ifndef KEYFRAMECOLLECTION_H
#define KEYFRAMECOLLECTION_H

#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Keyframe.h"
#include "datastructure/Lockable.h"
#include "core/Messages.h"
#include "xpcf/core/refs.h"
#include <map>

// Definition of SparsePointCloud Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
* @class KeyframeCollection
* @brief <B>A set of keyframes.</B>
* This class provides a set of keyframes.
*/
class  SOLARFRAMEWORK_API KeyframeCollection : public Lockable {
public:

	///
	/// @brief KeyframeCollection constructor.
	///
	KeyframeCollection() = default;
	KeyframeCollection(const KeyframeCollection& other) = default;
	KeyframeCollection& operator=(const KeyframeCollection& other) = default;

	///
	/// \brief ~KeyframeCollection
	///
	~KeyframeCollection() = default;

	/// @brief This method allow to add a frame to the keyframe manager component
	/// @param[in] frame the frame to add to the set of persistent keyframes
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addKeyframe(const SRef<SolAR::datastructure::Keyframe> keyframe);

	/// @brief This method allow to add a frame to the key frame manager component
	/// @param[in] frame the frame to add to the set of persistent keyframes
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addKeyframe(const SolAR::datastructure::Keyframe & keyframe);

	/// @brief This method allows to get a keyframe by its id
	/// @param[in] id of the keyframe to get
	/// @param[out] a keyframe stored in the keyframes manager
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getKeyframe(const uint32_t id, SRef<SolAR::datastructure::Keyframe> & keyframe) const;

	/// @brief This method allows to get a set of keyframes by their ids
	/// @param[in] a vector of ids of the keyframes to get
	/// @param[out] a vector of keyframes stored in the keyframe manager
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getKeyframes(const std::vector<uint32_t> & ids, std::vector<SRef<SolAR::datastructure::Keyframe>>& keyframes) const;

	/// @brief This method allows to get all keyframes
	/// @param[out] the set of keyframes
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getAllKeyframes(std::vector<SRef<SolAR::datastructure::Keyframe>>& keyframes) const;

	/// @brief This method allow to suppress a keyframe by its id
	/// @param[in] id of the keyframe to suppress
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode suppressKeyframe(const uint32_t id);

	/// @brief This method allows to get the descriptor type used to extract descriptor for each keyframe
	/// @return Descriptor type
    SolAR::datastructure::DescriptorType getDescriptorType() const;

	/// @brief This method allows to set the descriptor type used to extract descriptor for each keyframe
	/// @param[in] type the descriptor type
	/// @return @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode setDescriptorType(const SolAR::datastructure::DescriptorType & type);

	/// @brief This method allows to know if a keyframe is already stored in the component
	/// @param[in] Id of this keyframe
	/// @return true if exist, else false
	bool isExistKeyframe(const uint32_t id) const;

	/// @brief This method allows to get the number of keyframes stored in the point cloud
	/// @return The number of keyframes
	int getNbKeyframes() const;

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version);

    std::map<uint32_t, SRef<SolAR::datastructure::Keyframe>>m_keyframes;
    SolAR::datastructure::DescriptorType                    m_descriptorType;
    uint32_t                                                m_id;
};

DECLARESERIALIZE(KeyframeCollection);

}
}  // end of namespace SolAR

#endif // KEYFRAMECOLLECTION_H
