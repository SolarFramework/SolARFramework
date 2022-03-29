/**
 * @copyright Copyright (c) 2020 B-com http://www.b-com.com/
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

#include <core/SolARFrameworkDefinitions.h>
#include <core/SerializationDefinitions.h>
#include <datastructure/StorageWorldElement.h>
#include <datastructure/UnitSystem.h>
#include "datastructure/MathDefinitions.h"

#include "core/Log.h"

// Definition of StorageWorldAnchor Class //
// part of SolAR namespace //

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
        /// @brief WorldAnchor constructor from abstract supertype WorldElement
        ///
        StorageWorldAnchor(const StorageWorldElement& elem) : StorageWorldElement(elem) {};

        ///
        /// @brief WorldAnchor constructor with all its attributes
        ///
        StorageWorldAnchor(org::bcom::xpcf::uuids::uuid author, Transform3Df localCrs,
                           UnitSystem unitSystem, Vector3d scale,
                           std::multimap<std::string, std::string> tags);

        ////////////////////////////
        /// GETTERS AND SETTERS ////
        ////////////////////////////

        /// @brief Getter for the author ID of the Anchor
        const org::bcom::xpcf::uuids::uuid &getAuthor() const;
        /// @brief Setter for the author ID of the Anchor
        void setAuthor(const org::bcom::xpcf::uuids::uuid &newAuthor);

        /// @brief Getter for the local reference system of the Anchor
        const Transform3Df &getLocalCrs() const;
        /// @brief Setter for the local reference system of the Anchor
        void setLocalCrs(const Transform3Df &newLocalCrs);

        /// @brief Getter for the unit system
        UnitSystem getUnitSystem() const;
        /// @brief Setter for the unit system
        void setUnitSystem(UnitSystem newUnitSystem);

        /// @brief Getter for the dimension of the trackable
        const Vector3d &getScale() const;
        /// @brief Setter for the dimension of the trackable
        void setScale(const Vector3d &newScale);

        bool isWorldAnchor() override;

        bool isTrackable() override;


    private:

        org::bcom::xpcf::uuids::uuid m_author;
        Transform3Df m_LocalCrs;
        UnitSystem m_unitSystem;
        Vector3d m_scale;

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

    protected:
};

DECLARESERIALIZE(StorageWorldAnchor);

}
} // end of namespace SolAR

#endif // STORAGEWORLDANCHOR_H
