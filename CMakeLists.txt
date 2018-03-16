cmake_minimum_required(VERSION 2.8)

##################################################
set (VERSION_NUMBER "0.3.1")
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
##################################################

# various macros
include("macros.cmake")
# config setup
setup()
# process packagedependencies.txt
processPackagedependencies()
# define targets (library, install and uninstall)
defineTargets()

