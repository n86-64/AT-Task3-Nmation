#include "NWinEvent.h"

NWinEvent::NWinEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam):
	eventMessage({})
{
	eventMessage.hwnd = hWnd;
	eventMessage.message = message;
	eventMessage.wParam = wParam;
	eventMessage.lParam = lParam;
}

MSG NWinEvent::getEventData()
{
	return eventMessage;
}
