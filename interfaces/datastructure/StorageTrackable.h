#ifndef STORAGETRACKABLE_H
#define STORAGETRACKABLE_H

#include <core/SolARFrameworkDefinitions.h>
#include <core/SerializationDefinitions.h>
#include <datastructure/StorageWorldElement.h>
#include "datastructure/MathDefinitions.h"
#include <datastructure/Trackable.h>
#include <nlohmann/json.hpp>
#include <datastructure/UnitSystem.h>

#include "core/Log.h"

// Definition of StorageTrackable Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {



///
/// @brief Enumeration of all trackable object types according to the API specified in partnership with the Etsi
///
enum class StorageTrackableType : char {
    MAP,
    FIDUCIAL_MARKER,
    IMAGE_MARKER,
    OTHER
};

static StorageTrackableType resolveTrackableType(std::string input){
    if(input == "MAP"){return StorageTrackableType::MAP;}
    if(input == "FIDUCIAL_MARKER" || input == "FIDUCIAL"){return StorageTrackableType::FIDUCIAL_MARKER;}
    if(input == "IMAGE_MARKER" || input == "IMAGE"){return StorageTrackableType::IMAGE_MARKER;}
    return StorageTrackableType::OTHER;
}

static  std::string resolveTrackableType(StorageTrackableType input){
    if(input == StorageTrackableType::MAP){return "MAP";}
    if(input == StorageTrackableType::FIDUCIAL_MARKER){return "FIDUCIAL_MARKER";}
    if(input == StorageTrackableType::IMAGE_MARKER){return "IMAGE_MARKER";}
    return "OTHER";
}

///
/// @brief The EncodingInfo struct
///
struct EncodingInfo {
    std::string m_dataFormat;
    std::string m_version;

    EncodingInfo() = default;

    EncodingInfo(std::string dataFormat, std::string version){
        m_dataFormat = dataFormat;
        m_version = version;
    }

    std::string& getVersion(){
        return m_version;
    }

    std::string& getDataFormat(){
        return m_dataFormat;
    }

    void setDataFormat(std::string dataFormat){
        m_dataFormat = dataFormat;
    }

    void setVersion(std::string version){
        m_version = version;
    }

    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
        ar & m_version;
        ar & m_dataFormat;
    }
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
        /// @brief StorageTrackable constructor from abstract supertype WorldElement
        ///
        StorageTrackable(const StorageWorldElement& elem) : StorageWorldElement(elem) {};

        ///
        /// @brief StorageTrackable constructor with url
        ///
        StorageTrackable(const std::string & url);

        ///
        /// @brief StorageTrackable constructor with all its attributes
        ///
        StorageTrackable(org::bcom::xpcf::uuids::uuid creatorId, Transform3Df localCRS, UnitSystem unitSystem,
                         Vector3d size, SRef<StorageWorldElement> parent, Transform3Df transformFromParent,
                         std::map<org::bcom::xpcf::uuids::uuid, SRef<StorageWorldElement>> children, std::multimap<std::string, std::string> tags,
                         StorageTrackableType type, EncodingInfo encodingInfo, std::vector<std::byte> payload);

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

        bool isWorldAnchor() override;

        bool isTrackable() override;

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
BOOST_SERIALIZATION_ASSUME_ABSTRACT(StorageTrackable);

}
} // end of namespace SolAR

namespace boost { namespace serialization {

template<class Archive>
inline void serialize(Archive & ar,
                      SolAR::datastructure::EncodingInfo & parameters,
                      ATTRIBUTE(maybe_unused) const unsigned int version)
{
    ar & parameters.m_dataFormat;
    ar & parameters.m_version;
}}}

#endif // STORAGETRACKABLE_H
