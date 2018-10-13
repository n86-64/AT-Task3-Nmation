// File - InputState.h
// Definition - Defines the input state and data values for input.
// Defined for a win32 application only.
#pragma once

constexpr int NINPUT_NUMBER_OF_KEYS = 254;
constexpr int NINPUT_NUMBER_OF_BUTTONS = 7;

// Defines each of the keyboard keys.
enum NKeyboardKeys
{
	// KEYS HERE SHOULD MATCH WIN32 DEFINITIONS.

	// Control keys
	KEY_ENTER = 0x0D,
	KEY_ESCAPE = 0x1B,

	// Letter Keys
	KEY_A = 0x41,
};

// Defines each mouse key.
enum NMouseButtons 
{
	BUTTON_LEFT = 0x01,
	BUTTON_RIGHT = 0x02,
	BUTTON_MBUTTON = 0x04,

	BUTTON_1 = 0x05,
	BUTTON_2 = 0x06
};

// Stores the state of the keyboard.
struct NKeyboardState
{
	bool			keyState[NINPUT_NUMBER_OF_KEYS];

};

// Stores the state of the mouse.
struct NMouseState
{
	bool		buttonStates[NINPUT_NUMBER_OF_BUTTONS];
	float		xPos = 0.0f;
	float		yPos = 0.0f;
	float		mouseWheel = 0.0f;
};