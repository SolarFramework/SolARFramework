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

#ifndef STORAGEWORLDANCHOR_H
#define STORAGEWORLDANCHOR_H

#include "core/Log.h"

#include "core/SerializationDefinitions.h"
#include "core/SolARFrameworkDefinitions.h"

#include "datastructure/MathDefinitions.h"
#include "datastructure/StorageWorldElement.h"
#include "datastructure/UnitSystem.h"

namespace SolAR {
namespace datastructure {
/**
    * @class StorageWorldAnchor
    * @brief <B>This class defines the generic WorldAnchor datastructure.</B>
    */
class SOLARFRAMEWORK_API StorageWorldAnchor : virtual public StorageWorldElement
{
public:

    ////////////////////////////
    ///     CONSTRUCTORS    ////
    ////////////////////////////

    ///
    /// @brief WorldAnchor default constructor
    ///
    StorageWorldAnchor() = default;

    ///
    /// @brief WorldAnchor default destructor
    ///
    virtual ~StorageWorldAnchor() = default;

    ///
    /// @brief WorldAnchor constructor with all its attributes (autogenerated id)
    ///
    StorageWorldAnchor(const org::bcom::xpcf::uuids::uuid &creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                       Vector3d size, const std::multimap<std::string, std::string> &tags, std::string name);

    ///
    /// @brief WorldAnchor constructor with all its attributes (given id)
    ///
    StorageWorldAnchor(const org::bcom::xpcf::uuids::uuid &id, const org::bcom::xpcf::uuids::uuid &creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                       Vector3d size, const std::multimap<std::string, std::string> &tags, std::string name);

    virtual ElementKind getKind() const override;


private:

    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version);
};

DECLARESTORAGESERIALIZE(StorageWorldAnchor);

}
} // end of namespace SolAR

#endif // STORAGEWORLDANCHOR_H
