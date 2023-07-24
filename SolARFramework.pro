## remove Qt dependencies
QT       -= core gui
CONFIG -= qt
QMAKE_PROJECT_DEPTH = 0

#Add support for clang compiler
#QMAKE_CXX=clang

## global defintions : target lib name, version
INSTALLSUBDIR = SolARBuild
TARGET = SolARFramework
FRAMEWORK = $$TARGET
VERSION=1.1.0

DEFINES += MYVERSION=$${VERSION}
DEFINES += TEMPLATE_LIBRARY
CONFIG += c++1z

include(findremakenrules.pri)

CONFIG(debug,debug|release) {
    DEFINES += _DEBUG=1
    DEFINES += DEBUG=1
}

CONFIG(release,debug|release) {
    DEFINES += _NDEBUG=1
    DEFINES += NDEBUG=1
}

DEPENDENCIESCONFIG = sharedlib

## Configuration for Visual Studio to install binaries and dependencies. Work also for QT Creator by replacing QMAKE_INSTALL
PROJECTCONFIG = QTVS

#NOTE : CONFIG as staticlib or sharedlib, DEPENDENCIESCONFIG as staticlib or sharedlib, QMAKE_TARGET.arch and PROJECTDEPLOYDIR MUST BE DEFINED BEFORE templatelibconfig.pri inclusion
include ($$shell_quote($$shell_path($${QMAKE_REMAKEN_RULES_ROOT}/templatelibconfig.pri)))  # Shell_quote & shell_path required for visual on windows

msvc {
DEFINES += "_BCOM_SHARED=__declspec(dllexport)"
}

include (SolARFramework.pri)

unix {
    # Avoids adding install steps manually. To be commented to have a better control over them.
    QMAKE_POST_LINK += "make install"
}

linux {
    QMAKE_LFLAGS += -ldl
}

win32 {

    DEFINES += WIN64 UNICODE _UNICODE
    QMAKE_COMPILER_DEFINES += _WIN64
    QMAKE_CXXFLAGS += -wd4250 -wd4251 -wd4244 -wd4275
    QMAKE_CXXFLAGS_DEBUG += /Od
    QMAKE_CXXFLAGS_RELEASE += /O2
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
header_interfaces_output_files.path = $${PROJECTDEPLOYDIR}/interfaces/api/output/files/
header_interfaces_output_files.files = $$files($${PWD}/interfaces/api/output/files/*.h*)
header_interfaces_pointCloud.path  = $${PROJECTDEPLOYDIR}/interfaces/api/pointCloud/
header_interfaces_pointCloud.files = $$files($${PWD}/interfaces/api/pointCloud/*.h*)
header_interfaces_reloc.path = $${PROJECTDEPLOYDIR}/interfaces/api/reloc/
header_interfaces_reloc.files = $$files($${PWD}/interfaces/api/reloc/*.h*)
header_interfaces_sink.path = $${PROJECTDEPLOYDIR}/interfaces/api/sink
header_interfaces_sink.files = $$files($${PWD}/interfaces/api/sink/*.h*)
header_interfaces_source.path = $${PROJECTDEPLOYDIR}/interfaces/api/source
header_interfaces_source.files = $$files($${PWD}/interfaces/api/source/*.h*)
header_interfaces_tracking.path = $${PROJECTDEPLOYDIR}/interfaces/api/tracking/
header_interfaces_tracking.files = $$files($${PWD}/interfaces/api/tracking/*.h*)
header_interfaces_solver_pose.path = $${PROJECTDEPLOYDIR}/interfaces/api/solver/pose/
header_interfaces_solver_pose.files = $$files($${PWD}/interfaces/api/solver/pose/*.h*)
header_interfaces_solver_map.path = $${PROJECTDEPLOYDIR}/interfaces/api/solver/map/
header_interfaces_solver_map.files = $$files($${PWD}/interfaces/api/solver/map/*.h*)
header_interfaces_storage.path = $${PROJECTDEPLOYDIR}/interfaces/api/storage/
header_interfaces_storage.files = $$files($${PWD}/interfaces/api/storage/*.h*)
header_interfaces_reloc.path = $${PROJECTDEPLOYDIR}/interfaces/api/reloc/
header_interfaces_reloc.files = $$files($${PWD}/interfaces/api/reloc/*.h*)
header_interfaces_pipeline.path = $${PROJECTDEPLOYDIR}/interfaces/api/pipeline/
header_interfaces_pipeline.files = $$files($${PWD}/interfaces/api/pipeline/*.h*)
header_interfaces_core.path = $${PROJECTDEPLOYDIR}/interfaces/core/
header_interfaces_core.files += $$files($${PWD}/interfaces/core/*.h*)
header_interfaces_datastructure.path = $${PROJECTDEPLOYDIR}/interfaces/datastructure/
header_interfaces_datastructure.files += $$files($${PWD}/interfaces/datastructure/*.h*)
header_interfaces_loop.path = $${PROJECTDEPLOYDIR}/interfaces/api/loop/
header_interfaces_loop.files += $$files($${PWD}/interfaces/api/loop/*.h*)
header_interfaces_slam.path = $${PROJECTDEPLOYDIR}/interfaces/api/slam/
header_interfaces_slam.files += $$files($${PWD}/interfaces/api/slam/*.h*)
header_base_features.path = $${PROJECTDEPLOYDIR}/interfaces/base/features/
header_base_features.files += $$files($${PWD}/interfaces/base/features/*.h*)
header_base_geom.path = $${PROJECTDEPLOYDIR}/interfaces/base/geom/
header_base_geom.files += $$files($${PWD}/interfaces/base/geom/*.h*)
header_base_pipeline.path = $${PROJECTDEPLOYDIR}/interfaces/base/pipeline/
header_base_pipeline.files += $$files($${PWD}/interfaces/base/pipeline/*.h*)
header_interfaces_segm.path = $${PROJECTDEPLOYDIR}/interfaces/api/segm/
header_interfaces_segm.files = $$files($${PWD}/interfaces/api/segm/*.h*)
header_interfaces_sfm.path = $${PROJECTDEPLOYDIR}/interfaces/api/sfm/
header_interfaces_sfm.files += $$files($${PWD}/interfaces/api/sfm/*.h*)

INCLUDEPATH += $${PWD}/interfaces


INSTALLS += header_interfaces
INSTALLS += header_interfaces_display
INSTALLS += header_interfaces_features
INSTALLS += header_interfaces_fusion
INSTALLS += header_interfaces_geom
INSTALLS += header_interfaces_image
INSTALLS += header_interfaces_input_devices header_interfaces_input_files
INSTALLS += header_interfaces_output_files
INSTALLS += header_interfaces_pointCloud
INSTALLS += header_interfaces_reloc
INSTALLS += header_interfaces_sink
INSTALLS += header_interfaces_source
INSTALLS += header_interfaces_tracking
INSTALLS += header_interfaces_solver_pose
INSTALLS += header_interfaces_solver_map
INSTALLS += header_interfaces_storage
INSTALLS += header_interfaces_core
INSTALLS += header_interfaces_datastructure
INSTALLS += header_interfaces_pipeline
INSTALLS += header_interfaces_loop
INSTALLS += header_interfaces_segm
INSTALLS += header_interfaces_slam
INSTALLS += header_interfaces_sfm
INSTALLS += header_base_features
INSTALLS += header_base_geom
INSTALLS += header_base_pipeline


OTHER_FILES += \
    packagedependencies.txt \
    packagedependencies-win.txt \
    packagedependencies-linux.txt \
    extra-packages.txt \
    extra-packages-linux.txt

#NOTE : Must be placed at the end of the .pro
include ($$shell_quote($$shell_path($${QMAKE_REMAKEN_RULES_ROOT}/remaken_install_target.pri)))) # Shell_quote & shell_path required for visual on windows
