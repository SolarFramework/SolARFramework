#ifndef IMAPPER_H
#define IMAPPER_H

// Definition of IMapper Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
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

                       virtual bool initMap(SRef<Keyframe>&kframe_t0,
                                            SRef<Keyframe>&kframe_t1,
                                            std::vector<SRef<CloudPoint>>&new_cloud,
                                            std::vector<DescriptorMatch>&matches) = 0;

                       virtual void addNewKeyFrame(const SRef<Frame> & frame, SRef<Keyframe>& newKeyframe) = 0;

                       virtual SRef<Keyframe> getCurrentKeyframe(int idx) = 0;

                       virtual SRef<Map> getMap() = 0 ;

                       virtual bool updateMap(const SRef<Keyframe>&new_kframe,
                                              const std::vector<DescriptorMatch>& found_matches,
                                              const std::vector<DescriptorMatch>& new_matches,
                                              const std::vector<SRef<CloudPoint>>& newCloud) = 0;

                       virtual void associateReferenceKeyFrameToFrame(SRef<Frame> frame) = 0 ;

                       virtual std::vector<SRef<Keyframe>> getKeyframes() = 0;

                       virtual std::map<std::pair<int, int>, std::vector<DescriptorMatch> > getMatchesMatrix() = 0;
                       virtual int isKeyFrameCandidate(SRef<Frame> frame) = 0;

                    };
            }
        }
    }
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IMapper,
                             "90075c1b-915b-469d-b92d-41c5d575bf15",
                             "SolAR::api::solver::map::IMapper interface");

#endif // IMAPPER_H
