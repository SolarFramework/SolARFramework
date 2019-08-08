#ifndef MAP_H
#define MAP_H



#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/CloudPoint.h"


#include <memory>
namespace SolAR {
namespace datastructure {

/**
 * @class Map
 * @brief <B>A map of 3D points.</B>.
 *
 */
class SOLARFRAMEWORK_API Map{

public :

    /// \brief default constructor
    Map() ;

    /// \brief destructor
    ~Map() ;

    void addCloudPoints(const std::vector<CloudPoint> & newMapPoints);

    const std::vector<CloudPoint> & getPointCloud() const;

private :

    std::vector<CloudPoint> m_pointCloud ;

};

}
}



#endif // MAP_H
