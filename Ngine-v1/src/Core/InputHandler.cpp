#include "InputHandler.h"

void NInputHandler::updateKeyboardState(NWinEvent message)
{
	// TODO - Check if a key is down or up.
	keyboardState.keyState[message.getEventData().wParam] = (message.getEventData().message && WM_KEYDOWN);
}

void NInputHandler::updateMouseState(NWinEvent message)
{

}

bool NInputHandler::getKeyDown(NKeyboardKeys key)
{
	return keyboardState.keyState[key];
}

void NInputHandler::resetStates()
{
	prevKeyboardState = keyboardState; 
	for (int i = 0; i < NINPUT_NUMBER_OF_KEYS; i++) 
	{
		keyboardState.keyState[i] = false;
	}
}
