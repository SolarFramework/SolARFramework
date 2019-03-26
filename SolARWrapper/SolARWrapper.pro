#-------------------------------------------------
#
# Project created by QtCreator 2018-11-14T12:19:14
#
#-------------------------------------------------

QT       -= core gui

TARGET = SolARUnityPlugin
TEMPLATE = lib

DEFINES += SOLARUNITYPLUGIN_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	SolAR_Api_Display_wrap.cxx \
	SolAR_Api_Example_wrap.cxx \
	SolAR_Api_Features_wrap.cxx \
	SolAR_Api_Fusion_wrap.cxx \
	SolAR_Api_Geom_wrap.cxx \
	SolAR_Api_Image_wrap.cxx \
	SolAR_Api_Input_Devices_wrap.cxx \
	SolAR_Api_Input_Files_wrap.cxx \
	SolAR_Api_Pipeline_wrap.cxx \
	SolAR_Api_Reloc_wrap.cxx \
	SolAR_Api_Sink_wrap.cxx \
	SolAR_Api_Solver_Map_wrap.cxx \
	SolAR_Api_Solver_Pose_wrap.cxx \
	SolAR_Api_Source_wrap.cxx \
	SolAR_Core_wrap.cxx \
	SolAR_Datastructure_wrap.cxx \
	SolAR_wrap.cxx \
	XPCF_Api_wrap.cxx \
	XPCF_Collection_wrap.cxx \
	XPCF_Component_wrap.cxx \
	XPCF_Core_wrap.cxx \
	XPCF_Module_wrap.cxx \
	XPCF_Properties_wrap.cxx \
	XPCF_Threading_wrap.cxx \
	XPCF_Traits_wrap.cxx \

HEADERS += \

INCLUDEPATH += \
    ../../SolARFramework/0.5.1/interfaces \
    ../../SolARModuleTools/0.4.0/interfaces \
    ../../../thirdParties/xpcf/2.1.0/interfaces \
    ../../../thirdParties/eigen/3.3.5/interfaces \
    ../../../thirdParties/boost/1.68.0/interfaces \
    ../../../thirdParties/spdlog/0.14.0/interfaces \

LIBS += \
    -L../../SolARFramework/0.5.1/lib/x86_64/shared/debug \
    -L../../SolARModuleTools/0.4.0/lib/x86_64/shared/debug \
    -L../../../thirdParties/xpcf/2.1.0/lib/x86_64/shared/debug \
    -L../../../thirdParties/boost/1.68.0/lib/x86_64/shared/debug \
    -lSolARFramework \
    -lSolARModuleTools \
    -lxpcf \
    -lboost_filesystem \
    -lboost_system \

DEFINES += BOOST_ALL_NO_LIB

unix {
    target.path = /usr/lib
    INSTALLS += target
}
