project(cluster)

cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE true)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_INCLUDE_CURRENT_DIR on)

option(DEBUG "Include debugging symbols" on)
option(UNIT "Build unit tests" off)

if(DEBUG)
	message("DEBUG BUILD")
	set(CMAKE_BUILD_TYPE debug)
	set(CMAKE_CONFIGURATION_TYPES debug)
	set(SUFFIX d)
else()
	message("RELEASE BUILD")
	set(CMAKE_BUILD_TYPE release)
	set(CMAKE_CONFIGURATION_TYPES release)
endif()

if(WIN32)
else()
	if(UNIX)
		find_package(X11 REQUIRED)
                find_package(Threads REQUIRED)
		include_directories(${X11_INCLUDE_DIR})
                set(LIBS ${LIBS} ${X11_LIBRARIES})
	else()
	endif()
endif()

# Find and link OpenCV
set(OpenCV_DIR $ENV{OpenCV_DIR})
find_package(OpenCV REQUIRED core highgui)
include_directories(${OpenCV_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OpenCV_LIBS})

# Find and link Boost
set(BOOST_ROOT $ENV{BOOST_ROOT})
find_package(Boost REQUIRED regex)
include_directories(${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

file(COPY input DESTINATION ${EXECUTABLE_OUTPUT_PATH})

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}${SUFFIX})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} gdi32 ws2_32 ${LIBS})
else()
	if(UNIX)
            target_link_libraries(${PROJECT_NAME} ${LIBS})
	else()
	endif()
endif()
