/**
 * @copyright Copyright (c) 2023 B-com http://www.b-com.com/
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

#ifndef DETECTEDOBJECT_H
#define DETECTEDOBJECT_H

#include "core/SerializationDefinitions.h"

namespace SolAR {
namespace datastructure {

/**
 * @typedef DetectedObjectType
 * @brief <B>Define the types of objects that can be detected in an image.</B>
 */
typedef enum {
    UNKNOWN_OBJECT = 0,
    FIDUCIAL_MARKER_OBJECT = 1,
    QR_CODE_OBJECT = 2,
    NATURAL_IMAGE_OBJECT = 3
} DetectedObjectType;

/**
 * @struct DetectedObject
 * @brief <B>Define any object that can be detected in an image.</B>
 */
struct DetectedObject
{
    DetectedObjectType objectType;                               // Type of the object
    std::string objectUrl;                                       // URL defined for the object (unique)
    std::vector<Point3Df> pattern3DPoints; // Pattern 3D points of the object
    Transform3Df transform3D;              // 3D transformation to SolAR coordinate system

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & objectType;
        ar & objectUrl;
        ar & pattern3DPoints;
        ar & transform3D;
    }
};

DECLARESERIALIZE(DetectedObject);
IMPLEMENTSERIALIZE(DetectedObject);

}
}// namespace SolAR::datastructure

#endif // DETECTEDOBJECT_H
