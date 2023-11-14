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
#include "datastructure/MathDefinitions.h"

namespace SolAR {
namespace api {
namespace storage {

/**
 * @class IWorldGraphManager
 * @brief Allows to store the world graph with its components. This storage component can be accessed by processing components to share persistent data.
 * <TT>UUID: f8847b66-4bd0-48c6-ad54-e371a16fba1a</TT>
 */
class IWorldGraphManager : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IWorldGraphManager default constructor
    IWorldGraphManager() = default;

    /// @brief IWorldGraphManager default destructor
    virtual ~IWorldGraphManager() = default;

    /////////////////////////////////
    /// GRAPH INFORMATION METHODS ///
    /////////////////////////////////

    /// @brief this method returns from the world graph the relocation information
    /// @param[in] uuids: The list of all the UUID of WorldAnchors or Trackables asked and the configuration of the user.
    /// @param[in] token: The token which attest the permission of the user
    /// @param[in] capabilities: Capabilities of the user
    /// @param[out] result:  the result attest
    /// @return FrameworkReturnCode::_SUCCESS if the element was found, FrameworkReturnCode::_NOTFOUND if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getRelocationInformation(const std::vector<org::bcom::xpcf::uuids::uuid> &uuids, const std::string &token,const std::vector<datastructure::StorageCapabilities> &Capability,std::string &result) = 0;

    ////////////////////////////
    /// WORLDELEMENT METHODS ///
    ////////////////////////////

    /// @brief this method returns from the world graph the worldElement with id {worldElementId}
    /// @param[in] worldElementId: The Id of the WorldElement that is going to be fetched
    /// @param[out] worldElement:  the worldElement with id {worldElementId}
    /// @return FrameworkReturnCode::_SUCCESS if the element was found, FrameworkReturnCode::_NOTFOUND if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getWorldElement(const org::bcom::xpcf::uuids::uuid& worldElementId, SRef<datastructure::StorageWorldElement>& worldElement) = 0;

    /// @brief this method returns all the worldElements currently in the world graph
    /// @param[out] vector: a vector containing all the worldElements in the worldgraph
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldElements(std::vector<SRef<datastructure::StorageWorldElement>> &vector) = 0;

    /// @brief this method returns from the world graph all the elements with a given tag
    /// @param[in] key: the key of the tag
    /// @param[in] value: the value of the tag
    /// @param[out] vector: the elements in the world storage with the tag {key:value}
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldElementByKeyValue(const std::string &key, const std::string &value, std::vector<SRef<datastructure::StorageWorldElement>> &vector) = 0;

    /// @brief this method returns from the world graph all the elements that have a tag with a given key
    /// @param[in] key: the key of the tag
    /// @param[out] vector: the elements in the world storage with the tag {key:X}
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldElementByKey(const std::string &key, std::vector<SRef<datastructure::StorageWorldElement>> &vector) = 0;

    /////////////////////////
    /// TRACKABLE METHODS ///
    /////////////////////////

    /// @brief creates a Trackable and adds it to the worldGraph
    /// @param[out] id:  The id of the newly created and added trackable
    /// @param[in] trackable: The trackable to add in the worldgraph
    /// @return a FrameworkReturnCode succesfull if the trackable is created & added to the world storage
    virtual FrameworkReturnCode addTrackable(org::bcom::xpcf::uuids::uuid& id, SRef<datastructure::StorageTrackable> trackable) = 0;


    /// @brief this method returns from the world graph the trackable with id {trackableId}
    /// @param[in] trackableId: The Id of the Trackable that is going to be fetched
    /// @param[out] trackable: the trackable with id {trackableId}
    /// @return FrameworkReturnCode::_SUCCESS if the element is found, FrameworkReturnCode::_NOT_FOUND if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getTrackable(const org::bcom::xpcf::uuids::uuid &trackableId, SRef<datastructure::StorageTrackable> &trackable) = 0;


    /// @brief this method deletes the trackable with id {trackableId} from the world graph
    /// @param[in] trackableId: The Id of the Trackable that is going to be deleted
    /// @return FrameworkReturnCode success if the trackable has been removed from the world storage
    virtual FrameworkReturnCode removeTrackable(const org::bcom::xpcf::uuids::uuid &trackableId) = 0;

    /// @brief this method returns all the trackables that are in the world graph
    /// @param[out] vector: a vector of all the trackables that are in the world graph
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getTrackables(std::vector<SRef<datastructure::StorageTrackable>> &vector) = 0;

    /// @brief modifies a Trackable that is present in the world graph
    /// @param[out] id:  The id of the trackable to modify
    /// @param[in] trackable: The trackable to modify in the worldgraph
    /// @return a FrameworkReturnCode succesfull if the trackable is correctly modified
    virtual FrameworkReturnCode modifyTrackable(org::bcom::xpcf::uuids::uuid& id, SRef<datastructure::StorageTrackable> trackable) = 0;

    ///////////////////////////
    /// WORLDANCHOR METHODS ///
    ///////////////////////////

    /// @brief this method adds a world anchor to the world graph
    /// @param[out] id: the uuid of the newly created and added world anchor
    /// @param[in] worldAnchor: the anchor that is to be added
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode addWorldAnchor(org::bcom::xpcf::uuids::uuid& id, SRef<datastructure::StorageWorldAnchor> worldAnchor) = 0;


    /// @brief this method returns from the world graph the world anchor with id {worldAnchorId}
    /// @param[in] worldAnchorId: The Id of the world anchor that is going to be fetched
    /// @param[out] worldAnchor: the world anchor with id {worldAnchorId}
    /// @return FrameworkReturnCode::_SUCCESS if the element is found, FrameworkReturnCode::_NOT_FOUND if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getWorldAnchor(const org::bcom::xpcf::uuids::uuid &worldAnchorId, SRef<datastructure::StorageWorldAnchor>& worldAnchor) = 0;


    /// @brief this method deletes the world anchor with id {worldAnchorId} from the world graph
    /// @param[in] worldAnchorId: The Id of the world anchor that is going to be deleted
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode removeWorldAnchor(const org::bcom::xpcf::uuids::uuid &worldAnchorId) = 0;

    /// @brief this method returns all the world anchors that are in the world graph
    /// @param[out] vector: a vector of all the world anchors that are in the world graph
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldAnchors(std::vector<SRef<datastructure::StorageWorldAnchor>>& vector) = 0;

    /// @brief modifies a world anchor that is present in the world graph
    /// @param[out] id:  The id of the world anchor to modify
    /// @param[in] worldAnchor: The world anchor to modify in the worldgraph
    /// @return a FrameworkReturnCode succesfull if the world anchor is correctly modified
    virtual FrameworkReturnCode modifyWorldAnchor(org::bcom::xpcf::uuids::uuid& id, SRef<datastructure::StorageWorldAnchor> worldAnchor) = 0;

    /////////////////////////
    /// WORLDLINK METHODS ///
    /////////////////////////

    /// @brief this method adds a transfrom between two world elements
    /// @param[out] id: the uuid of the newly created and added world link
    /// @param[in] worldLink: the worldLink that we want to add to the worldStorage
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode addWorldLink(org::bcom::xpcf::uuids::uuid& id, SRef<datastructure::StorageWorldLink> worldLink) = 0;


    /// @brief this method returns from the world graph the worldLink connecting the two elements given as parameters
    /// @param[in] parentId: the UID of the parent world element
    /// @param[in] childId: the UID of the child world element
    /// @param[out] worldLink: the worldLink connecting the two elements given as parameters
    /// @return FrameworkReturnCode::_SUCCESS if the element is found, FrameworkReturnCode::_NOT_FOUND if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getWorldLink(const org::bcom::xpcf::uuids::uuid &parentId, const org::bcom::xpcf::uuids::uuid &childId, SRef<datastructure::StorageWorldLink> &worldLink) = 0;


    /// @brief this method returns from the world graph the worldLink with the given ID
    /// @param[in] linkId: the UID of the link that is to be deleted
    /// @param[out] worldLink: the worldLink with the given ID
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldLink(const org::bcom::xpcf::uuids::uuid &linkId, SRef<datastructure::StorageWorldLink> &worldLink) = 0;


    /// @brief this method deletes from the world graph the transform between two given world elements
    /// @param[in] parentId: the UID of the parent world element
    /// @param[in] childId: the UID of the child world element
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode removeWorldLink(const org::bcom::xpcf::uuids::uuid &parentId, const org::bcom::xpcf::uuids::uuid &childId) = 0;


    /// @brief this method deletes from the world graph the transform between two given world elements
    /// @param[in] linkId: the UID of the link that is to be deleted
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode removeWorldLink(const org::bcom::xpcf::uuids::uuid &linkId) = 0;

    /// @brief this method returns all the world links that are in the world graph
    /// @param[out] vector: a vector of all the world links that are in the world graph
    /// @return FrameworkReturnCode::_SUCCESS if there was no error
    virtual FrameworkReturnCode getWorldLinks(std::vector<SRef<datastructure::StorageWorldLink>> &vector) = 0;

    /// @brief modifies a world link that is present in the world graph
    /// @param[out] id:  The id of the world link to modify
    /// @param[in] worldLink: The world link to modify in the worldgraph
    /// @return a FrameworkReturnCode succesfull if the world link is correctly modified
    virtual FrameworkReturnCode modifyWorldLink(org::bcom::xpcf::uuids::uuid& id, SRef<datastructure::StorageWorldLink> worldLink) = 0;


};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IWorldGraphManager,
                             "f8847b66-4bd0-48c6-ad54-e371a16fba1a",
                             "IWorldGraphManager",
                             "SolAR::api::storage::IWorldGraphManager defines the interface of a world graph manager and its representation with all its components such as trackables, worldanchors and their relations (3DF).");

#endif // IWORLDGRAPHMANAGER_H
