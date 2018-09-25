#pragma once

// NWindow class will go here.

#include <functional>
#include <string>

#include "Helpers/Win32Ref.h"

class NWindow 
{
public:
	NWindow(std::string  windowTitle,
		int winWidth,
		int winHeight,
		bool isFullscreen,
		std::function<LRESULT CALLBACK(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)> winEventHandler);

private:
	HWND   windowHandle;
};