/**
 * @copyright Copyright (c) 2021-2022 B-com http://www.b-com.com/
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

#include "core/SerializationDefinitions.h"
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/StorageWorldElement.h"
#include "datastructure/UnitSystem.h"
#include "datastructure/MathDefinitions.h"

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
        /// @brief StorageWorldLink constructor with all its attributes
        ///
        StorageWorldLink(org::bcom::xpcf::uuids::uuid author, boost::uuids::uuid uuidFrom,
                         boost::uuids::uuid uuidTo, ElementKind typeFrom, ElementKind typeTo, Transform3Df transform);

        ////////////////////////////
        /// GETTERS AND SETTERS ////
        ////////////////////////////

        /// @brief Getter for the ID of the WorldLink
        const org::bcom::xpcf::uuids::uuid &getId() const;

        /// @brief Getter for the author ID of the WorldLink
        const org::bcom::xpcf::uuids::uuid &getAuthor() const;
        /// @brief Setter for the author ID of the WorldLink
        void setAuthor(const org::bcom::xpcf::uuids::uuid &newAuthor);

        /// @brief Getter for the transform of the WorldLink
        const Transform3Df &getTransform() const;
        /// @brief Setter for the transform of the WorldLink
        void setTransform(const Transform3Df &newTransform);

        /// @brief Getter for the unitSystem of the WorldLink
        UnitSystem unitSystem() const;
        /// @brief Getter for the unitSystem of the WorldLink
        void setUnitSystem(UnitSystem newUnitSystem);

        /// @brief Getter for the tags of the WorldLink
        const std::multimap<std::string, std::string> &tags() const;
        /// @brief Getter for the tags of the WorldLink
        void setTags(const std::multimap<std::string, std::string> &newTags);

        /// @brief returns the two ids of the elements that are attached by the link
        std::pair<org::bcom::xpcf::uuids::uuid, org::bcom::xpcf::uuids::uuid> getAttachedIds() const;

        const boost::uuids::uuid &getUuidFrom() const;
        void setUuidFrom(const boost::uuids::uuid &newUuidFrom);

        const boost::uuids::uuid &getUuidTo() const;
        void setUuidTo(const boost::uuids::uuid &newUuidTo);

        ElementKind getTypeFrom() const;
        void setTypeFrom(ElementKind newTypeFrom);

        ElementKind getTypeTo() const;
        void setTypeTo(ElementKind newTypeTo);

protected:

        org::bcom::xpcf::uuids::uuid m_id;
        org::bcom::xpcf::uuids::uuid m_author;
        boost::uuids::uuid m_uuidFrom;
        boost::uuids::uuid m_uuidTo;
        ElementKind m_typeFrom;
        ElementKind m_typeTo;
        Transform3Df m_transform;
        UnitSystem m_unitSystem;
        std::multimap<std::string, std::string> m_tags;


    private:

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);



};

DECLARESERIALIZE(StorageWorldLink);

}
} // end of namespace SolAR

#endif // STORAGEWORLDLINK_H
