#ifndef IMULTIVIEWSTEREO_H
#define IMULTIVIEWSTEREO_H

#include "xpcf/api/IComponentIntrospect.h"
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
 * @brief <B>???</B>
 * <TT>UUID: d73ae23f-e1ce-4abe-91cd-9aa2f34c8dff</TT>
 *
 * ???
 */

class XPCF_IGNORE IMultiViewStereo : virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    ///@brief IStructureFromMotion default constructor.
    IMultiViewStereo() = default;

    ///@brief IStructureFromMotion default destructor.
    virtual ~IMultiViewStereo() override = default;



    /// @brief Create map
    /// @param[in] keyframe: the keyframe to add to the bag of words
    /// @return FrameworkReturnCode::_SUCCESS if the keyfram adding succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createDenseMap(const SRef<SolAR::datastructure::Map>& map,
                                               SRef<SolAR::datastructure::Map>& densemap) = 0; //last argument for test
};


} // namespace mvs
} // namespace api
} // namespace SolAR


template <> struct org::bcom::xpcf::InterfaceTraits<SolAR::api::sfm::IMultiViewStereo>
{
    static constexpr const char * UUID = "{d73ae23f-e1ce-4abe-91cd-9aa2f34c8dff}";
    static constexpr const char * NAME = "IMultiViewStereo";
    static constexpr const char * DESCRIPTION = "IMultiViewStereo interface description";
};
#endif // IMULTIVIEWSTEREO_H
