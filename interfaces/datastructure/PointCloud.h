/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SOLAR_POINTCLOUD_H
#define SOLAR_POINTCLOUD_H

#include <vector>
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "xpcf/core/refs.h"
#include "datastructure/BufferInternal.hpp"
#include <map>

// Definition of PointCloud Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

///
/// \brief The PointCloud class
///
class  SOLARFRAMEWORK_API PointCloud {

    public:

//    enum PointType {
//        TYPE_XYZ = 1,  /**< each point is defined by its 3D coordinates */
//        TYPE_RGB = 2,  /**< each point is defined by its 3D coordinates */
//        TYPE_XYZRGB = 3, /**< each point is defined by its 3D coordinates and its color (RGB) */
//        TYPE_NORMAL = 4, /**< each point is defined by its 3D coordinates and its color (RGB) */
//        TYPE_XYZNORMAL = 5, /**< each point is defined by its 3D coordinates, and its normal */
//        TYPE_XYZRGBNORMAL = 7, /**< each point is defined by its 3D coordinates, its color (RGB), and its normal */
//    };

///// static std::map<PointType,int> pointTypeNbElements = {{PointType::TYPE_XYZ, 3}, {PointType::TYPE_XYZRGB, 6}, {PointType::TYPE_XYZRGBNORMAL, 9}, {}};

//    enum DataType {
//        TYPE_32F = 4, /**< each point element is stored in four bytes. */
//        TYPE_64D = 8  /**< each point element is stored in eight bytes. */
//    };

//   /** @brief  PointCloud constructor
//   *  @param pointsData: pointer to an existing array structure storing the points
//   *  @param dataType: enum to describe the data type of point element (Float32 or double64)
//   *  @param pointType: enum to describe the type of point
//   *  @param nbPoints: the number of points stored in the buffer
//   * The data are copied to get full ownership of the memory allocation.
//   */
//   PointCloud(float* pointsData, DataType dataType, PointType pointType, uint32_t nbPoints);

//   /** @brief  PointCloud constructor
//   *  @param dataType: enum to describe the data type of point element (Float32 or double64)
//   *  @param pointType: enum to describe the type of point
//   *  @param nbPoints: the number of points stored in the buffer
//   * The data are copied to get full ownership of the memory allocation.
//   */
//   PointCloud(DataType dataType, PointType pointType, uint32_t nbPoints);

   PointCloud() = default;
   ///
   /// \brief ~PointCloud
   ///
    ~PointCloud();

//   /** @brief  return the number of points stored in the structure
//   */
//   inline uint32_t getNbPoints(void){
//       return m_nbPoints;
//   }

//   /** @brief  return the internal storage type of descriptor
//   */
//   inline enum PointType getPointType()
//   {
//       return m_pointType;
//   }

//   /** @brief  return the 3D point cloud size in bytes
//   */
//   inline uint32_t getPointCloudByteSize(void)
//   {
//       return m_nbPoints * m_dataType * 3;
//   }

//   /** @brief  return the normals point cloud size in bytes
//   */
//   inline uint32_t getNormalCloudByteSize(void)
//   {
//       if (m_pointType & PointType::TYPE_NORMAL)
//            return m_nbPoints * m_dataType * 3;
//       else
//           return 0;
//   }

//   /** @brief  return the color point cloud size in bytes
//   */
//   inline uint32_t getColorCloudByteSize(void)
//   {
//       return m_nbPoints * 3 ;
//   }

   const std::vector<Point3Df>& getConstPointCloud() const;
   std::vector<Point3Df>& getPointCloud();

    private:
//        PointType m_pointType;
//        uint32_t m_nbPoints;

//        SRef<BufferInternal> m_points;
//        DataType m_dataType;
//        SRef<BufferInternal> m_normals;
//        SRef<BufferInternal> m_colors;
//
        std::vector<Point3Df> m_points;

};

}
}  // end of namespace SolAR

#endif // SOLAR_POINTCLOUD_H
