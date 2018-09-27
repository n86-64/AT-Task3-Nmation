#include "NWindow.h"


NWindow::NWindow()
{}

NWindow::NWindow(NWindowHandle* window)
	:windowObject(window)
{
}

void NWindow::setAndSetupNWindow(NWindowHandle* window)
{
	windowObject = window;
}

void NWindow::setWindowTitle(std::string newWindowTitle)
{
	SetWindowText(*windowObject, newWindowTitle.c_str());
}

NWindowHandle* NWindow::getWindowHandle()
{
	return windowObject;
}

