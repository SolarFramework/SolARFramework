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
	std::unique_lock<std::mutex> lock(m_mutexPointCloud);
     m_pointCloud.insert(m_pointCloud.end(), newMapPoints.begin()  , newMapPoints.end()) ;
}
void Map::updateCloudPoints(const std::vector<CloudPoint> & correctedMapPoints) {
	std::unique_lock<std::mutex> lock(m_mutexPointCloud);
	for (unsigned int i = 0; i < m_pointCloud.size(); ++i) {
		m_pointCloud[i].setX(correctedMapPoints[i].getX());
		m_pointCloud[i].setY(correctedMapPoints[i].getY());
		m_pointCloud[i].setZ(correctedMapPoints[i].getZ());
	}
}
}
}
