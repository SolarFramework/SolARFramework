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

#ifndef STORAGETRACKABLE_H
#define STORAGETRACKABLE_H

#include <nlohmann/json.hpp>

#include "core/Log.h"
#include "core/SerializationDefinitions.h"
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/StorageWorldElement.h"
#include "datastructure/Trackable.h"
#include "datastructure/UnitSystem.h"

namespace SolAR {
namespace datastructure {



///
/// @brief Enumeration of all trackable object types according to the API specified in partnership with the Etsi
///
enum class StorageTrackableType : char {
    MAP,
    FIDUCIAL_MARKER,
    IMAGE_MARKER,
    GEOPOSE,
    MESH,
    OTHER
};

static StorageTrackableType resolveTrackableType(std::string input){
    if(input == "MAP"){return StorageTrackableType::MAP;}
    if(input == "MESH"){return StorageTrackableType::MESH;}
    if(input == "FIDUCIAL_MARKER" || input == "FIDUCIAL"){return StorageTrackableType::FIDUCIAL_MARKER;}
    if(input == "IMAGE_MARKER" || input == "IMAGE"){return StorageTrackableType::IMAGE_MARKER;}
    if(input == "GEOPOSE"){return StorageTrackableType::GEOPOSE;}
    return StorageTrackableType::OTHER;
}

static  std::string resolveTrackableType(StorageTrackableType input){
    if(input == StorageTrackableType::MAP){return "MAP";}
    if(input == StorageTrackableType::MESH){return "MESH";}
    if(input == StorageTrackableType::FIDUCIAL_MARKER){return "FIDUCIAL_MARKER";}
    if(input == StorageTrackableType::IMAGE_MARKER){return "IMAGE_MARKER";}
    if(input == StorageTrackableType::GEOPOSE){return "GEOPOSE";}
    return "OTHER";
}

///
/// @brief The EncodingInfo struct
///
class EncodingInfo {

    public:

        EncodingInfo() = default;

        EncodingInfo(const std::string &dataFormat, const std::string &version){
            m_dataFormat = dataFormat;
            m_version = version;
        }

        std::string getVersion(){
            return m_version;
        }

        std::string getDataFormat(){
            return m_dataFormat;
        }

        void setDataFormat(const std::string &dataFormat){
            m_dataFormat = dataFormat;
        }

        void setVersion(const std::string &version){
            m_version = version;
        }

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
            ar & m_version;
            ar & m_dataFormat;
        }

    private:

        std::string m_dataFormat;
        std::string m_version;
};

/**
    * @class StorageTrackable
    * @brief <B>This class defines the generic trackable datastructure defined in the world graph.</B>
    */
class SOLARFRAMEWORK_API StorageTrackable : virtual public StorageWorldElement
{
    public:

        ////////////////////////////
        ///     CONSTRUCTORS    ////
        ////////////////////////////

        ///
        /// @brief StorageTrackable default constructor
        ///
        StorageTrackable() = default;

        ///
        /// @brief StorageTrackable default destructor
        ///
        virtual ~StorageTrackable() = default;

        ///
        /// @brief StorageTrackable constructor with url
        ///
        StorageTrackable(const std::string &url);

        ///
        /// @brief StorageTrackable constructor with all its attributes (autogenerated id)
        ///
        StorageTrackable(const org::bcom::xpcf::uuids::uuid &creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                         Vector3d size, const std::multimap<std::string, std::string> &tags,
                         StorageTrackableType type, EncodingInfo encodingInfo, const std::vector<std::byte> &payload, std::string name);



        ///
        /// @brief StorageTrackable constructor with all its attributes (given id)
        ///
        StorageTrackable(const org::bcom::xpcf::uuids::uuid &id, const org::bcom::xpcf::uuids::uuid &creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                         Vector3d size, const std::multimap<std::string, std::string> &tags,
                         StorageTrackableType type, EncodingInfo encodingInfo, const std::vector<std::byte> &payload, std::string name);

        ////////////////////////////
        /// GETTERS AND SETTERS ////
        ////////////////////////////

        /// @brief Getter for the url of the trackable object
        std::string getURL() const;
        /// @brief Setter for the url of the trackable object
        void setURL(const std::string & url);

        /// @brief Getter for the type of Trackable
        StorageTrackableType getType() const;
        /// @brief Setter for the type of Trackable
        void setType(StorageTrackableType newType);

        /// @brief Setter for the Encoding informations
        void setEncodingInfo(const EncodingInfo &newEncodingInfo);
        /// @brief Getter for the Encoding informations
        const EncodingInfo &getEncodingInfo() const;

        /// @brief Getter for the buffer for the payload contained by the trackable
        const std::vector<std::byte> &getPayload() const;
        /// @brief Setter for the buffer for the payload contained by the trackable
        void setPayload(const std::vector<std::byte> &newPayload);

        virtual ElementKind getKind() override;

    private:

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

protected:

        StorageTrackableType m_type;
        EncodingInfo m_encodingInfo;
        std::vector<std::byte> m_payload;
        std::string m_url; // The url of the trackable object

};

DECLARESERIALIZE(StorageTrackable);

}
} // end of namespace SolAR

#endif // STORAGETRACKABLE_H
