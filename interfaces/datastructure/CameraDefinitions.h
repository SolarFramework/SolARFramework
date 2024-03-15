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

/** @file */

#ifndef SOLAR_CAMERADEFINITIONS_H
#define SOLAR_CAMERADEFINITIONS_H

//#define EIGEN_DEFAULT_TO_ROW_MAJOR
#include <datastructure/GeometryDefinitions.h>
#include <datastructure/MathDefinitions.h>
#include <core/Log.h>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cassert>

#define SOLAR_PI           3.14159265358979323846
#define SOLAR_RAD2DEG      57.29577951308233
#define SOLAR_DEG2RAD      0.0174532925199433

namespace SolAR {
namespace datastructure {


/**
 * @typedef CamCalibration
 * @brief <B>A camera calibration matrix defining the intrinsic parameters of a camera.</B>
 *
 *  Camera intrinsic parameters defined with a 3x3 matrix with the following format:
 *  \f[ \begin{matrix} f_x & 0 & c_x \\ 0 & f_y & c_y \\ 0  & 0  & 1  \end{matrix}\f]
 *  Where \f$c_x\f$ and \f$c_y\f$ define the optical center, \f$f_x\f$ and \f$f_y\f$ the focal.
 */
typedef Maths::Matrix<float, 3, 3, Eigen::RowMajor> CamCalibration;

/**
 * @typedef CamDistortion
 * @brief <B>A camera distortion matrix defining the distortion parameters of a camera.</B>
 *
 *  Camera distortion parameters defined with a vector with 5 floats with the following format:
 *  \f$ \left( K_1, K_2, P_1, P_2, K_3 \right) \f$ <BR>
 *  Look at <a href="https://docs.opencv.org/2.4/doc/tutorials/calib3d/camera_calibration/camera_calibration.html">OpenCV</a>  documentation for more information.
 */
typedef Maths::Matrix<float, 5, 1> CamDistortion;

/**
 * @typedef CamExtrinsics
 * @brief <B>A 3D transform defining the extrinsics of a camera in a rig.</B>
 *
 * Camera extrinsics is defined with a 4x4 matrix that describe a transformation in 3D space (3D rotation + translation).
*/
typedef Transform3Df CamExtrinsics;

//Pose matrix definition               Vector defintion
//
//  R1x1    R1x2    R1x3    Tx         | X |
//  R2x1    R2x2    R2x3    Ty     *   | Y |
//  R3x1    R3x2    R3x3    Tz         | Z |
//  0       0       0       1          | 1 |
//
// This defintion avoids to apply a tranpose...
/**
 * @typedef PoseMatrix
 * @brief <B>A pose defining both position and orientation thanks to a 4x4 homogenous matrix.</B>
 *
 *  A pose defined with a 4x4 matrix with the following format:
 *  \f[ \begin{matrix} R_{11} & R_{12} & R_{13} & T_x \\ R_{21} & R_{22} & R_{23} & T_y \\ R_{31} & R_{32} & R_{33} & T_z \\ 0 & 0 & 0  & 1  \end{matrix}\f]
 *  Where \f$R\f$ is the 3x3 rotation matrix and \f$T\f$ is the translation vector.
 */
typedef Maths::Matrix<float, 4, 4, Eigen::RowMajor> PoseMatrix;

/**
* @typedef CameraType
* @brief <B>The CameraType enum.</B>
*/
typedef enum {
	RGB = 0,
	Gray = 1
} CameraType;

/**
* @typedef StereoType
* @brief <B>The StereoType enum.</B>
*/
typedef enum {
	Horizontal = 0,
	Vertical = 1
} StereoType;

/**
 * @typedef CameraParameters
 * @brief <B>Define parameters of a camera.</B>
 */
struct CameraParameters
{
    std::string name;
    uint32_t id;
    CameraType type;
    Sizei resolution;
    CamCalibration intrinsic;
    CamDistortion distortion;
    CamExtrinsics extrinsics;
};

/**
 * @typedef RectificationParameters
 * @brief <B>Define rectification parameters of a camera.</B>
 * Rectification parameters consists of two elements: rotation matrix and projection matrix.
 * The first one brings points given in the unrectified camera's coordinate system to points in the rectified camera's coordinate system.
 * The second one projects points given in the rectified first camera coordinate system into the rectified first camera's image.
 */
struct RectificationParameters
{
	// This matrix brings points given in the unrectified camera coordinate system to points in the rectified camera coordinate system
	Rotation rotation;
	// Projects points given in the rectified camera coordinate system into the rectified image coordinate system.
	Projection projection;
	// Stereo type
	SolAR::datastructure::StereoType type;
	// Stereo baseline in meters
	float baseline;
};

/**
 * @typedef CameraRigParameters
 * @brief <B>Define parameters of a camera rig.</B>
 */
struct CameraRigParameters
{
	std::map<uint32_t, CameraParameters> cameraParams;
	std::map<std::pair<uint32_t, uint32_t>, Transform3Df> transformations;
	std::map<std::pair<uint32_t, uint32_t>, std::pair<RectificationParameters, RectificationParameters>> rectificationParams;
};

}
}


namespace boost { namespace serialization {

template<class Archive>
inline void serialize(Archive & ar,
                      SolAR::datastructure::CameraParameters & parameters,
                      const unsigned int /* version */)
{
    ar & parameters.name;
    ar & parameters.id;
    ar & parameters.type;
    ar & parameters.resolution;
    ar & parameters.intrinsic;
    ar & parameters.distortion;
    ar & parameters.extrinsics;
}

template<class Archive>
inline void serialize(Archive & ar,
                      SolAR::datastructure::RectificationParameters & parameters,
                      const unsigned int /* version */)
{
	ar & parameters.baseline;
	ar & parameters.type;
	ar & parameters.rotation;
	ar & parameters.projection;	
}

template<class Archive>
inline void serialize(Archive & ar,
                      SolAR::datastructure::CameraRigParameters & parameters,
                      const unsigned int /* version */)
{
	ar & parameters.cameraParams;
	ar & parameters.rectificationParams;
	ar & parameters.transformations;
}

}} // namespace boost::serialization

namespace Eigen{
//Explicit template specialization SquaredBinaryPatternMatrix
template <class BasicJsonType, int Ops_, int MaxRows_, int MaxCols_>
inline void to_json(BasicJsonType& j, const Eigen::Matrix<bool, Dynamic, Dynamic, Ops_, MaxRows_, MaxCols_>& eigenData)
{
    std::vector<int> data;
    int size = eigenData.rows();
    for (int x = 0; x < size; ++x)
        for (int y = 0; y < size; ++y)
            data.push_back((int)eigenData(x, y));
    j = data;
}

//Explicit template specialization SquaredBinaryPatternMatrix
template <class BasicJsonType, int Ops_, int MaxRows_, int MaxCols_>
inline void from_json(const BasicJsonType& j, Eigen::Matrix<bool, Dynamic, Dynamic, Ops_, MaxRows_, MaxCols_>& eigenData)
{
    std::vector<int> data = j.template get<std::vector<int>>();
    int size = (int)std::sqrt(data.size());
    assert((size * size == (int) data.size()) && "Must be a squared matrix");
    eigenData.resize(size, size);
    for (int x = 0; x < size; ++x)
        for (int y = 0; y < size; ++y)
            eigenData(x, y) = (bool)data[x * size + y];
}

template <class BasicJsonType, class T, int Rows_, int Cols_, int Ops_, int MaxRows_, int MaxCols_>
inline void to_json(BasicJsonType& j, const Eigen::Matrix<T, Rows_, Cols_, Ops_, MaxRows_, MaxCols_>& eigenData)
{
    std::vector<T> data(eigenData.data(), eigenData.data() + eigenData.rows() * eigenData.cols());
    j = data;
}

template <class BasicJsonType, class T, int Rows_, int Cols_, int Ops_, int MaxRows_, int MaxCols_>
inline void from_json(const BasicJsonType& j, Eigen::Matrix<T, Rows_, Cols_, Ops_, MaxRows_, MaxCols_>& eigenData)
{
    std::vector<T> data = j.template get<std::vector<T>>();
    eigenData = Eigen::Map<Eigen::Matrix<T, Rows_, Cols_, Ops_, MaxRows_, MaxCols_>>(data.data());
}

template <class BasicJsonType, class T, int Dim_, int Mode_, int Options_>
inline void to_json(BasicJsonType& j, const Eigen::Transform<T, Dim_, Mode_, Options_>& eigenData)
{
    std::vector<T> data(eigenData.matrix().data(), eigenData.matrix().data() + eigenData.matrix().rows() * eigenData.matrix().cols());
    j = data;
}

template <class BasicJsonType, class T, int Dim_, int Mode_, int Options_>
inline void from_json(const BasicJsonType& j, Eigen::Transform<T, Dim_, Mode_, Options_ >& eigenData)
{
    std::vector<T> data = j.template get<std::vector<T>>();
    eigenData = Eigen::Map<SolAR::datastructure::Matrix<T, Dim_ + 1, Dim_ + 1>>(data.data());
    eigenData.makeAffine();
}
} // namespace Eigen

namespace SolAR{
namespace datastructure {
template <typename BasicJsonType>
inline void to_json(BasicJsonType& j, const CameraParameters& camParams)
{
    j["name"] = camParams.name;
    j["id"] = camParams.id;
    j["type"] = camParams.type;
    j["resolution"]["width"] = camParams.resolution.width;
    j["resolution"]["height"] = camParams.resolution.height;
    j["intrinsic"] = camParams.intrinsic;
    j["distortion"] = camParams.distortion;
    j["extrinsics"] = camParams.extrinsics;
}

template <typename BasicJsonType>
inline void from_json(BasicJsonType& j, CameraParameters& camParams)
{
    camParams.name = j["name"].template get<std::string>();
    camParams.id = j["id"].template get<uint32_t>();
    camParams.type = j["type"].template get<CameraType>();
    camParams.resolution.width = j["resolution"]["width"].template get<uint32_t>();
    camParams.resolution.height = j["resolution"]["height"].template get<uint32_t>();
    camParams.intrinsic = j["intrinsic"].template get<CamCalibration>();
    camParams.distortion = j["distortion"].template get<CamDistortion>();
    camParams.extrinsics = j["extrinsics"].template get<CamExtrinsics>();
}

template <typename BasicJsonType>
inline void to_json(BasicJsonType& j, const RectificationParameters& rectParams)
{
	j["type"] = rectParams.type;
	j["baseline"] = rectParams.baseline;
	j["rotation"] = rectParams.rotation;
	j["projection"] = rectParams.projection;
}

template <typename BasicJsonType>
inline void from_json(BasicJsonType& j, RectificationParameters& rectParams)
{
    rectParams.type = j["type"].template get<StereoType>();
    rectParams.baseline = j["baseline"].template get<float>();
    rectParams.rotation = j["rotation"].template get<Rotation>();
    rectParams.projection = j["projection"].template get<Projection>();
}

inline bool saveToFile(const SolAR::datastructure::CameraParameters& camParams, std::string filePath)
{
    nlohmann::ordered_json j;
    j["CameraParameters"] = camParams;
    std::ofstream f(filePath);
    f << std::setw(4) << j;
    f.close();
    return true;
}

inline bool loadFromFile(SolAR::datastructure::CameraParameters& camParams, std::string filePath)
{
    std::ifstream f(filePath);
    nlohmann::ordered_json j = nlohmann::ordered_json::parse(f, nullptr, false);
	if (j.is_discarded()) {
		LOG_ERROR("Error when parsing file: {}", filePath);
		return false;
	}
	std::string key = "CameraParameters";
	if (!j.contains(key))
		return false;
    camParams = j[key].get<SolAR::datastructure::CameraParameters>();
    f.close();
	return true;
}

inline bool saveToFile(const SolAR::datastructure::RectificationParameters& rectParams, std::string filePath)
{
	nlohmann::ordered_json j;
	j["Rectification"] = rectParams;
	std::ofstream f(filePath);
	f << std::setw(4) << j;
	f.close();
    return true;
}

inline bool loadFromFile(SolAR::datastructure::RectificationParameters& rectParams, std::string filePath)
{
	std::ifstream f(filePath);
	nlohmann::ordered_json j = nlohmann::ordered_json::parse(f, nullptr, false);
	if (j.is_discarded()) {
		LOG_ERROR("Error when parsing file: {}", filePath);
		return false;
	}
	std::string key = "Rectification";
	if (!j.contains(key))
		return false;
	rectParams = j[key].get<SolAR::datastructure::RectificationParameters>();
	f.close();
	return true;
}

inline bool saveToFile(const SolAR::datastructure::CameraRigParameters& camParams, std::string filePath)
{
	nlohmann::ordered_json j;
	// write camera parameters to json
    int nbCameras = (int) camParams.cameraParams.size();
	j["NbCameras"] = nbCameras;
	int countCamera(0);
	for (const auto& it : camParams.cameraParams) {
		j["CameraParameters " + std::to_string(countCamera)] = it.second;
		countCamera++;
	}
	// write rectifications to json
    int nbRects = (int) camParams.rectificationParams.size();
	j["NbRectifications"] = nbRects;
	int countRect(0);
	for (const auto& it : camParams.rectificationParams) {
		std::string nodeName = "Rectification " + std::to_string(countRect);
		j[nodeName]["Id1"] = it.first.first;
		j[nodeName]["Rect1"] = it.second.first;
		j[nodeName]["Id2"] = it.first.second;
		j[nodeName]["Rect2"] = it.second.second;
		countRect++;
	}
	// write transformations to json
    int nbTransformations = (int) camParams.transformations.size();
	j["NbTransformations"] = nbTransformations;
	int countTrans(0);
	for (const auto& it : camParams.transformations) {
		std::string nodeName = "Transformation " + std::to_string(countTrans);
		j[nodeName]["Id1"] = it.first.first;
		j[nodeName]["Id2"] = it.first.second;
		j[nodeName]["Transform"] = it.second;
		countTrans++;
	}
	// save to file
	std::ofstream f(filePath);
	f << std::setw(4) << j;
	f.close();
    return true;
}

inline bool loadFromFile(SolAR::datastructure::CameraRigParameters& camParams, std::string filePath)
{
	std::ifstream f(filePath);
	nlohmann::ordered_json j = nlohmann::ordered_json::parse(f, nullptr, false);
	if (j.is_discarded()){
		LOG_ERROR("Error when parsing file: {}", filePath);
		return false;
	}
	if (!j.contains("NbCameras"))
		return false;
	// load camera parameters to json
	int nbCameras = j["NbCameras"].get<int>();
	for (int i = 0; i < nbCameras; ++i) {
		CameraParameters cam = j["CameraParameters " + std::to_string(i)].get<CameraParameters>();
		camParams.cameraParams[cam.id] = cam;
	}
	// load rectifications to json
	if (j.contains("NbRectifications")) {
		int nbRects = j["NbRectifications"].get<int>();
		for (int i = 0; i < nbRects; ++i) {
			std::string nodeName = "Rectification " + std::to_string(i);
			uint32_t id1 = j[nodeName]["Id1"].get<uint32_t>();
			uint32_t id2 = j[nodeName]["Id2"].get<uint32_t>();
			RectificationParameters rect1 = j[nodeName]["Rect1"].get<RectificationParameters>();
			RectificationParameters rect2 = j[nodeName]["Rect2"].get<RectificationParameters>();
			camParams.rectificationParams[std::make_pair(id1, id2)] = std::make_pair(rect1, rect2);
		}
	}
	// load transformations to json
	if (j.contains("NbTransformations")) {
		int nbTransformations = j["NbTransformations"].get<int>();
		for (int i = 0; i < nbTransformations; ++i) {
			std::string nodeName = "Transformation " + std::to_string(i);
			uint32_t id1 = j[nodeName]["Id1"].get<uint32_t>();
			uint32_t id2 = j[nodeName]["Id2"].get<uint32_t>();
			Transform3Df transform = j[nodeName]["Transform"].get<Transform3Df>();
			camParams.transformations[std::make_pair(id1, id2)] = transform;
		}
	}
	f.close();
	return true;
}
}
}// namespace SolAR::datastructure


#endif // SOLAR_CAMERADEFINITIONS_H
