#include "NGame.h"

void NGame::init(HWND* window)
{
	// Initialise the engine and all its managers. 

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
