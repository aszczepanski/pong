cmake_minimum_required(VERSION 2.8)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(LIBS common)
set(LIBS ${LIBS} pthread SDL2)

set(CLIENT_SRCS
	ClientApplication.cpp
	ClientTCP.cpp
	ClientUDP.cpp
	Communicator.cpp
	IClientSocket.cpp
)

link_directories(${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

add_executable(client-application ${CLIENT_SRCS})
target_link_libraries(client-application ${LIBS})
