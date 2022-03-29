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

    /////////////////////////////
    /// WORLDELEMENT METHODS ////
    /////////////////////////////

    /// @brief this methods returns from the world graph the worldElement with id {worldElementId}
    /// @param worldElementId : The Id of the WorldElement that is going to be fetched
    /// @return the worldElement with id {worldElementId}
    virtual SRef<datastructure::StorageWorldElement> getWorldElement(org::bcom::xpcf::uuids::uuid worldElementId) = 0;


    /// @brief this methods returns all the world graph the worldElement currently in the world graph
    /// @return all the worldElements in the worldgrpah
    virtual std::vector<SRef<datastructure::StorageWorldElement>> getWorldElements() = 0;

    //////////////////////////
    /// TRACKABLE METHODS ////
    //////////////////////////


    /// @brief creates a Trackable and adds it to the worldGraph
    /// @param author : The id of the trackable creator
    /// @param type : the trackable type
    /// @param encodingInfo : The information given to decode the trackable and extract its features
    /// @param payload : the buffer in wich the trackables informations are stored
    /// @param localCrs : the local reference system
    /// @param unitSystem : the system of measurement unit used for the trackable
    /// @param scale : the dimensions of the trackable
    /// @param tags : a list of tags associated with a key (e.g. : {<Author, nchambron>, <Date, 25/10/2021>}
    /// @return the ID of the newly created & added trackable
    virtual org::bcom::xpcf::uuids::uuid addTrackable(org::bcom::xpcf::uuids::uuid author, datastructure::StorageTrackableType type,
                                            datastructure::EncodingInfo encodingInfo, std::vector<std::byte> payload, datastructure::Transform3Df LocalCrs,
                                            datastructure::UnitSystem unitSystem, datastructure::Vector3d scale,
                                            std::multimap<std::string, std::string> tags) = 0;


    /// @brief this methods returns from the world graph the trackable with id {trackableId}
    /// @param trackableId : The Id of the Trackable that is going to be fetched
    /// @return the trackable with id {trackableId}
    virtual SRef<datastructure::StorageTrackable> getTrackable(org::bcom::xpcf::uuids::uuid trackableId) = 0;


    /// @brief this methods deletes the trackable with id {trackableId} from the world graph
    /// @param trackableId : The Id of the Trackable that is going to be deleted
    /// @return true if the trackable has been deleted from the worldgraph
    virtual bool removeTrackable(org::bcom::xpcf::uuids::uuid trackableId) = 0;

    /// @brief this methods returns all the trackables that are in the world graph
    /// @return a vector of all the trackables that are in the world graph
    virtual std::vector<SRef<datastructure::StorageTrackable>> getTrackables() = 0;

    ////////////////////////////
    /// WORLDANCHOR METHODS ////
    ////////////////////////////

    /// @brief this methods adds a world anchor to the world graph
    /// @param author : The UID of the creator of the world anchor that we are looking to add to the worldgraph
    /// @param localCrs : the local reference system
    /// @param unitSystem : The mesurement system used for the world anchor that we are looking to add to the worldgraph
    /// @param scale : The dimension of the world anchor that we are looking to add to the worldgraph
    /// @param tags : A map where the key is an enum and the value is a string corresponding to a tag associated with the world anchor that we are looking to add to the worldgraph
    /// @return the uuid of the newly created & added world anchor
    virtual org::bcom::xpcf::uuids::uuid addWorldAnchor(org::bcom::xpcf::uuids::uuid authorID, datastructure::Transform3Df localCrs,
                                                      datastructure::UnitSystem unitSystem, datastructure::Vector3d scale,
                                                      std::multimap<std::string, std::string> tags) = 0;


    /// @brief this methods returns from the world graph the world anchor with id {worldAnchorId}
    /// @param worldAnchorId : The Id of the world anchor that is going to be fetched
    /// @return the world anchor with id {worldAnchorId}
    virtual SRef<datastructure::StorageWorldAnchor> getWorldAnchor(org::bcom::xpcf::uuids::uuid worldAnchorId) = 0;


    /// @brief this methods deletes the world anchor with id {worldAnchorId} from the world graph
    /// @param worldAnchorId : The Id of the world anchor that is going to be deleted
    /// @return true if the world anchor has been deleted from the worldgraph
    virtual bool removeWorldAnchor(org::bcom::xpcf::uuids::uuid worldAnchorId) = 0;

    /// @brief this methods returns all the world anchors that are in the world graph
    /// @return a vector of all the world anchors that are in the world graph
    virtual std::vector<SRef<datastructure::StorageWorldAnchor>> getWorldAnchors() = 0;

    //////////////////////////
    /// WORLDLINK METHODS ////
    //////////////////////////

    /// @brief this methods adds a world link to the world graph
    /// @param author : The UID of the creator of the world link that we are looking to add to the worldgraph
    /// @param fromElement : The UID of the WorldElement that our world link originates from
    /// @param fromElement : The UID of the WorldElement that our world link targets
    /// @param transform : The transformation between the two world elements
    /// @param unitSystem : The mesurement system used for the world link that we are looking to add to the worldgraph
    /// @param scale : The dimension of the world link that we are looking to add to the worldgraph
    /// @param tags : A map where the key is an enum and the value is a string corresponding to a tag associated with the world link that we are looking to add to the worldgraph
    /// @return the uuid of the newly created & added world link
    virtual org::bcom::xpcf::uuids::uuid addWorldLink(org::bcom::xpcf::uuids::uuid authorID, org::bcom::xpcf::uuids::uuid fromElementID,
                                                      org::bcom::xpcf::uuids::uuid toElementID, datastructure::Transform3Df transform,
                                                      datastructure::UnitSystem unitSystem, datastructure::Vector3d scale,
                                                      std::multimap<std::string, std::string> tags) = 0;


    /// @brief this methods returns from the world graph the world link with id {worldLinkId}
    /// @param worldLinkId : The Id of the world link that is going to be fetched
    /// @return the world link with id {worldLinkId}
    virtual SRef<datastructure::StorageWorldLink> getWorldLink(org::bcom::xpcf::uuids::uuid worldLinkId) = 0;


    /// @brief this methods deletes the world link with id {worldLinkId} from the world graph
    /// @param worldLinkId : The Id of the world link that is going to be deleted
    /// @return true if the world link has been deleted from the worldgraph
    virtual bool removeWorldLink(org::bcom::xpcf::uuids::uuid worldLinkId) = 0;

    /// @brief this methods returns all the world links that are in the world graph
    /// @return a vector of all the world links that are in the world graph
    virtual std::vector<SRef<datastructure::StorageWorldLink>> getWorldLinks() = 0;

    /// @brief this methods returns the elements that are connected to a given world link
    /// @return a vector of the 2 elements that are connected to the worldLink (in position 0 the element where it comes from, in position 1 the element to which its pointing), if there is only one element,
    ///     it means that the two worldElements (or one of them) were not found in the worldGraph, if the vector is empty it means that the worldLink was not found in the worldGraph
    virtual std::vector<SRef<datastructure::StorageWorldElement>> getConnectedElements(org::bcom::xpcf::uuids::uuid worldLinkId) = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IWorldGraphManager,
                             "f8847b66-4bd0-48c6-ad54-e371a16fba1a",
                             "IWorldGraphManager",
                             "SolAR::api::storage::IWorldGraphManager defines the interface of a world graph manager and its representation with all its components such as trackables, worldanchors and their relations (3DF).");

#endif // IWORLDGRAPHMANAGER_H
