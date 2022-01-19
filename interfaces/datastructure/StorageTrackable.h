#ifndef STORAGETRACKABLE_H
#define STORAGETRACKABLE_H

#include <core/SolARFrameworkDefinitions.h>
#include <core/SerializationDefinitions.h>
#include <datastructure/WorldElement.h>
#include "datastructure/MathDefinitions.h"
#include <datastructure/Trackable.h>
#include <nlohmann/json.hpp>

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
/// @brief Enumeration of all units of measurement
///
enum class UnitSystem : char {

    //metric units

    //millimeter
    MM,
    //centimeter
    CM,
    //decimeter
    DM,
    //meter
    M,
    //decameter
    DAM,
    //hectometer
    HM,
    //kilometer
    KM,

    //imperial units

    INCH,
    FOOT,
    YARD,
    MILE,
    INVALID

};

static UnitSystem resolveUnitSystem(std::string input){
    if(input == "MM" || input == "mm"){return UnitSystem::MM;}
    if(input == "CM" || input == "cm"){return UnitSystem::CM;}
    if(input == "DM" || input == "dm"){return UnitSystem::DM;}
    if(input == "M" || input == "m"){return UnitSystem::M;}
    if(input == "DAM" || input == "dam"){return UnitSystem::DAM;}
    if(input == "HM" || input == "hm"){return UnitSystem::HM;}
    if(input == "KM" || input == "km"){return UnitSystem::KM;}
    if(input == "INCH" || input == "inch"){return UnitSystem::INCH;}
    if(input == "FOOT" || input == "foot"){return UnitSystem::FOOT;}
    if(input == "YARD" || input == "yard"){return UnitSystem::YARD;}
    if(input == "MILE" || input == "mile"){return UnitSystem::MILE;}
    return UnitSystem::INVALID;
}

static std::string resolveUnitSystem(UnitSystem input){
    if(input == UnitSystem::MM){return "MM";}
    if(input == UnitSystem::CM){return "CM";}
    if(input == UnitSystem::DM){return "DM";}
    if(input == UnitSystem::M){return "M";}
    if(input == UnitSystem::DAM){return "DAM";}
    if(input == UnitSystem::HM){return "HM";}
    if(input == UnitSystem::KM){return "KM";}
    if(input == UnitSystem::INCH){return "INCH";}
    if(input == UnitSystem::FOOT){return "FOOT";}
    if(input == UnitSystem::YARD){return "YARD";}
    if(input == UnitSystem::MILE){return "MILE";}
    return "INVALID";
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
class SOLARFRAMEWORK_API StorageTrackable : virtual public WorldElement
{
    public:
        ///
        /// @brief StorageTrackable default constructor
        ///
        StorageTrackable() = default;

        ///
        /// @brief StorageTrackable constructor from abstract supertype WorldElement
        ///
        StorageTrackable(const WorldElement& elem) : WorldElement(elem) {};

        ///
        /// @brief StorageTrackable constructor with url
        ///
        StorageTrackable(const std::string & url);

        ///
        /// @brief StorageTrackable constructor with all its attributes
        ///
        StorageTrackable(boost::uuids::uuid author, datastructure::StorageTrackableType type,
                  datastructure::EncodingInfo encodingInfo, std::vector<std::byte> payload, datastructure::Transform3Df LocalCrs,
                  datastructure::UnitSystem unitSystem, datastructure::Vector3d scale,
                  std::multimap<std::string, std::string> tags);

        ///
        /// @brief StorageTrackable default destructor
        ///
        ~StorageTrackable() = default;

        /// @brief Returns the url of the trackable object
        /// @return the url of the trackable object
        std::string getURL() const;

        /// @brief Sets the url of the trackable object
        void setURL(const std::string & url);

        ///
        /// @brief Returns the type of the StorageTrackable object
        /// @return StorageTrackableType: the type of Trackable (MAP, FIDUCIAL, IMAGE or UNKNOWN)
        ///
        StorageTrackableType getType() const;

        /// @brief Sets the type of Trackable
        void setType(datastructure::StorageTrackableType newType);

        /// @brief Gets the author ID of the Trackable
        const boost::uuids::uuid &getAuthor() const;
        /// @brief Sets the author ID of the Trackable
        void setAuthor(const boost::uuids::uuid &newAuthor);


        /// @brief Sets the Encoding informations
        void setEncodingInfo(const datastructure::EncodingInfo &newEncodingInfo);
        /// @brief Gets the Encoding informations
        const datastructure::EncodingInfo &getEncodingInfo() const;


        /// @brief Sets the local reference system of the trackable
        void setLocalCrs(const datastructure::Transform3Df &newLocalCrs);
        /// @brief Gets the local reference system of the trackable
        const datastructure::Transform3Df &getLocalCrs() const;


        /// @brief Sets the unit system
        UnitSystem getUnitSystem() const;
        void setUnitSystem(UnitSystem newUnitSystem);


        /// @brief Sets the dimension of the trackable
        const datastructure::Vector3d &getScale() const;
        void setScale(const datastructure::Vector3d &newScale);


        /// @brief Sets the buffer for the payload contained by the trackable
        const std::vector<std::byte> &getPayload() const;
        void setPayload(const std::vector<std::byte> &newPayload);

        bool isWorldAnchor();

        bool isTrackable();

private:

        boost::uuids::uuid m_author;
        datastructure::StorageTrackableType m_type;
        datastructure::EncodingInfo m_encodingInfo;
        datastructure::Transform3Df m_LocalCrs;
        UnitSystem m_unitSystem;
        datastructure::Vector3d m_scale;
        std::vector<std::byte> m_payload;

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

protected:

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
