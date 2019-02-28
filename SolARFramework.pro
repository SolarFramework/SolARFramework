## remove Qt dependencies
QT       -= core gui
CONFIG -= qt

#Add support for clang compiler
#QMAKE_CXX=clang

## global defintions : target lib name, version
TARGET = SolARFramework
INSTALLSUBDIR = bcomBuild
FRAMEWORK = $$TARGET
VERSION=0.5.1

DEFINES += MYVERSION=$${VERSION}
DEFINES += TEMPLATE_LIBRARY
CONFIG += c++11


CONFIG(debug,debug|release) {
    DEFINES += _DEBUG=1
    DEFINES += DEBUG=1
}

CONFIG(release,debug|release) {
    DEFINES += _NDEBUG=1
    DEFINES += NDEBUG=1
}
PROJECTDEPLOYDIR = $$(BCOMDEVROOT)/$${INSTALLSUBDIR}/$${FRAMEWORK}/$${VERSION}
DEPENDENCIESCONFIG = shared

#NOTE : CONFIG as staticlib or sharedlib, DEPENDENCIESCONFIG as staticlib or sharedlib, QMAKE_TARGET.arch and PROJECTDEPLOYDIR MUST BE DEFINED BEFORE templatelibconfig.pri inclusion
include ($$(BCOMDEVROOT)/builddefs/qmake/templatelibconfig.pri)

msvc {
DEFINES += "_BCOM_SHARED=__declspec(dllexport)"
}

HEADERS += interfaces/SharedBuffer.hpp \
interfaces/SharedCircularBuffer.hpp \
interfaces/SharedFifo.hpp \
interfaces/core/SolARFrameworkDefinitions.h \
interfaces/api/display/I2DOverlay.h \
interfaces/api/display/I3DOverlay.h \
interfaces/api/display/IImageViewer.h \
interfaces/api/display/IMatchesOverlay.h \
interfaces/api/display/I3DPointsViewer.h \
interfaces/api/example/IInterface1.h \
interfaces/api/example/IInterface2.h \
interfaces/api/features/IContoursExtractor.h \
interfaces/api/features/IDescriptorMatcher.h \
interfaces/api/features/IContoursFilter.h \
interfaces/api/features/IDescriptorsExtractor.h \
interfaces/api/features/IDescriptorsExtractorSBPattern.h \
interfaces/api/features/IKeypointDetector.h \
interfaces/api/features/IKeypointsReIndexer.h \
interfaces/api/features/ISBPatternReIndexer.h \
interfaces/api/features/IMatchesFilter.h \
interfaces/api/fusion/IVisualInertialFusion.h \
interfaces/api/geom/I2DTransform.h \
interfaces/api/geom/I3DTransform.h \
interfaces/api/geom/IImage2WorldMapper.h \
interfaces/api/image/IImageConvertor.h \
interfaces/api/image/IImageFilter.h \
interfaces/api/image/IImageLoader.h \
interfaces/api/image/IPerspectiveController.h \
interfaces/api/input/devices/ICamera.h \
interfaces/api/input/devices/ICameraCalibration.h \
interfaces/api/input/devices/IIMU.h \
interfaces/api/input/files/IMarker.h \
interfaces/api/input/files/IMarker2DNaturalImage.h \
interfaces/api/input/files/IMarker2DSquared.h \
interfaces/api/input/files/IMarker2DSquaredBinary.h \
interfaces/api/reloc/IKeyframeRetriever.h \
interfaces/api/reloc/IRelocalizer.h \
interfaces/api/solver/pose/IHomographyValidation.h \
interfaces/api/solver/pose/I2DTransformFinder.h \
interfaces/api/solver/pose/I2Dto3DTransformDecomposer.h \
interfaces/api/solver/pose/I2Dto3DTransformDecomposerValidation.h \
interfaces/api/solver/pose/I2D3DCorrespondencesFinder.h\
interfaces/api/solver/pose/I3DTransformFinderFrom2D3D.h \
interfaces/api/solver/pose/I3DTransformFinderFrom2D2D.h \
interfaces/api/solver/map/IBundler.h\
interfaces/api/solver/map/ITriangulator.h\
interfaces/api/solver/map/IMapFilter.h\
interfaces/api/solver/map/IMapper.h\
interfaces/core/SolARFramework.h \
interfaces/core/Messages.h \
interfaces/core/Log.h \
interfaces/datastructure/BufferInternal.hpp \
interfaces/datastructure/CloudPoint.h \
interfaces/datastructure/DescriptorBuffer.h \
interfaces/datastructure/DescriptorMatch.h \
interfaces/datastructure/GeometryDefinitions.h \
interfaces/datastructure/Image.h \
interfaces/datastructure/Keypoint.h \
interfaces/datastructure/Keyframe.h \
interfaces/datastructure/Frame.h \
interfaces/datastructure/Map.h \
interfaces/datastructure/MathDefinitions.h \
interfaces/datastructure/SquaredBinaryPattern.h \
interfaces/api/input/files/IMarker.h \
interfaces/api/input/files/IMarker2DNaturalImage.h \
interfaces/api/input/files/IMarker2DSquared.h \
interfaces/api/input/files/IMarker2DSquaredBinary.h \
interfaces/api/display/I3DPointsViewer.h \
interfaces/api/solver/pose/I3DTransformFinderFrom2D2D.h \
interfaces/api/solver/pose/I3DTransformFinderFrom2D3D.h \
interfaces/api/solver/pose/I3DTransformSACFinderFrom2D3D.h \
interfaces/api/solver/pose/I3DTransformFinderFrom2D2D.h \
interfaces/api/solver/map/IKeyframeSelector.h \
interfaces/api/pipeline/IPipeline.h \
interfaces/api/sink/ISinkPoseImage.h \
interfaces/api/sink/ISinkPoseTextureBuffer.h \
interfaces/api/sink/ISinkReturnCode.h \
interfaces/api/source/ISourceImage.h \
interfaces/api/source/ISourceReturnCode.h

SOURCES += src/core/SolARFramework.cpp \
    src/core/Log.cpp \
    src/datastructure/DescriptorBuffer.cpp \
    src/datastructure/Image.cpp \
    src/datastructure/Keypoint.cpp \
    src/datastructure/SquaredBinaryPattern.cpp \
    src/datastructure/Frame.cpp \
    src/datastructure/Keyframe.cpp \
    src/datastructure/CloudPoint.cpp \
    src/datastructure/Map.cpp

unix {
#
#   if buidling with clang
#	    QMAKE_CXX = clang++
#   	QMAKE_LINK= clang++
#
}

macx {
    DEFINES += _MACOS_TARGET_
    QMAKE_MAC_SDK= macosx
    QMAKE_CFLAGS += -mmacosx-version-min=10.7 -std=c11 #-x objective-c++
    QMAKE_CXXFLAGS += -mmacosx-version-min=10.7 -std=c11 -std=c++11 -fPIC#-x objective-c++
    QMAKE_LFLAGS += -mmacosx-version-min=10.7 -v -lstdc++
    LIBS += -lstdc++ -lc -lpthread
}

win32 {

    DEFINES += WIN64 UNICODE _UNICODE
    QMAKE_COMPILER_DEFINES += _WIN64
    QMAKE_CXXFLAGS += -wd4250 -wd4251 -wd4244 -wd4275
}
header_interfaces.path  = $${PROJECTDEPLOYDIR}/interfaces/
header_interfaces.files  = $$files($${PWD}/interfaces/*.h*)

header_interfaces_display.path  = $${PROJECTDEPLOYDIR}/interfaces/api/display/
header_interfaces_display.files = $$files($${PWD}/interfaces/api/display/*.h*)
header_interfaces_features.path = $${PROJECTDEPLOYDIR}/interfaces/api/features/
header_interfaces_features.files = $$files($${PWD}/interfaces/api/features/*.h*)
header_interfaces_fusion.path = $${PROJECTDEPLOYDIR}/interfaces/api/fusion/
header_interfaces_fusion.files = $$files($${PWD}/interfaces/api/fusion/*.h*)
header_interfaces_geom.path = $${PROJECTDEPLOYDIR}/interfaces/api/geom/
header_interfaces_geom.files = $$files($${PWD}/interfaces/api/geom/*.h*)
header_interfaces_image.path = $${PROJECTDEPLOYDIR}/interfaces/api/image/
header_interfaces_image.files = $$files($${PWD}/interfaces/api/image/*.h*)
header_interfaces_input_devices.path = $${PROJECTDEPLOYDIR}/interfaces/api/input/devices/
header_interfaces_input_devices.files = $$files($${PWD}/interfaces/api/input/devices/*.h*)
header_interfaces_input_files.path = $${PROJECTDEPLOYDIR}/interfaces/api/input/files/
header_interfaces_input_files.files = $$files($${PWD}/interfaces/api/input/files/*.h*)
header_interfaces_reloc.path = $${PROJECTDEPLOYDIR}/interfaces/api/reloc/
header_interfaces_reloc.files = $$files($${PWD}/interfaces/api/reloc/*.h*)
header_interfaces_sink.path = $${PROJECTDEPLOYDIR}/interfaces/api/sink
header_interfaces_sink.files = $$files($${PWD}/interfaces/api/sink/*.h*)
header_interfaces_source.path = $${PROJECTDEPLOYDIR}/interfaces/api/source
header_interfaces_source.files = $$files($${PWD}/interfaces/api/source/*.h*)
header_interfaces_solver_pose.path = $${PROJECTDEPLOYDIR}/interfaces/api/solver/pose/
header_interfaces_solver_pose.files = $$files($${PWD}/interfaces/api/solver/pose/*.h*)

header_interfaces_solver_map.path = $${PROJECTDEPLOYDIR}/interfaces/api/solver/map/
header_interfaces_solver_map.files = $$files($${PWD}/interfaces/api/solver/map/*.h*)

header_interfaces_reloc.path = $${PROJECTDEPLOYDIR}/interfaces/api/reloc/
header_interfaces_reloc.files = $$files($${PWD}/interfaces/api/reloc/*.h*)

header_interfaces_example.path = $${PROJECTDEPLOYDIR}/interfaces/api/example/
header_interfaces_example.files = $$files($${PWD}/interfaces/api/example/*.h*)

header_interfaces_pipeline.path = $${PROJECTDEPLOYDIR}/interfaces/api/pipeline/
header_interfaces_pipeline.files = $$files($${PWD}/interfaces/api/pipeline/*.h*)

header_interfaces_core.path = $${PROJECTDEPLOYDIR}/interfaces/core/
header_interfaces_core.files += $$files($${PWD}/interfaces/core/*.h*)

header_interfaces_datastructure.path = $${PROJECTDEPLOYDIR}/interfaces/datastructure/
header_interfaces_datastructure.files += $$files($${PWD}/interfaces/datastructure/*.h*)


INCLUDEPATH += $${PWD}/interfaces


INSTALLS += header_interfaces
INSTALLS += header_interfaces_display
INSTALLS += header_interfaces_features
INSTALLS += header_interfaces_fusion
INSTALLS += header_interfaces_geom
INSTALLS += header_interfaces_image
INSTALLS += header_interfaces_input_devices header_interfaces_input_files
INSTALLS += header_interfaces_reloc
INSTALLS += header_interfaces_sink
INSTALLS += header_interfaces_source
INSTALLS += header_interfaces_solver_pose
INSTALLS += header_interfaces_solver_map
INSTALLS += header_interfaces_reloc
INSTALLS += header_interfaces_core
INSTALLS += header_interfaces_datastructure
INSTALLS += header_interfaces_example
INSTALLS += header_interfaces_pipeline

solarmacros.path=$$(BCOMDEVROOT)/$${INSTALLSUBDIR}/$${FRAMEWORK}
solarmacros.files=$$files($${PWD}/solarmacros.cmake)
INSTALLS += solarmacros

