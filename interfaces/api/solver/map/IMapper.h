#ifndef IMAPPER_H
#define IMAPPER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of IMapper Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

#include "datastructure/Keyframe.h"
#include "datastructure/Frame.h"
#include "datastructure/Keypoint.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/Map.h"

namespace SolAR {
    using namespace datastructure;
    namespace api {
        namespace solver {
            namespace map {
///
/// @brief The IMapper class
///

            class  IMapper : public virtual org::bcom::xpcf::IComponentIntrospect {
                    public:
                       IMapper() = default;
                       ///
                       ///@brief ~IMapper
                       ///
                       virtual ~IMapper() {}

                       virtual bool find2D3DCorrespondances(const int keyframe_id,
                                                            const std::vector<DescriptorMatch>&current_matches,
                                                            const std::vector<SRef<Keypoint>>&kp,
                                                            std::vector<SRef<Point2Df>>&pt2d,
                                                            std::vector<SRef<Point3Df>>&pt3d) = 0 ;

                       virtual bool initMap(SRef<Keyframe>&kframe_t0,
                                            SRef<Keyframe>&kframe_t1,
                                            std::vector<SRef<CloudPoint>>&new_cloud,
                                            std::vector<DescriptorMatch>&matches) = 0;

                        virtual SRef<Map> getMap() = 0 ;


                       virtual void associateReferenceKeyFrameToFrame(SRef<Frame> frame) = 0 ;


                       virtual bool tryToAddKeyFrame(SRef<Frame> frame) = 0;

                       virtual void testMethod()=0;
                       XPCF_DECLARE_UUID("90075c1b-915b-469d-b92d-41c5d575bf15");
                    };
            }
        }
    }
}


#endif // IMAPPER_H
