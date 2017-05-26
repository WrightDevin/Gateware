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
}

#include "../../Source/G_System/GWindow_Callback.cpp"
#include <atomic>
#include <mutex>

class AppWindow : public GWindow
{
private:

	std::atomic<unsigned int> refCount;
	
	std::atomic<int> xPos;
	std::atomic<int> yPos;
	std::atomic<int> width;
	std::atomic<int> height;
	
	std::atomic<HWND> wndHandle;

	GWindowStyle style;
	unsigned int style2;
	std::mutex refMutex;

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

AppWindow::AppWindow() : refCount(1) , xPos(0) , yPos(0) , width(0) , height(0) , style(FULLSCREENBORDERED), style2(WINDOWEDBORDERED), wndHandle(0)
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

	LPCWSTR appName = L"GWindow Application";
	
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	winClass.hCursor = LoadCursorW(NULL, IDC_CROSS);
	winClass.hIcon = LoadIconW(0, IDI_APPLICATION);
	winClass.lpfnWndProc = GWindowProc;
	winClass.lpszClassName = appName;
	winClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClass.hInstance = GetModuleHandleW(0);

	if (!RegisterClassExW(&winClass))
	{
		printf("RegisterClassExW Error : %d \n", GetLastError());
	}
		

	RECT windowRect = { xPos, yPos, width, height };
	DWORD windowsStyle;

	if (style == WINDOWEDBORDERED)
	{
		windowsStyle = WS_OVERLAPPEDWINDOW;
	}

	else if (style == WINDOWEDBORDERLESS)
	{
		windowsStyle = WS_POPUP;
	}

	else if (style == FULLSCREENBORDERED)
	{
		windowsStyle = WS_OVERLAPPEDWINDOW;
	}

	else if (style == FULLSCREENBORDERLESS)
	{
		windowsStyle = WS_POPUP;
	}

	//Create the window
	wndHandle = CreateWindowW(appName, L"Win32Window", windowsStyle, xPos, yPos, 800, 800, NULL, NULL, GetModuleHandleW(0), 0);

	if (wndHandle && style != MINIMIZED)
	{
		if (ShowWindow(wndHandle, SW_SHOWDEFAULT) != 0)
		{
			printf("ShowWindow Error Message : %d \n", GetLastError());
			return FAILURE;
		}

		SetWindowPos(wndHandle, HWND_TOP, 500, 500, 800, 800, SWP_SHOWWINDOW);
		
		printf("ShowWindow Error Message : %d \n", GetLastError());

	}
	else if (wndHandle && style == MINIMIZED)
	{
		ShowWindow(wndHandle, SW_MINIMIZE);
		return SUCCESS;
	}
	else
		return FAILURE;
}

GReturn AppWindow::ReconfigureWindow(int _x, int _y, int _width, int _height, GWindowStyle _style)
{
	if (!wndHandle)
		return REDUNDANT_OPERATION;

	GWindowStyle previousStyle = style;

	GReturn Gret = InitWindow(_x, _y, _width, _height, _style);
	if (Gret != SUCCESS)
		return Gret;

	if (previousStyle != style)
	{
		switch (style)
		{
		case WINDOWEDBORDERED:
		{
			SetWindowLongPtr(wndHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			BOOL winRet = SetWindowPos(wndHandle, nullptr, xPos, yPos, width, height, SWP_SHOWWINDOW);
			if (winRet == 0)
				return FAILURE;
			else
				return SUCCESS;

		}
		break;

		case WINDOWEDBORDERLESS:
		{
			SetWindowLongPtr(wndHandle, GWL_STYLE, WS_POPUP);
			BOOL winRet = SetWindowPos(wndHandle, nullptr, xPos, yPos, width, height, SWP_SHOWWINDOW);
			if (winRet == 0)
				return FAILURE;
			else
				return SUCCESS;
		}
		break;

		case FULLSCREENBORDERED:
		{
			RECT windowRect = { xPos, yPos, width, height };
			GetWindowRect(wndHandle, &windowRect);

			SetWindowLongPtr(wndHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			BOOL winRet = SetWindowPos(wndHandle, nullptr, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);
			if (winRet == 0)
				return FAILURE;

		
			GetWindowRect(wndHandle, &windowRect);

			return InitWindow(windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, style);
			
		}
		break;

		case FULLSCREENBORDERLESS:
		{
			SetWindowLongPtr(wndHandle, GWL_STYLE, WS_POPUP);
			BOOL winRet = SetWindowPos(wndHandle, nullptr, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);
			if (winRet == 0)
				return FAILURE;

			RECT windowRect = { xPos, yPos, width, height };
			GetWindowRect(wndHandle, &windowRect);
			
			return InitWindow(windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, style);
		}
		break;

		case MINIMIZED:
		{
			//SetWindowLongPtr(wndHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_MINIMIZE);
			//BOOL winRet = SetWindowPos(wndHandle, nullptr, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);
			//if (winRet == 0)
			//	return FAILURE;
			//
			//RECT windowRect = { xPos, yPos, width, height };
			//GetWindowRect(wndHandle, &windowRect);
			ShowWindow(wndHandle, SW_MINIMIZE);

			RECT windowRect = { xPos, yPos, width, height };
			GetWindowRect(wndHandle, &windowRect);

			return InitWindow(windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, style);
		}
		break;
		}
	}
	RECT windowRect = { xPos, yPos, width, height };
	GetWindowRect(wndHandle, &windowRect);

	return SUCCESS;
}

GReturn AppWindow::InitWindow(int _x, int _y, int _width, int _height, GWindowStyle _style)
{
	if (_style < 0 || _style > 4)
		return INVALID_ARGUMENT;

	int xMax = GetSystemMetrics(SM_CXSCREEN);
	int yMax = GetSystemMetrics(SM_CYSCREEN);

	if (_width > xMax)
		width = xMax;
	else if (_width < 0)
		width = 0;
	else
		width = _width;

	if (_height > yMax)
		height = yMax;
	else if (_height < 0)
		height = 0;
	else
		height = _height;

	if (_x > xMax)
		xPos = xMax;
	else if (_x < 0)
		xPos = 0;
	else
		xPos = _x;

	if (_y > yMax)
		yPos = yMax;
	else if (_y < 0)
		yPos = 0;
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

	RECT windowRect = { xPos, yPos, width, height };
	GetWindowRect(wndHandle, &windowRect);

	if (Winret == 0)
		return FAILURE;
	else
		return SUCCESS;
}

GReturn AppWindow::Maximize()
{
	if (style == WINDOWEDBORDERED || MINIMIZED)
	{
		return ChangeWindowStyle(FULLSCREENBORDERED);
	}

	else if (style == WINDOWEDBORDERLESS)
		return ChangeWindowStyle(FULLSCREENBORDERLESS);
	else
		return REDUNDANT_OPERATION;
}

GReturn AppWindow::Minimize()
{
	return ChangeWindowStyle(MINIMIZED);
}

GReturn AppWindow::ChangeWindowStyle(GWindowStyle _style)
{
	return ReconfigureWindow(xPos, yPos, width, height, _style);
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
	if (_addListener == nullptr) {
		return INVALID_ARGUMENT;
	}

	refMutex.lock();

	std::map<GListener*, unsigned long long>::const_iterator iter = listeners.find(_addListener);
	if (iter != listeners.end()) {
		return REDUNDANT_OPERATION;
	}

	listeners[_addListener] = _eventMask;
	IncrementCount();

	refMutex.unlock();

	return SUCCESS;
}

GReturn AppWindow::DeregisterListener(GListener* _removeListener)
{
	if (_removeListener == nullptr) {
		return INVALID_ARGUMENT;
	}

	refMutex.lock();

	std::map<GListener*, unsigned long long>::const_iterator iter = listeners.find(_removeListener);
	if (iter != listeners.end()) {
		listeners.erase(iter);
		refMutex.unlock();
		DecrementCount();
	}
	else {
		refMutex.unlock();
		return FAILURE;
	}

	return SUCCESS;
}

int AppWindow::GetWidth()
{
	if (!wndHandle)
		return -1;

	RECT windowRect;
	GetWindowRect(wndHandle, &windowRect);

	width = windowRect.right - windowRect.left;
	return width;
}

int AppWindow::GetHeight()
{
	if (!wndHandle)
		return -1;

	RECT windowRect;
	GetWindowRect(wndHandle, &windowRect);

	height = windowRect.bottom - windowRect.top;
	return height;
}

int AppWindow::GetX()
{
	if (!wndHandle)
		return -1;

	RECT windowRect;
	GetWindowRect(wndHandle, &windowRect);

	xPos = windowRect.left;
	return xPos;
}

int AppWindow::GetY()
{
	if (!wndHandle)
		return -1;

	RECT windowRect;
	GetWindowRect(wndHandle, &windowRect);

	yPos = windowRect.top;
	return yPos;
}

void* AppWindow::GetWindowHandle()
{
	return wndHandle;
}

bool AppWindow::IsFullscreen()
{
	int xMax = GetSystemMetrics(SM_CXSCREEN);
	int yMax = GetSystemMetrics(SM_CYSCREEN);
	
	if (GetWidth() >= xMax && GetHeight() >= yMax)
		return true;
	else
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