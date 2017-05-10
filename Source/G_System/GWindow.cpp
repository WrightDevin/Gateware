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

	 GReturn GetCount(unsigned int& _outCount);

	 GReturn IncrementCount();

	 GReturn DecrementCount();

	 GReturn RequestInterface(const GUUIID& _interfaceID, void** _outputInterface);

	 GReturn RegisterListener(GListener* _addListener, unsigned long long _eventMask);

	 GReturn DeregisterListener(GListener* _removeListener);

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
	return FAILURE;
}

GReturn AppWindow::ReconfigureWindow(int _x, int _y, int _width, int height, GWindowStyle _style)
{
	return FAILURE;
}

GReturn AppWindow::MoveWindow(int _x, int _y)
{
	return FAILURE;
}

GReturn AppWindow::ResizeWindow(int _width, int _height)
{
	return FAILURE;
}

GReturn AppWindow::Maximize()
{
	return FAILURE;
}

GReturn AppWindow::Minimize()
{
	return FAILURE;
}

GReturn AppWindow::ChangeWindowStyle(GWindowStyle _style)
{
	return FAILURE;
}

GReturn AppWindow::GetCount(unsigned int& _outCount)
{
	return FAILURE;
}

GReturn AppWindow::IncrementCount()
{
	return FAILURE;
}

GReturn AppWindow::DecrementCount()
{
	return FAILURE;
}

GReturn AppWindow::RequestInterface(const GUUIID& _interfaceID, void** _outputInterface)
{
	return FAILURE;
}

GReturn AppWindow::RegisterListener(GListener* _addListener, unsigned long long _eventMask)
{
	return FAILURE;
}

GReturn AppWindow::DeregisterListener(GListener* _removeListener)
{
	return FAILURE;
}

int AppWindow::GetWidth()
{
	return -1;
}

int AppWindow::GetHeight()
{
	return -1;
}

int AppWindow::GetX()
{
	return -1;
}

int AppWindow::GetY()
{
	return -1;
}

void* AppWindow::GetWindowHandle()
{
	return nullptr;
}

bool AppWindow::IsFullscreen()
{
	return false;
}

GATEWARE_EXPORT_EXPLICIT GReturn CreateGWindow(int _x, int _y, int _width, int _height, GWindowStyle _style, GWindow** _outWindow)
{
	return FAILURE;
}
