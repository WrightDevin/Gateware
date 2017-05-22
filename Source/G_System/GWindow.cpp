// Override export symbols for DLL builds (must be included before interface code).
#include "../../Source/DLL_Export_Symbols.h"
#include "../../Source/G_System/GI_Static.cpp"
#include "../../Interface/G_System/GWindow.h"

using namespace GW;
using namespace CORE;
using namespace SYSTEM;

namespace
{
	// GWindow global variables.

	//! Map of Listeners to send event information to.
	std::map<GListener *, unsigned long long> listeners;

	//! Store the users implementation of the windows procedure.
	LONG_PTR userWinProc;
	//! Store the global handle to the Windows window.
	HWND wndHandle;
}

#include "../../Source/G_System/GWindow_Callback.cpp"
#include <atomic>

using std::atomic;

class AppWindow : public GWindow
{
private:

	atomic<unsigned int> refCount;

	atomic<int> xPos;
	atomic<int> yPos;
	atomic<int> width;
	atomic<int> height;

	GWindowStyle style;


public:

	AppWindow();
	virtual ~AppWindow();

	 GReturn OpenWindow(int _x, int _y, int _width, int _height, GWindowStyle _style);
	 
	 GReturn ReconfigureWindow(int _x, int _y, int _width, int _height, GWindowStyle _style);
	
	 GReturn MoveWindow(int _x, int _y);

	 GReturn ResizeWindow(int _width, int _height);
	 
	 GReturn Maximize();
	 
	 GReturn Minimize();
	 
	 GReturn ChangeWindowStyle(GWindowStyle _style);

	 GReturn GetCount(unsigned int& _outCount);

	 GReturn IncrementCount();

	 GReturn DecrementCount();

	 GReturn RequestInterface(const GUUIID& _interfaceID, void** _outputInterface);

	 GReturn RegisterListener(GListener* _addListener, unsigned long long _eventMask);

	 GReturn DeregisterListener(GListener* _removeListener);

	 int GetWidth();

	 int GetHeight();

	 int GetX();

	 int GetY();

	 void* GetWindowHandle();

	 bool IsFullscreen();
};

AppWindow::AppWindow() : refCount(1) , xPos(0) , yPos(0) , width(0) , height(0) , style(WINDOWEDBORDERED)
{
	
}

AppWindow::~AppWindow()
{

}

GReturn AppWindow::OpenWindow(int _x, int _y, int _width, int _height, GWindowStyle _style)
{
	if (wndHandle)
		return REDUNDANT_OPERATION;

	if (_x < 0 || _y < 0 || _width < 0 || _height < 0)
		return INVALID_ARGUMENT;

	WNDCLASSEX winClass;
	ZeroMemory(&winClass, sizeof(WNDCLASSEX));

	LPCWSTR appName = L"GWindow Test App";
	
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	winClass.hCursor = LoadCursorW(NULL, IDC_CROSS);
	winClass.hIcon = LoadIconW(0, IDI_EXCLAMATION);
	winClass.hInstance = GetModuleHandleW(0);
	winClass.lpfnWndProc = GWindowProc;
	winClass.lpszClassName = appName;
	winClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassExW(&winClass);
	
	int width, height, x, y = 0;

	if (_width > 1920)
		width = 1920;
	else
		width = _width;

	if (_height > 1080)
		height = 1080;
	else
		height = _height;

	if (_x > 1920)
		x = 1920;
	else
		x = _x;

	if (_y > 1080)
		y = 1080;
	else
		y = _y;

	RECT windowRect = { x, y, width, height };
	
	switch (_style)
	{
	case WINDOWEDBORDERED:
	{
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

		wndHandle = CreateWindowW(appName, L"Win32Window", WS_OVERLAPPEDWINDOW,
			0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			NULL, NULL, GetModuleHandleW(0), 0);
	}
	break;

	case WINDOWEDBORDERLESS:
	{
		AdjustWindowRect(&windowRect, WS_POPUP, false);

		wndHandle = CreateWindowW(appName, L"Win32Window", WS_POPUP,
			0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			NULL, NULL, GetModuleHandleW(0), 0);
	}
	break;

	case FULLSCREENBORDERED:
	{
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, false);

		wndHandle = CreateWindowW(appName, L"Win32Window", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
			0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			NULL, NULL, GetModuleHandleW(0), 0);
	}
	break;

	case FULLSCREENBORDERLESS:
	{
		AdjustWindowRect(&windowRect, WS_POPUP | WS_MAXIMIZE, false);

		wndHandle = CreateWindowW(appName, L"Win32Window", WS_POPUP | WS_MAXIMIZE,
			0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			NULL, NULL, GetModuleHandleW(0), 0);
	}
	break;

	case MINIMIZED:
	{
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW | WS_MINIMIZE, false);

		wndHandle = CreateWindowW(appName, L"Win32Window", WS_OVERLAPPEDWINDOW | WS_MINIMIZE,
			0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			NULL, NULL, GetModuleHandleW(0), 0);
	}
	break;
	}
	
	if (wndHandle)
	{
		ShowWindow(wndHandle, SW_SHOW);
		return SUCCESS;
	}
	else
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
	return GW::SYSTEM::CreateGWindow(_x, _y, _width, _height, _style, _outWindow);
}

GReturn GW::SYSTEM::CreateGWindow(int _x, int _y, int _width, int _height, GWindowStyle _style, GWindow** _outWindow)
{
	if (_outWindow == nullptr)
		return INVALID_ARGUMENT;

	AppWindow* Window = new AppWindow();

	*_outWindow = Window;
	return FAILURE;
}