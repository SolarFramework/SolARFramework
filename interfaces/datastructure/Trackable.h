/**
 * @copyright Copyright (c) 2020 B-com http://www.b-com.com/
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

#ifndef TRACKABLE_H
#define TRACKABLE_H

#include <core/SolARFrameworkDefinitions.h>
#include <core/SerializationDefinitions.h>

#include "core/Log.h"
#include "MathDefinitions.h"
#include "CameraDefinitions.h"
#include "nlohmann/json.hpp"

// Definition of Trackable Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

///
/// @brief Enumeration of all trackable object types
///
enum TrackableType {
    UNKNOWN,
    FIDUCIAL_MARKER,
    IMAGE_MARKER,
    QRCODE_MARKER
};


/**
    * @class Trackable
    * @brief <B>This abstract class defines the generic trackable datastructure.</B>
    */
class SOLARFRAMEWORK_API Trackable
{
    public:
        ///
        /// @brief Trackable default constructor
        ///
        Trackable() = default;

        ///
        /// @brief Trackable constructor with url
        ///
        Trackable(const std::string & url);

        ///
        /// @brief Trackable default destructor
        ///
        virtual ~Trackable() = default;

        ///
        /// @brief Returns the type of the Trackable object
        /// @return TrackableType: the type of the instance
        ///
        virtual TrackableType getType() const = 0;

        /// @brief Returns the url of the trackable object
        /// @return the url of the trackable object
        std::string getURL() const;

        /// @brief Sets the url of the trackable object
        /// @param[in] url the url
        void setURL(const std::string & url);

        /// @brief Returns the 3D transform from the trackable object to the world coordinates system
        /// @return the 3D transform to the world coordinates system
        datastructure::Transform3Df getTransform3D() const;

        /// @brief Sets the 3D transform to the world coordinates system
        /// @param[in] transform3D the 3D transform to the world coordinates system
        void setTransform3D(const datastructure::Transform3Df & transform3D);

    private:

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

    protected:
        std::string m_url; // The url of the trackable object
        datastructure::Transform3Df m_transform3D = Transform3Df::Identity(); // The 3D transform to the world coordinates system
};

DECLARESERIALIZE(Trackable);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Trackable);

}
} // end of namespace SolAR

#endif // TRACKABLE_H
