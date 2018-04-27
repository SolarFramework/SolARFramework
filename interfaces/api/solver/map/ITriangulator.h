#ifndef ITRIANGULATOR_H
#define ITRIANGULATOR_H

#include "IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Pose.h"

namespace SolAR {
    using namespace datastructure;
    namespace api {
        namespace solver {
            namespace map {
            /**
             * @class ITriangulator
             * @brief Triangulates a set of 2D-2d points correspondances with known respective camera poses.
             */
            class  ITriangulator : public virtual org::bcom::xpcf::IComponentIntrospect {
            public:
                /// @brief ITriangulator default constructor
                ITriangulator() = default;

                /// @brief ITriangulator default destructor
                virtual ~ITriangulator() = default;
                /// @brief triangulate pairs of points 2d captured from two views with differents poses (with respect to the camera instrinsic parameters).
                /// @param[in] Set of 2d_points seen in view_1.
                /// @param[in] Set of 2d_points seen in view_2.
                /// @param[in] Camera pose in the world coordinates system of the view_1.
                /// @param[in] Camera pose in the world coordinates system of the view_2.
                /// @param[in] Camera calibration matrix parameters.
                /// @param[in] Camera calibration distorsion parameters.
                /// @param[out] Set of triangulated 3d_points.
                virtual FrameworkReturnCode triangulate(const std::vector<SRef<Point2Df>>& pt2d_1,
                                         const std::vector<SRef<Point2Df>>& pt2d_2,
                                         const SRef<Pose>&p1,
                                         const SRef<Pose>&p2,
                                         const CamCalibration&cam,
                                         const CamDistortion&dist,
                                         std::vector<SRef<Point3Df>>& pt3d)=0;

                XPCF_DECLARE_UUID("3a01b0e9-9a76-43f5-97b3-85bb6979b953");
            };

}
}
}
}  // end of namespace Solar

#endif // ITRIANGULATOR_H
