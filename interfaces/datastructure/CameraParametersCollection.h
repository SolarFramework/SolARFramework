#ifndef CAMERAPARAMETERSCOLLECTION_H
#define CAMERAPARAMETERSCOLLECTION_H

#include <core/SolARFrameworkDefinitions.h>
#include <datastructure/GeometryDefinitions.h>
#include <datastructure/CameraDefinitions.h>
#include <datastructure/Lockable.h>
#include <core/Messages.h>
#include <core/SerializationDefinitions.h>
#include <xpcf/core/refs.h>
#include <map>


// Definition of CameraParametersCollection Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
* @class CameraParametersCollection
* @brief <B>A set of CameraParameters.</B>
* This class provides a set of CameraParameters.
*/
class  SOLARFRAMEWORK_API CameraParametersCollection : public Lockable {
public:

	///
    /// @brief CameraParametersCollection constructor.
	///
    CameraParametersCollection() = default;
    CameraParametersCollection(const CameraParametersCollection& other) = default;
    CameraParametersCollection& operator=(const CameraParametersCollection& other) = default;

	///
    /// \brief ~CameraParametersCollection
	///
    ~CameraParametersCollection() = default;

    /// @brief This method allow to add CameraParameters to the CameraParameters manager component
    /// @param[in] cameraParameters the CameraParameters to add to the set of persistent CameraParameterss
    /// @param[in] defineCameraParametersId if true an id will be set for the added CameraParameters, if false the id of the CameraParameters will be used
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addCameraParameters(const SRef<SolAR::datastructure::CameraParameters> cameraParameters, bool defineCameraParametersId = true);

	/// @brief This method allow to add a frame to the key frame manager component
    /// @param[in] cameraParameters the cameraParameters to add to the set of persistent CameraParameterss
    /// @param[in] defineCameraParametersId if true an id will be set for the added cameraParameters, if false the id of the cameraParameters will be used
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addCameraParameters(SolAR::datastructure::CameraParameters & cameraParameters, bool defineCameraParametersId = true);

    /// @brief This method allows to get a cameraParameters by its id
    /// @param[in] id of the cameraParameters to get
    /// @param[out] cameraParameters the cameraParameters stored in the cameraParameters manager
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getCameraParameters(const uint32_t id, SRef<SolAR::datastructure::CameraParameters> & cameraParameters) const;

    /// @brief This method allows to get a cameraParameters by its id
    /// @param[in] id of the cameraParameters to get
    /// @param[out] cameraParameters the cameraParameters stored in the cameraParameters manager
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getCameraParameters(const uint32_t id, SolAR::datastructure::CameraParameters & cameraParameters) const;

    /// @brief This method allows to get a set of cameraParameters by their ids
    /// @param[in] a vector of ids of the cameraParameters to get
    /// @param[out] a vector of cameraParameters stored in the cameraParameters manager
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getCameraParameters(const std::vector<uint32_t> & ids, std::vector<SRef<SolAR::datastructure::CameraParameters>>& cameraParameters) const;

    /// @brief This method allows to get all cameraParameters
    /// @param[out] the set of cameraParameters
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getAllCameraParameters(std::vector<SRef<SolAR::datastructure::CameraParameters>>& CameraParameters) const;

    /// @brief This method allow to suppress a cameraParameters by its id
    /// @param[in] id of the cameraParameters to suppress
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode suppressCameraParameters(const uint32_t id);

    /// @brief This method allows to know if a cameraParameters is already stored in the component
    /// @param[in] Id of this cameraParameters
	/// @return true if exist, else false
    bool isExistCameraParameters(const uint32_t id) const;

    /// @brief This method allows to get the number of cameraParameters stored in the collection of cameraParameters
    /// @return The number of cameraParameters
    int getNbCameraParameters() const;

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version);

    std::map<uint32_t, SRef<SolAR::datastructure::CameraParameters>> m_cameraParameters;
    uint32_t                                                         m_id = 0;
};

DECLARESERIALIZE(CameraParametersCollection);

}
}  // end of namespace SolAR

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::CameraParametersCollection);

#endif // CAMERAPARAMETERSCOLLECTION_H
