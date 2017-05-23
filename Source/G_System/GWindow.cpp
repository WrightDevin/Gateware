// Override export symbols for DLL builds (must be included before interface code).
#include "../../Source/DLL_Export_Symbols.h"
#include "../../Source/G_System/GI_Static.cpp"
#include "../../Interface/G_System/GWindow.h"
#include "GUtility.h"

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

	 GReturn OpenWindow();
	 
	 GReturn ReconfigureWindow(int _x, int _y, int _width, int _height, GWindowStyle _style);
	 
	 GReturn InitWindow(int _x, int _y, int _width, int _height, GWindowStyle _style);

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

GReturn AppWindow::OpenWindow()
{
	if (wndHandle)
		return REDUNDANT_OPERATION;

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

	RECT windowRect = { xPos, yPos, width, height };
	
	switch (style)
	{
	case WINDOWEDBORDERED:
	{
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

		wndHandle = CreateWindowW(appName, L"Win32Window", WS_OVERLAPPEDWINDOW,
			0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			NULL, NULL, GetModuleHandleW(0), 0);

		if(!wndHandle)
			printf("CreateWindowW error: %d\r\n", GetLastError());
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

GReturn AppWindow::ReconfigureWindow(int _x, int _y, int _width, int _height, GWindowStyle _style)
{
	if (!wndHandle)
		return REDUNDANT_OPERATION;

	GReturn Gret = InitWindow(_x, _y, _width, _height, _style);
	if (Gret != SUCCESS)
		return Gret;

	BOOL Winret = SetWindowPos(wndHandle, nullptr, xPos, yPos, width, height, SWP_SHOWWINDOW);
	if (Winret == 0)
		return FAILURE;
	else
		return SUCCESS;
}

GReturn AppWindow::InitWindow(int _x, int _y, int _width, int _height, GWindowStyle _style)
{
	if (_x < 0 || _y < 0 || _width < 0 || _height < 0 || _style < 0 || _style > 4)
		return INVALID_ARGUMENT;

	if (_width > 1920)
		width = 1920;
	else
		width = _width;

	if (_height > 1080)
		height = 1080;
	else
		height = _height;

	if (_x > 1920)
		xPos = 1920;
	else
		xPos = _x;

	if (_y > 1080)
		yPos = 1080;
	else
		yPos = _y;

	style = _style;
	
	return SUCCESS;
}

GReturn AppWindow::MoveWindow(int _x, int _y)
{
	if (!wndHandle)
		return REDUNDANT_OPERATION;

	GReturn Gret = InitWindow(_x, _y, width, height, style);
	if (Gret != SUCCESS)
		return Gret;

	BOOL Winret = SetWindowPos(wndHandle, nullptr, xPos, yPos, width, height, SWP_SHOWWINDOW);
	if (Winret == 0)
		return FAILURE;
	else
		return SUCCESS;
}

GReturn AppWindow::ResizeWindow(int _width, int _height)
{
	if (!wndHandle)
		return REDUNDANT_OPERATION;

	GReturn Gret = InitWindow(xPos, yPos, _width, _height, style);
	if (Gret != SUCCESS)
		return Gret;

	BOOL Winret = SetWindowPos(wndHandle, nullptr, xPos, yPos, width, height, SWP_SHOWWINDOW);
	if (Winret == 0)
		return FAILURE;
	else
		return SUCCESS;
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
	_outCount = refCount;
	return SUCCESS;
}

GReturn AppWindow::IncrementCount()
{
	//Check for possible overflow.
	if (refCount == G_UINT_MAX)
		return FAILURE;

	++refCount;

	return SUCCESS;
}

GReturn AppWindow::DecrementCount()
{
	//Check to make sure underflow will not occur.
	if (refCount == 0)
	{
		delete this;
		return FAILURE;
	}
		
	--refCount;

	return SUCCESS;
}

GReturn AppWindow::RequestInterface(const GUUIID& _interfaceID, void** _outputInterface)
{
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	if (_interfaceID == GWindowUUIID)
	{
		GWindow* convert = reinterpret_cast<GWindow*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GBroadcastingUUIID)
	{
		GBroadcasting* convert = reinterpret_cast<GBroadcasting*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GMultiThreadedUUIID)
	{
		GMultiThreaded* convert = reinterpret_cast<GMultiThreaded*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GInterfaceUUIID)
	{
		GInterface* convert = reinterpret_cast<GInterface*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else
		return INTERFACE_UNSUPPORTED;

	return SUCCESS;
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
	return width;
}

int AppWindow::GetHeight()
{
	return height;
}

int AppWindow::GetX()
{
	return xPos;
}

int AppWindow::GetY()
{
	return yPos;
}

void* AppWindow::GetWindowHandle()
{
	return wndHandle;
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

	if (Window == nullptr)
		return FAILURE;

	GReturn Gret = Window->InitWindow(_x, _y, _width, _height, _style);

	if (Gret == INVALID_ARGUMENT)
		return Gret;

	*_outWindow = Window;

	return SUCCESS;
}