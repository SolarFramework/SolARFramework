## remove Qt dependencies
QT       -= core gui
CONFIG -= qt

## global defintions : target lib name, version
TARGET = SolARFramework
INSTALLSUBDIR = bcomBuild
FRAMEWORK = $$TARGET
VERSION=1.0.0

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

## lib link configuration : staticlib|shared
#CONFIG -= staticlib
#CONFIG += shared

PROJECTDEPLOYDIR = $$(BCOMDEVROOT)/$${INSTALLSUBDIR}/$${FRAMEWORK}/$${VERSION}
DEPENDENCIESCONFIG = shared

#NOTE : CONFIG as staticlib or sharedlib, DEPENDENCIESCONFIG as staticlib or sharedlib, QMAKE_TARGET.arch and PROJECTDEPLOYDIR MUST BE DEFINED BEFORE templatelibconfig.pri inclusion
include (builddefs/qmake/templatelibconfig.pri)

## Defines for shared library
#shared {
#    DEFINES += _BCOM_SHARED BCOM_HEADER_EXPORTS
#}

## DEFINES FOR MSVC/INTEL C++ compilers
msvc {
DEFINES += "_BCOM_SHARED=__declspec(dllexport)"
#SOURCES += $$files($${PWD}/src/main.cpp)
}

HEADERS += interfaces/ISolARCamera.h \
interfaces/ISolARDescriptor.h \
interfaces/ISolARDescriptorExtractor.h \
interfaces/ISolARDescriptorMatcher.h \
interfaces/ISolARFilter.h \
interfaces/ISolARImageConvertor.h \
interfaces/ISolARImageFilter.h \
interfaces/ISolARImageLoader.h \
interfaces/ISolARImageViewer.h \
interfaces/ISolARKeypointDetector.h \
interfaces/ISolARMarker.h \
interfaces/ISolARMarkerFiducial.h \
interfaces/ISolARPoseHomography.h \
interfaces/SolARFramework.h \
interfaces/SolARFrameworkDefinitions.h \
interfaces/SolARImage.h \
interfaces/SolARMathDefinitions.h \
interfaces/SolARMessages.h \
interfaces/SolARPinholeCamera.h \
interfaces/SolARPose.h \
interfaces/SolARKeypoint.h \
interfaces/SolARMarker.h \
interfaces/ISolARMarkerFinder.h \
interfaces/ISolARMarkerFiducialFinder.h \
interfaces/ISolARCameraCalibration.h

SOURCES += src/SolARFramework.cpp \
src/SolARImage.cpp \
src/SolARPinholeCamera.cpp \
src/SolARPose.cpp \
src/SolARKeypoint.cpp \
src/SolARMarker.cpp


unix {
}

macx {
}

win32 {

    DEFINES += WIN64 UNICODE _UNICODE
    QMAKE_COMPILER_DEFINES += _WIN64
}

INCLUDEPATH += $${PWD}/interfaces/ $${PWD}/libs/eigen/Eigen/

header_files.path = $${PROJECTDEPLOYDIR}/interfaces
header_files.files = $$files($${PWD}/interfaces/*.h*)

eigen_files.path = $${PROJECTDEPLOYDIR}/interfaces/Eigen
eigen_files.files = $$files($${PWD}/libs/eigen/Eigen/*)

INSTALLS += header_files eigen_files
