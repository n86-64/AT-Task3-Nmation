#include <windowsx.h>
#include "InputHandler.h"

void NInputHandler::updateKeyboardState(NWinEvent message)
{
	// TODO - Check if a key is down or up.
	keyboardState.keyState[message.getEventData().wParam] = (message.getEventData().message == WM_KEYDOWN);
}

void NInputHandler::updateMouseState(NWinEvent message)
{
	mouseState.xPos = GET_X_LPARAM(message.getEventData().lParam);
	mouseState.yPos = GET_Y_LPARAM(message.getEventData().lParam);
}

bool NInputHandler::getKeyDown(NKeyboardKeys key)
{
	return keyboardState.keyState[key];
}

void NInputHandler::updateStates()
{
	prevKeyboardState = keyboardState;
	prevMouseState = mouseState;
}
