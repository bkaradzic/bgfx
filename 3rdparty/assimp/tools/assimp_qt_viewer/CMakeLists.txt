set(PROJECT_VERSION "")
project(assimp_qt_viewer)

cmake_minimum_required(VERSION 2.6)

find_package(Qt5Widgets REQUIRED)
find_package(DevIL REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
	${Qt5Widgets_INCLUDES}
	${Assimp_SOURCE_DIR}/include
	${Assimp_SOURCE_DIR}/code
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_SOURCE_DIR}
	${OPENGL_INCLUDE_DIR}
	${IL_INCLUDE_DIR}
)

link_directories(${Assimp_BINARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall")

set(assimp_qt_viewer_SRCS main.cpp loggerview.cpp glview.cpp mainwindow.cpp)
qt5_wrap_ui(UISrcs mainwindow.ui)
qt5_wrap_cpp(MOCrcs mainwindow.hpp glview.hpp)

add_executable(${PROJECT_NAME} ${assimp_qt_viewer_SRCS} ${UISrcs} ${MOCrcs})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${IL_LIBRARIES} ${OPENGL_LIBRARIES} assimp)

qt5_use_modules(${PROJECT_NAME} Widgets OpenGL)
if(WIN32) # Check if we are on Windows
	if(MSVC) # Check if we are using the Visual Studio compiler
		#set_target_properties(TestProject PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
	elseif(CMAKE_COMPILER_IS_GNUCXX)
		# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
	else()
		message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
	endif()
elseif(UNIX)
	# Nothing special required
else()
	message(SEND_ERROR "You are on an unsupported platform! (Not Win32 or Unix)")
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
