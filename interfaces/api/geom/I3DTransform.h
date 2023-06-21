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

#ifndef SOLAR_I3DTRANSFORM_H
#define SOLAR_I3DTRANSFORM_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/PointCloud.h"
#include "datastructure/KeyframeCollection.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Map.h"

namespace SolAR {
namespace api {
namespace geom {

/**
 * @class I3DTransform
 * @brief <B>Applies a 3D transformation (e.g. an affine transformation) to a set of 3D points.</B>
 * <TT>UUID: 9c1052b2-46c0-467b-8363-36f19b6b445f</TT>
 */

class XPCF_CLIENTUUID("600dd260-12ff-4fa3-877a-0db9d490e20e") XPCF_SERVERUUID("a8c4d66c-b112-49a2-9eae-d9e1fd0e34b5") I3DTransform :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I3DTransform default constructor
    I3DTransform() = default;

    /// @brief I3DTransform default destructor
    virtual ~I3DTransform() = default;

    /// @brief This method applies a transformation (4x4 float matrix) to a set of 3D points
    /// @param[in] inputPoints the set of 3D points to transform
    /// @param[in] transformation the 3D transformation to apply (a 4x4 float matrix)
    /// @param[out] outputPoints the resulting set of 3D points after 3D transformation
    /// @return FrameworkReturnCode::_SUCCESS_ if 3D transformation succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode transform(const std::vector<SolAR::datastructure::Point3Df> & inputPoints,
                                          const SolAR::datastructure::Transform3Df & transformation,
                                          std::vector<SolAR::datastructure::Point3Df> & outputPoints) = 0;

	/// @brief This method applies a transformation (4x4 float matrix) to a map including point cloud and keyframes	
	/// @param[in] transformation: transformation the 3D transformation to apply (a 4x4 float matrix)
	/// @param[in,out] map: the map to apply the transformation
	/// @return FrameworkReturnCode::_SUCCESS_ if 3D transformation succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode transformInPlace(const SolAR::datastructure::Transform3Df & transformation,
                                          SRef<SolAR::datastructure::Map> map) = 0;

    /// @brief This method applies a transformation (4x4 float matrix) to a point cloud
    /// @param[in] transformation: transformation the 3D transformation to apply (a 4x4 float matrix)
    /// @param[in,out] pointCloud: the point cloud to apply the transformation
    /// @return FrameworkReturnCode::_SUCCESS_ if 3D transformation succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode transformInPlace(const SolAR::datastructure::Transform3Df & transformation,
                                          std::vector<SRef<SolAR::datastructure::CloudPoint>>& pointCloud) = 0;

    /// @brief This method applies a transformation (4x4 float matrix) to a set of keyframes
    /// @param[in] transformation: transformation the 3D transformation to apply (a 4x4 float matrix)
    /// @param[in,out] keyframes: the set of keyframes to apply the transformation
    /// @return FrameworkReturnCode::_SUCCESS_ if 3D transformation succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode transformInPlace(const SolAR::datastructure::Transform3Df & transformation,
                                          std::vector<SRef<SolAR::datastructure::Keyframe>>& keyframes) = 0;

	/// @brief This method applies a transformation (4x4 float matrix) to a point cloud
	/// @param[in] transformation the 3D transformation to apply (a 4x4 float matrix)
	/// @param[in,out] pointCloud the point cloud to apply the transformation
	/// @return FrameworkReturnCode::_SUCCESS_ if 3D transformation succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode transformInPlace(const SolAR::datastructure::Transform3Df & transformation, 
										SRef<SolAR::datastructure::PointCloud> pointCloud) = 0;

	/// @brief This method applies a transformation (4x4 float matrix) to a keyframe collection
	/// @param[in] transformation the 3D transformation to apply (a 4x4 float matrix)
	/// @param[in,out] keyframeCollection the keyframe collection to apply the transformation
	/// @return FrameworkReturnCode::_SUCCESS_ if 3D transformation succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode transformInPlace(const SolAR::datastructure::Transform3Df & transformation,
                                        SRef<SolAR::datastructure::KeyframeCollection> keyframeCollection) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::I3DTransform,
                             "9c1052b2-46c0-467b-8363-36f19b6b445f",
                             "I3DTransform",
                             "SolAR::api::geom::I3DTransform");


#endif //SOLAR_I3DTRANSFORM_H

