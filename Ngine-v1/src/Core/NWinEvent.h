#pragma once

// File - NWinEvent.h
// Allows for the handaling of window events.
// We will only handle events that we care about all others will be handled via 
// WndProc exclusivly.

#include "Helpers/Platform.h"

class NWinEvent 
{
public:
	NWinEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	NWindowMessage  getEventData();

private:
	NWindowMessage  eventMessage;
};