%module solar
%{
#include "SharedBuffer.hpp"
#include "SharedCircularBuffer.hpp"
#include "SharedFifo.hpp"
%}

%include "Swig.i"

///

%include "SharedFifo.hpp"

//%include "SharedFifo.i"
%include "SharedBuffer.hpp"

//%include "SharedFifo.i"
%include "SharedCircularBuffer.hpp"

///

%{
#include <xpcf/xpcf.h>

#include "api/display/I2DOverlay.h"
#include "api/display/I3DOverlay.h"
#include "api/display/I3DPointsViewer.h"
#include "api/display/IImageViewer.h"
#include "api/display/IMatchesOverlay.h"

#include "api/example/IInterface1.h"
#include "api/example/IInterface2.h"

#include "api/features/IContoursExtractor.h"
#include "api/features/IContoursFilter.h"
#include "api/features/IDescriptorMatcher.h"
#include "api/features/IDescriptorsExtractor.h"
#include "api/features/IDescriptorsExtractorSBPattern.h"
#include "api/features/IKeypointDetector.h"
#include "api/features/IKeypointsReIndexer.h"
#include "api/features/IMatchesFilter.h"
#include "api/features/ISBPatternReIndexer.h"

#include "api/fusion/IVisualInertialFusion.h"

#include "api/geom/I2DTransform.h"
#include "api/geom/I3DTransform.h"
#include "api/geom/IImage2WorldMapper.h"
#include "api/geom/IUndistortPoints.h"

#include "api/image/IImageConvertor.h"
#include "api/image/IImageFilter.h"
#include "api/image/IImageLoader.h"
#include "api/image/IPerspectiveController.h"

#include "api/input/devices/ICamera.h"
#include "api/input/devices/ICameraCalibration.h"
#include "api/input/devices/IIMU.h"

#include "api/input/files/IMarker.h"
#include "api/input/files/IMarker2DNaturalImage.h"
#include "api/input/files/IMarker2DSquared.h"
#include "api/input/files/IMarker2DSquaredBinary.h"

#include "api/pipeline/IPipeline.h"

#include "api/reloc/IKeyframeRetriever.h"
#include "api/reloc/IRelocalizer.h"

#include "api/sink/ISinkPoseImage.h"
#include "api/sink/ISinkPoseTextureBuffer.h"
#include "api/sink/ISinkReturnCode.h"

#include "api/solver/map/IBundler.h"
#include "api/solver/map/IKeyframeSelector.h"
#include "api/solver/map/IMapFilter.h"
#include "api/solver/map/IMapper.h"
#include "api/solver/map/ITriangulator.h"

#include "api/solver/pose/I2D3DCorrespondencesFinder.h"
#include "api/solver/pose/I2Dto3DTransformDecomposer.h"
//#include "api/solver/pose/I2Dto3DTransformDecomposerValidation.h" //TODO Wrong Namespace
#include "api/solver/pose/I2DTransformFinder.h"
#include "api/solver/pose/I3DTransformFinderFrom2D2D.h"
#include "api/solver/pose/I3DTransformFinderFrom2D3D.h"
#include "api/solver/pose/I3DTransformSACFinderFrom2D3D.h"
#include "api/solver/pose/IHomographyValidation.h"

#include "api/source/ISourceImage.h"
#include "api/source/ISourceReturnCode.h"
%}

%import (module="XPCF.Core") "XPCF_Core.i"

%inline %{
template <class I>
SRef<I> bindTo(SRef<org::bcom::xpcf::IComponentIntrospect> component)
{
	return component->bindTo<I>();
};
%}

%define BIND_TO_INTERFACE(NAME, TYPE)
%rename(bindTo_ ## NAME) bindTo<TYPE>;
%template(bindTo_ ## NAME) bindTo<TYPE>;
%enddef

/*
//TODO Try to redefine XPCF_DEFINE_BIND_TO_INTERFACE_TRAITS to automatically BIND_TO_INTERFACE
#undef XPCF_DEFINE_BIND_TO_INTERFACE_TRAITS

#define XPCF_DEFINE_BIND_TO_INTERFACE_TRAITS(fullComponentType,uuidString,nameString,descriptionString) \
%warn "900:" ## nameString

%define XPCF_DEFINE_BIND_TO_INTERFACE_TRAITS(fullComponentType,uuidString,nameString,descriptionString)
%warn "900:" ## nameString
%enddef

#undef XPCF_DEFINE_COMPONENT_TRAITS
#define XPCF_DEFINE_COMPONENT_TRAITS(fullComponentType,uuidString,nameString,descriptionString)
*/

%import (module="SolAR.Api.Display")	"SolAR_Api_Display.i"
%import (module="SolAR.Api.Example")	"SolAR_Api_Example.i"
%import (module="SolAR.Api.Features")	"SolAR_Api_Features.i"
%import (module="SolAR.Api.Fusion")		"SolAR_Api_Fusion.i"
%import (module="SolAR.Api.Geom")		"SolAR_Api_Geom.i"
%import (module="SolAR.Api.Image")		"SolAR_Api_Image.i"
%import (module="SolAR.Api.Input.Devices")	"SolAR_Api_Input_Devices.i"
%import (module="SolAR.Api.Input.Files")	"SolAR_Api_Input_Files.i"
%import (module="SolAR.Api.Pipeline")	"SolAR_Api_Pipeline.i"
%import (module="SolAR.Api.Reloc")		"SolAR_Api_Reloc.i"
%import (module="SolAR.Api.Sink")		"SolAR_Api_Sink.i"
%import (module="SolAR.Api.Solver.Map")	"SolAR_Api_Solver_Map.i"
%import (module="SolAR.Api.Solver.Pose")	"SolAR_Api_Solver_Pose.i"
%import (module="SolAR.Api.Source")		"SolAR_Api_Source.i"

%pragma(csharp) moduleimports=%{
    using XPCF.Api;
    using SolAR.Api.Display;
    using SolAR.Api.Example;
    using SolAR.Api.Features;
    using SolAR.Api.Fusion;
    using SolAR.Api.Geom;
    using SolAR.Api.Image;
    using SolAR.Api.Input.Devices;
    using SolAR.Api.Input.Files;
    using SolAR.Api.Pipeline;
    using SolAR.Api.Reloc;
    using SolAR.Api.Sink;
    using SolAR.Api.Solver.Map;
    using SolAR.Api.Solver.Pose;
    using SolAR.Api.Source;
%}

//*
BIND_TO_INTERFACE(IConfigurable,	xpcf::IConfigurable)

BIND_TO_INTERFACE(I2DOverlay,		SolAR::api::display::I2DOverlay)
BIND_TO_INTERFACE(I3DOverlay,		SolAR::api::display::I3DOverlay)
BIND_TO_INTERFACE(I3DPointsViewer,	SolAR::api::display::I3DPointsViewer)
BIND_TO_INTERFACE(IImageViewer,		SolAR::api::display::IImageViewer)
BIND_TO_INTERFACE(IMatchesOverlay,	SolAR::api::display::IMatchesOverlay)

BIND_TO_INTERFACE(IInterface1,	SolAR::api::example::IInterface1)
BIND_TO_INTERFACE(IInterface2,	SolAR::api::example::IInterface2)

BIND_TO_INTERFACE(IContoursExtractor,		SolAR::api::features::IContoursExtractor)
BIND_TO_INTERFACE(IContoursFilter,			SolAR::api::features::IContoursFilter)
BIND_TO_INTERFACE(IDescriptorMatcher,		SolAR::api::features::IDescriptorMatcher)
BIND_TO_INTERFACE(IDescriptorsExtractor,	SolAR::api::features::IDescriptorsExtractor)
BIND_TO_INTERFACE(IDescriptorsExtractorSBPattern,	SolAR::api::features::IDescriptorsExtractorSBPattern)
BIND_TO_INTERFACE(IKeypointDetector,		SolAR::api::features::IKeypointDetector)
BIND_TO_INTERFACE(IKeypointsReIndexer,		SolAR::api::features::IKeypointsReIndexer)
BIND_TO_INTERFACE(IMatchesFilter,			SolAR::api::features::IMatchesFilter)
BIND_TO_INTERFACE(ISBPatternReIndexer,		SolAR::api::features::ISBPatternReIndexer)

BIND_TO_INTERFACE(IVisualInertialFusion,	SolAR::api::fusion::IVisualInertialFusion)

BIND_TO_INTERFACE(I2DTransform,			SolAR::api::geom::I2DTransform)
BIND_TO_INTERFACE(I3DTransform,			SolAR::api::geom::I3DTransform)
BIND_TO_INTERFACE(IImage2WorldMapper,	SolAR::api::geom::IImage2WorldMapper)
BIND_TO_INTERFACE(IUndistortPoints,	SolAR::api::geom::IUndistortPoints)

BIND_TO_INTERFACE(IImageConvertor,			SolAR::api::image::IImageConvertor)
BIND_TO_INTERFACE(IImageFilter,				SolAR::api::image::IImageFilter)
BIND_TO_INTERFACE(IImageLoader,				SolAR::api::image::IImageLoader)
BIND_TO_INTERFACE(IPerspectiveController,	SolAR::api::image::IPerspectiveController)

BIND_TO_INTERFACE(ICamera,				SolAR::api::input::devices::ICamera)
BIND_TO_INTERFACE(ICameraCalibration,	SolAR::api::input::devices::ICameraCalibration)
BIND_TO_INTERFACE(IIMU,					SolAR::api::input::devices::IIMU)

BIND_TO_INTERFACE(IMarker,					SolAR::api::input::files::IMarker)
BIND_TO_INTERFACE(IMarker2DNaturalImage,	SolAR::api::input::files::IMarker2DNaturalImage)
BIND_TO_INTERFACE(IMarker2DSquared,			SolAR::api::input::files::IMarker2DSquared)
BIND_TO_INTERFACE(IMarker2DSquaredBinary,	SolAR::api::input::files::IMarker2DSquaredBinary)

BIND_TO_INTERFACE(IPipeline,	SolAR::api::pipeline::IPipeline)

BIND_TO_INTERFACE(IKeyframeRetriever,	SolAR::api::reloc::IKeyframeRetriever)
BIND_TO_INTERFACE(IRelocalizer,			SolAR::api::reloc::IRelocalizer)

BIND_TO_INTERFACE(ISinkPoseImage,	SolAR::api::sink::ISinkPoseImage)
BIND_TO_INTERFACE(ISinkPoseTextureBuffer,	SolAR::api::sink::ISinkPoseTextureBuffer)

BIND_TO_INTERFACE(IBundler,				SolAR::api::solver::map::IBundler)
BIND_TO_INTERFACE(IKeyframeSelector,	SolAR::api::solver::map::IKeyframeSelector)
BIND_TO_INTERFACE(IMapFilter,			SolAR::api::solver::map::IMapFilter)
BIND_TO_INTERFACE(IMapper,				SolAR::api::solver::map::IMapper)
BIND_TO_INTERFACE(ITriangulator,		SolAR::api::solver::map::ITriangulator)

BIND_TO_INTERFACE(I2D3DCorrespondencesFinder,	SolAR::api::solver::pose::I2D3DCorrespondencesFinder)
BIND_TO_INTERFACE(I2Dto3DTransformDecomposer,	SolAR::api::solver::pose::I2Dto3DTransformDecomposer)
//BIND_TO_INTERFACE(I2Dto3DTransformDecomposerValidation,	SolAR::api::solver::pose::I2Dto3DTransformDecomposerValidation) //TODO Wrong Namespace
BIND_TO_INTERFACE(I2DTransformFinder,			SolAR::api::solver::pose::I2DTransformFinder)
BIND_TO_INTERFACE(I3DTransformFinderFrom2D2D,	SolAR::api::solver::pose::I3DTransformFinderFrom2D2D)
BIND_TO_INTERFACE(I3DTransformFinderFrom2D3D,	SolAR::api::solver::pose::I3DTransformFinderFrom2D3D)
BIND_TO_INTERFACE(I3DTransformSACFinderFrom2D3D,	SolAR::api::solver::pose::I3DTransformSACFinderFrom2D3D)
BIND_TO_INTERFACE(IHomographyValidation,		SolAR::api::solver::pose::IHomographyValidation)

BIND_TO_INTERFACE(ISourceImage,		SolAR::api::source::ISourceImage)
/* */
