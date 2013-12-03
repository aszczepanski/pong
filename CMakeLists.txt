project(pong)
cmake_minimum_required(VERSION 2.8)

find_package(OpenCV REQUIRED)

set(TLD_VERSION_MAJOR 1)
set(TLD_VERSION_MINOR 3)
set(TLD_VERSION_PATCH 0)
set(TLD_VERSION ${TLD_VERSION_MAJOR}.${TLD_VERSION_MINOR}.${TLD_VERSION_PATCH})

if(NOT CMAKE_BUILD_TYPE)   
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."                                    
	FORCE)
endif(NOT CMAKE_BUILD_TYPE)

option(USE_SYSTEM_LIBS "Use the installed version of libconfig++." OFF)

if(APPLE)                                                                                         
         add_definitions(-DHAVE_XLOCALE_H)
endif(APPLE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgomp")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


add_subdirectory(3rdparty/cvblobs)

if(NOT USE_SYSTEM_LIBS)
	add_subdirectory(3rdparty/libconfig)
endif(NOT USE_SYSTEM_LIBS)

add_subdirectory(3rdparty/libopentld)
add_subdirectory(src/)

set(INCLUDE_DIRS
	${CMAKE_SOURCE_DIR}/3rdparty/cvblobs
	${CMAKE_SOURCE_DIR}/3rdparty/libconfig
	${CMAKE_SOURCE_DIR}/libopentld/tld
	${CMAKE_SOURCE_DIR}/libopentld/mftracker
	${CMAKE_SOURCE_DIR}/libopentld/imacq
	${CMAKE_SOURCE_DIR}/inc)
INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

