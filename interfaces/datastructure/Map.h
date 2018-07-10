#ifndef MAP_H
#define MAP_H



#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/CloudPoint.h"


#include <memory>
namespace SolAR {
namespace datastructure {

class SOLARFRAMEWORK_API Map{

public :

    /// \brief default constructor
    Map() ;

    /// \brief destructor
    ~Map() ;

    void addCloudPoints(std::vector<SRef<CloudPoint>> & newMapPoints);

    SRef<std::vector<SRef<CloudPoint>>> getPointCloud() ;

    void computeGravity(Point3Df &grav, float& maxDist) const ;

private :

    SRef<std::vector<SRef<CloudPoint>>> m_pointCloud ;

};

}
}



#endif // MAP_H
