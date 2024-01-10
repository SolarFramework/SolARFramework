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

#ifndef SOLAR_ICAMERASPARAMETERSSMANAGER_H
#define SOLAR_ICAMERASPARAMETERSSMANAGER_H


#include <xpcf/api/IComponentIntrospect.h>
#include "core/Messages.h"
#include "datastructure/CameraParametersCollection.h"
#include <vector>

namespace SolAR {
namespace api {
namespace storage {

/**
 * @class ICameraParametersManager
 * @brief <B>Allows to store a set of cameraParameters.</B>
 * <TT>UUID: 31f151fc-326d-11ed-a261-0242ac120002</TT>
 *
 * This storage component can be accessed by processing components to share persistent data.
 */

class XPCF_IGNORE ICameraParametersManager :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief ICameraParameterstorage default constructor
    ICameraParametersManager() = default;

    /// @brief ICameraParameterstorage default destructor
    virtual ~ICameraParametersManager() = default;

    /// @brief This method allow to add cameraParameters to the CameraParameters manager component
    /// @param[in] cameraParameters the cameraParameters to add to the set of persistent CameraParameters
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode addCameraParameters(const SRef<SolAR::datastructure::CameraParameters> cameraParameters) = 0;

    /// @brief This method allow to add cameraParameters to the CameraParameters manager component
    /// @param[in] frame the frame to add to the set of persistent CameraParameters
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode addCameraParameters(SolAR::datastructure::CameraParameters & cameraParameters) = 0;

    /// @brief This method allows to get cameraParameters by their id
    /// @param[in] id id of the cameraParameters to get
    /// @param[out] cameraParameters cameraParameters stored in the CameraParameters manager
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getCameraParameters(const uint32_t id, SRef<SolAR::datastructure::CameraParameters> & cameraParameters) const = 0;

    /// @brief This method allows to get cameraParameters by their id
    /// @param[in] id id of the cameraParameters to get
    /// @param[out] cameraParameters cameraParameters stored in the CameraParameters manager
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getCameraParameters(const uint32_t id, SolAR::datastructure::CameraParameters & cameraParameters) const = 0;

    /// @brief This method allows to get a set of CameraParameters by their ids
    /// @param[in] ids a vector of ids of the cameraParameters to get
    /// @param[out] cameraParameters a vector of cameraParameters stored in the CameraParameters manager
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getCameraParameters(const std::vector<uint32_t> & ids, std::vector<SRef<SolAR::datastructure::CameraParameters>> & cameraParameters) const = 0;

    /// @brief This method allows to get all cameraParameters
    /// @param[out] cameraParameters the set of cameraParameters
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getAllCameraParameters(std::vector<SRef<SolAR::datastructure::CameraParameters>> & CameraParameters) const = 0;

    /// @brief This method allow to suppress cameraParameters by its id
    /// @param[in] id id of cameraParameters to suppress
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode suppressCameraParameters(const uint32_t id) = 0;

    /// @brief This method allows to know if cameraParameters are already stored in the component
    /// @param[in] id id of this cameraParameters
    /// @return true if exist, else false
    virtual bool isExistCameraParameters(const uint32_t id) const = 0;

    /// @brief This method allows to get the number of CameraParameters stored in the point cloud
    /// @return The number of CameraParameters
    virtual int getNbCameraParameters() const = 0;

    /// @brief This method allows to save all cameraParameters to the external file
    /// @param[in] file the file name
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode saveToFile(const std::string & file) const = 0;

    /// @brief This method allows to load all CameraParameters from the external file
    /// @param[in] file the file name
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode loadFromFile(const std::string & file) = 0;

    /// @brief This method returns the CameraParameters collection
    /// @return the CameraParameters collection
    virtual const SRef<SolAR::datastructure::CameraParametersCollection> & getConstCameraParametersCollection() const = 0;

    /// @brief This method returns the CameraParameters collection
    /// @param[out] CameraParametersCollection the CameraParameters collection of map
    /// @return the CameraParameters collection
    virtual std::unique_lock<std::mutex> getCameraParametersCollection(SRef<SolAR::datastructure::CameraParametersCollection>& cameraParametersCollection) = 0;

    /// @brief This method is to set the CameraParameters collection
    /// @param[in] cameraParameters the CameraParameters collection of map
    virtual void setCameraParametersCollection(const SRef<SolAR::datastructure::CameraParametersCollection> cameraParametersCollection) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::ICameraParametersManager,
                             "31f151fc-326d-11ed-a261-0242ac120002",
                             "ICameraParametersManager",
                             "A component interface for storing a set of persistent CameraParameters accessible by processing components.");


#endif //SOLAR_ICAMERASPARAMETERSSMANAGER_H

