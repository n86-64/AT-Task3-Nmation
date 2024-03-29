/*
*  NGine - A 3D lightweight game engine created for Creative Technologies
*  Author - Nathan Butt
*/

// TODO - Look at using doxygen instead for easier documentation.

#include <tchar.h>
#include <string>

#include "Core/NGame.h"
#include "Core/NWinEvent.h"

namespace Application 
{
	// The game object which is static to allow for 
	// use in WndProc.
	static NGame game;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Functions as the C main()
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow) 
{
	HWND windowHandle;
	TCHAR strWindowClass[] = _T("NGineApp");
	TCHAR strWindowTitle[] = _T("NGinev1.0");

	WNDCLASSEX  windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW; // The Style of the window.
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = strWindowClass;
	windowClass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&windowClass))
	{
		OutputDebugString("Error there was a problem. The window did not initialise.");
	}

	windowHandle = CreateWindow(
		strWindowClass,
		strWindowTitle,
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		200,
		400,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!windowHandle)
	{
		OutputDebugString("Error failed to create window handle.");
	}

	NInitSettings initParams = {};
	initParams.gameTitle = "NAnimationSystem";
	initParams.nCmdShow = nCmdShow;

	MSG msg = {};
	if (Application::game.init(&windowHandle, initParams)) 
	{
		// TODO- Move window processing into the game object.
		// For now we will do it here as it allows us to ensure that the game works.
		// Yes this includes the ticking call.
		// makes life easier.
		while (!Application::game.shouldQuit())
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else 
			{
				// tick the game here.
				Application::game.Tick();
			}
		}
	}
	else 
	{
		return 1; // TODO - Impliment error codes.
	}

	return 0;
}

// Application callback function.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	NWinEvent winEvent(hWnd, message, wParam, lParam);

	// Here the callbacks for the windows should get passed to the game.
	// Allowing us to deal with them.
	// These will be processed within the engine.
	switch (message) 
	{
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
	case WM_DESTROY:
	case WM_SIZE:
		Application::game.ProcessWindowEvents(winEvent);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}