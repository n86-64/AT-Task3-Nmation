#include "NWindow.h"

NWindow::NWindow(std::string windowTitle,
	int winWidth,
	int winHeight,
	bool isFullscreen,
	std::function<LRESULT (HWND, UINT, WPARAM, LPARAM)> WndProc,
	HINSTANCE appInstance, int params)
{
	windowRectangle.top = 0;
	windowRectangle.left = 0;
	windowRectangle.bottom = winHeight;
	windowRectangle.right = winWidth;

	// TODO - Move to std::string and then pass these through based on application names.
	TCHAR strWindowClass[] = _T("NGinev1.0");
	TCHAR strWindowTitle[] = _T("NGinev1.0");

	WNDCLASSEX  windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW; // The Style of the window.
	//windowClass.lpfnWndProc = WndProc.target();
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = appInstance;
	windowClass.hIcon = LoadIcon(appInstance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = strWindowClass;
	windowClass.hIconSm = LoadIcon(appInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&windowClass)) 
	{
		OutputDebugString("Error there was a problem. The window did not initialise.");
	}

	hInst = appInstance;

	windowHandle = CreateWindow(
		strWindowClass, 
		strWindowTitle, 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT,
		CW_USEDEFAULT, 
		winWidth, 
		winHeight,
		NULL, 
		NULL, 
		hInst,
		NULL
	);

	if (!windowHandle) 
	{
		OutputDebugString("Error failed to create window handle.");
	}

	ShowWindow(windowHandle, params);
	UpdateWindow(windowHandle);
}

HWND* NWindow::getNWindow()
{
	return &windowHandle;
}

// Processes any window messages before ticking the application.
void NWindow::UpdateNWindow()
{
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);

	quit = (msg.message == WM_QUIT);

	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

bool NWindow::shouldQuit() const
{
	return quit;
}

LRESULT NWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
