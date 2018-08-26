#include "datastructure/Map.h"
namespace xpcf  = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

Map::Map()
{
    m_pointCloud = xpcf::utils::make_shared<std::vector<SRef<CloudPoint>>>() ;

}

Map::~Map()
{

}

void Map::addCloudPoints(const std::vector<SRef<CloudPoint>> & newMapPoints)
{
     m_pointCloud->insert(m_pointCloud->end(), newMapPoints.begin()  , newMapPoints.end()) ;
}

SRef<std::vector<SRef<CloudPoint>>> Map::getPointCloud()
{
     return m_pointCloud ;

}

void Map::computeGravity(Point3Df &grav, float& maxDist) const
{
   grav =  Point3Df(0, 0, 0);
   maxDist  =0.f;

   Point3Df  vr_temp(0, 0, 0);
    int count = 0;
    for (int i = 0; i < m_pointCloud->size(); ++i) {
        vr_temp = Point3Df((*m_pointCloud)[i]->getX(), (*m_pointCloud)[i]->getX(), (*m_pointCloud)[i]->getY());
        grav = grav + vr_temp;
        count++;
    }
    maxDist = 0;
    if (count > 0) {
        grav= grav*(1.f / (float)count);
        for (int i = 0; i < m_pointCloud->size(); ++i) {
            vr_temp = Point3Df((*m_pointCloud)[i]->getX(),(*m_pointCloud)[i]->getY(), (*m_pointCloud)[i]->getZ());
            Point3Df temp = vr_temp - grav;
            maxDist = std::max(maxDist, (vr_temp - grav).magnitude());
        }
    }
}



}
}
