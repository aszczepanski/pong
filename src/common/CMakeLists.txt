cmake_minimum_required(VERSION 2.8)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(COMMON_SRCS
	Ball.cpp
	Camera.cpp
	CameraEngine.cpp
	CursorPosition.cpp
	Drawer.cpp
	GameBoardDrawer.cpp
	ICommunicator.cpp
	IControllerEngine.cpp
	ISocket.cpp
	IThread.cpp
	MouseEngine.cpp
	Mutex.cpp
	Player.cpp
	SharedMemory.cpp
	Transferable.cpp
)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

add_library(common ${COMMON_SRCS})
