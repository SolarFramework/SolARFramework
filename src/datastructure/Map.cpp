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
void Map::updateCloudPoints(const std::vector<CloudPoint> & correctedMapPoints) {
	for (unsigned int i = 0; i < m_pointCloud.size(); ++i) {
		m_pointCloud[i].setX(correctedMapPoints[i].getX());
		m_pointCloud[i].setY(correctedMapPoints[i].getY());
		m_pointCloud[i].setZ(correctedMapPoints[i].getZ());
	}
}
}
}
