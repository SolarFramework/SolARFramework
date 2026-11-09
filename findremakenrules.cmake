# builddefs-cmake : locate the remaken CMake rules (equivalent of findremakenrules.pri)
# Copy this file in your project and include it before include(RemakenRules) :
#
#   include(findremakenrules.cmake)
#   include(RemakenRules)
#
# Search order :
#   1. builddefs/cmake folder in the project
#   2. ${REMAKEN_RULES_ROOT}/cmake (environment variable)
#   3. ${USERHOMEFOLDER}/.remaken/rules/cmake
#   4. ${USERHOMEFOLDER}/.remaken/rules/builddefs-cmake

if(CMAKE_HOST_WIN32)
    set(_remaken_home "$ENV{USERPROFILE}")
    if(_remaken_home STREQUAL "")
        set(_remaken_home "$ENV{HOMEDRIVE}$ENV{HOMEPATH}")
    endif()
else()
    set(_remaken_home "$ENV{HOME}")
endif()
file(TO_CMAKE_PATH "${_remaken_home}" _remaken_home)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/builddefs/cmake/RemakenRules.cmake")
    set(REMAKEN_CMAKE_RULES_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/builddefs/cmake")
elseif(NOT "$ENV{REMAKEN_RULES_ROOT}" STREQUAL "")
    file(TO_CMAKE_PATH "$ENV{REMAKEN_RULES_ROOT}/cmake" REMAKEN_CMAKE_RULES_ROOT)
elseif(EXISTS "${_remaken_home}/.remaken/rules/cmake/RemakenRules.cmake")
    set(REMAKEN_CMAKE_RULES_ROOT "${_remaken_home}/.remaken/rules/cmake")
else()
    set(REMAKEN_CMAKE_RULES_ROOT "${_remaken_home}/.remaken/rules/builddefs-cmake")
endif()

if(NOT EXISTS "${REMAKEN_CMAKE_RULES_ROOT}/RemakenRules.cmake")
    message(FATAL_ERROR "Unable to locate remaken rules in ${REMAKEN_CMAKE_RULES_ROOT}. Either check your remaken installation, or provide the path to your remaken rules root folder in REMAKEN_RULES_ROOT environment variable.")
endif()

message(STATUS "Remaken cmake build rules used : ${REMAKEN_CMAKE_RULES_ROOT}")
list(APPEND CMAKE_MODULE_PATH "${REMAKEN_CMAKE_RULES_ROOT}")
