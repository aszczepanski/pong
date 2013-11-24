cmake_minimum_required(VERSION 2.8)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(LIBS common)
set(LIBS ${LIBS} pthread Box2D SDL2 opencv_core opencv_highgui opencv_imgproc)

set(SERVER_SRCS
  Communicator.cpp
  GameEngine.cpp
  IServerSocket.cpp
  ServerApplication.cpp
  ServerConnection.cpp
  ServerTCP.cpp
  ServerUDP.cpp
)

link_directories(${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

add_executable(server-application ${SERVER_SRCS})
target_link_libraries(server-application ${LIBS})
