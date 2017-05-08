// Override export symbols for DLL builds (must be included before interface code).
#include "../../Source/DLL_Export_Symbols.h"

#include "../../Interface/G_System/GWindow.h"

class Window : public GW::SYSTEM::GWindow
{
private:

public:

	Window();
	virtual ~Window();

	 GW::GReturn CreateWindow(int _x, int _y, int _width, int _height, GWindowStyle _style) = 0;
	 
	 GW::GReturn ReconfigureWindow(int _x, int _y, int _width, int _height, GWindowStyle _style) = 0;
	
	 GW::GReturn MoveWindow(int _x, int _y) = 0;

	 GW::GReturn ResizeWindow(int _width, int _height) = 0;
	 
	 GW::GReturn Maximize() = 0;
	 
	 GW::GReturn Minimize() = 0;
	 
	 GW::GReturn ChangeWindowStyle(GWindowStyle _style) = 0;

	 int GetWidth() = 0;

	 int GetHeight() = 0;

	 int GetX() = 0;

	 int GetY() = 0;

	 void* GetWindowHandle() = 0;

	 bool IsFullscreen() = 0;
};