#include "datastructure/Map.h"

namespace SolAR {
namespace datastructure {

Map::Map() = default;
Map::~Map() = default;

void Map::addCloudPoints(const std::vector<CloudPoint> & newMapPoints)
{
     m_pointCloud.insert(m_pointCloud.end(), newMapPoints.begin()  , newMapPoints.end()) ;
}

const std::vector<CloudPoint> & Map::getPointCloud()
{
     return m_pointCloud ;

}

}
}
