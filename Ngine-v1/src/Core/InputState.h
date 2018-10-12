// File - InputState.h
// Definition - Defines the input state and data values for input.
// Defined for a win32 application only.
#pragma once

constexpr int NINPUT_NUMBER_OF_KEYS = 254;

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

};

// Stores the state of the keyboard.
struct NKeyboardState
{
	bool			keyState[NINPUT_NUMBER_OF_KEYS];

};

struct NMouseButtonState
{

};