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

#ifndef STORAGEWORLDELEMENT_H
#define STORAGEWORLDELEMENT_H

#include <core/SolARFrameworkDefinitions.h>
#include <datastructure/MathDefinitions.h>
#include <datastructure/UnitSystem.h>
#include <core/SerializationDefinitions.h>

#include "xpcf/core/uuid.h"
#include "core/Log.h"



// Definition of WorldElement Class //
// part of SolAR namespace //
namespace SolAR {
namespace datastructure {

/**
    * @class WorldElement
    * @brief <B>This abstract class defines the generic world element datastructure.</B>
    */
class SOLARFRAMEWORK_API StorageWorldElement
{
    public :

        ////////////////////
        /// CONSTRUCTORS ///
        ////////////////////

        /// @brief WorldElement default constructor
        StorageWorldElement() = default;

        /// @brief WorldElement constructor
        StorageWorldElement(org::bcom::xpcf::uuids::uuid creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                            Vector3d size, std::map<org::bcom::xpcf::uuids::uuid, std::pair<SRef<StorageWorldElement>, Transform3Df>> parents,
                            std::map<org::bcom::xpcf::uuids::uuid, SRef<StorageWorldElement>> children, std::multimap<std::string, std::string> tags);

        /// @brief WorldElement default destructor
        virtual ~StorageWorldElement() = default;

        ///////////////////////////
        /// GETTERS AND SETTERS ///
        ///////////////////////////

        /// @brief Getter for the id of the WorldElement object
        org::bcom::xpcf::uuids::uuid getID() const;
        /// @brief Setter for the id of the WorldElement object
        void setID(const org::bcom::xpcf::uuids::uuid & id);

        /// @brief Getter for the author ID of the WorldElement
        org::bcom::xpcf::uuids::uuid getCreatorID() const;
        /// @brief Setter for the author ID of the WorldElement
        void setCreatorID(const org::bcom::xpcf::uuids::uuid &newCreator);

        /// @brief Getter for the local reference system of the WorldElement
        Transform3Df getLocalCrs() const;
        /// @brief Setter for the local reference system of the WorldElement
        void setLocalCrs(const Transform3Df &newLocalCrs);

        /// @brief Getter for the unit system
        UnitSystem getUnitSystem() const;
        /// @brief Setter for the unit system
        void setUnitSystem(const UnitSystem newUnitSystem);

        /// @brief Getter for the dimension of the WorldElement
        Vector3d getSize() const;
        /// @brief Setter for the dimension of the WorldElement
        void setSize(const Vector3d &newSize);

        /// @brief Getter for the parent of the element
        std::map<org::bcom::xpcf::uuids::uuid, std::pair<SRef<StorageWorldElement>, Transform3Df>> getParents() const;
        /// @brief Setter for the parent of the element
        void setParents(const std::map<org::bcom::xpcf::uuids::uuid, std::pair<SRef<StorageWorldElement>, Transform3Df>> parents);

        /// @brief Getter for the children of the element
        std::map<org::bcom::xpcf::uuids::uuid, SRef<StorageWorldElement>> getChildren() const;
        /// @brief Setter for the children of the element
        void setChildren(std::map<org::bcom::xpcf::uuids::uuid, SRef<StorageWorldElement>> children);

        /// @brief Getter for the list of tags associated with the element
        std::multimap<std::string, std::string> getTags() const;
        /// @brief Setter for the list of tags associated with the element
        void setTags(const std::multimap<std::string, std::string> tags);

        ///////////////
        /// METHODS ///
        ///////////////

        /// @brief Add a new tag to associate to the element
        void addTag(std::string, std::string);

        /// @brief Add a new child to the element
        void addChild(SRef<StorageWorldElement> child);

        /// @brief Add a new parent to the element
        void addParent(SRef<StorageWorldElement> parent, Transform3Df transform);

        /// @brief removes a child from the element
        bool removeChild(org::bcom::xpcf::uuids::uuid childId);

        /// @brief removes a parent from the element
        bool removeParent(org::bcom::xpcf::uuids::uuid parentId);

        /// @brief Checks if the caller has the element with given id as a child
        bool hasChild(org::bcom::xpcf::uuids::uuid childId);

        /// @brief Checks if the caller has the element with given id as a parent
        bool hasParent(org::bcom::xpcf::uuids::uuid parentId);

        /// @brief Gets the parent with given id and the tansformation between the parent and the caller
        std::pair<SRef<StorageWorldElement>, Transform3Df> getParentWithTransform(org::bcom::xpcf::uuids::uuid parentId);

        virtual bool isWorldAnchor()=0;

        virtual bool isTrackable()=0;

    private:

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

    protected:

        org::bcom::xpcf::uuids::uuid m_id;
        org::bcom::xpcf::uuids::uuid m_creatorId;
        Transform3Df m_localCRS;
        UnitSystem m_unitSystem;
        Vector3d m_size;
        std::map<org::bcom::xpcf::uuids::uuid, std::pair<SRef<StorageWorldElement>, Transform3Df>> m_parents;
        std::map<org::bcom::xpcf::uuids::uuid, SRef<StorageWorldElement>> m_children;
        std::multimap<std::string, std::string> m_tags;


};

DECLARESERIALIZE(StorageWorldElement);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(StorageWorldElement);

}
}
#endif // STORAGEWORLDELEMENT_H
