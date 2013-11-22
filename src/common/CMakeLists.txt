cmake_minimum_required(VERSION 2.8)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(COMMON_SRCS
	Ball.cpp
	Communicator.cpp
	IThread.cpp
	Mutex.cpp
	Player.cpp
	Transferable.cpp
)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_library(common ${COMMON_SRCS})
