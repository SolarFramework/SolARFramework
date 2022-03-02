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

#ifndef TRACKABLE2D_H
#define TRACKABLE2D_H

#include <datastructure/Trackable.h>
#include <datastructure/GeometryDefinitions.h>
#include <core/Messages.h>

// Definition of Trackable2D Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
    * @class Trackable2D
    * @brief <B>This abstract class defines the generic 2D trackable datastructure.</B>
    */
class SOLARFRAMEWORK_API Trackable2D : virtual public Trackable {
    public:
        ///
        /// @brief Trackable default constructor
        ///
        Trackable2D() = default;

        ///
        /// @brief Trackable2D constructor
        /// with url and size
        ///
        Trackable2D(const std::string & url, const Sizef & size);

        ///
        /// @brief Trackable2D constructor
        /// with url, width and height
        ///
        Trackable2D(const std::string & url, const float & width, const float & height);

        ///
        /// @brief Trackable2D destructor
        ///
        virtual ~Trackable2D();

        // Class methods

        /// @brief Provides the size of the 2D trackable object
        /// @return size value
        Sizef getSize() const;

        /// @brief Provides the width of the 2D trackable object
        /// @return width value
        float getWidth() const;

        /// @brief Provides the height of the 2D trackable object
        /// @return height value
        float getHeight() const;

        /// @brief Sets the size of the 2D trackable object
        /// @param[in] size: size value
        void setSize(const Sizef & size);

        /// @brief Sets the width of the 2D trackable object
        /// @param[in] width: width value
        void setWidth(const float & width);

        /// @brief Sets the height of the 2D trackable object
        /// @param[in] height: height value
        void setHeight(const float & height);

        /// @brief Provide the position of 3D corners in world coordinate system
        /// @param[out] worldCorners the 3D corners of the marker in world coordinate system
        /// @return FrameworkReturnCode::_SUCCESS if sucessful, eiher FrameworkRetunrnCode::_ERROR_.
        FrameworkReturnCode getWorldCorners(std::vector<SolAR::datastructure::Point3Df> & worldCorners) const;

    private:

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

    protected:
        Sizef m_size; // Size (width and height) of 2D trackable object
};

DECLARESERIALIZE(Trackable2D);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Trackable2D);

}
} // end of namespace SolAR

#endif // TRACKABLE2D_H
