project(diploma)

cmake_minimum_required(VERSION 2.6)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules )

if(WIN32)
SET( CMAKE_CXX_FLAGS  "-fexceptions -std=c++11 -mwindows" )
ELSE()
SET( CMAKE_CXX_FLAGS  "-fexceptions -std=c++11" )
ENDIF()

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} 
		    ${Qt5Core_INCLUDE_DIRS} ${Qt5Sql_INCLUDE_DIRS} 
		    ${Qt5PrintSupport_INCLUDE_DIRS})
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Sql REQUIRED)
FIND_PACKAGE(Qt5PrintSupport REQUIRED)

set(diploma "diploma")

set(diploma_includes
${CMAKE_BINARY_DIR}/src
)

include_directories(${diploma_includes})

set(diploma_moc_hdrs 
	alunni.h
	anno.h
	mainwindow.h
	print.h
	scuola.h
	settingsmanager.h
)

qt5_wrap_cpp(diploma_mocs ${diploma_moc_hdrs})

set(diploma_uis 
	ui/alunni.ui
	ui/anno.ui
	ui/mainwindow.ui
	ui/scuola.ui
)


qt5_wrap_ui(diploma_ui_hdrs ${diploma_uis})

set(diploma_srcs 
	alunni.cpp
	anno.cpp
	mainwindow.cpp
	print.cpp
	scuola.cpp
	settingsmanager.cpp
	main.cpp
)


qt5_add_resources(RESOURCE_FILES images.qrc) 


IF(WIN32)
	SET(WINRC "${CMAKE_CURRENT_BINARY_DIR}/diploma.obj")
	ADD_DEFINITIONS(-D__USE_MINGW_ANSI_STDIO=1)
	ADD_CUSTOM_COMMAND(OUTPUT ${WINRC}
						COMMAND ${WINDRES}
							-I${CMAKE_CURRENT_SOURCE_DIR}
							-o${WINRC}
							-i${CMAKE_CURRENT_BINARY_DIR}/winicon.rc
						DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/winicon.rc)

ENDIF(WIN32)

LINK_LIBRARIES(-lpthread)

if (APPLE)
    set(SOURCE_FILES ${SOURCE_FILES} images/diploma.icns)
    set_source_files_properties(images/diploma.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    ADD_EXECUTABLE(diploma MACOSX_BUNDLE ${diploma_srcs} ${diploma_mocs} ${diploma_ui_hdrs} ${RESOURCE_FILES} ${WINRC} ${SOURCE_FILES})
else()
ADD_EXECUTABLE(diploma ${diploma_srcs} ${diploma_mocs} ${diploma_ui_hdrs} ${RESOURCE_FILES} ${WINRC} ${SOURCE_FILES})
endif()


target_link_libraries( diploma
  xlsx_diploma
  Qt5::Widgets Qt5::Gui 
  Qt5::Sql Qt5::Core 
  Qt5::PrintSupport 
)



IF(WIN32)
    INSTALL(TARGETS diploma RUNTIME DESTINATION .)
	INSTALL(FILES
		"${MINGW_PREFIX}/bin/Qt5Core.dll"
		"${MINGW_PREFIX}/bin/Qt5Gui.dll"
		"${MINGW_PREFIX}/bin/Qt5Sql.dll"
		"${MINGW_PREFIX}/bin/Qt5Widgets.dll"
		"${MINGW_PREFIX}/bin/Qt5PrintSupport.dll"
		"${MINGW_PREFIX}/bin/libexpat-1.dll"
		"${MINGW_PREFIX}/bin/libjpeg-62.dll"
		"${MINGW_PREFIX}/bin/libpng16-16.dll"
		"${MINGW_PREFIX}/bin/libstdc++-6.dll"
		"${MINGW_PREFIX}/bin/libtiff-5.dll"
		"${MINGW_PREFIX}/bin/libtiffxx-5.dll"
		"${MINGW_PREFIX}/bin/libturbojpeg.dll"
		"${MINGW_PREFIX}/bin/zlib1.dll"
		"${MINGW_PREFIX}/bin/libwinpthread-1.dll"
		"${MINGW_PREFIX}/bin/libgcc_s_sjlj-1.dll"
		"${MINGW_PREFIX}/bin/libsqlite3-0.dll"
		"${MINGW_PREFIX}/bin/iconv.dll"
		"${MINGW_PREFIX}/bin/libGLESv2.dll"
		"${MINGW_PREFIX}/bin/libfreetype-6.dll"
		"${MINGW_PREFIX}/bin/libglib-2.0-0.dll"
		"${MINGW_PREFIX}/bin/libharfbuzz-0.dll"
		"${MINGW_PREFIX}/bin/libpcre16-0.dll"
		"${MINGW_PREFIX}/bin/libintl-8.dll"
		"${MINGW_PREFIX}/bin/libbz2-1.dll"
		"diploma.db"
		"../README.txt"
		DESTINATION .
		)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt5/plugins/sqldrivers/qsqlite.dll" DESTINATION ./sqldrivers
		)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt5/plugins/platforms/qminimal.dll" 
		"${MINGW_PREFIX}/lib/qt5/plugins/platforms/qwindows.dll"
		DESTINATION ./platforms
		)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt5/plugins/printsupport/windowsprintersupport.dll" 
		DESTINATION ./printsupport
		)
ELSE()
    INSTALL( TARGETS diploma RUNTIME DESTINATION /opt/diploma)
    INSTALL( FILES "images/diploma.png" DESTINATION /opt/diploma)
    INSTALL( FILES "diploma.db" DESTINATION /opt/diploma)
    INSTALL( FILES "desktop/diploma.desktop" DESTINATION /usr/share/applications )
endif()
