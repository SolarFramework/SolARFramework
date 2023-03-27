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

#ifndef SOLAR_MESH_H
#define SOLAR_MESH_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <xpcf/api/IComponentIntrospect.h>
#include <core/SolARFrameworkDefinitions.h>
#include <core/SerializationDefinitions.h>
#include <datastructure/GeometryDefinitions.h>
#include <datastructure/MathDefinitions.h>


// Definition of Mesh Class //
// part of SolAR namespace //
namespace SolAR {
namespace datastructure {
/**
 * @class Mesh
 * @brief <B>A textured mesh of triangles base on indexed face sets.</B>
 */
class  SOLARFRAMEWORK_API Mesh  {
public:
    Mesh() = default;

	/// @brief CloudPoint constructor with a Point3Df.
    /// @param[in] points vector of the 3D points of the mesh.
    /// @param[in] indexedFaceSets indexed face sets representing the id of points for each triangle of the mesh.
    /// @param[in] normals (optional): vector of normal for each 3D point..
    /// @param[in] colors (optional): color of each point of the mesh (RGB).
    /// @param[in] texCoordinates (optional): Coordinate texture of each 3D point of the mesh..
    explicit Mesh( const std::vector<Point3Df> points,
                   const std::vector<Vector3ui> indexedFaceSets,
                   const std::vector<Vector3f> normals = {},
                   const std::vector<Vector3f> colors = {},
                   const std::vector<Vector2f> texCoordinates = {});

    ///
    /// \brief ~Mesh
    ///
    ~Mesh();

    /// @brief This method returns the 3D points of the mesh
    /// @return the vector of 3D points
    inline std::vector<Point3Df> getPoints () const { return m_points; }

    /// @brief This method allows to set the 3D points of the mesh
    /// @param[in] points The 3D points of the mesh
    inline void setPoints(std::vector<Point3Df> points) {m_points = points;}

    /// @brief This method returns the indexed face set of the mesh
    /// @return the vector indexed face set
    inline std::vector<Vector3ui> getIndexedFaceSets () const { return m_indexedFaceSets; }

    /// @brief This method allows to set the indexed face sets of the mesh
    /// @param[in] indexedFaceSets The indexed face sets of the mesh
    inline void setIndexedFaceSets(std::vector<Vector3ui> indexedFaceSets) {m_indexedFaceSets = indexedFaceSets;}

    /// @brief This method returns the normals to the points of the mesh
    /// @return the normals to the points of the mesh
    inline std::vector<Vector3f> getNormals () const { return m_normals; }

    /// @brief This method allows to set the normals to the points of the mesh
    /// @param[in] normals The normals to the points of the mesh
    inline void setNormals(std::vector<Vector3f> normals) {m_normals = normals;}


    /// @brief This method returns the colors of the points of the mesh
    /// @return the colors of the points of the mesh
    inline std::vector<Vector3f> getColors () const { return m_colors; }

    /// @brief This method allows to set the colors of the points of the mesh
    /// @param[in] colors The colors of the points of the mesh
    inline void setColors(std::vector<Vector3f> colors) {m_colors = colors;}

    /// @brief This method returns the texture coordinates of the points of the mesh
    /// @return the texture coordinates of the points of the mesh
    inline std::vector<Vector2f> getTexCoordinates () const { return m_texCoordinates; }

    /// @brief This method allows to set the texture coordinates of the points of the mesh
    /// @param[in] texCoordinates The texture coordinates of the points of the mesh
    inline void setTexCoordinates(std::vector<Vector2f> texCoordinates) {m_texCoordinates = texCoordinates;}


private:
	friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

private:	
    std::vector<Point3Df> m_points;
    std::vector<Vector3ui> m_indexedFaceSets;
    std::vector<Vector3f> m_normals;
    std::vector<Vector3f> m_colors;
    std::vector<Vector2f> m_texCoordinates;
};

DECLARESERIALIZE(Mesh);

}  // end of namespace datastructure
}  // end of namespace SolAR

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Mesh);

#endif // SOLAR_MESH_H
