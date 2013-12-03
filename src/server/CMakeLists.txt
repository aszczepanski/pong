
set(LIBS common)
set(LIBS ${LIBS}
	pthread
	Box2D
	boost_program_options
	libopentld cvblobs config++ ${OpenCV_LIBS})

set(SERVER_SRCS
	Communicator.cpp
	ConnectionTCP.cpp
	ConnectionUDP.cpp
	GameEngine.cpp
	IServerSocket.cpp
	ServerApplication.cpp
	ServerTCP.cpp
	ServerUDP.cpp
)

include_directories(
	../../inc
	${OpenCV_INCLUDE_DIRS})

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(server-application ${SERVER_SRCS})
target_link_libraries(server-application ${LIBS})
