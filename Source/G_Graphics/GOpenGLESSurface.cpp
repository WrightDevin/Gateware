#include "../DLL_Export_Symbols.h"
#include "../../Interface/G_Graphics/GOpenGLESSurface.h"
#include "../../Source/G_System/GUtility.h"


#ifdef _WIN32

#include <Windows.h>

#pragma comment(lib, "OpenGL32.lib")
#include <gl\GL.h>

#include <atomic>
#include <mutex>
#include <thread>

#elif __linux__
#elif __APPLE__
#endif

using namespace GW;
using namespace CORE;
using namespace SYSTEM;
using namespace GRAPHICS;

class GOpenGLES : public GOpenGLESSurface
{
private:
	// declare all necessary members (platform specific)
	unsigned int	refCount;

	GWindow*		gWnd;
	HDC				hdc;
	HGLRC			OGLcontext;
	unsigned int	clientX;
	unsigned int	clientY;
	float			width;
	float			height;
	float			aspectRatio;

#ifdef _WIN32

	HWND surfaceWindow;

#elif __linux__
#elif __APPLE__
#endif
	
public:
	GOpenGLES();
	virtual ~GOpenGLES();
	GReturn Initialize();
	GReturn GetContext(void** _outContext);
	GReturn GetDeviceContextHandle(void** _outHDC);
	float GetAspectRatio();

	void	SetGWindow(GWindow* _window);
	GReturn GetCount(unsigned int& _outCount);
	GReturn IncrementCount();
	GReturn DecrementCount();
	GReturn RequestInterface(const GUUIID& _interfaceID, void** _outputInterface);
	GReturn OnEvent(const GUUIID& _senderInterface, unsigned int _eventID, void* _eventData, unsigned int _dataSize);
};

GOpenGLES::GOpenGLES()
{
#ifdef _WIN32

	ZeroMemory(&surfaceWindow, sizeof(HWND));

#elif __linux__
#elif __APPLE__
#endif
}

GOpenGLES::~GOpenGLES()
{
	gWnd->DeregisterListener(this);
	DecrementCount();
}

void GOpenGLES::SetGWindow(GWindow* _window)
{
	gWnd = _window;
}

GReturn GOpenGLES::Initialize()
{
#ifdef _WIN32

	gWnd->OpenWindow();
	gWnd->GetWindowHandle(&surfaceWindow, sizeof(HWND));
	RECT windowRect;
	GetWindowRect(surfaceWindow, &windowRect);
	width = windowRect.right - windowRect.left;
	height = windowRect.bottom - windowRect.top;
	aspectRatio = width / height;

	hdc = GetDC(surfaceWindow);

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);

	OGLcontext = wglCreateContext(hdc);
	wglMakeCurrent(hdc, OGLcontext);

#elif __linux__
#elif __APPLE__
#endif

	return SUCCESS;
}

GReturn GOpenGLES::GetContext(void ** _outContext)
{
#ifdef _WIN32

	*_outContext = OGLcontext;

#elif __linux__
#elif __APPLE__
#endif

	return SUCCESS;
}

GReturn GOpenGLES::GetDeviceContextHandle(void** _outHDC)
{
#ifdef _WIN32

	*_outHDC = &hdc;

#elif __linux__
#elif __APPLE__
#endif

	return SUCCESS;
}

float GOpenGLES::GetAspectRatio()
{
	return aspectRatio;
}

GReturn GOpenGLES::GetCount(unsigned int& _outCount)
{
	_outCount = refCount;

	return SUCCESS;
}

GReturn GOpenGLES::IncrementCount()
{
	if (refCount == G_UINT_MAX)
		return FAILURE;

	++refCount;

	return SUCCESS;
}

GReturn GOpenGLES::DecrementCount()
{
	if (refCount == 0)
	{
		delete this;
		return FAILURE;
	}

	--refCount;

	return SUCCESS;
}

GReturn GOpenGLES::RequestInterface(const GUUIID & _interfaceID, void ** _outputInterface)
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
	else if (_interfaceID == GOpenGLESSurfaceUUIID)
	{
		GOpenGLESSurface* convert = reinterpret_cast<GOpenGLESSurface*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else
		return INTERFACE_UNSUPPORTED;

	return SUCCESS;
}

GReturn GOpenGLES::OnEvent(const GUUIID & _senderInterface, unsigned int _eventID, void * _eventData, unsigned int _dataSize)
{

	if (_senderInterface == GWindowUUIID)
	{

		GWINDOW_EVENT_DATA* eventStruct = (GWINDOW_EVENT_DATA*)_eventData;

		switch (_eventID)
		{
		case GW::SYSTEM::NOTIFY:
			break;
		case GW::SYSTEM::MINIMIZE:
			break;
		case GW::SYSTEM::MAXIMIZE:
		{
			unsigned int maxWidth;
			unsigned int maxHeight;
			unsigned int currX;
			unsigned int currY;

			gWnd->GetWidth(maxWidth);
			gWnd->GetHeight(maxHeight);

			aspectRatio = maxWidth / maxHeight;

			glViewport(0, 0, maxWidth, maxHeight);
		}
			break;
		case GW::SYSTEM::RESIZE:
		{
			unsigned int maxWidth;
			unsigned int maxHeight;
			unsigned int currX;
			unsigned int currY;

			gWnd->GetWidth(maxWidth);
			gWnd->GetHeight(maxHeight);
			gWnd->GetClientTopLeft(currX, currY);

			aspectRatio = maxWidth / maxHeight;

			glViewport(currX, currY, maxWidth, maxHeight);
		}
			break;
		case GW::SYSTEM::MOVE:
		{
			unsigned int maxWidth;
			unsigned int maxHeight;
			unsigned int currX;
			unsigned int currY;

			gWnd->GetWidth(maxWidth);
			gWnd->GetHeight(maxHeight);
			gWnd->GetClientTopLeft(currX, currY);

			glViewport(currX, currY, maxWidth, maxHeight);
		}
			break;
		case GW::SYSTEM::DESTROY:
		{
			this->~GOpenGLES();
		}
			break;

		}
	}

	return SUCCESS;
}

GATEWARE_EXPORT_EXPLICIT GReturn CreateGOpenGLESSurface(SYSTEM::GWindow* _gWin, GOpenGLESSurface** _outSurface)
{
	return GW::GRAPHICS::CreateGOpenGLESSurface(_gWin, _outSurface);
}

GReturn GW::GRAPHICS::CreateGOpenGLESSurface(SYSTEM::GWindow* _gWin, GOpenGLESSurface** _outSurface)
{
	if (_outSurface == nullptr)
		return INVALID_ARGUMENT;

	GOpenGLES* Surface = new GOpenGLES();
	Surface->SetGWindow(_gWin);
	Surface->Initialize();

	_gWin->RegisterListener(Surface, 0);

	if (Surface == nullptr)
		return FAILURE;

	*_outSurface = Surface;

	return SUCCESS;
}