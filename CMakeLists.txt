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

set (HEADERS
		interfaces/SharedBuffer.hpp
		interfaces/SharedCircularBuffer.hpp
		interfaces/SharedFifo.hpp
		interfaces/core/SolARFrameworkDefinitions.h
		interfaces/api/sink/ThirdPartyConnector.h
		interfaces/api/sink/IThirdPartyConnector.h
		interfaces/api/display/I2DOverlay.h
		interfaces/api/display/I3DOverlay.h
		interfaces/api/display/ISideBySideOverlay.h
		interfaces/api/display/IImageViewer.h
		interfaces/api/features/IContoursExtractor.h
		interfaces/api/features/IDescriptorMatcher.h
		interfaces/api/features/IContoursFilter.h
		interfaces/api/features/IDescriptorsExtractor.h
		interfaces/api/features/IDescriptorsExtractorSBPattern.h
		interfaces/api/features/IKeypointDetector.h
		interfaces/api/features/IKeypointsReIndexer.h
		interfaces/api/features/ISBPatternReIndexer.h
		interfaces/api/features/IMatchesFilter.h
		interfaces/api/geom/I2DTransform.h
		interfaces/api/geom/I3DTransform.h
		interfaces/api/geom/IImage2WorldMapper.h
		interfaces/api/image/IImageConvertor.h
		interfaces/api/image/IImageFilter.h
		interfaces/api/image/IImageLoader.h
		interfaces/api/image/IPerspectiveController.h
		interfaces/api/input/devices/ICamera.h
		interfaces/api/input/devices/ICameraCalibration.h
		interfaces/api/input/devices/IIMU.h
		interfaces/api/solver/pose/I2DTransformFinder.h
		interfaces/api/solver/pose/I3DTransformFinder.h
		interfaces/api/solver/pose/I2Dto3DTransformDecomposer.h
		interfaces/api/solver/map/ITriangulator.h
		interfaces/core/SolARFramework.h
		interfaces/core/Messages.h
		interfaces/core/Log.h
		interfaces/datastructure/BufferInternal.hpp
		interfaces/datastructure/DescriptorBuffer.h
		interfaces/datastructure/DescriptorMatch.h
		interfaces/datastructure/GeometryDefinitions.h
		interfaces/datastructure/Image.h
		interfaces/datastructure/Keypoint.h
		interfaces/datastructure/MathDefinitions.h
		interfaces/datastructure/Pose.h
		interfaces/datastructure/SquaredBinaryPattern.h
		interfaces/api/input/files/IMarker.h
		interfaces/api/input/files/IMarker2DNaturalImage.h
		interfaces/api/input/files/IMarker2DSquared.h
		interfaces/api/input/files/IMarker2DSquaredBinary.h
)

install (FILES "${CMAKE_CURRENT_SOURCE_DIR}/solarmacros.cmake" DESTINATION $ENV{BCOMDEVROOT}/bcomBuild/${PROJECT_NAME}	)

##################################################

# various macros
include("solarmacros.cmake")
# config setup
setup()
# process packagedependencies.txt
processPackagedependencies()
# define targets (type library)
defineTargets("library" "")

