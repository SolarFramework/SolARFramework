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


    /// @brief this methods adds a trackable to the world graph
    /// @param author The UID of the creator of the trackable that we are looking to add to the worldgraph
    /// @param type The type of trackable that we are looking to add to the worldgraph
    /// @param encodingInfo
    /// @param payload
    /// @param LocalCrs
    /// @param unitSystem The mesurement system used for the trackable that we are looking to add to the worldgraph
    /// @param scale The dimension of the trackable that we are looking to add to the worldgraph
    /// @param tags A map where the key is an enum and the value is a string corresponding to a tag associated with the trackable that we are looking to add to the worldgraph
    /// @return the uuid of the newly created & added Trackable
    virtual org::bcom::xpcf::uuids::uuid addTrackable(org::bcom::xpcf::uuids::uuid author, datastructure::StorageTrackableType type,
                                            datastructure::EncodingInfo encodingInfo, std::vector<std::byte> payload, datastructure::Transform3Df LocalCrs,
                                            datastructure::UnitSystem unitSystem, datastructure::Vector3d scale,
                                            std::multimap<std::string, std::string> tags) = 0;


    /// @brief this methods returns from the world graph the trackable with id {trackableId}
    /// @param The Id of the Trackable that is going to be fetched
    /// @return void
    virtual SRef<datastructure::StorageTrackable> getTrackable(org::bcom::xpcf::uuids::uuid trackableId) = 0;


    /// @brief this methods deletes the trackable with id from the world graph
    /// @param The Id of the Trackable that is going to be deleted
    /// @return true if the trackable has been deleted from the worldgraph
    virtual bool removeTrackable(org::bcom::xpcf::uuids::uuid trackableId) = 0;

    /// @brief this methods returns all the trackables that are in the world graph
    /// @return a list of all the trackables that are in the world graph
    virtual std::vector<SRef<datastructure::StorageTrackable>> getTrackables() = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IWorldGraphManager,
                             "f8847b66-4bd0-48c6-ad54-e371a16fba1a",
                             "IWorldGraphManager",
                             "SolAR::api::storage::IWorldGraphManager defines the interface of a world graph manager and its representation with all its components such as trackables, worldanchors and their relations (3DF).");

#endif // IWORLDGRAPHMANAGER_H
