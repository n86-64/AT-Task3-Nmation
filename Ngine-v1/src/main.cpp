/*
*  NGine - A 3D lightweight game engine created for Creative Technologies
*  Author - Nathan Butt
*/

// TODO - Look at using doxygen instead for easier documentation.


#include <string>
#include "Helpers/Win32Ref.h"

// Functions as the C main()
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow) 
{
	OutputDebugString("LOL this works.");
	return 0;
}
