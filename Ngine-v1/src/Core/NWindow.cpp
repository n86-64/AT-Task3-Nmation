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

NWindowHandle* NWindow::getWindowHandle()
{
	return windowObject;
}

void NWindow::updateWindow()
{

}

