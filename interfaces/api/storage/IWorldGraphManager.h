/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
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

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/StorageWorldElement.h"
#include "datastructure/StorageTrackable.h"
#include "datastructure/StorageWorldAnchor.h"
#include "datastructure/StorageWorldLink.h"
#include "datastructure/MathDefinitions.h"
#include <xpcf/core/uuid.h>

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

    ////////////////////////////
    /// WORLDELEMENT METHODS ///
    ////////////////////////////

    /// @brief this methods returns from the world graph the worldElement with id {worldElementId}
    /// @param worldElementId : The Id of the WorldElement that is going to be fetched
    /// @param[out] worldElement :  the worldElement with id {worldElementId}
    /// @return FrameworkReturnCode::_SUCCESS if the element was found, FrameworkReturnCode::_NOTIMPLEMENTED if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getWorldElement(org::bcom::xpcf::uuids::uuid worldElementId, SRef<datastructure::StorageWorldElement>& worldElement) = 0;

    /// @brief this methods returns all the world graph the worldElement currently in the world graph
    /// @param[out] vector : a vector containing all the worldElements in the worldgraph
    /// @return FrameworkReturnCode::_SUCCESS
    virtual FrameworkReturnCode getWorldElements(std::vector<SRef<datastructure::StorageWorldElement>> &vector) = 0;

    /////////////////////////
    /// TRACKABLE METHODS ///
    /////////////////////////

    /// @brief creates a Trackable and adds it to the worldGraph
    /// @param[out] id :  The id of the newly created & added trackable
    /// @param creatorId : The id of the trackable creator
    /// @param localCrs : the local reference system
    /// @param unitSystem : the system of measurement unit used for the trackable
    /// @param size : the dimensions of the trackable
    /// @param parents : the world elements that are parents of the trackable taht we want to add
    /// @param children : the world elements that are children of the trackable taht we want to add
    /// @param tags : a list of tags associated with a key (e.g. : {<Author, nchambron>, <Date, 25/10/2021>}
    /// @param type : the trackable type
    /// @param encodingInfo : The information given to decode the trackable and extract its features
    /// @param payload : the buffer in wich the trackables informations are stored
    /// @return A FrameworkReturnCode succesfull if the trackable is created & added tot he world storage
    virtual FrameworkReturnCode addTrackable(org::bcom::xpcf::uuids::uuid& id,org::bcom::xpcf::uuids::uuid creatorId, datastructure::Transform3Df localCRS, datastructure::UnitSystem unitSystem,
                                                      datastructure::Vector3d size, std::map<org::bcom::xpcf::uuids::uuid, std::pair<SRef<datastructure::StorageWorldElement>, datastructure::Transform3Df>> parents,
                                                      std::map<org::bcom::xpcf::uuids::uuid, SRef<datastructure::StorageWorldElement>> children, std::multimap<std::string, std::string> tags,
                                                      datastructure::StorageTrackableType type, datastructure::EncodingInfo encodingInfo, std::vector<std::byte> payload) = 0;


    /// @brief this methods returns from the world graph the trackable with id {trackableId}
    /// @param trackableId : The Id of the Trackable that is going to be fetched
    /// @param[out] trackable : the trackable with id {trackableId}
    /// @return FrameworkReturnCode::_SUCCESS if the trackable is found, FrameworkReturnCode::_NOTIMPLEMENTED if the element was not found, FrameworkReturnCode::_ERROR_ if something went wrong
    virtual FrameworkReturnCode getTrackable(org::bcom::xpcf::uuids::uuid trackableId, SRef<datastructure::StorageTrackable> &trackable) = 0;


    /// @brief this methods deletes the trackable with id {trackableId} from the world graph
    /// @param trackableId : The Id of the Trackable that is going to be deleted
    /// @return FrameworkReturnCode success if the trackable has been removed from the world storage
    virtual FrameworkReturnCode removeTrackable(org::bcom::xpcf::uuids::uuid trackableId) = 0;

    /// @brief this methods returns all the trackables that are in the world graph
    /// @param[out] vector : a vector of all the trackables that are in the world graph
    /// @return FrameworkReturnCode success if no exception has been raised
    virtual FrameworkReturnCode getTrackables(std::vector<SRef<datastructure::StorageTrackable>> &vector) = 0;

    ///////////////////////////
    /// WORLDANCHOR METHODS ///
    ///////////////////////////

    /// @brief this methods adds a world anchor to the world graph
    /// @param[out] id : the uuid of the newly created & added world anchor
    /// @param creatorId : The UID of the creator of the world anchor that we are looking to add to the worldgraph
    /// @param localCrs : the local reference system
    /// @param unitSystem : The mesurement system used for the world anchor that we are looking to add to the worldgraph
    /// @param size : The dimension of the world anchor that we are looking to add to the worldgraph
    /// @param parents : the world elements that are parents of the anchor taht we want to add
    /// @param children : the world elements that are children of the anchor taht we want to add
    /// @param tags : A map where the key is an enum and the value is a string corresponding to a tag associated with the world anchor that we are looking to add to the worldgraph
    /// @return FrameworkReturnCode success if no exception has been raised
    virtual FrameworkReturnCode addWorldAnchor(org::bcom::xpcf::uuids::uuid& id, org::bcom::xpcf::uuids::uuid creatorId, datastructure::Transform3Df localCRS, datastructure::UnitSystem unitSystem,
                                                        datastructure::Vector3d size, std::map<org::bcom::xpcf::uuids::uuid, std::pair<SRef<datastructure::StorageWorldElement>, datastructure::Transform3Df>> parents,
                                                        std::map<org::bcom::xpcf::uuids::uuid, SRef<datastructure::StorageWorldElement>> children, std::multimap<std::string, std::string> tags) = 0;


    /// @brief this methods returns from the world graph the world anchor with id {worldAnchorId}
    /// @param worldAnchorId : The Id of the world anchor that is going to be fetched
    /// @param[out] worldAnchor : the world anchor with id {worldAnchorId}
    /// @return FrameworkReturnCode success if no exception has been raised
    virtual FrameworkReturnCode getWorldAnchor(org::bcom::xpcf::uuids::uuid worldAnchorId, SRef<datastructure::StorageWorldAnchor>& worldAnchor) = 0;


    /// @brief this methods deletes the world anchor with id {worldAnchorId} from the world graph
    /// @param worldAnchorId : The Id of the world anchor that is going to be deleted
    /// @return FrameworkReturnCode success if no exception has been raised
    virtual FrameworkReturnCode removeWorldAnchor(org::bcom::xpcf::uuids::uuid worldAnchorId) = 0;

    /// @brief this methods returns all the world anchors that are in the world graph
    /// @param[out] vector : a vector of all the world anchors that are in the world graph
    /// @return FrameworkReturnCode success if no exception has been raised
    virtual FrameworkReturnCode getWorldAnchors(std::vector<SRef<datastructure::StorageWorldAnchor>>& vector) = 0;

    /////////////////////////
    /// WORLDLINK METHODS ///
    /////////////////////////

    /// @brief this methods adds a transfrom between two world elements
    /// @param[out] id : the uuid of the newly created & added world link
    /// @param parentId : The UID of the parent world element
    /// @param childId : The UID of the child world element
    /// @param transform : The transform between the two elements
    /// @return FrameworkReturnCode success if no exception has been raised
    virtual FrameworkReturnCode addWorldLink(org::bcom::xpcf::uuids::uuid& id, org::bcom::xpcf::uuids::uuid authorId, org::bcom::xpcf::uuids::uuid parentId, org::bcom::xpcf::uuids::uuid childId, datastructure::Transform3Df transform) = 0;


    /// @brief this methods returns from the world graph the worldLink connecting the two elements given as parameters
    /// @param parentId : The UID of the parent world element
    /// @param childId : The UID of the child world element
    /// @param[out] worldLink : The worldLink connecting the two elements given as parameters
    /// @return FrameworkReturnCode success if no exception has been raised
    virtual FrameworkReturnCode getWorldLink(org::bcom::xpcf::uuids::uuid parentId, org::bcom::xpcf::uuids::uuid childId, SRef<datastructure::StorageWorldLink>& worldLink) = 0;


    /// @brief this methods returns from the world graph the worldLink with the given ID
    /// @param linkId : The UID of the link that is to be deleted
    /// @param[out] worldLink : The worldLink with the given ID
    /// @return FrameworkReturnCode success if no exception has been raised
    virtual FrameworkReturnCode getWorldLink(org::bcom::xpcf::uuids::uuid linkId, SRef<datastructure::StorageWorldLink> &worldLink) = 0;


    /// @brief this methods deletes from the world graph the transform between two given world elements
    /// @param parentId : The UID of the link that is to be deleted
    /// @return FrameworkReturnCode success if no exception has been raised
    virtual FrameworkReturnCode removeWorldLink(org::bcom::xpcf::uuids::uuid linkId) = 0;

    /// @brief this methods returns all the world links that are in the world graph
    /// @param[out] vector : a vector of all the world links that are in the world graph
    /// @return FrameworkReturnCode success if no exception has been raised
    virtual FrameworkReturnCode getWorldLinks(std::vector<SRef<datastructure::StorageWorldLink>> &vector) = 0;



};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IWorldGraphManager,
                             "f8847b66-4bd0-48c6-ad54-e371a16fba1a",
                             "IWorldGraphManager",
                             "SolAR::api::storage::IWorldGraphManager defines the interface of a world graph manager and its representation with all its components such as trackables, worldanchors and their relations (3DF).");

#endif // IWORLDGRAPHMANAGER_H
