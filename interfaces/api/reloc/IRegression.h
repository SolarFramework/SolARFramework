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

#ifndef IREGRESSION_H
#define IREGRESSION_H

#include "datastructure/Frame.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/CameraDefinitions.h"
#include "core/Messages.h"
#include <set>

namespace SolAR {
namespace api {
namespace reloc {


/**
 * @class IRegression
 * @brief <B>learn and define a set of 3D world coordinates corresponding to a set of 2D descriptors.</B>
 * <TT>UUID: 6741d3ed-0d19-4117-8a66-501704a7ad04</TT>
 *
 * This class provides a solution to learn and define a set of 3D world coordinates corresponding to a set of 2D descriptors.
 */

class IRegression : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief IRegression default constructor.
	IRegression() = default;
    ///@brief IRegression default destructor.
    virtual ~IRegression() = default;

	/// @brief this method is used to set intrinsic parameters and distorsion of the camera
	/// @param[in] intrinsicParams camera calibration matrix parameters.
	/// @param[in] distorsionParams camera distorsion parameters.
	virtual void setCameraParameters(const datastructure::CamCalibration & intrinsicParams, const datastructure::CamDistortion & distorsionParams) = 0;

    /// @brief Add 2D descriptor and 3D location correspondences
    /// @param[in] descriptors a set of descriptors
    /// @param[in] points3D a set of corresponding 3D locations
    /// @return FrameworkReturnCode::_SUCCESS if adding succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode add(const std::vector<SRef<datastructure::DescriptorBuffer>> &descriptors, const std::vector<datastructure::Point3Df> &points3D) = 0;


    /// @brief Regress a set of descriptors to define 2D-3D point correspondences
    /// @param[in] frame the frame contains descriptors for regression.
    /// @param[out] points2D a set of 2D points
    /// @param[out] points3D a set of 3D points
    /// @return FrameworkReturnCode::_SUCCESS if the regression succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode regress(const SRef<datastructure::Frame> &frame, std::vector<datastructure::Point2Df> &points2D, std::vector<datastructure::Point3Df> &points3D) = 0;

	/// @brief Update regression model
	/// @param[in] inliers inliers and outliers are defined for each 2D point
	/// @param[in] cameraPose camera pose of the current frame
	/// @return FrameworkReturnCode::_SUCCESS if the regression succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode update(std::vector<bool> &inliers, datastructure::Transform3Df &cameraPose) = 0;

	/// @brief Load regression model
	/// @return FrameworkReturnCode::_SUCCESS if the regression succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode loadModel() = 0;

	/// @brief Get the current training status
	/// @return Vector where first value is the size of the current training data, and second is the maximum nb of training data.
	virtual std::vector<int> getTrainingStatus() = 0;

	/// @brief Get number of active leaves
	/// @return Nb of active leaves as integer.
	virtual int getNumActiveLeaves() = 0;

	/// @brief Get number of passive leaves
	/// @return Nb of passive leaves as integer.
	virtual int getNumPassiveLeaves() = 0;
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::reloc::IRegression,
                             "6741d3ed-0d19-4117-8a66-501704a7ad04",
                             "IRegression",
                             "SolAR::api::reloc::IRegression describes the interface to learn and regress image descriptors to define 2D-3D point correspondences.");

#endif // IREGRESSION_H
