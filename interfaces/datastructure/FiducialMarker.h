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

#ifndef FIDUCIALMARKER_H
#define FIDUCIALMARKER_H

#include <datastructure/SquaredBinaryPattern.h>
#include <datastructure/Trackable2D.h>

// Definition of FiducialMarker Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
    * @class FiducialMarker
    * @brief <B>This class defines a fiducial marker datastructure.</B>
    */
class SOLARFRAMEWORK_API FiducialMarker : virtual public Trackable2D {
    public:
        ///
        /// @brief FiducialMarker default constructor
        ///
        FiducialMarker() = default;

        ///
        /// @brief FiducialMarker constructor
        /// with binary pattern and size of fiducial image
        /// @param[in] url: url of the trackable object
        /// @param[in] size: size (width and height) of the fiducial marker image
        /// @param[in] binaryPattern: binary pattern of the fiducial marker
        ///
        FiducialMarker(const std::string & url, const Sizef & size, const SquaredBinaryPattern & binaryPattern);

        // Class methods

        ///
        /// @brief Returns the type of the Trackable object
        /// @return TrackableType: the type of the instance
        ///
        TrackableType getType() const override;

        /// @brief Sets the binary pattern of the fiducial marker
        /// @param[in] binaryPattern: the binary pattern of the fiducial marker object
        void setPattern(const SquaredBinaryPattern & binaryPattern);

        /// @brief Returns the pattern of the fiducial marker
        /// @result SquaredBinaryPattern: the binary pattern of the fiducial marker object
        SquaredBinaryPattern getPattern() const;

    private:
        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar,  const unsigned int version);

    private:
        SquaredBinaryPattern m_pattern; // Binary pattern of the fiducial marker

    public:
        template <typename JsonType>
        friend void to_json(JsonType& j, const FiducialMarker& marker)
        {
            j["url"] = marker.m_url;
            j["transform3D"] = marker.m_transform3D;
            j["size"]["width"] = marker.m_size.width;
            j["size"]["height"] = marker.m_size.height;
            j["pattern"] = marker.m_pattern.getPatternMatrix();
        }
        template <typename JsonType>
        friend void from_json(JsonType& j, FiducialMarker& marker)
        {
            marker.m_url = j.at("url");
            marker.m_transform3D = j.at("transform3D");
            marker.m_size.width = j["size"]["width"].template get<float>();
            marker.m_size.height = j["size"]["height"].template get<float>();
            SquaredBinaryPatternMatrix spm;
            spm = j["pattern"].template get<SquaredBinaryPatternMatrix>();
            marker.m_pattern.setPatternMatrix(spm);
        }
};

DECLARESERIALIZE(FiducialMarker);

}
} // end of namespace SolAR

#endif // FIDUCIALMARKER_H
