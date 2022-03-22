#ifndef UNITSYSTEM_H
#define UNITSYSTEM_H

namespace SolAR {
namespace datastructure {

///
/// @brief Enumeration of all units of measurement used by the StorageWorldElements
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



}
}
#endif // UNITSYSTEM_H
