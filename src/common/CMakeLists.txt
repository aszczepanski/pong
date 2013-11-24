cmake_minimum_required(VERSION 2.8)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(COMMON_SRCS
	Ball.cpp
	Camera.cpp
	CursorPosition.cpp
	Drawer.cpp
	ICommunicator.cpp
	ISocket.cpp
	IThread.cpp
	Mutex.cpp
	Player.cpp
	SharedMemory.cpp
	Transferable.cpp
)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

add_library(common ${COMMON_SRCS})
