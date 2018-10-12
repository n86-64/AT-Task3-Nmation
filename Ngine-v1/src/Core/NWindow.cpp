#include "NWindow.h"


NWindow::NWindow()
{
}

NWindow::NWindow(NWindowHandle* window)
	:windowObject(window)
{
}

// DEPRECATED
void NWindow::setAndSetupNWindow(NWindowHandle* window)
{
	windowObject = window;
}

void NWindow::setAndSetupWindow(NWindowHandle * window, int nCmdShow)
{
	// Here we show the window once its created
	windowObject = window;
	ShowWindow(*windowObject, nCmdShow);
	UpdateWindow(*windowObject);
}

void NWindow::setWindowTitle(std::string newWindowTitle)
{
	SetWindowText(*windowObject, newWindowTitle.c_str());
}

void NWindow::setWindowSize(int width, int height)
{
	RECT newRect = {};
	GetWindowRect(*windowObject, &newRect);

	newRect.right = width;
	newRect.bottom = height;

	AdjustWindowRect(&newRect, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(*windowObject, HWND_TOP, newRect.left, newRect.top, newRect.right, newRect.bottom, SWP_SHOWWINDOW);
}

void NWindow::CloseWindow()
{
	if (windowObject) 
	{
		DestroyWindow(*windowObject);
		windowObject = nullptr;
	}
}

NWindowHandle* NWindow::getWindowHandle()
{
	return windowObject;
}
