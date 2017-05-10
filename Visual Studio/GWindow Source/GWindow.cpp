// Override export symbols for DLL builds (must be included before interface code).
#include "../../Source/DLL_Export_Symbols.h"

#include "../../Interface/G_System/GWindow.h"
#include <atomic>

using namespace GW;
using namespace SYSTEM;
using namespace CORE;
using std::atomic;

class AppWindow : public GWindow
{
	atomic<unsigned int> refCount;

	atomic<int> xPos;
	atomic<int> yPos;
	atomic<int> width;
	atomic<int> height;

	GWindowStyle style;

private:

public:

	AppWindow();
	virtual ~AppWindow();

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

AppWindow::AppWindow() : refCount(1)
{

}

AppWindow::~AppWindow()
{

}

GReturn AppWindow::CreateWindow(int _x, int _y, int _width, int height, GWindowStyle _style)
{

}

GReturn AppWindow::ReconfigureWindow(int _x, int _y, int _width, int height, GWindowStyle _style)
{

}

GReturn AppWindow::MoveWindow(int _x, int _y)
{

}

GReturn AppWindow::ResizeWindow(int _width, int _height)
{

}

GReturn AppWindow::Maximize()
{

}

GReturn AppWindow::Minimize()
{

}

GReturn AppWindow::ChangeWindowStyle(GWindowStyle _style)
{

}

int AppWindow::GetWidth()
{

}

int AppWindow::GetHeight()
{

}

int AppWindow::GetX()
{

}

int AppWindow::GetY()
{

}

void* AppWindow::GetWindowHandle()
{

}

bool AppWindow::IsFullscreen()
{

}

GATEWARE_EXPORT_EXPLICIT GReturn CreateGWindow(int _x, int _y, int _width, int _height, GWindowStyle _style, GWindow** _outWindow)
{

}
