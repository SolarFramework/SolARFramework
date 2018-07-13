#ifndef IMAPFILTER_H
#define IMAPFILTER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of IMapper Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

#include "datastructure/CloudPoint.h"

namespace SolAR {
    using namespace datastructure;
    namespace api {
        namespace solver {
            namespace map {
///
/// @brief The IMapFilter class
///
            class  IMapFilter : public virtual org::bcom::xpcf::IComponentIntrospect {
                    public:
                       IMapFilter() = default;
                       ///
                       ///@brief ~IMapper
                       ///
                       virtual ~IMapFilter() {}


					   /// @brief Check triangulation status.Warn negative-Z triangulated points.
					   /// @param[in] Set of triangulated 3d_points.
					   /// @param[in] Camera pose of the second view at triangulation step (the first one supposed canonical).
					   /// @param[out] Status of each reprojected =3d_point (false: negative-z, true: non-negative z).
					   /// @return validity of the triangulated points
					   virtual  bool checkFrontCameraPoints(const std::vector<SRef<CloudPoint>>& pcloud, const Transform3Df & cameraPose, std::vector<bool> & isFrontCamera) = 0;

					   /// @brief  Filter point cloud according to reprojection error and front camera status
					   /// @param[in] Set of triangulated 3d_points.
					   /// @param[in] Status of each reprojected =3d_point (false: negative-z, true: non-negative z).
					   /// @param[out] filtered point cloud without z negative points and points with a large reprojection error
                       virtual void  filterPointCloud(const std::vector<SRef<CloudPoint>>& input, const std::vector<bool> & isFrontCamera,  std::vector<SRef<CloudPoint>>& output) = 0;

                    };
            }
        }
    }
}
XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IMapFilter,
                             "e0d6cc82-6af2-493d-901a-2384fca0b16f",
                             "SolAR::api::solver::map::IMapFilter interface");


#endif // IMAPPER_H
