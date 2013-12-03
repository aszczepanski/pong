#include <common/CameraEngine.h>
#include <common/SharedMemory.h>
#include <common/ICommunicator.h>
#include <common/Camera.h>
#include <iostream>

#include "Main.h"
#include "Config.h"
#include "ImAcq.h"
#include "Gui.h"

using tld::Config;
using tld::Gui;
using tld::Settings;

using namespace common;
using namespace std;

CameraEngine::CameraEngine(SharedMemory& sharedMemory, ICommunicator& communicator)
	: IControllerEngine(sharedMemory, communicator)
{
}

void CameraEngine::run()
{
	cout << "CameraEngine" << endl;
	Main *main = new Main(communicator);
	Config config;
	ImAcq *imAcq = imAcqAlloc();
	Gui *gui = new Gui();

	main->gui = gui;
	main->imAcq = imAcq;

	int argc = 2;
	char* argv[] = {"./server-application", "--camera"};
	if(config.init(argc, argv) == PROGRAM_EXIT)
	{
//	    return EXIT_FAILURE;
	}

	config.configure(main);

	srand(main->seed);

	imAcqInit(imAcq);

	if(main->showOutput)
	{
		gui->init();
	}

	main->doWork();

	delete main;
	main = NULL;
	delete gui;
	gui = NULL;

//	return EXIT_SUCCESS;
}
