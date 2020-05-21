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

#ifndef IMAPPER_H
#define IMAPPER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of IMapper Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

#include "datastructure/Identification.h"
#include "datastructure/CoordinateSystem.h"
#include "api/storage/ICovisibilityGraph.h"
#include "api/storage/IKeyframesManager.h"
#include "api/storage/IPointCloudManager.h"
#include "api/reloc/IKeyframeRetriever.h"

namespace SolAR {
    using namespace datastructure;
    namespace api {
		using namespace storage;
		using namespace reloc;
        namespace solver {
            namespace map {
/**
  * @class IMapper
  * @brief <B>Allow to manage all components of a map.</B>
  * <TT>UUID: 90075c1b-915b-469d-b92d-41c5d575bf15</TT>
  */

class  IMapper : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
   IMapper() = default;
   ///
   ///@brief ~IMapper
   ///
   virtual ~IMapper() {}

   /// @brief Set identification component.
   /// @param[in] an identification instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode setIdentification (SRef<Identification> &identification) = 0;

   /// @brief Get identification component.
   /// @param[out] an identification instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode getIdentification(SRef<Identification> &identification) = 0;

   /// @brief Set coordinate system component.
   /// @param[in] a coordinate system instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode setCoordinateSystem(SRef<CoordinateSystem> &coordinateSystem) = 0;

   /// @brief Get coordinate system component.
   /// @param[out] a coordinate system instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode getCoordinateSystem(SRef<CoordinateSystem> &coordinateSystem) = 0;

   /// @brief Set point cloud component.
   /// @param[in] a point cloud instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode setPointCloudManager(SRef<IPointCloudManager> &pointCloudManager) = 0;

   /// @brief Get point cloud component.
   /// @param[out] a point cloud instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode getPointCloudManager(SRef<IPointCloudManager> &pointCloudManager) = 0;

   /// @brief Set keyframes manager component.
   /// @param[in] a keyframes manager instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode setKeyframesManager(SRef<IKeyframesManager> &keyframesManager) = 0;

   /// @brief Get keyframes manager component.
   /// @param[out] a keyframes manager instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode getKeyframesManager(SRef<IKeyframesManager> &keyframesManager) = 0;

   /// @brief Set covisibility graph component.
   /// @param[in] a covisibility graph instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode setCovisibilityGraph(SRef<ICovisibilityGraph> &covisibilityGraph) = 0;

   /// @brief Get covisibility graph component.
   /// @param[out] a covisibility graph instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode getCovisibilityGraph(SRef<ICovisibilityGraph> &covisibilityGraph) = 0;

   /// @brief Set keyframe retriever component.
   /// @param[in] a keyframe retriever instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode setKeyframeRetriever(SRef<IKeyframeRetriever> &keyframeRetriever) = 0;

   /// @brief Get keyframe retriever component.
   /// @param[out] a keyframe retriever instance
   /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
   virtual FrameworkReturnCode getKeyframeRetriever(SRef<IKeyframeRetriever> &keyframeRetriever) = 0;

   /// @brief Save the map to the external file
	/// @param[out] the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
   virtual FrameworkReturnCode saveToFile(std::string file) = 0;

   /// @brief Load the map from the external file
   /// @param[in] the file name
   /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
   virtual FrameworkReturnCode loadFromFile(std::string file) = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IMapper,
                             "90075c1b-915b-469d-b92d-41c5d575bf15",
                             "IMapper",
                             "SolAR::api::solver::map::IMapper defines the interface of a mapper that manages all components of a map such as point cloud, keyframes, retriever model, coordinate, identification.");

#endif // IMAPPER_H
