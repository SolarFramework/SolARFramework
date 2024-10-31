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

#ifndef RELOCALIZATIONINFORMATION_H
#define RELOCALIZATIONINFORMATION_H

#include <nlohmann/json.hpp>
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/StorageTrackable.h"

namespace SolAR {
namespace datastructure {

///
/// @brief The RelocObject struct
///
class SOLARFRAMEWORK_API RelocObject {

public:

    RelocObject() = default;

    RelocObject(const datastructure::StorageTrackable &trackable, const Transform3Df &transform3D){
        m_trackable = trackable;
        m_transform3D = transform3D;
    }

    Transform3Df getTransform3D() const{
        return m_transform3D;
    }

    datastructure::StorageTrackable getTrackable() const{
        return m_trackable;
    }

    void setTrackable(const datastructure::StorageTrackable &trackable){
        m_trackable = trackable;
    }

    void setTransform3D(const Transform3Df &transform3D){
        m_transform3D = transform3D;
    }

private:

    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version);

protected:

    datastructure::StorageTrackable m_trackable;
    Transform3Df m_transform3D;
};


/**
        * @class StorageCapabilities
        * @brief <B>This class defines the generic RelocalizationInformation datastructure.</B>
        */
class SOLARFRAMEWORK_API RelocalizationInformation
{
public:

    ////////////////////////////
    ///     CONSTRUCTORS    ////
    ////////////////////////////

    ///
    /// @brief RelocalizationInformation default constructor
    ///
    RelocalizationInformation() = default;

    ///
    /// @brief RelocalizationInformation default destructor
    ///
    virtual ~RelocalizationInformation() = default;

    //
    /// @brief RelocalizationInformation constructor with all its attributes
    ///
    RelocalizationInformation(const org::bcom::xpcf::uuids::uuid &rootUUID,const std::vector<RelocObject> relocObjects, const bool deviceToWorldAnchor);

    ////////////////////////////
    /// GETTERS AND SETTERS ////
    ////////////////////////////

    ///
    /// @brief Getter for the rootUUID
    ///
    org::bcom::xpcf::uuids::uuid getRootUUID() const;

    ///
    /// @brief Setter for the rootUUID
    ///
    void setRootUUID(org::bcom::xpcf::uuids::uuid uuid);

    ///
    /// @brief Getter for the RelocObjects
    ///
    const std::vector<RelocObject> getRelocObjects() const;

    ///
    /// @brief Setter for the RelocObjects
    ///
    void setRelocObjects(std::vector<RelocObject> NewRelocObjects);

    ///
    /// @brief Inform if the relocalization informations are given from the Device to the World Anchor or inversely
    ///
    bool isDeviceToWorldAnchor() const;

    ///
    /// @brief Set if the relocalization informations are given from the Device to the World Anchor or inversely
    ///
    void setDeviceToWorldAnchor(bool newDeviceToWorldAnchor);

private:

    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version);

protected:
    org::bcom::xpcf::uuids::uuid m_rootUUID;
    std::vector<RelocObject> m_relocObjects;
    bool m_deviceToWorldAnchor;
};

DECLARESTORAGESERIALIZE(RelocObject);
DECLARESTORAGESERIALIZE(RelocalizationInformation);

}
}
#endif // RELOCALIZATIONINFORMATION_H
