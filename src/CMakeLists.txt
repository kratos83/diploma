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
	InvioStampaDiplomaThread.h
	scuola.h
	pref.h
	settingsmanager.h
	conn_db.h
)

qt5_wrap_cpp(diploma_mocs ${diploma_moc_hdrs})

set(diploma_uis 
	ui/alunni.ui
	ui/anno.ui
	ui/mainwindow.ui
	ui/pref.ui
	ui/scuola.ui
)


qt5_wrap_ui(diploma_ui_hdrs ${diploma_uis})

set(diploma_srcs 
	conn_db.cpp
	alunni.cpp
	anno.cpp
	InvioStampaDiplomaThread.cpp
	mainwindow.cpp
	print.cpp
	scuola.cpp
	pref.cpp
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
		"${MINGW_PREFIX}/bin/Qt5Svg.dll"
		"${MINGW_PREFIX}/bin/Qt5Xml.dll"
		"${MINGW_PREFIX}/bin/Qt5Network.dll"
		"${MINGW_PREFIX}/bin/Qt5Multimedia.dll"
		"${MINGW_PREFIX}/bin/Qt5MultimediaWidgets.dll"
		"${MINGW_PREFIX}/bin/Qt5Sql.dll"
		"${MINGW_PREFIX}/bin/Qt5Widgets.dll"
		"${MINGW_PREFIX}/bin/Qt5PrintSupport.dll"
		"${MINGW_PREFIX}/bin/Qt5OpenGL.dll"
		"${MINGW_PREFIX}/bin/Qt5Concurrent.dll"
		"${MINGW_PREFIX}/bin/Qt5WebKit.dll"
        "${MINGW_PREFIX}/bin/Qt5WebKitWidgets.dll"
		"${MINGW_PREFIX}/bin/libexpat-1.dll"
		"${MINGW_PREFIX}/bin/libjpeg-8.dll"
		"${MINGW_PREFIX}/bin/libpng16-16.dll"
		"${MINGW_PREFIX}/bin/libstdc++-6.dll"
		"${MINGW_PREFIX}/bin/libtiff-5.dll"
		"${MINGW_PREFIX}/bin/libtiffxx-5.dll"
		"${MINGW_PREFIX}/bin/libturbojpeg-0.dll"
		"${MINGW_PREFIX}/bin/zlib1.dll"
		"${MINGW_PREFIX}/bin/libwinpthread-1.dll"
		"${MINGW_PREFIX}/bin/libsqlite3-0.dll"
		"${MINGW_PREFIX}/bin/libiconv-2.dll"
		"${MINGW_PREFIX}/bin/libGLESv2.dll"
		"${MINGW_PREFIX}/bin/libfreetype-6.dll"
		"${MINGW_PREFIX}/bin/libglib-2.0-0.dll"
		"${MINGW_PREFIX}/bin/libharfbuzz-0.dll"
		"${MINGW_PREFIX}/bin/libpcre16-0.dll"
		"${MINGW_PREFIX}/bin/libpcre2-16-0.dll"
		"${MINGW_PREFIX}/bin/libintl-8.dll"
		"${MINGW_PREFIX}/bin/libbz2-1.dll"
		"${MINGW_PREFIX}/bin/libcurl-4.dll"
        "${MINGW_PREFIX}/bin/libpcre-1.dll"
        "${MINGW_PREFIX}/bin/libpcre32-0.dll"
        "${MINGW_PREFIX}/bin/libidn-11.dll"
        "${MINGW_PREFIX}/bin/libssh2-1.dll"
        "${MINGW_PREFIX}/bin/libEGL.dll"
        "${MINGW_PREFIX}/bin/Qt5Qml.dll"
        "${MINGW_PREFIX}/bin/Qt5Quick.dll"
        "${MINGW_PREFIX}/bin/Qt5Positioning.dll"
        "${MINGW_PREFIX}/bin/Qt5Sensors.dll"
        "${MINGW_PREFIX}/bin/libwebp-7.dll"
        "${MINGW_PREFIX}/bin/libxml2-2.dll"
        "${MINGW_PREFIX}/bin/libxslt-1.dll"
        "${MINGW_PREFIX}/bin/libpoppler-qt5-1.dll"
        "${MINGW_PREFIX}/bin/liblcms2-2.dll"
        "${MINGW_PREFIX}/bin/libopenjpeg-1.dll"
        "${MINGW_PREFIX}/bin/libopenjp2-7.dll"
        "${MINGW_PREFIX}/bin/libgraphite2.dll"
        "${MINGW_PREFIX}/bin/libicudt57.dll"
        "${MINGW_PREFIX}/bin/libicuin57.dll"
        "${MINGW_PREFIX}/bin/libicuuc57.dll"
        "${MINGW_PREFIX}/bin/liblzma-5.dll"
         "${MINGW_PREFIX}/bin/libidn2-0.dll"
         "${MINGW_PREFIX}/bin/libunistring-2.dll"
		"diploma.db"
		"../README.txt"
		DESTINATION .
		)
		INSTALL(FILES "${MINGW_PREFIX}/bin/libopenjp2-7.dll" DESTINATION . RENAME "libopenjp2.dll")
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt/plugins/sqldrivers/qsqlite.dll" DESTINATION ./sqldrivers
		)
		IF(WIN64)
    INSTALL(FILES 
        "${MINGW_PREFIX}/bin/libgcc_s_seh-1.dll"
        "${MINGW_PREFIX}/bin/libssl-1_1-x64.dll"
        "${MINGW_PREFIX}/bin/libcrypto-1_1-x64.dll"
        DESTINATION . )
ELSE ()
    INSTALL(FILES 
        "${MINGW_PREFIX}/bin/libgcc_s_sjlj-1.dll"
        "${MINGW_PREFIX}/bin/libssl-1_1.dll"
        "${MINGW_PREFIX}/bin/libcrypto-1_1.dll"
        DESTINATION . )
ENDIF(WIN64)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt/plugins/platforms/qminimal.dll" 
		"${MINGW_PREFIX}/lib/qt/plugins/platforms/qwindows.dll"
		DESTINATION ./platforms
		)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt/plugins/audio/qtaudio_windows.dll" 
		DESTINATION ./audio
		)
	INSTALL(FILES
		"${MINGW_PREFIX}/lib/qt/plugins/imageformats/qgif.dll"
		"${MINGW_PREFIX}/lib/qt/plugins/imageformats/qico.dll"
		"${MINGW_PREFIX}/lib/qt/plugins/imageformats/qjpeg.dll"
		"${MINGW_PREFIX}/lib/qt/plugins/imageformats/qsvg.dll"
		DESTINATION ./imageformats
		)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt/plugins/printsupport/windowsprintersupport.dll" 
		DESTINATION ./printsupport
		)
    INSTALL(FILES
        "${MINGW_PREFIX}/lib/qt/plugins/styles/qwindowsvistastyle.dll" 
		DESTINATION ./styles
		)
ELSE()
    INSTALL( TARGETS diploma RUNTIME DESTINATION /opt/diploma)
    INSTALL( FILES "images/diploma.png" DESTINATION /opt/diploma)
    INSTALL( FILES "diploma.db" DESTINATION /opt/diploma)
    INSTALL( FILES "desktop/diploma.desktop" DESTINATION /usr/share/applications )
endif()
