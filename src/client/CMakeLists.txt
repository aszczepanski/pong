
set(LIBS common)
set(LIBS ${LIBS}
	pthread
	boost_program_options
	X11
	libopentld cvblobs config++ ${Opencv_LIBS})

set(CLIENT_SRCS
	ClientApplication.cpp
	ClientTCP.cpp
	ClientUDP.cpp
	Communicator.cpp
	IClientSocket.cpp
	ReceiverTCP.cpp
	ReceiverUDP.cpp
)

include_directories(
	${CMAKE_SOURCE_DIR}/inc
)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(client-application ${CLIENT_SRCS})
target_link_libraries(client-application ${LIBS})
