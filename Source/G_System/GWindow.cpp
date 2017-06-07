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
	int testInt;
}

#include "../../Source/G_System/GWindow_Callback.hpp"
#include <atomic>
#include <mutex>
#include <string.h>

class AppWindow : public GWindow
{
private:

#ifdef _WIN32
	std::atomic<HWND> wndHandle;
#elif __linux__
	Display * display;
	Window window;
#endif

	std::atomic<unsigned int> refCount;

	std::atomic<int> xPos;
	std::atomic<int> yPos;
	std::atomic<int> width;
	std::atomic<int> height;

	GWindowStyle style;

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

AppWindow::AppWindow() : refCount(1), xPos(0), yPos(0), width(0), height(0), style(FULLSCREENBORDERED)
{
#ifdef _WIN32
	ZeroMemory(&wndHandle, sizeof(HWND));
#elif __linux__
	display = nullptr;
	memset(&window, 0, sizeof(window));
#endif // __WIN32
}

AppWindow::~AppWindow()
{

}

GReturn AppWindow::OpenWindow()
{
#ifdef _WIN32
	if (wndHandle)
		return REDUNDANT_OPERATION;

	WNDCLASSEX winClass;
	ZeroMemory(&winClass, sizeof(WNDCLASSEX));

	LPCWSTR appName = L"GWindow Application";

	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	winClass.hCursor = LoadCursorW(NULL, IDC_CROSS);
	winClass.hIcon = LoadIconW(0, IDI_EXCLAMATION);
	winClass.lpfnWndProc = GWindowProc;
	winClass.lpszClassName = appName;
	winClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClass.hInstance = GetModuleHandleW(0);

	if (!RegisterClassExW(&winClass))
	{
		printf("RegisterClassExW Error : %d \n", GetLastError());
	}

	DWORD windowsStyle;

	if (style == WINDOWEDBORDERED || style == FULLSCREENBORDERED)
	{
		windowsStyle = WS_OVERLAPPEDWINDOW;
	}

	else if (style == WINDOWEDBORDERLESS || style == FULLSCREENBORDERLESS)
	{
		windowsStyle = WS_POPUP;
	}

	else if (style == MINIMIZED)
	{
		windowsStyle = WS_MINIMIZE;
	}
	//Create the window
	wndHandle = CreateWindowW(appName, L"Win32Window", windowsStyle, xPos, yPos,
		xPos + width, yPos + height, NULL, NULL, GetModuleHandleW(0), 0);

	if (wndHandle && style != MINIMIZED)
	{
		if (ShowWindow(wndHandle, SW_SHOWDEFAULT) != 0)
		{
			printf("ShowWindow Error Message : %d \n", GetLastError());
			return FAILURE;
		}
		else
		{
			return SUCCESS;
		}

	}

	else if (wndHandle && style == MINIMIZED)
	{
		ShowWindow(wndHandle, SW_MINIMIZE);
		return SUCCESS;
	}
	else
		return FAILURE;

#elif __linux__
	if (window)
		return REDUNDANT_OPERATION;

	typedef struct
	{
		unsigned long flags;
		unsigned long functions;
		unsigned long decorations;
		long inputMode;
		unsigned long status;

	} Hints;

	XSetWindowAttributes attributes;
	Atom property;
	unsigned long valueMask = 0;
	XSizeHints rect;
	Hints hint;
	display = XOpenDisplay(NULL);
	int screen = DefaultScreen(display);
	int depth = DefaultDepth(display, 0);

	attributes.background_pixel = XWhitePixel(display, 0);
	attributes.border_pixel = XBlackPixel(display, 0);
	//attributes.event_mask = KeyPressMask | StructureNotifyMask;
	valueMask |= CWBackPixel;
	valueMask |= CWBorderWidth;
	valueMask |= CWEventMask;

	// set rect hints
	rect.flags = PSize | PPosition;

	window = XCreateWindow(display, XRootWindow(display, screen), xPos, yPos, width, height, 10,
		depth, CopyFromParent, CopyFromParent, valueMask, &attributes);

	printf("error");
	if (!window)
		return FAILURE;

	XStoreName(display, window, "BasicWindowApp");
	/*
	if(style == WINDOWEDBORDERLESS || style == FULLSCREENBORDERLESS)
	{
	hint.flags = 2;
	hint.decorations = 0;

	property = XInternAtom(display, "_MOTIF_WM_HINTS", 0);
	XChangeProperty(display,window,property,property,32,PropModeReplace,(unsigned char *)&hint,5);
	}
	*/
	XSetWMNormalHints(display, window, &rect);

	XMapWindow(display, window)

		return SUCCESS;

#endif

}

GReturn AppWindow::ReconfigureWindow(int _x, int _y, int _width, int _height, GWindowStyle _style)
{
#ifdef _WIN32
	if (!wndHandle)
		return REDUNDANT_OPERATION;
#elif __linux__

#endif
	GWindowStyle previousStyle = style;

	GReturn Gret = InitWindow(_x, _y, _width, _height, _style);
	if (Gret != SUCCESS)
		return Gret;

	switch (style)
	{
	case WINDOWEDBORDERED:
	{
#ifdef _WIN32
		SetWindowLongPtr(wndHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		BOOL winRet = SetWindowPos(wndHandle, nullptr, xPos, yPos, width, height, SWP_SHOWWINDOW);
		if (winRet == 0)
		{
			printf("SetWindowPos Error : %d \n", GetLastError());
			return FAILURE;
		}

		if (previousStyle == MINIMIZED)
			ShowWindow(wndHandle, SW_RESTORE);
		else
			ShowWindow(wndHandle, SW_SHOW);

		return SUCCESS;
#elif __linux__

#endif // __linux__
	}
	break;

	case WINDOWEDBORDERLESS:
	{
#ifdef _WIN32
		SetWindowLongPtr(wndHandle, GWL_STYLE, WS_POPUP);
		BOOL winRet = SetWindowPos(wndHandle, nullptr, xPos, yPos, width, height, SWP_SHOWWINDOW);
		if (winRet == 0)
		{
			printf("SetWindowPos Error : %d \n", GetLastError());
			return FAILURE;
		}


		if (previousStyle == MINIMIZED)
			ShowWindow(wndHandle, SW_RESTORE);
		else
			ShowWindow(wndHandle, SW_SHOW);

		return SUCCESS;

#elif __linux__

#endif // __linux__
	}
	break;

	case FULLSCREENBORDERED:
	{
#ifdef _WIN32
		RECT windowRect;
		GetWindowRect(wndHandle, &windowRect);

		SetWindowLongPtr(wndHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		BOOL winRet = SetWindowPos(wndHandle, nullptr, windowRect.left, windowRect.top, windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top, SWP_NOREDRAW);
		if (winRet == 0)
			return FAILURE;


		if (previousStyle == MINIMIZED)
			ShowWindow(wndHandle, SW_RESTORE);
		else
			ShowWindow(wndHandle, SW_MAXIMIZE);

		return SUCCESS;

#elif __linux__

#endif // __linux__
	}
	break;

	case FULLSCREENBORDERLESS:
	{
#ifdef _WIN32
		RECT windowRect;
		GetWindowRect(wndHandle, &windowRect);

		SetWindowLongPtr(wndHandle, GWL_STYLE, WS_POPUP);
		BOOL winRet = SetWindowPos(wndHandle, nullptr, windowRect.left, windowRect.top, windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top, SWP_NOREDRAW);
		if (winRet == 0)
			return FAILURE;

		if (previousStyle == MINIMIZED)
			ShowWindow(wndHandle, SW_RESTORE);
		else
			ShowWindow(wndHandle, SW_MAXIMIZE);

		return SUCCESS;
#elif __linux__

#endif // __linux__
	}
	break;

	case MINIMIZED:
	{
#ifdef _WIN32
		ShowWindow(wndHandle, SW_MINIMIZE);

		RECT windowRect = { xPos, yPos, width, height };
		GetWindowRect(wndHandle, &windowRect);

		return SUCCESS;
#elif __linux__

#endif // __linux__

	}
	break;
	}

	return SUCCESS;
}

GReturn AppWindow::InitWindow(int _x, int _y, int _width, int _height, GWindowStyle _style)
{
	if (_style < 0 || _style > 4)
		return INVALID_ARGUMENT;

	else
	{
		width = _width;
		height = _height;
		xPos = _x;
		yPos = _y;
		style = _style;
	}

	//display = nullptr;
	return SUCCESS;
}

GReturn AppWindow::MoveWindow(int _x, int _y)
{
#ifdef _WIN32
	if (!wndHandle)
		return REDUNDANT_OPERATION;
#elif __linux__
	if (!display)
		return REDUNDANT_OPERATION;

#endif // __linux__

	GReturn Gret = InitWindow(_x, _y, width, height, style);
	if (Gret != SUCCESS)
		return Gret;

#ifdef _WIN32
	BOOL Winret = SetWindowPos(wndHandle, nullptr, xPos, yPos, width, height, SWP_SHOWWINDOW);
	if (Winret == 0)
		return FAILURE;
	else
		return SUCCESS;
#elif __linux__
	if (XMoveWindow(display, window, xPos, yPos))
		return SUCCESS;
	else
		return FAILURE;
#endif // __linux__

}

GReturn AppWindow::ResizeWindow(int _width, int _height)
{
#ifdef _WIN32
	if (!wndHandle)
		return REDUNDANT_OPERATION;
#elif __linux__
	if (!display)
		return REDUNDANT_OPERATION;
#endif // __linux__

	GReturn Gret = InitWindow(xPos, yPos, _width, _height, style);
	if (Gret != SUCCESS)
		return Gret;

#ifdef _WIN32
	BOOL Winret = SetWindowPos(wndHandle, nullptr, xPos, yPos, width, height, SWP_SHOWWINDOW);
	if (Winret == 0)
		return FAILURE;
	else
		return SUCCESS;
#elif __linux__
	if (XResizeWindow(display, window, width, height))
		return SUCCESS;
	else
		return FAILURE;
#endif // __linux__

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
#ifdef _WIN32
	if (!wndHandle)
		return -1;

	RECT windowRect;
	GetWindowRect(wndHandle, &windowRect);

	width = windowRect.right - windowRect.left;
#elif __linux__
	width = XDisplayWidth(display, DefaultScreen(display));
#endif // __linux__
	return width;
}

int AppWindow::GetHeight()
{
#ifdef _WIN32
	if (!wndHandle)
		return -1;

	RECT windowRect;
	GetWindowRect(wndHandle, &windowRect);

	height = windowRect.bottom - windowRect.top;
#elif __linux__
	height = XDisplayHeight(display, DefaultScreen(display));

#endif // __linux__
	return height;
}

int AppWindow::GetX()
{
#ifdef _WIN32
	if (!wndHandle)
		return -1;

	RECT windowRect;
	GetWindowRect(wndHandle, &windowRect);

	xPos = windowRect.left;
#elif __linux__
	XWindowAttributes attrib;
	Window child;
	int x, y;

	XTranslateCoordinates(display, window, XRootWindow(display, DefaultScreen(display)), 0, 0, &x, &y, &child);
	XGetWindowAttributes(display, window, &attrib);

	xPos = x - attrib.x;

#endif // __linux__
	return xPos;
}

int AppWindow::GetY()
{
#ifdef _WIN32
	if (!wndHandle)
		return -1;

	RECT windowRect;
	GetWindowRect(wndHandle, &windowRect);

	yPos = windowRect.top;
#elif __linux__
	XWindowAttributes attrib;
	Window child;
	int x, y;

	XTranslateCoordinates(display, window, XRootWindow(display, DefaultScreen(display)), 0, 0, &x, &y, &child);
	XGetWindowAttributes(display, window, &attrib);

	yPos = y - attrib.y;

#endif // __linux__
	return yPos;
}

void* AppWindow::GetWindowHandle()
{
#ifdef _WIN32
	return wndHandle;
#elif __linux__
	return display;
#endif
}

bool AppWindow::IsFullscreen()
{
	int xMax = 0;
	int yMax = 0;
	int borderHeight = 0;
	int resizeBarHeight = 0;
#ifdef _WIN32
	xMax = GetSystemMetrics(SM_CXSCREEN);
	yMax = GetSystemMetrics(SM_CYSCREEN);
	borderHeight = GetSystemMetrics(SM_CYCAPTION);
	resizeBarHeight = GetSystemMetrics(SM_CYBORDER);
#elif __linux__

#endif // __linux__

	if (GetWidth() >= xMax && (GetHeight() + borderHeight + resizeBarHeight) >= yMax)
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
	int v = 9;
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
