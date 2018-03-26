set(CMAKE_INSTALL_PREFIX $ENV{BCOMDEVROOT}/bcomBuild CACHE INTERNAL "")
####################################################
# macro to parse 3rd parties via pkgconfig
####################################################
# find PkgConfig
find_package(PkgConfig)
if (UNIX)
	set (LIBPREFIX "lib")
	set (LIBEXTENSION "so")
	set (OPENCV_VERSION "")
endif(UNIX)
macro (process3rdParty THIRDPARTY THIRDPARTY_PATH)
	message ("searching for ${THIRDPARTY} in ${THIRDPARTY_PATH}")
	# string (TOLOWER ${THIRDPARTY} thirdparty_pc)

	# set search path
	set(ENV{PKG_CONFIG_PATH} ${THIRDPARTY_PATH})
	
	# set lib directory variable for release and debug
	set (THIRDPARTY_LIB_DIR_RELEASE "${THIRDPARTY_PATH}/lib/${PROJECT_ARCH}/shared/release" )
	set (THIRDPARTY_LIB_DIR_DEBUG "${THIRDPARTY_PATH}/lib/${PROJECT_ARCH}/shared/debug" )

	#set (LIB_PATHS_LINKER_FLAGS "${LIB_PATHS_LINKER_FLAGS} ${LIBPATH_FLAG}${${THIRDPARTY}_LIB_DIR}")

	message ("searching for bcom-${THIRDPARTY} in ${THIRDPARTY_PATH}")
	#message ("${THIRDPARTY}_LIB_DIR  is set to ${${THIRDPARTY}_LIB_DIR}")

	# INCLUDE DIRS
	set (${THIRDPARTY}_INCLUDE_DIR "")
	execute_process(COMMAND ${PKG_CONFIG_EXECUTABLE} "bcom-${THIRDPARTY}" "--cflags-only-I" "--define-variable=prefix=${THIRDPARTY_PATH}" OUTPUT_VARIABLE ${THIRDPARTY}_INCLUDE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
	# get only the include directory
	string (COMPARE NOTEQUAL "${${THIRDPARTY}_INCLUDE_DIR}" "" _cmp)
	if (${_cmp})
	  string(REPLACE "-I" ";" ${THIRDPARTY}_INCLUDE_DIR ${${THIRDPARTY}_INCLUDE_DIR})
	endif()	
	message ("${THIRDPARTY}_INCLUDE_DIR  is set to ${${THIRDPARTY}_INCLUDE_DIR}")
	set (INCLUDE_DIRS "${${THIRDPARTY}_INCLUDE_DIR}${INCLUDE_DIRS}")
	
	
	# get the name of libs with "-l" flag
	set (${THIRDPARTY}_LIBS "")
	execute_process(COMMAND ${PKG_CONFIG_EXECUTABLE} "bcom-${THIRDPARTY}" "--libs-only-l" "${MSVC_SYNTAX}" OUTPUT_VARIABLE ${THIRDPARTY}_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
	string (COMPARE NOTEQUAL "${${THIRDPARTY}_LIBS}" "" _cmp)
	# get only the name of libs
	if (${_cmp})
	  string(REPLACE "-l" "" "${THIRDPARTY}_LIBS" ${${THIRDPARTY}_LIBS})	  
	endif()
	
	#set libraries with path for release and debug
	set(LIBS_LIST "${${THIRDPARTY}_LIBS}" )
	string(REGEX REPLACE " " ";" LIBS_LIST "${LIBS_LIST}")
	foreach( library ${LIBS_LIST} )
		set (LINK_LIBRARIES_RELEASE "${THIRDPARTY_LIB_DIR_RELEASE}/${LIBPREFIX}${library}.${LIBEXTENSION} ${LINK_LIBRARIES_RELEASE}")
		set (LINK_LIBRARIES_DEBUG "${THIRDPARTY_LIB_DIR_DEBUG}/${LIBPREFIX}${library}.${LIBEXTENSION} ${LINK_LIBRARIES_DEBUG}")
	endforeach(library)

endmacro (process3rdParty)

####################################################
# macro to parse packagedependencies.txt
####################################################
macro (processPackagedependencies)
	if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/packagedependencies.txt")
	  message(FATAL_ERROR "Cannot find packagedependencies.txt file: ${CMAKE_CURRENT_SOURCE_DIR}/packagedependencies.txt")
	endif(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/packagedependencies.txt")
	file(READ "${CMAKE_CURRENT_SOURCE_DIR}/packagedependencies.txt" files)
	string(REGEX REPLACE "\n" ";" files "${files}")
	foreach(file ${files})
	  #message(STATUS "processing $ENV{DESTDIR}${file}")
	  string(REPLACE "|" ";" PKGDATA "$ENV{DESTDIR}${file}")
	  #message(STATUS "processing ${PKGDATA}")
	  list(LENGTH PKGDATA _len)
	  #message ("pkdata length : ${_len}")
	  list(GET PKGDATA 0 PKGNAME)
	  list(GET PKGDATA 1 PKGVERSION)
	  list(GET PKGDATA 3 PKGPARENTDIR)
	  set (PKGPATH "$ENV{BCOMDEVROOT}/${PKGPARENTDIR}/${PKGNAME}/${PKGVERSION}") 
	  process3rdParty("${PKGNAME}" ${PKGPATH})
	endforeach(file)
endmacro(processPackagedependencies)


####################################################
# macro to parse sources.txt
####################################################
macro (processSources)	
	set (SOURCES "")
	if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/sources.txt")
	  message(FATAL_ERROR "Cannot find sources.txt file: ${CMAKE_CURRENT_SOURCE_DIR}/sources.txt")
	endif(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/sources.txt")
	file(READ "${CMAKE_CURRENT_SOURCE_DIR}/sources.txt" files)
	string(REGEX REPLACE "\n" ";" files "${files}")
	foreach(file ${files})
	  message(STATUS "adding source file $ENV{DESTDIR}${file}")
	  set (SOURCES ${SOURCES} $ENV{DESTDIR}${file})
	endforeach(file)	
endmacro(processSources)


####################################################
# macro to define targets
####################################################
macro (defineTargets EXEORLIBRARY FILES_TO_COPY)
	# define project target
	if ("${EXEORLIBRARY}" STREQUAL "library")
		add_library (${PROJECT_NAME} SHARED ${SOURCES})
		#set (CMAKE_SHARED_LINKER_FLAGS ${LIB_PATHS_LINKER_FLAGS})
	else()
		add_executable(${PROJECT_NAME} ${SOURCES})
		#set (CMAKE_EXE_LINKER_FLAGS ${LIB_PATHS_LINKER_FLAGS})
		# do the copying of NECESSARY FILES
		foreach( file_i ${FILES_TO_COPY})
		    add_custom_command(
			    TARGET ${PROJECT_NAME}
			    POST_BUILD
			    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${file_i}" $<TARGET_FILE_DIR:${PROJECT_NAME}>
			)
		endforeach()
	endif()

	message (STATUS "INCLUDE DIRS : ${INCLUDE_DIRS}")
	message (STATUS "LIB_PATHS_LINKER_FLAGS : ${LIB_PATHS_LINKER_FLAGS}")
	string (REPLACE " " ";" LINK_LIBRARIES_RELEASE ${LINK_LIBRARIES_RELEASE})
	string (REPLACE " " ";" LINK_LIBRARIES_DEBUG ${LINK_LIBRARIES_DEBUG})
	# message (STATUS "LINK_LIBRARIES : ${LINK_LIBRARIES}")
	target_include_directories (${PROJECT_NAME} PUBLIC
									${CMAKE_CURRENT_SOURCE_DIR}/interfaces
									"${INCLUDE_DIRS}"
								)
	target_compile_options(${PROJECT_NAME} PUBLIC
									${BOOST_CFLAGS_OTHER}								
								)			
	target_link_libraries(${PROJECT_NAME} debug ${LINK_LIBRARIES_DEBUG} optimized ${LINK_LIBRARIES_RELEASE})
	# message (STATUS "${LINK_LIBRARIES_RELEASE}")
	if ("${EXEORLIBRARY}" STREQUAL "library") # only for libraries

		# install target
		set (BUILDCONFIG $<$<CONFIG:Debug>:debug>$<$<NOT:$<CONFIG:Debug>>:release>)

		install (TARGETS ${PROJECT_NAME} DESTINATION $ENV{BCOMDEVROOT}/bcomBuild/${PROJECT_NAME}/${VERSION_NUMBER}/lib/${PROJECT_ARCH}/shared/${BUILDCONFIG})
		if (WIN32)
			if (MSVC)
				install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION $ENV{BCOMDEVROOT}/bcomBuild/${PROJECT_NAME}/${VERSION_NUMBER}/lib/${PROJECT_ARCH}/shared/${BUILDCONFIG} OPTIONAL)
			endif(MSVC)
		endif(WIN32)
		# install interfaces
		install (DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/"        
		         DESTINATION $ENV{BCOMDEVROOT}/bcomBuild/${PROJECT_NAME}/${VERSION_NUMBER}/interfaces)
		install (FILES "${CMAKE_CURRENT_SOURCE_DIR}/bcom-${PROJECT_NAME}.pc.in" DESTINATION $ENV{BCOMDEVROOT}/bcomBuild/${PROJECT_NAME}/${VERSION_NUMBER} RENAME "bcom-${PROJECT_NAME}.pc")
		install (FILES "${CMAKE_CURRENT_SOURCE_DIR}/packagedependencies.txt" DESTINATION $ENV{BCOMDEVROOT}/bcomBuild/${PROJECT_NAME}/${VERSION_NUMBER})

		# uninstall target
		if(NOT TARGET uninstall)
		    configure_file(
		        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
		        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
		        IMMEDIATE @ONLY)

		    add_custom_target(uninstall
		        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
		endif()        

	endif() 
endmacro(defineTargets)

####################################################
# macro to setup architecture dependant variables
####################################################
macro (setup)
	IF(WIN32) # Check if we are on Windows
	  if(MSVC) # Check if we are using the Visual Studio compiler
	  	message ("MSVC detected")
	  	set (LIBPATH_FLAG "/LIBPATH:")
	  	set (MSVC_SYNTAX "--msvc-syntax")	
	  	add_definitions(-D${PROJECT_NAME}_API_DLLEXPORT)
	  	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4250 -wd4251 -wd4244 -wd4275")
	  	add_definitions(-DWIN64 -DUNICODE -D_UNICODE)
	  	add_definitions (-DBOOST_ALL_DYN_LINK -DBOOST_AUTO_LINK_NOMANGLE)
	  endif()
	ELSE()
	  set (MSVC_SYNTAX "")	
	  set (LIBPATH_FLAG "-L")	
	ENDIF()
	if(UNIX)
	    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
	endif()



	# architecture detection
	if (CMAKE_SIZEOF_VOID_P MATCHES 8)
		set( PROJECT_ARCH "x86_64" )
	else(CMAKE_SIZEOF_VOID_P MATCHES 8)
		set( PROJECT_ARCH "x86" )
	endif(CMAKE_SIZEOF_VOID_P MATCHES 8)
	# initialize some variables
	set (INCLUDE_DIRS "")
	set (LIB_PATHS_LINKER_FLAGS "")
	set (LINK_LIBRARIES "")
	set (CFLAGS_OTHER "")	
endmacro(setup)