cmake_minimum_required(VERSION 3.7.2)

##################################################
set (VERSION_NUMBER "0.4.0")
project("SolARFramework")
set (SOURCES 
		src/core/SolARFramework.cpp
		src/sink/ThirdPartyConnector.cpp
		src/core/Log.cpp
		src/datastructure/DescriptorBuffer.cpp
		src/datastructure/Image.cpp
		src/datastructure/Keypoint.cpp
		src/datastructure/Pose.cpp
		src/datastructure/SquaredBinaryPattern.cpp
	)

install (FILES "${CMAKE_CURRENT_SOURCE_DIR}/macros.cmake" DESTINATION $ENV{BCOMDEVROOT}/bcomBuild/${PROJECT_NAME}	)

##################################################

# various macros
include("macros.cmake")
# config setup
setup()
# process packagedependencies.txt
processPackagedependencies()
# define targets (type library)
defineTargets("library" "")

