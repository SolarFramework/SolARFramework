#ifndef IMULTIVIEWSTEREO_H
#define IMULTIVIEWSTEREO_H

#include <xpcf/api/IComponentIntrospect.h>
#include "core/Messages.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/Keypoint.h"
#include "datastructure/Map.h"

namespace SolAR {
namespace api {
namespace sfm {

/**
 * @class IMultiViewStereo
 * @brief <B>Create a dense point cloud from images with corresponding poses.</B>
 * <TT>UUID: d73ae23f-e1ce-4abe-91cd-9aa2f34c8dff</TT>
 *
 */

class XPCF_IGNORE IMultiViewStereo : virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    ///@brief IStructureFromMotion default constructor.
    IMultiViewStereo() = default;

    ///@brief IStructureFromMotion default destructor.
    virtual ~IMultiViewStereo() override = default;



    /// @brief Create dense point cloud
    /// @param[in] map: the sparse map to densify
    /// @param[in] densePointCloud: the dense point cloud resulting from the densification of the sparse map
    /// @return FrameworkReturnCode::_SUCCESS if the keyfram adding succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createDensePointCloud(const SRef<SolAR::datastructure::Map>& map,
                                                      SRef<SolAR::datastructure::PointCloud>& densePointCloud) = 0; //last argument for test
};


} // namespace mvs
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::sfm::IMultiViewStereo,
                             "d73ae23f-e1ce-4abe-91cd-9aa2f34c8dff",
                             "IMultiViewStereo",
                             "IMultiViewStereo interface description");

#endif // IMULTIVIEWSTEREO_H
