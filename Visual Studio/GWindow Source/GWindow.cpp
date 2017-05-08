// Override export symbols for DLL builds (must be included before interface code).
#include "../../Source/DLL_Export_Symbols.h"

#include "../../Interface/G_System/GWindow.h"

using namespace GW;
using namespace SYSTEM;
using namespace CORE;

class Window : public GWindow
{
private:

public:

	Window();
	virtual ~Window();

	 GReturn CreateWindow(int _x, int _y, int _width, int _height, GWindowStyle _style) = 0;
	 
	 GReturn ReconfigureWindow(int _x, int _y, int _width, int _height, GWindowStyle _style) = 0;
	
	 GReturn MoveWindow(int _x, int _y) = 0;

	 GReturn ResizeWindow(int _width, int _height) = 0;
	 
	 GReturn Maximize() = 0;
	 
	 GReturn Minimize() = 0;
	 
	 GReturn ChangeWindowStyle(GWindowStyle _style) = 0;

	 int GetWidth() = 0;

	 int GetHeight() = 0;

	 int GetX() = 0;

	 int GetY() = 0;

	 void* GetWindowHandle() = 0;

	 bool IsFullscreen() = 0;
};