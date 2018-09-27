#include <string>
#include "NGame.h"

void NGame::init(NWindowHandle* window, std::string gameTitle)
{
	// Initialise the engine and all its managers. 
	SetWindowText(*window, gameTitle.c_str());
}

void NGame::ProcessWindowEvents(NWinEvent winEvent)
{
	NWindowMessage message = winEvent.getEventData();

	switch (message.message) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		OutputDebugString("The window has been resized");
		break;
	}
}
