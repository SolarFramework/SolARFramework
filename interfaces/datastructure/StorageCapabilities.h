/**
 * @copyright Copyright (c) 2021-2022 B-com http://www.b-com.com/
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
#ifndef STORAGECAPABILITIES_H
#define STORAGECAPABILITIES_H

#include <nlohmann/json.hpp>
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/StorageTrackable.h"

namespace SolAR {
namespace datastructure {



        /**
            * @class StorageCapabilities
            * @brief <B>This class defines the generic StorageCapabilities datastructure.</B>
            */
        class SOLARFRAMEWORK_API StorageCapabilities
        {

            public:

                ////////////////////////////
                ///     CONSTRUCTORS    ////
                ////////////////////////////

                ///
                /// @brief StorageCapabilities default constructor
                ///
                StorageCapabilities() = default;

                ///
                /// @brief StorageCapabilities default destructor
                ///
                virtual ~StorageCapabilities() = default;

                ///
                /// @brief StorageCapabilities constructor with all its attributes
                ///
                StorageCapabilities(StorageTrackableType trackableType,EncodingInfo encodingInformation );

                /// @brief Getter for the type of Trackable
                StorageTrackableType getTrackableType() const;

                /// @brief Setter for the type of Trackable
                void setTrackableType(StorageTrackableType newType);

                /// @brief Getter for the EncodingInformation
                EncodingInfo getEncodingInformation() const;

                /// @brief Setter for the encodingInformation
                void setEncodingInformation(EncodingInfo newEncodingInfo);

            protected:
                StorageTrackableType m_trackableType;
                EncodingInfo m_encodingInformation;
        };
    }

}


#endif // STORAGECAPABILITIES_H
