# CMake build of SolARFramework (equivalent of SolARFramework.pro, using the builddefs-cmake remaken rules)
cmake_minimum_required(VERSION 3.16)

## global definitions : target lib name, version
project(SolARFramework VERSION 1.7.0 LANGUAGES CXX)

include(findremakenrules.cmake)
include(RemakenRules)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Version.h generated from Version.h.in (QMAKE_SUBSTITUTES equivalent)
set(_version_in "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/Version.h.in")
set(_version_out "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/Version.h")
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${_version_in}")
file(READ "${_version_in}" _version_content)
string(REPLACE "$$VERSION" "${PROJECT_VERSION}" _version_content "${_version_content}")
string(REPLACE "\\\"" "\"" _version_content "${_version_content}")
set(_version_old "")
if(EXISTS "${_version_out}")
    file(READ "${_version_out}" _version_old)
endif()
if(NOT _version_old STREQUAL _version_content)
    file(WRITE "${_version_out}" "${_version_content}")
endif()

## sources (SolARFramework.pri)
set(SOLARFRAMEWORK_SOURCES
    src/api/map/IMultiViewStereo.cpp
    src/api/map/IRectifyMap.cpp
    src/api/reloc/IKeyframeRetriever.cpp
    src/api/segm/IInstanceSegmentation.cpp
    src/api/segm/IPanopticSegmentation.cpp
    src/api/segm/ISemanticSegmentation.cpp
    src/base/features/ADescriptorMatcher.cpp
    src/base/features/ADescriptorMatcherGeometric.cpp
    src/base/features/ADescriptorMatcherRegion.cpp
    src/base/features/ADescriptorMatcherStereo.cpp
    src/base/geom/A2DPointsRectification.cpp
    src/base/geom/AReprojectionStereo.cpp
    src/base/pipeline/AMappingPipeline.cpp
    src/core/Log.cpp
    src/core/ScopedTempDir.cpp
    src/core/SolARFramework.cpp
    src/core/ZipBufferUtils.cpp
    src/datastructure/CameraParametersCollection.cpp
    src/datastructure/CloudPoint.cpp
    src/datastructure/CoordinateSystem.cpp
    src/datastructure/CovisibilityGraph.cpp
    src/datastructure/DescriptorBuffer.cpp
    src/datastructure/DescriptorMatch.cpp
    src/datastructure/FiducialMarker.cpp
    src/datastructure/Frame.cpp
    src/datastructure/GlobalDescriptor.cpp
    src/datastructure/Identification.cpp
    src/datastructure/Image.cpp
    src/datastructure/ImageMarker.cpp
    src/datastructure/Keyframe.cpp
    src/datastructure/KeyframeCollection.cpp
    src/datastructure/KeyframeRetrieval.cpp
    src/datastructure/Keypoint.cpp
    src/datastructure/Map.cpp
    src/datastructure/Mask2D.cpp
    src/datastructure/Mask2DCollection.cpp
    src/datastructure/Mesh.cpp
    src/datastructure/PointCloud.cpp
    src/datastructure/PrimitiveInformation.cpp
    src/datastructure/QRCode.cpp
    src/datastructure/RelocalizationInformation.cpp
    src/datastructure/SquaredBinaryPattern.cpp
    src/datastructure/StorageCapabilities.cpp
    src/datastructure/StorageTrackable.cpp
    src/datastructure/StorageWorldAnchor.cpp
    src/datastructure/StorageWorldElement.cpp
    src/datastructure/StorageWorldLink.cpp
    src/datastructure/Trackable.cpp
    src/datastructure/Trackable2D.cpp
)
file(GLOB_RECURSE SOLARFRAMEWORK_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/*.hpp")

add_library(SolARFramework SHARED ${SOLARFRAMEWORK_SOURCES} ${SOLARFRAMEWORK_HEADERS})
target_include_directories(SolARFramework PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interfaces>")

target_compile_definitions(SolARFramework PRIVATE
    MYVERSION=${PROJECT_VERSION}
    TEMPLATE_LIBRARY
    $<$<CONFIG:Debug>:_DEBUG=1>
    $<$<CONFIG:Debug>:DEBUG=1>
    $<$<NOT:$<CONFIG:Debug>>:_NDEBUG=1>
    $<$<NOT:$<CONFIG:Debug>>:NDEBUG=1>)

if(MSVC)
    target_compile_definitions(SolARFramework PRIVATE "_BCOM_SHARED=__declspec(dllexport)")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(SolARFramework PRIVATE ${CMAKE_DL_LIBS})
    target_compile_options(SolARFramework PRIVATE
        -Wno-attributes
        -Werror=switch-enum
        -Werror=unused-result)
endif()

if(WIN32)
    target_compile_definitions(SolARFramework PRIVATE WIN64 UNICODE _UNICODE)
    if(MSVC)
        target_compile_options(SolARFramework PRIVATE /wd4250 /wd4251 /wd4244 /wd4275)
    endif()
    target_link_libraries(SolARFramework PRIVATE shell32)
endif()

## remaken rules : dependencies (packagedependencies*.txt), package installation
## INSTALL_AFTER_BUILD : the qmake project runs 'make install' after each link on unix
## (disabled with -DREMAKEN_INSTALL_AFTER_BUILD=OFF)
remaken_target(SolARFramework
    FRAMEWORK SolARFramework
    INSTALLSUBDIR SolARBuild
    DEPENDENCIESCONFIG shared install_recurse externaldeps
    INSTALL_AFTER_BUILD)

## headers installation (interfaces/**/*.h*, Version.h.in excluded)
install(DIRECTORY interfaces/
    DESTINATION "${PROJECTDEPLOYDIR}/interfaces"
    FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp")
