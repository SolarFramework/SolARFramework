#ifndef STORAGETRACKABLE_H
#define STORAGETRACKABLE_H

#include <core/SolARFrameworkDefinitions.h>
#include <core/SerializationDefinitions.h>
#include <datastructure/WorldElement.h>
#include "datastructure/MathDefinitions.h"
#include <datastructure/Trackable.h>

#include "core/Log.h"

// Definition of StorageTrackable Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {


///
/// @brief Enumeration of all units of measurement
///
enum UnitSystem {

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

};


///
/// @brief The EncodingInfo struct
///
struct EncodingInfo {
    std::string dataFormat;
    std::string version;
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
        /// @brief StorageTrackable constructor with url
        ///
        StorageTrackable(const std::string & url);

        ///
        /// @brief StorageTrackable constructor with TODO
        ///
        StorageTrackable(boost::uuids::uuid author, datastructure::TrackableType type,
                  datastructure::EncodingInfo encodingInfo, std::vector<std::byte> payload, datastructure::Transform3Df LocalCrs,
                  UnitSystem unitSystem, datastructure::Vector3d scale,
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
        /// @return TrackableType: the type of Trackable (MAP, FIDUCIAL, IMAGE or UNKNOWN)
        ///
        TrackableType getType() const;

        /// @brief Sets the type of Trackable
        void setType(datastructure::TrackableType newType);


        /// @brief Sets the author ID of the Trackable
        const boost::uuids::uuid &getAuthor() const;
        void setAuthor(const boost::uuids::uuid &newAuthor);


        /// @brief Sets the Encoding informations
        const datastructure::EncodingInfo &getEncodingInfo() const;
        void setEncodingInfo(const datastructure::EncodingInfo &newEncodingInfo);


        /// @brief Sets the local reference system of the trackable
        const datastructure::Transform3Df &getLocalCrs() const;
        void setLocalCrs(const datastructure::Transform3Df &newLocalCrs);


        /// @brief Sets the unit system
        UnitSystem getUnitSystem() const;
        void setUnitSystem(UnitSystem newUnitSystem);


        /// @brief Sets the dimension of the trackable
        const datastructure::Vector3d &getScale() const;
        void setScale(const datastructure::Vector3d &newScale);


        /// @brief Sets the buffer for the payload contained by the trackable
        const std::vector<std::byte> &payload() const;
        void setPayload(const std::vector<std::byte> &newPayload);

private:

        boost::uuids::uuid m_author;
        datastructure::TrackableType m_type;
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
    ar & parameters.dataFormat;
    ar & parameters.version;
}}}

#endif // STORAGETRACKABLE_H
