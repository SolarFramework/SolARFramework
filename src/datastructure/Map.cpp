#include "datastructure/Map.h"
namespace xpcf  = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

Map::Map()
{
}

Map::~Map()
{

}

void Map::addCloudPoints(const std::vector<CloudPoint> & newMapPoints)
{
     m_pointCloud.insert(m_pointCloud.end(), newMapPoints.begin()  , newMapPoints.end()) ;
}

}
}
