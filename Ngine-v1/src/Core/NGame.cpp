#include <string>
#include "NGame.h"

void NGame::init(HWND* window, std::string gameTitle)
{
	// Initialise the engine and all its managers. 
	SetWindowText(*window, gameTitle.c_str());
}

void NGame::ProcessWindowEvents(NWinEvent winEvent)
{
	MSG message = winEvent.getEventData();

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
