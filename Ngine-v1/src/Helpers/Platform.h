#pragma once

// File - Platform.h
// Discription - Platform specific classes and constants are defined here. 

#include <string>
#include "Helpers/Win32Ref.h"


#ifdef _WIN32
using NWindowHandle = HWND;
using NWindowMessage = MSG;
#else // ITS A UNIX SYSTEM!!!
// Place other system window definitions here.
// (Linux (Tom I know this upsets you)\Mac)
#endif


// Defines initialisation parameters
struct NInitSettings 
{
public:
#ifdef _WIN32
	int nCmdShow = 0;
#endif
	std::string  gameTitle;
};