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

#ifndef IWORLDGRAPHMANAGER_H
#define IWORLDGRAPHMANAGER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/uuid.h>

#include "core/Messages.h"
#include "datastructure/StorageCapabilities.h"
#include "datastructure/StorageWorldElement.h"
#include "datastructure/StorageTrackable.h"
#include "datastructure/StorageWorldAnchor.h"
#include "datastructure/StorageWorldLink.h"
#include "datastructure/RelocalizationInformation.h"
#include "datastructure/MathDefinitions.h"

namespace SolAR {
namespace api {
namespace storage {

/**
 * @class IWorldGraphManager
 * @brief Allows to store the world graph with its components. This storage component can be accessed by processing components to share persistent data.
 * <TT>UUID: f8847b66-4bd0-48c6-ad54-e371a16fba1a</TT>
 */
class XPCF_IGNORE
    IWorldGraphManager : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IWorldGraphManager default constructor
    IWorldGraphManager() = default;

    /// @brief IWorldGraphManager default destructor
    virtual ~IWorldGraphManager() = default;

    /////////////////////////////////
    /// GRAPH INFORMATION METHODS ///
    /////////////////////////////////

    /// @brief this method returns from the world graph the relocation information
    /// @param[in] uuids The list of all the UUID of WorldAnchors or Trackables asked and the configuration of the user.
    /// @param[in] token The token which attest the permission of the user
    /// @param[in] capabilities Capabilities of the user
    /// @param[out] result All relocalization (trackable and corresponding 3D transform) which can be used to relocalize the input WorldAnchors.
    /// @return FrameworkReturnCode::_SUCCESS if the element was found, FrameworkReturnCode::_NOTFOUND if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getRelocalizationInformation(const std::vector<std::tuple<org::bcom::xpcf::uuids::uuid,bool>> &uuids, const std::string &token,const std::vector<SolAR::datastructure::StorageCapabilities> &capability, std::vector<SolAR::datastructure::RelocalizationInformation> &relocalizationInformation ) const = 0;

    ////////////////////////////
    /// WORLDELEMENT METHODS ///
    ////////////////////////////

    /// @brief this method returns from the world graph the worldElement with id {worldElementId}
    /// @param[in] worldElementId The Id of the WorldElement that is going to be fetched
    /// @param[out] worldElement  the worldElement with id {worldElementId}
    /// @return FrameworkReturnCode::_SUCCESS if the element was found, FrameworkReturnCode::_NOTFOUND if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getWorldElement(const org::bcom::xpcf::uuids::uuid& worldElementId, SRef<SolAR::datastructure::StorageWorldElement>& worldElement) const = 0;

    /// @brief this method returns all the worldElements currently in the world graph
    /// @param[out] worldElements a vector containing all the worldElements in the worldgraph
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldElements(std::vector<SRef<SolAR::datastructure::StorageWorldElement>> &worldElements) const = 0;

    /// @brief this method returns from the world graph all the elements with a given tag
    /// @param[in] key the key of the tag
    /// @param[in] value the value of the tag
    /// @param[out] worldElements the worldElements in the world storage with the tag {key:value}
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldElementsByKeyValue(const std::string &key, const std::string &value, std::vector<SRef<SolAR::datastructure::StorageWorldElement>> &worldElements) const = 0;

    /// @brief this method returns from the world graph all the elements that have a tag with a given key
    /// @param[in] key the key of the tag
    /// @param[out] worldElements the worldElements in the world storage with the tag {key:X}
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldElementsByKey(const std::string &key, std::vector<SRef<SolAR::datastructure::StorageWorldElement>> &worldElements) const = 0;

    /////////////////////////
    /// TRACKABLE METHODS ///
    /////////////////////////

    /// @brief creates a Trackable and adds it to the worldGraph
    /// @param[in] trackable: The trackable to add in the worldgraph
    /// @param[out] id The id of the newly created and added trackable
    /// @return a FrameworkReturnCode succesfull if the trackable is created & added to the world storage
    virtual FrameworkReturnCode addTrackable(SRef<SolAR::datastructure::StorageTrackable> trackable, org::bcom::xpcf::uuids::uuid& id) = 0;


    /// @brief this method returns from the world graph the trackable with id {trackableId}
    /// @param[in] trackableId The Id of the Trackable that is going to be fetched
    /// @param[out] trackable the trackable with id {trackableId}
    /// @return FrameworkReturnCode::_SUCCESS if the element is found, FrameworkReturnCode::_NOT_FOUND if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getTrackable(const org::bcom::xpcf::uuids::uuid &trackableId, SRef<SolAR::datastructure::StorageTrackable> &trackable) const = 0;


    /// @brief this method deletes the trackable with id {trackableId} from the world graph
    /// @param[in] trackableId The Id of the Trackable that is going to be deleted
    /// @return FrameworkReturnCode::_SUCCESS if the trackable is correctly removed, FrameworkReturnCode::_NOT_FOUND if the trackable was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode removeTrackable(const org::bcom::xpcf::uuids::uuid &trackableId) = 0;

    /// @brief this method returns all the trackables that are in the world graph
    /// @param[out] vector a vector of all the trackables that are in the world graph
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getTrackables(std::vector<SRef<SolAR::datastructure::StorageTrackable>> &vector) const = 0;

    /// @brief modifies a Trackable that is present in the world graph
    /// @param[in] trackable: The trackable to modify in the worldgraph
    /// @param[out] id  The id of the trackable to modify
    /// @return FrameworkReturnCode::_SUCCESS if the trackable is correctly modified, FrameworkReturnCode::_NOT_FOUND if the trackable was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode modifyTrackable(SRef<SolAR::datastructure::StorageTrackable> trackable, org::bcom::xpcf::uuids::uuid& id) = 0;

    ///////////////////////////
    /// WORLDANCHOR METHODS ///
    ///////////////////////////

    /// @brief this method adds a world anchor to the world graph
    /// @param[in] worldAnchor: the anchor that is to be added
    /// @param[out] id the uuid of the newly created and added world anchor
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode addWorldAnchor(SRef<SolAR::datastructure::StorageWorldAnchor> worldAnchor, org::bcom::xpcf::uuids::uuid& id) = 0;

    /// @brief this method returns from the world graph the world anchor with id {worldAnchorId}
    /// @param[in] worldAnchorId The Id of the world anchor that is going to be fetched
    /// @param[out] worldAnchor the world anchor with id {worldAnchorId}
    /// @return FrameworkReturnCode::_SUCCESS if the element is found, FrameworkReturnCode::_NOT_FOUND if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getWorldAnchor(const org::bcom::xpcf::uuids::uuid &worldAnchorId, SRef<SolAR::datastructure::StorageWorldAnchor>& worldAnchor) const = 0;


    /// @brief this method deletes the world anchor with id {worldAnchorId} from the world graph
    /// @param[in] worldAnchorId The Id of the world anchor that is going to be deleted
    /// @return FrameworkReturnCode::_SUCCESS if the world Anchor is correctly removed, FrameworkReturnCode::_NOT_FOUND if the world Anchor was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode removeWorldAnchor(const org::bcom::xpcf::uuids::uuid &worldAnchorId) = 0;

    /// @brief this method returns all the world anchors that are in the world graph
    /// @param[out] vector a vector of all the world anchors that are in the world graph
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldAnchors(std::vector<SRef<SolAR::datastructure::StorageWorldAnchor>>& vector) const = 0;

    /// @brief modifies a world anchor that is present in the world graph
    /// @param[in] worldAnchor The world anchor to modify in the worldgraph
    /// @param[out] id  The id of the world anchor to modify
    /// @return a FrameworkReturnCode succesfull if the world anchor is correctly modified
    /// @return FrameworkReturnCode::_SUCCESS if the world Anchor is correctly modified, FrameworkReturnCode::_NOT_FOUND if the world Anchor was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode modifyWorldAnchor(SRef<SolAR::datastructure::StorageWorldAnchor> worldAnchor, org::bcom::xpcf::uuids::uuid& id) = 0;

    /////////////////////////
    /// WORLDLINK METHODS ///
    /////////////////////////

    /// @brief this method adds a transform between two world elements
    /// @param[in] worldLink the worldLink that we want to add to the worldStorage
    /// @param[out] id the uuid of the newly created and added world link
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode addWorldLink(SRef<SolAR::datastructure::StorageWorldLink> worldLink, org::bcom::xpcf::uuids::uuid& id) = 0;


    /// @brief this method returns from the world graph the worldLink connecting the two elements given as parameters
    /// @param[in] parentId the UID of the parent world element
    /// @param[in] childId the UID of the child world element
    /// @param[out] worldLink the worldLink connecting the two elements given as parameters
    /// @return FrameworkReturnCode::_SUCCESS if the element is found, FrameworkReturnCode::_NOT_FOUND if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getWorldLink(const org::bcom::xpcf::uuids::uuid &parentId, const org::bcom::xpcf::uuids::uuid &childId, SRef<SolAR::datastructure::StorageWorldLink> &worldLink) const = 0;


    /// @brief this method returns from the world graph the worldLink with the given ID
    /// @param[in] linkId the UID of the link that is to be deleted
    /// @param[out] worldLink the worldLink with the given ID
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldLink(const org::bcom::xpcf::uuids::uuid &linkId, SRef<SolAR::datastructure::StorageWorldLink> &worldLink) const = 0;


    /// @brief this method deletes from the world graph the transform between two given world elements
    /// @param[in] parentId the UID of the parent world element
    /// @param[in] childId the UID of the child world element
    /// @return FrameworkReturnCode::_SUCCESS if the world link is correctly removed, FrameworkReturnCode::_NOT_FOUND if the world link was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode removeWorldLink(const org::bcom::xpcf::uuids::uuid &parentId, const org::bcom::xpcf::uuids::uuid &childId) = 0;


    /// @brief this method deletes from the world graph the transform between two given world elements
    /// @param[in] linkId the UID of the link that is to be deleted
    /// @return FrameworkReturnCode::_SUCCESS if the world link is correctly removed, FrameworkReturnCode::_NOT_FOUND if the world link was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode removeWorldLink(const org::bcom::xpcf::uuids::uuid &linkId) = 0;

    /// @brief this method returns all the world links that are in the world graph
    /// @param[out] vector a vector of all the world links that are in the world graph
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldLinks(std::vector<SRef<SolAR::datastructure::StorageWorldLink>> &vector) const = 0;

    /// @brief modifies a world link that is present in the world graph
    /// @param[in] worldLink The world link to modify in the worldgraph
    /// @param[out] id  The id of the world link to modify
    /// @return FrameworkReturnCode::_SUCCESS if the world link is correctly modified, FrameworkReturnCode::_NOT_FOUND if the world link was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode modifyWorldLink(SRef<SolAR::datastructure::StorageWorldLink> worldLink, org::bcom::xpcf::uuids::uuid& id) = 0;

    /// @brief Save the World Graph to the external file
    /// @return FrameworkReturnCode::_SUCCESS_ if the backup succeeds, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode saveToFile() const = 0;

    /// @brief Load the World Graph from the external file
    /// @return FrameworkReturnCode::_SUCCESS_ if the loading succeeds, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode loadFromFile() = 0;

    /// @brief Delete the World Graph in external file
    /// @return FrameworkReturnCode::_SUCCESS_ if the deletion succeeds, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode deleteFile() = 0;


};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IWorldGraphManager,
                             "f8847b66-4bd0-48c6-ad54-e371a16fba1a",
                             "IWorldGraphManager",
                             "SolAR::api::storage::IWorldGraphManager defines the interface of a world graph manager and its representation with all its components such as trackables, worldanchors and their relations (3DF).");

#endif // IWORLDGRAPHMANAGER_H
