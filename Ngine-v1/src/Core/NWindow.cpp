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

void NWindow::CloseWindow()
{
	DestroyWindow(*windowObject);
	windowObject = nullptr;
}

NWindowHandle* NWindow::getWindowHandle()
{
	return windowObject;
}
