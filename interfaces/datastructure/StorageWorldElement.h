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
    ///
    /// @brief WorldElement default constructor
    ///
    StorageWorldElement() = default;

    ///
    /// @brief WorldElement constructor
    ///
    StorageWorldElement(std::multimap<std::string, std::string>);


    ///
    /// @brief WorldElement default destructor
    ///
    virtual ~StorageWorldElement() = default;

    /// @brief Returns the id of the WorldElement object
    /// @return the id of the WorldElement object
    org::bcom::xpcf::uuids::uuid getID() const;

    /// @brief Sets the id of the WorldElement object
    void setID(const org::bcom::xpcf::uuids::uuid & id);

    /// @brief Returns the list of tags associated with the element
    /// @return the list of tags associated with the element
    std::multimap<std::string, std::string> getTags() const;

    /// @brief Sets the list of tags associated with the element
    void setTags(std::multimap<std::string, std::string> tags);

    /// @brief Add a new tag to associate to the element
    void addTag(std::string, std::string);

    virtual bool isWorldAnchor()=0;

    virtual bool isTrackable()=0;

    private:

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

    protected:

        org::bcom::xpcf::uuids::uuid m_id;
        std::multimap<std::string, std::string> m_tags;


};

DECLARESERIALIZE(StorageWorldElement);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(StorageWorldElement);

}
}
#endif // STORAGEWORLDELEMENT_H
