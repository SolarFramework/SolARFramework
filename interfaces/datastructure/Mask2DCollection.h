/**
 * @copyright Copyright (c) 2017-2025 B-com http://www.b-com.com/
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

#ifndef MASK2DCOLLECTION_H
#define MASK2DCOLLECTION_H

#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/Lockable.h"
#include "datastructure/Mask2D.h"

namespace SolAR {
namespace datastructure {

/**
* @class Mask2DCollection
* @brief <B>A set of 2D masks.</B>
* This class provides a set of 2D masks.
*/
class  SOLARFRAMEWORK_API Mask2DCollection : public Lockable {
public:
    /// @brief default constructor
    Mask2DCollection() = default;

    /// @brief default copy constructor
    Mask2DCollection(const Mask2DCollection&) = default;

    /// @brief default operator =
    Mask2DCollection& operator=(const Mask2DCollection&) = default;

    /// @brief default destructor
    ~Mask2DCollection() = default;

    /// @brief This method allow to add a Mask2D to the Mask2D manager component
    /// @param[in] mask the Mask2D to add to the set of persistent Mask2Ds
    /// @param[in] defineMaskId if true an id will be set for the added Mask2D, if false the id of the Mask2D will be used
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addMask(SRef<const Mask2D> mask, bool defineMaskId = true);

    /// @brief This method allow to add a Mask2D to the key Mask2D manager component
    /// @param[in] mask the Mask2D to add to the set of persistent Mask2Ds
    /// @param[in] defineMaskId if true an id will be set for the added Mask2D, if false the id of the Mask2D will be used
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addMask(const Mask2D& mask, bool defineMaskId = true);

    /// @brief This method allows to get a Mask2D by its id
    /// @param[in] id of the Mask2D to get
    /// @param[out] mask Mask2D stored in the Mask2Ds manager
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getMask(uint32_t id, SRef<Mask2D>& mask) const;

    /// @brief This method allows to get a set of Mask2Ds by their ids
    /// @param[in] ids vector of ids of the Mask2Ds to get
    /// @param[out] masks vector of Mask2Ds stored in the Mask2D manager
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getMasks(const std::vector<uint32_t>& ids, std::vector<SRef<Mask2D>>& masks) const;

    /// @brief This method allows to get all Mask2Ds
    /// @param[out] masks set of Mask2Ds
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getAllMasks(std::vector<SRef<Mask2D>>& masks) const;

    /// @brief This method allow to suppress a Mask2D by its id
    /// @param[in] id of the Mask2D to suppress
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode suppressMask(uint32_t id);

    /// @brief This method allows to know if a Mask2D is already stored in the component
    /// @param[in] id ID of this Mask2D
    /// @return true if exist, else false
    bool isExistMask(uint32_t id) const;

    /// @brief This method allows to get the number of Mask2Ds stored in the point cloud
    /// @return the number of Mask2Ds
    size_t getNbMasks() const;

    /// @brief This method allows to clear the contents of current Mask2DCollection
    void clear();

    /// @brief save list of Mask2Ds to folder (each mask corresponds to a PNG file and a json file)
    /// @param[in] pathToFolder path to folder
    /// @return FrameworkReturnCode::_SUCCESS (saved successfully) or FrameworkReturnCode::_ERROR_ (failed to save)
    FrameworkReturnCode save(const std::string& pathToFolder) const;

    /// @brief print info
    void print() const;

private:
    /// @brief serialize
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    std::map<uint32_t, SRef<Mask2D>> m_masks;
    uint32_t m_currentId = 0;
};

DECLARESERIALIZE(Mask2DCollection);

} // datastructure 
} // SolAR

#endif // MASK2DCOLLECTION_H
