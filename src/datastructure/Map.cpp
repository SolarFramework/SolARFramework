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

}
}
