// File - InputHandler.h
// Description - Retrieves input from window handaling libaries for procesing.
// - Also contains input datastructures for mouse and keyboard. 

#pragma once

#include "NWinEvent.h"

#include "InputState.h"


class NInputHandler 
{
public:
	NInputHandler() = default;
	~NInputHandler() = default;

	void updateKeyboardState(NWinEvent message);
	void updateMouseState(NWinEvent  message);

	// retrieve key down state.
	bool getKeyDown(NKeyboardKeys key);


	void resetStates();
private:
	// Double buffer allows for new types of input checks.
	// Useful for text input etc.
	NKeyboardState			 keyboardState;
	NKeyboardState			 prevKeyboardState;

	NMouseState		 mouseState;
	NMouseState		 prevMouseState;
};