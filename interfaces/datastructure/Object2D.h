/**
 * @copyright Copyright (c) 2025 B-com http://www.b-com.com/
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

#ifndef SOLAR_OBJECT2D_H
#define SOLAR_OBJECT2D_H

#include <array>
#include "core/SerializationDefinitions.h"
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/PrimitiveInformation.h"
#include <vector>

namespace SolAR {
namespace datastructure {

/**
 * @class Object2D
 * @brief <B>Object2D used to represent object on 2D Image.</B>.
 *
 * This class provides Object2D definition.
 */
class SOLARFRAMEWORK_API Object2D : public PrimitiveInformation {
public:
    /// @brief default constructor
    Object2D() = default;

    /// @brief default destructor
    ~Object2D() = default;

    /// @brief set instance ID
    /// @param[in] id object instance ID
    void setInstanceID(const uint32_t& id);

    /// @brief set bounding box
    /// @param[in] x upper left corner x coordinate
    /// @param[in] y upper left corner y coordinate
    /// @param[in] w width of the bounding box
    /// @param[in] h height of the bounding box
    void setBoundingBox(const float& x, const float& y, const float& w, const float& h);

    /// @brief set segmentation represented by a number of 2D points
    /// @param[in] contour ordered list of points of the contour
    void setSegmentation(const Contour2Df& contour);

    /// @brief get instance ID
    /// @return instance ID
    const uint32_t& getInstanceID() const;

    /// @brief get bounding box
    /// @return 2D bounding box
    const BBox2Df& getBoundingBox() const;

    /// @brief get segmentation
    /// @return list of points of the contour
    const Contour2Df& getSegmentation() const;

private:
    /// @brief serialization
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    uint32_t m_instanceID = 0;   // object instance ID
    BBox2Df m_bbox;              // bounding box (x, y, width, height)
    Contour2Df m_contour;   // list of 2D points of the segmentation contour
};

DECLARESERIALIZE(Object2D);

} // namespace datastructure
} // namespace SolAR

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Object2D);

#endif //SOLAR_OBJECT2D_H
