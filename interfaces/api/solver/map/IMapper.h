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

#ifndef IMAPPER_H
#define IMAPPER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of IMapper Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

#include "datastructure/Keyframe.h"
#include "datastructure/Frame.h"
#include "datastructure/Keypoint.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/Map.h"

namespace SolAR {
    using namespace datastructure;
    namespace api {
        namespace solver {
            namespace map {
/**
  * @class IMapper
  * @brief <B>Updates a point map with new triangulated 3D points.</B>
  * <TT>UUID: 90075c1b-915b-469d-b92d-41c5d575bf15</TT>
  */

class  IMapper : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
   IMapper() = default;
   ///
   ///@brief ~IMapper
   ///
   virtual ~IMapper() {}

   /// @brief update the current map with the new triangulated map points at the insertion of a new keyframe.
   /// minArg(pts3ds,intrinsics,extrinsics) = MIN_cam_i(MIN_3d_j(pts2d_j - reproje(pt3ds_j,intrinsics_i,extrinsics_i)),
   /// @param[in,out] map current constructed map.
   /// @param[in,out] neyKeyframe current new keyframe to insert.
   /// @param[in] newCloud new triangulated 3D points
   /// @param[in] newPointMatches new detected matches from the reference keyframe and current frame.
   /// @param[in] existingPointMatches new detected matches from the reference keyframe and current frame.
   /// @return FrameworkReturnCode::_SUCCESS if the map updating succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode update (SRef<Map> & map,
                                       SRef<Keyframe> & newKeyframe,
                                       const std::vector<CloudPoint> & newCloud = {},
                                       const std::vector<DescriptorMatch> & newPointsMatches = {},
                                       const std::vector<DescriptorMatch> & existingPointsMatches = {}) = 0;

   /// @brief update the current map with the new triangulated map points at the insertion of a new keyframe.
   /// minArg(pts3ds,intrinsics,extrinsics) = MIN_cam_i(MIN_3d_j(pts2d_j - reproje(pt3ds_j,intrinsics_i,extrinsics_i)),
   /// @param[in,out] map current constructed map.
   /// @param[in,out] neyKeyframe current new keyframe to insert.
   /// @param[in] newCloud new triangulated 3D points
   /// @param[in] newPointMatches a set of tuple contains information of matches corresponding newCloudPoint. 
   ///			  The first value is the idx of keypoint in the new keyframe. The remaining values are idx of keyframe and its keypoint.
   /// @param[in] existingPointMatches new detected matches from the reference keyframe and current frame.
   /// @return FrameworkReturnCode::_SUCCESS if the map updating succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode update(	SRef<Map> & map,
									   SRef<Keyframe> & newKeyframe,
									   const std::vector<CloudPoint> & newCloud = {},
									   const std::vector<std::tuple<unsigned int, int, unsigned int>> &newPointMatches = {}) = 0;

   /// @brief update the current map/keyframes(poses)with corrected map/keyframes(poses).
/// minArg(pts3ds,intrinsics,extrinsics) = MIN_cam_i(MIN_3d_j(pts2d_j - reproje(pt3ds_j,intrinsics_i,extrinsics_i)),
/// @param[in,out] map current constructed map.
/// @param[in,out] neyKeyframe current new keyframe to insert.
/// @param[in] newCloud new triangulated 3D points
/// @param[in] newPointMatches new detected matches from the reference keyframe and current frame.
/// @param[in] existingPointMatches new detected matches from the reference keyframe and current frame.
/// @return FrameworkReturnCode::_SUCCESS if the map updating succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode update(const std::vector<Transform3Df> & correctedPoses,
									  const std::vector<CloudPoint> & correctedMap) = 0;

	/// @brief return all the keyframes of the map.
	/// @return the keyframes of the map.
    virtual const std::vector<SRef<Keyframe>> &getKeyframes() = 0;
	/// @brief return a keyframe
	/// @param[in] Index of the keyframe
	virtual SRef<Keyframe> &getKeyframe(int index) = 0;
	/// @brief get local map from reference keyframe and its neighbors
	virtual void getLocalMap(SRef<Keyframe> refKF, std::vector<CloudPoint> &localCloudPoints) = 0;
	virtual SRef<Map> getGlobalMap() = 0;

	/// @brief get index of cloud point in local map from reference keyframe and its neighbors
	virtual void getLocalMapIndex(SRef<Keyframe> refKF, std::vector<unsigned int> &idxLocalCloudPoints) = 0;

	/// @brief update connections between new keyframe and neighboring keyframes.
	/// @param[in] a new keyframe.
	/// @param[in] the minimum number of common point to accept a connection.
	virtual void updateNeighborConnections(SRef<Keyframe> &newKeyframe, int minDis) = 0;

 //   virtual SRef<Map> getMap() = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IMapper,
                             "90075c1b-915b-469d-b92d-41c5d575bf15",
                             "IMapper",
                             "SolAR::api::solver::map::IMapper defines the interface of a mapper that considered a map, keyframe, point cloud to update the map representation in the 3D scene.");

#endif // IMAPPER_H
