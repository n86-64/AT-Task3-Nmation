/*
*  NGine - A 3D lightweight game engine created for Creative Technologies
*  Author - Nathan Butt
*/

// TODO - Look at using doxygen instead for easier documentation.


#include <string>
#include "Helpers/Win32Ref.h"

#include "Core/NWindow.h"

// Functions as the C main()
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow) 
{
	NWindow win = NWindow("Test", 100, 100, false, hInstance, nCmdShow);
	
	while (!win.shouldQuit()) 
	{
		win.UpdateNWindow();
	}

	OutputDebugString("LOL this works.");
	return 0;
}
