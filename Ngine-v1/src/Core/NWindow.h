#pragma once

// NWindow class will go here.

#include <functional>
#include <string>
#include <tchar.h>

#include "Helpers/Win32Ref.h"

// TODO - Create an event notification.


class NWindow 
{
public:
	NWindow(std::string  windowTitle,
		int winWidth,
		int winHeight,
		bool isFullscreen,
		std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> winProc,
		HINSTANCE appInstance, int params);

	HWND* getNWindow();
	void UpdateNWindow();

	bool shouldQuit() const;

private:
	 bool quit = false;

	// THe window itself.
	HWND   windowHandle;
	HINSTANCE hInst;

	// Window Properties and Pointers.
	RECT   windowRectangle;

	// Windows procedure call. Handles all the events for the window, these will be sent to our game.
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};