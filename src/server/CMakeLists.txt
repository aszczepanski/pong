cmake_minimum_required(VERSION 2.8)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(LIBS common)
set(LIBS ${LIBS} pthread)

set(SERVER_SRCS
	GameEngine.cpp
	ServerApplication.cpp
	ServerTCP.cpp
	SharedMemory.cpp
)

link_directories(${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(server-application ${SERVER_SRCS})
target_link_libraries(server-application ${LIBS})
