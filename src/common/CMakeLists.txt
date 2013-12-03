
link_directories(${OpenCV_LIB_DIR})

include_directories(
	../../3rdparty/libopentld/imacq    
	../../3rdparty/libopentld/mftracker
	../../3rdparty/libopentld/tld      
	../../3rdparty/cvblobs    
	../../inc
	${OpenCV_INCLUDE_DIRS})

set(COMMON_SRCS
	Ball.cpp
	Camera.cpp
	CameraEngine.cpp
	Config.cpp
	CursorPosition.cpp
	Drawer.cpp
	GameBoardDrawer.cpp
	Gui.cpp
	ICommunicator.cpp
	IControllerEngine.cpp
	ISocket.cpp
	IThread.cpp
	Main.cpp
	MouseEngine.cpp
	Mutex.cpp
	Player.cpp
	Settings.cpp
	SharedMemory.cpp
	Trajectory.cpp
	Transferable.cpp
)

add_library(common ${COMMON_SRCS})

target_link_libraries(common
	sfml-graphics sfml-window sfml-system
	libopentld cvblobs config++ ${OpenCV_LIBS})
