/**
 * @copyright Copyright (c) 2025 B-com http://www.b-com.com/
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

#ifndef SOLAR_I2DMASKSMANAGER_H
#define SOLAR_I2DMASKSMANAGER_H

#include "datastructure/Mask2DCollection.h"
#include <xpcf/api/IComponentIntrospect.h>

namespace SolAR {
using namespace datastructure; 
namespace api {
namespace storage {

/**
 * @class IMasks2DManager
 * @brief <B>Allows to store a set of 2D masks.</B>
 * <TT>UUID: 56f36544-85c4-4636-bd4e-b3493a9e95c4</TT>
 *
 * This storage component can be accessed by processing components to share persistent data.
 */

class XPCF_IGNORE IMasks2DManager : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IMasks2DManager default constructor
    IMasks2DManager() = default;

    /// @brief IMasks2DManager default destructor
    virtual ~IMasks2DManager() = default;

    /// @brief This method allows to add a mask to the 2D mask manager component
    /// @param[in] mask the mask to add to the set of persistent masks
    /// @param[in] defineMaskId if true an id will be set for the added mask, if false the id of the mask will be used
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode addMask(SRef<Mask2D> mask, bool defineMaskId = true) = 0;

    /// @brief This method allows to get a mask by its id
    /// @param[in] id id of the mask to get
    /// @param[out] mask a mask stored in the masks manager
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getMask(uint32_t id, SRef<Mask2D>& mask) const = 0;

    /// @brief This method allows to get a set of masks by their ids
    /// @param[in] ids a vector of ids of the masks to get
    /// @param[out] masks a vector of masks stored in the mask manager
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getMasks(const std::vector<uint32_t>& ids, std::vector<SRef<Mask2D>>& masks) const = 0;

    /// @brief This method allows to get all masks
    /// @param[out] masks the set of masks
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getAllMasks(std::vector<SRef<Mask2D>>& masks) const = 0;

    /// @brief This method allows to know if a mask is already stored in the component
    /// @param[in] id id of this mask
    /// @return true if exist, else false
    virtual bool isExistMask(uint32_t id) const = 0;

    /// @brief This method allows to get the number of masks stored in the component
    /// @return The number of masks
    virtual size_t getNbMasks() const = 0;

    /// @brief This method allow to suppress a mask by its id
    /// @param[in] id id of the mask to suppress
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode suppressMask(uint32_t id) = 0;

    /// @brief This method is to set the mask collection
    /// @param[in] maskCollection the mask collection of map
    virtual void setMaskCollection(SRef<Mask2DCollection> maskCollection) = 0;

    /// @brief This method returns a pointer to the const mask collection
    /// @return the mask collection
    virtual SRef<const Mask2DCollection> getConstMaskCollection() const = 0;

    /// @brief This method returns a pointer to the mask collection
    /// @return the mask collection
    virtual SRef<Mask2DCollection> getMaskCollection() const = 0;

    /// @brief This method returns the mask collection
    /// @param[out] maskCollection the mask collection of map
    /// @return std::unique_lock<std::mutex> which can be used to lock the access to data
    virtual std::unique_lock<std::mutex> getMaskCollection(SRef<Mask2DCollection>& maskCollection) = 0;

    /// @brief This method allows to save the masks to the external file
    /// @param[in] file the file name
    /// @return FrameworkReturnCode::_SUCCESS_ if the save succeeded, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode saveToFile(const std::string& file) const = 0;

    /// @brief This method allows to load the masks from the external file
    /// @param[in] file the file name
    /// @return FrameworkReturnCode::_SUCCESS_ if the load succeeded, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode loadFromFile(const std::string& file) = 0;
};

} // storage
} // api
} // SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IMasks2DManager,
                             "56f36544-85c4-4636-bd4e-b3493a9e95c4",
                             "IMasks2DManager",
                             "A component interface for storing a set of 2D masks accessible by processing components.");



#endif