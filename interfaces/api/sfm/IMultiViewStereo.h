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

///@enum class MvsStatus
enum class MvsStatus {
    NOT_INITIALIZED,
    IDLE_INITIALIZED,
    RUNNING_IMAGE_UNDISTORTION,
    IDLE_IMAGE_UNDISTORTION_FINISHED,
    RUNNING_PATCH_MATCH,
    IDLE_PATCH_MATCH_FINISHED,
    RUNNING_STEREO_FUSION,
    IDLE_STEREO_FUSION_FINISHED,
    IDLE_COMPLETED,
    IDLE_ABORTED,
};

/// @brief map from MvsStatus to string
const static std::map<MvsStatus, std::string> mapMvsStatusToStr = {
    {MvsStatus::NOT_INITIALIZED, "NOT_INITIALIZED"},
    {MvsStatus::IDLE_INITIALIZED, "IDLE_INITIALIZED"},
    {MvsStatus::RUNNING_IMAGE_UNDISTORTION, "RUNNING_IMAGE_UNDISTORTION"},
    {MvsStatus::IDLE_IMAGE_UNDISTORTION_FINISHED, "IDLE_IMAGE_UNDISTORTION_FINISHED"},
    {MvsStatus::RUNNING_PATCH_MATCH, "RUNNING_PATCH_MATCH"},
    {MvsStatus::IDLE_PATCH_MATCH_FINISHED, "IDLE_PATCH_MATCH_FINISHED"},
    {MvsStatus::RUNNING_STEREO_FUSION, "RUNNING_STEREO_FUSION"},
    {MvsStatus::IDLE_STEREO_FUSION_FINISHED, "IDLE_STEREO_FUSION_FINISHED"},
    {MvsStatus::IDLE_COMPLETED, "IDLE_COMPLETED"},
    {MvsStatus::IDLE_ABORTED, "IDLE_ABORTED"}
};

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
    /// @return FrameworkReturnCode::_SUCCESS if the keyfram adding succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createDensePointCloud(const SRef<SolAR::datastructure::Map>& map) = 0; //last argument for test

    /// @brief Get output map
    /// @param[out] map the output MVS map
    /// @return FrameworkReturnCode::_SUCCESS if map was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getOutputMap(SRef<SolAR::datastructure::Map>& map) = 0;

    /// @brief Get MVS status
    /// @return status the current MVS status
    virtual MvsStatus getStatus() = 0;

    /// @brief Get MVS progress percentage
    /// @return progress percentage between 0 and 1
    virtual float getProgress() = 0;

    /// @brief Get current cloud points
    /// @param[out] cloudPoints current point cloud consisting of a number of 3D points
    /// @return FrameworkReturnCode::_SUCCESS if points was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCurrentCloudPoints(std::vector<SRef<SolAR::datastructure::CloudPoint>>& cloudPoints) = 0;

    /// @brief force stop
    virtual void forceStop() = 0;

    /// @brief release memory usage
    virtual void releaseMemoryUsage() = 0;
};


} // namespace mvs
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::sfm::IMultiViewStereo,
                             "d73ae23f-e1ce-4abe-91cd-9aa2f34c8dff",
                             "IMultiViewStereo",
                             "IMultiViewStereo interface description");

#endif // IMULTIVIEWSTEREO_H
