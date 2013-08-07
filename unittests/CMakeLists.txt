project(unittests CXX)

option(GMOCK_DOWNLOAD "Download Google Mock" ON)
set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11")

######## GOOGLEMOCK #######
# Ahh this should be an option that enables/disables update. Not sure how to get it working.
include(ExternalProject)
ExternalProject_Add(
	googlemock
	# Comment this out to have it pull an update or rebuild from scratch.
#	UPDATE_COMMAND ""
	SVN_REPOSITORY http://googlemock.googlecode.com/svn/trunk/
	TIMEOUT 10
	CMAKE_ARGS -Dgtest_disable_pthreads=ON
	INSTALL_COMMAND ""
)
ExternalProject_Get_Property(googlemock source_dir)
ExternalProject_Get_Property(googlemock binary_dir)
include_directories(${source_dir}; ${source_dir}/include; ${source_dir}/gtest; ${source_dir}/gtest/include)
link_directories(${binary_dir})
set(LIBS ${LIBS} gmock gmock_main)
###########################

# useage testcase(name libs srcs)
# name.cpp is included in the executable.
#function(testcase name libs)
#	add_executable(${name} ${name}.cpp ${ARGN})

##	set_target_properties()

#	add_test(${name} ${name})
#endfunction()

set(SOURCES ${SOURCES} main.cpp)

enable_testing()

#set(SOURCES ${SOURCES} cluster/cluster.cpp)
#file(COPY [FILE] DESTINATION ${EXECUTABLE_OUTPUT_PATH}/unittests/[TESTCASE]/)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
add_dependencies(${PROJECT_NAME} googlemock)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}${SUFFIX})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
