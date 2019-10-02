## remove Qt dependencies
QT       -= core gui
CONFIG -= qt

#Add support for clang compiler
#QMAKE_CXX=clang

## global defintions : target lib name, version
INSTALLSUBDIR = SolARBuild
TARGET = SolARFramework
FRAMEWORK = $$TARGET
VERSION=0.6.0

DEFINES += MYVERSION=$${VERSION}
DEFINES += TEMPLATE_LIBRARY
CONFIG += c++1z


CONFIG(debug,debug|release) {
    DEFINES += _DEBUG=1
    DEFINES += DEBUG=1
}

CONFIG(release,debug|release) {
    DEFINES += _NDEBUG=1
    DEFINES += NDEBUG=1
}

DEPENDENCIESCONFIG = sharedlib recursive install

## Configuration for Visual Studio to install binaries and dependencies. Work also for QT Creator by replacing QMAKE_INSTALL
PROJECTCONFIG = QTVS

#NOTE : CONFIG as staticlib or sharedlib, DEPENDENCIESCONFIG as staticlib or sharedlib, QMAKE_TARGET.arch and PROJECTDEPLOYDIR MUST BE DEFINED BEFORE templatelibconfig.pri inclusion
include ($$(REMAKEN_RULES_ROOT)/qmake/templatelibconfig.pri)

msvc {
DEFINES += "_BCOM_SHARED=__declspec(dllexport)"
}

include (SolARFramework.pri)

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
header_interfaces_tracking.path = $${PROJECTDEPLOYDIR}/interfaces/api/tracking/
header_interfaces_tracking.files = $$files($${PWD}/interfaces/api/tracking/*.h*)
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
INSTALLS += header_interfaces_tracking
INSTALLS += header_interfaces_solver_pose
INSTALLS += header_interfaces_solver_map
INSTALLS += header_interfaces_core
INSTALLS += header_interfaces_datastructure
INSTALLS += header_interfaces_example
INSTALLS += header_interfaces_pipeline

solarmacros.path=$${PROJECTDEPLOYDIR}
solarmacros.files=$$files($${PWD}/solarmacros.cmake)
INSTALLS += solarmacros

OTHER_FILES += \
    packagedependencies.txt

#NOTE : Must be placed at the end of the .pro
include ($$(REMAKEN_RULES_ROOT)/qmake/remaken_install_target.pri))
