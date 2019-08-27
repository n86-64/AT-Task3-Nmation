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
	KEY_B = 0x42,
	KEY_C = 0x43,
	KEY_D = 0x44,
	KEY_E = 0x45,
	KEY_F = 0x46,
	KEY_G = 0x47,
	KEY_H = 0x48,
	KEY_I = 0x49,
	KEY_J = 0x4A,
	KEY_K = 0x4B,
	KEY_L = 0x4C,
	KEY_M = 0x4D,
	KEY_N = 0x4E,
	KEY_O = 0x4F,
	KEY_P = 0x50,
	KEY_Q = 0x51,
	KEY_R = 0x52,
	KEY_S = 0x53,
	KEY_T = 0x54,
	KEY_U = 0x55,
	KEY_V = 0x56,
	KEY_W = 0x57,
	KEY_X = 0x58,
	KEY_Y = 0x59,
	KEY_Z = 0x5A
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