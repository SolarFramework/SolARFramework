HEADERS += interfaces/api/display/I2DOverlay.h \
interfaces/api/solver/pose/ITrackablePose.h \
interfaces/api/input/devices/IDepthCamera.h \
interfaces/api/display/I3DOverlay.h \
interfaces/api/display/I3DPointsViewer.h \
interfaces/api/display/IImageViewer.h \
interfaces/api/display/IMatchesOverlay.h \
interfaces/api/features/IContoursExtractor.h \
interfaces/api/features/IContoursFilter.h \
interfaces/api/features/IDescriptorMatcher.h \
interfaces/api/features/IDescriptorMatcherStereo.h \
interfaces/api/features/IDescriptorMatcherGeometric.h \
interfaces/api/features/IDescriptorMatcherRegion.h \
interfaces/api/features/IDescriptorsExtractor.h \
interfaces/api/features/IDescriptorsExtractorFromImage.h \
interfaces/api/features/IDescriptorsExtractorSBPattern.h \
interfaces/api/features/IImageMatcher.h \
interfaces/api/features/IKeypointDetector.h \
interfaces/api/features/IKeypointDetectorRegion.h \
interfaces/api/features/IKeypointsReIndexer.h \
interfaces/api/features/IMatchesFilter.h \
interfaces/api/features/ISBPatternReIndexer.h \
interfaces/api/features/ICornerRefinement.h \
interfaces/api/features/IFeatureWithDepthFromStereo.h \
interfaces/api/features/I2DTrackablesDetector.h \
interfaces/api/fusion/IVisualInertialFusion.h \
interfaces/api/geom/I2DTransform.h \
interfaces/api/geom/I2DPointsRectification.h \
interfaces/api/geom/I3DTransform.h \
interfaces/api/geom/IImage2WorldMapper.h \
interfaces/api/geom/IProject.h \
interfaces/api/geom/IUndistortPoints.h \
interfaces/api/geom/IUnproject.h \
interfaces/api/geom/IDepthEstimation.h \
interfaces/api/geom/IReprojectionStereo.h \
interfaces/api/image/IImageConvertor.h \
interfaces/api/image/IImageFilter.h \
interfaces/api/image/IImageLoader.h \
interfaces/api/image/IPerspectiveController.h \
interfaces/api/image/IImageRectification.h \
interfaces/api/input/devices/IARDevice.h \
interfaces/api/input/devices/ICamera.h \
interfaces/api/input/devices/ICameraCalibration.h \
interfaces/api/input/devices/IDevice.h \
interfaces/api/input/devices/IIMU.h \
interfaces/api/input/devices/IRGBDCamera.h \
interfaces/api/input/devices/IStereoCameraCalibration.h \
interfaces/api/input/files/IMeshLoader.h \
interfaces/api/input/files/IPointCloudLoader.h \
interfaces/api/input/files/ITrackableLoader.h \
interfaces/api/input/files/IWorldGraphLoader.h \
interfaces/api/loop/ILoopClosureDetector.h \
interfaces/api/loop/ILoopCorrector.h \
interfaces/api/loop/IOverlapDetector.h \
interfaces/api/output/files/IMeshExporter.h \
interfaces/api/output/files/IPointCloudExporter.h \
interfaces/api/pipeline/IDenseMappingPipeline.h \
interfaces/api/pipeline/IMappingPipeline.h \
interfaces/api/pipeline/IPipeline.h \
interfaces/api/pipeline/IPoseEstimationPipeline.h \
interfaces/api/pipeline/IMapUpdatePipeline.h \
interfaces/api/pipeline/IRelocalizationPipeline.h \
interfaces/api/pointCloud/IPCFilter.h \
interfaces/api/pointCloud/IPCFilterCentroid.h \
interfaces/api/reloc/IKeyframeRetriever.h \
interfaces/api/reloc/IRelocalizer.h \
interfaces/api/reloc/IRegression.h \
interfaces/api/service/IFrontEnd.h \
interfaces/api/service/IServiceManager.h \
interfaces/api/sfm/IMeshing.h \
interfaces/api/sfm/IMultiViewStereo.h \
interfaces/api/sfm/IStructureFromMotion.h \
interfaces/api/sink/ISinkPoseImage.h \
interfaces/api/sink/ISinkPoseTextureBuffer.h \
interfaces/api/sink/ISinkReturnCode.h \
interfaces/api/slam/IBootstrapper.h \
interfaces/api/slam/IMapping.h \
interfaces/api/slam/ITracking.h \
interfaces/api/solver/map/IBundler.h \
interfaces/api/solver/map/IKeyframeSelector.h \
interfaces/api/solver/map/IMapFilter.h \
interfaces/api/solver/map/IMapFusion.h \
interfaces/api/solver/map/IMapUpdate.h \
interfaces/api/solver/map/ITriangulator.h \
interfaces/api/solver/pose/I2D3DCorrespondencesFinder.h \
interfaces/api/solver/pose/I2Dto3DTransformDecomposer.h \
interfaces/api/solver/pose/I2Dto3DTransformDecomposerValidation.h \
interfaces/api/solver/pose/I2DTransformFinder.h \
interfaces/api/solver/pose/I3D3DCorrespondencesFinder.h \
interfaces/api/solver/pose/I3DTransformFinderFrom2D2D.h \
interfaces/api/solver/pose/I3DTransformFinderFrom2D3D.h \
interfaces/api/solver/pose/I3DTransformFinderFrom3D3D.h \
interfaces/api/solver/pose/I3DTransformSACFinderFrom2D3D.h \
interfaces/api/solver/pose/I3DTransformSACFinderFrom3D3D.h \
interfaces/api/solver/pose/IHomographyValidation.h \
interfaces/api/solver/pose/IMultiTrackablesPose.h \
interfaces/api/source/ISourceImage.h \
interfaces/api/source/ISourceReturnCode.h \
interfaces/api/storage/ICovisibilityGraphManager.h \
interfaces/api/storage/IKeyframesManager.h \
interfaces/api/storage/ICameraParametersManager.h \
interfaces/api/storage/IPointCloudManager.h \
interfaces/api/storage/IMapManager.h \
interfaces/api/tracking/IOpticalFlowEstimator.h \
interfaces/core/Log.h \
interfaces/core/Timer.h \
interfaces/core/Messages.h \
interfaces/core/SerializationDefinitions.h \
interfaces/core/SolARFramework.h \
interfaces/core/SolARFrameworkDefinitions.h \
interfaces/datastructure/BufferInternal.hpp \
interfaces/datastructure/CameraDefinitions.h \
interfaces/datastructure/CameraParametersCollection.h \
interfaces/datastructure/CloudPoint.h \
interfaces/datastructure/CoordinateSystem.h \
interfaces/datastructure/DescriptorBuffer.h \
interfaces/datastructure/DescriptorMatch.h \
interfaces/datastructure/FiducialMarker.h \
interfaces/datastructure/QRCode.h \
interfaces/datastructure/Frame.h \
interfaces/datastructure/GeometryDefinitions.h \
interfaces/datastructure/Identification.h \
interfaces/datastructure/Image.h \
interfaces/datastructure/ImageMarker.h \
interfaces/datastructure/Keyframe.h \
interfaces/datastructure/Keypoint.h \
interfaces/datastructure/MathDefinitions.h \
interfaces/datastructure/Mesh.h \
interfaces/datastructure/PointCloud.h \
interfaces/datastructure/PrimitiveInformation.h \
interfaces/datastructure/SquaredBinaryPattern.h \
interfaces/datastructure/Trackable.h \
interfaces/datastructure/Trackable2D.h \
interfaces/datastructure/CovisibilityGraph.h \
interfaces/datastructure/KeyframeRetrieval.h \
interfaces/datastructure/KeyframeCollection.h \
interfaces/datastructure/Lockable.h \
interfaces/datastructure/Map.h \
interfaces/base/features/ADescriptorMatcher.h \
interfaces/base/features/ADescriptorMatcherGeometric.h \
interfaces/base/features/ADescriptorMatcherRegion.h \
interfaces/base/features/ADescriptorMatcherStereo.h \
interfaces/base/geom/A2DPointsRectification.h \
interfaces/base/geom/AReprojectionStereo.h \
interfaces/base/pipeline/AMappingPipeline.h \
interfaces/api/segm/IInstanceSegmentation.h \
interfaces/api/segm/ISemanticSegmentation.h \
interfaces/api/segm/IPanopticSegmentation.h \
interfaces/api/display/IMaskOverlay.h

SOURCES += src/api/reloc/IKeyframeRetriever.cpp \
src/core/Log.cpp \
src/core/SolARFramework.cpp \
src/datastructure/CameraParametersCollection.cpp \
src/datastructure/CloudPoint.cpp \
src/datastructure/CoordinateSystem.cpp \
src/datastructure/DescriptorBuffer.cpp \
src/datastructure/DescriptorMatch.cpp \
src/datastructure/FiducialMarker.cpp \
src/datastructure/QRCode.cpp \
src/datastructure/Frame.cpp \
src/datastructure/Identification.cpp \
src/datastructure/Image.cpp \
src/datastructure/ImageMarker.cpp \
src/datastructure/Keyframe.cpp \
src/datastructure/Keypoint.cpp \
src/datastructure/PointCloud.cpp \
src/datastructure/PrimitiveInformation.cpp \
src/datastructure/SquaredBinaryPattern.cpp \
src/datastructure/Trackable.cpp \
src/datastructure/Trackable2D.cpp \
src/datastructure/CovisibilityGraph.cpp \
src/datastructure/KeyframeRetrieval.cpp \
src/datastructure/KeyframeCollection.cpp \
src/datastructure/Map.cpp \
src/datastructure/Mesh.cpp \
src/base/features/ADescriptorMatcher.cpp \
src/base/features/ADescriptorMatcherGeometric.cpp \
src/base/features/ADescriptorMatcherRegion.cpp \
src/base/features/ADescriptorMatcherStereo.cpp \
src/base/geom/A2DPointsRectification.cpp \
src/base/geom/AReprojectionStereo.cpp \
src/base/pipeline/AMappingPipeline.cpp
