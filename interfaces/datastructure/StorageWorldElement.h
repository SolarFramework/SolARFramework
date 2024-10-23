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

#ifndef STORAGEWORLDELEMENT_H
#define STORAGEWORLDELEMENT_H

#include <xpcf/core/uuid.h>

#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/UnitSystem.h"

// -> uncomment to use text serialization for World Graph structure
//#define SOLAR_STORAGE_USE_TEXT_SERIALIZATION

// -> uncomment to use xml serialization for World Graph structure
#define SOLAR_STORAGE_USE_XML_SERIALIZATION


// Specific to World Storage Serialization
#ifdef SOLAR_STORAGE_USE_TEXT_SERIALIZATION
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using OutputStorageArchive = ::boost::archive::text_oarchive;
using InputStorageArchive = ::boost::archive::text_iarchive;
#elif defined (SOLAR_STORAGE_USE_XML_SERIALIZATION)
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
using OutputStorageArchive = ::boost::archive::xml_oarchive;
using InputStorageArchive = ::boost::archive::xml_iarchive;
#else
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
using OutputStorageArchive = ::boost::archive::binary_oarchive;
using InputStorageArchive = ::boost::archive::binary_iarchive;
#endif


#define DECLARESTORAGESERIALIZE(T) \
    extern template SOLARFRAMEWORK_API void T::serialize<OutputStorageArchive>(OutputStorageArchive &ar, const unsigned int version);\
    extern template SOLARFRAMEWORK_API void T::serialize<InputStorageArchive>(InputStorageArchive &ar, const unsigned int version);

#define IMPLEMENTSTORAGESERIALIZE(T) \
    template void T::serialize<OutputStorageArchive>(OutputStorageArchive &ar, const unsigned int version);\
    template void T::serialize<InputStorageArchive>(InputStorageArchive &ar, const unsigned int version);

// Definition of WorldElement Class //
// part of SolAR namespace //
namespace SolAR {
namespace datastructure {

///
/// @brief Enumeration of all element object types
///
enum class ElementKind : char {
    TRACKABLE,
    ANCHOR,
    INVALID
};

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
        StorageWorldElement(const org::bcom::xpcf::uuids::uuid &creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                            Vector3d size, const std::multimap<std::string, std::string> &tags, std::string name);


        /// @brief WorldElement constructor with id
        StorageWorldElement(const org::bcom::xpcf::uuids::uuid &id, const org::bcom::xpcf::uuids::uuid &creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                            Vector3d size, const std::multimap<std::string, std::string> &tags, std::string name);

        /// @brief WorldElement default destructor
        virtual ~StorageWorldElement() = default;

        ///////////////////////////
        /// GETTERS AND SETTERS ///
        ///////////////////////////

        /// @brief Getter for the id of the WorldElement object
        org::bcom::xpcf::uuids::uuid getID() const;
        /// @brief Setter for the id of the WorldElement object
        void setID(const org::bcom::xpcf::uuids::uuid &id);

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
        void setUnitSystem(const UnitSystem &newUnitSystem);

        /// @brief Getter for the dimension of the WorldElement
        Vector3d getSize() const;
        /// @brief Setter for the dimension of the WorldElement
        void setSize(const Vector3d &newSize);

        /// @brief Getter for the list of tags associated with the element
        std::multimap<std::string, std::string> getTags() const;
        /// @brief Setter for the list of tags associated with the element
        void setTags(const std::multimap<std::string, std::string> &tags);

        ///////////////
        /// METHODS ///
        ///////////////

        /// @brief Add a new tag to associate to the element
        void addTag(const std::string &key, const std::string &value);

        /// @brief removes a tag form the element
        bool removeTag(const std::string &key, const std::string &value);

        /// @brief Gets the type of worldElement ( trackable or anchor )
        virtual ElementKind getKind() = 0;

        const std::string &getName() const;
        void setName(const std::string &newName);

private:

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

    protected:

        org::bcom::xpcf::uuids::uuid m_id;
        std::string m_name;
        org::bcom::xpcf::uuids::uuid m_creatorId;
        Transform3Df m_localCRS;
        UnitSystem m_unitSystem;
        Vector3d m_size;
        std::multimap<std::string, std::string> m_tags;


};

DECLARESTORAGESERIALIZE(StorageWorldElement);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(StorageWorldElement);

}
}
#endif // STORAGEWORLDELEMENT_H
