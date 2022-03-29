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

#ifndef STORAGEWORLDLINK_H
#define STORAGEWORLDLINK_H

#include <core/SolARFrameworkDefinitions.h>
#include <core/SerializationDefinitions.h>
#include <datastructure/StorageWorldElement.h>
#include <datastructure/UnitSystem.h>
#include "datastructure/MathDefinitions.h"

#include "core/Log.h"

// Definition of StorageWorldLink Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {
/**
    * @class StorageWorldLink
    * @brief <B>This class defines the generic WorldLink datastructure.</B>
    */
class SOLARFRAMEWORK_API StorageWorldLink
{
    public:

        ////////////////////////////
        ///     CONSTRUCTORS    ////
        ////////////////////////////

        ///
        /// @brief StorageWorldLink default constructor
        ///
        StorageWorldLink() = default;

        ///
        /// @brief StorageWorldLink default destructor
        ///
        virtual ~StorageWorldLink() = default;

        ///
        /// @brief WorldAnchor constructor from abstract supertype WorldElement
        ///
        StorageWorldLink(const StorageWorldElement& elem);

        ///
        /// @brief StorageWorldLink constructor with all its attributes
        ///
        StorageWorldLink(org::bcom::xpcf::uuids::uuid author, org::bcom::xpcf::uuids::uuid fromElement,
                         org::bcom::xpcf::uuids::uuid toElement, Transform3Df transform,
                         UnitSystem unitSystem, Vector3d scale,
                         std::multimap<std::string, std::string> tags);

        ////////////////////////////
        /// GETTERS AND SETTERS ////
        ////////////////////////////

        /// @brief Returns the id of the WorldElement object
        /// @return the id of the WorldElement object
        org::bcom::xpcf::uuids::uuid getID() const;
        /// @brief Sets the id of the WorldElement object
        void setID(const org::bcom::xpcf::uuids::uuid & id);

        /// @brief Returns the list of tags associated with the element
        /// @return the list of tags associated with the element
        std::multimap<std::string, std::string> getTags() const;
        /// @brief Sets the list of tags associated with the element
        void setTags(const std::multimap<std::string, std::string> tags);

        /// @brief Getter for the author ID of the WorldLink
        const org::bcom::xpcf::uuids::uuid &getAuthor() const;
        /// @brief Setter for the author ID of the WorldLink
        void setAuthor(const org::bcom::xpcf::uuids::uuid &newAuthor);

        /// @brief Getter for the origin element ID of the WorldLink
        const org::bcom::xpcf::uuids::uuid &getFromElement() const;
        /// @brief Setter for the origin element ID of the WorldLink
        void setFromElement(const org::bcom::xpcf::uuids::uuid &newFromElement);

        /// @brief Getter for the destination element ID of the WorldLink
        const org::bcom::xpcf::uuids::uuid &getToElement() const;
        /// @brief Setter for the destination element ID of the WorldLink
        void setToElement(const org::bcom::xpcf::uuids::uuid &newToElement);

        /// @brief Getter for the transform of the WorldLink
        const Transform3Df &getTransform() const;
        /// @brief Setter for the transform of the WorldLink
        void setTransform(const Transform3Df &newTransform);

        /// @brief Getter for the unit system
        UnitSystem getUnitSystem() const;
        /// @brief Setter for the unit system
        void setUnitSystem(UnitSystem newUnitSystem);

        /// @brief Getter for the dimension of the trackable
        const Vector3d &getScale() const;
        /// @brief Setter for the dimension of the trackable
        void setScale(const Vector3d &newScale);

        /// @brief Add a new tag to associate to the element
        void addTag(std::string, std::string);

    private:

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

    protected:

        org::bcom::xpcf::uuids::uuid m_id;
        std::multimap<std::string, std::string> m_tags;
        org::bcom::xpcf::uuids::uuid m_author;
        org::bcom::xpcf::uuids::uuid m_fromElement;
        org::bcom::xpcf::uuids::uuid m_toElement;
        Transform3Df m_transform;
        UnitSystem m_unitSystem;
        Vector3d m_scale;



};

DECLARESERIALIZE(StorageWorldLink);

}
} // end of namespace SolAR

#endif // STORAGEWORLDLINK_H
