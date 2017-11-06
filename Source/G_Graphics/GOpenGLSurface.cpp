#include "../DLL_Export_Symbols.h"
#include "../../Interface/G_Graphics/GOpenGLSurface.h"
#include "../../Interface/G_System/GKeyDefines.h"
#include "../../Source/G_System/GUtility.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32

#include <Windows.h>
#pragma comment(lib, "OpenGL32.lib")
#include <gl\GL.h>
#include <atomic>
#include <mutex>
#include <thread>

#elif __linux__

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

#elif __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#endif

using namespace GW;
using namespace CORE;
using namespace SYSTEM;
using namespace GRAPHICS;

class GOpenGL : public GOpenGLSurface
{
private:
	// declare all necessary members (platform specific)
	unsigned int	refCount;

	GWindow*		gWnd;
	unsigned int	clientX;
	unsigned int	clientY;
	float			width;
	float			height;
	float			aspectRatio;

#ifdef _WIN32

	HWND surfaceWindow;
    HDC				hdc;
	HGLRC			OGLcontext;

#elif __linux__

    Window                  root;
    GLint                   attributes[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
    XVisualInfo*            vi;
    Colormap                cmap;
    XSetWindowAttributes    swa;
    GLXContext              OGLXcontext;
    XWindowAttributes       gwa;
    XEvent                  event;
    LINUX_WINDOW            lWnd;

#elif __APPLE__
    
    NSOpenGLContext* OGLMcontext;
    NSWindow* nsWnd;
    
#endif

public:
	GOpenGL();
	virtual ~GOpenGL();
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

GOpenGL::GOpenGL()
{
#ifdef _WIN32

	ZeroMemory(&surfaceWindow, sizeof(HWND));

#elif __linux__
#elif __APPLE__
#endif
}

GOpenGL::~GOpenGL()
{
	gWnd->DeregisterListener(this);
	DecrementCount();

	#ifdef _WIN32
	#elif __linux__

	glXMakeCurrent((Display*)lWnd.display, None, NULL);
	glXDestroyContext((Display*)lWnd.display, OGLXcontext);
	XDestroyWindow((Display*)lWnd.display, *(Window*)lWnd.window);
	XCloseDisplay((Display*)lWnd.display);

	#elif __APPLE__
	#endif

}

void GOpenGL::SetGWindow(GWindow* _window)
{
	gWnd = _window;
}

GReturn GOpenGL::Initialize()
{

    gWnd->OpenWindow();

#ifdef _WIN32

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

gWnd->GetWindowHandle(&lWnd, sizeof(LINUX_WINDOW));
lWnd.window = (void*)DefaultRootWindow((Display*)lWnd.display);
root = RootWindow((Display*)lWnd.display, DefaultScreen((Display*)lWnd.display));
vi = glXChooseVisual((Display*)lWnd.display, DefaultScreen((Display*)lWnd.display), attributes);
cmap = XCreateColormap((Display*)lWnd.display, root, vi->visual, AllocNone);
OGLXcontext = glXCreateContext((Display*)lWnd.display, vi, NULL, GL_TRUE);

int ret = glXMakeCurrent((Display*)lWnd.display, root, OGLXcontext);
XGetWindowAttributes((Display*)lWnd.display, root, &gwa);
glViewport(0, 0, gwa.width, gwa.height);

#elif __APPLE__
    
    gWnd->GetWindowHandle(nsWnd, sizeof(NSWindow*));
    
    NSOpenGLPixelFormatAttribute pixelAttributes[] =
    {
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAStencilSize, 8,
        NSOpenGLPFASampleBuffers, 0,
        0,
    };
    
    NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelAttributes];
    
    assert(pixelFormat);
    
    OGLMcontext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:NULL];
    assert(OGLMcontext);
    
    [OGLMcontext makeCurrentContext];
    //[OGLMcontext setView:nsWnd.contentView];
    //[nsWnd.contentView display];
    
    unsigned int temp_mWidth;
    unsigned int temp_mHeight;
    gWnd->GetWidth(temp_mWidth);
    gWnd->GetHeight(temp_mHeight);
    glViewport(0, 0, temp_mWidth, temp_mHeight);
    
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    
    
    
#endif

	return SUCCESS;
}

GReturn GOpenGL::GetContext(void ** _outContext)
{
#ifdef _WIN32

	*_outContext = OGLcontext;

#elif __linux__

    *_outContext = OGLXcontext;

#elif __APPLE__
    
    *_outContext = OGLMcontext;
    
#endif

	return SUCCESS;
}

GReturn GOpenGL::GetDeviceContextHandle(void** _outHDC)
{
#ifdef _WIN32

	*_outHDC = &hdc;

#elif __linux__

    *_outHDC = &lWnd;

#elif __APPLE__
#endif

	return SUCCESS;
}

float GOpenGL::GetAspectRatio()
{
	return aspectRatio;
}

GReturn GOpenGL::GetCount(unsigned int& _outCount)
{
	_outCount = refCount;

	return SUCCESS;
}

GReturn GOpenGL::IncrementCount()
{
	if (refCount == G_UINT_MAX)
		return FAILURE;

	++refCount;

	return SUCCESS;
}

GReturn GOpenGL::DecrementCount()
{
	if (refCount == 0)
	{
		delete this;
		return FAILURE;
	}

	--refCount;

	return SUCCESS;
}

GReturn GOpenGL::RequestInterface(const GUUIID & _interfaceID, void ** _outputInterface)
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
	else if (_interfaceID == GOpenGLSurfaceUUIID)
	{
		GOpenGLSurface* convert = reinterpret_cast<GOpenGLSurface*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else
		return INTERFACE_UNSUPPORTED;

	return SUCCESS;
}

GReturn GOpenGL::OnEvent(const GUUIID & _senderInterface, unsigned int _eventID, void * _eventData, unsigned int _dataSize)
{

	if (_senderInterface == GWindowUUIID)
	{

		GWINDOW_EVENT_DATA* eventStruct = (GWINDOW_EVENT_DATA*)_eventData;
        
#ifdef _WIN32
        
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
                this->~GOpenGL();
            }
                break;
        }
        
#elif __linux__
        
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
                this->~GOpenGL();
            }
                break;
        }
        
#elif __APPLE__
#endif

	}

	return SUCCESS;
}

GATEWARE_EXPORT_EXPLICIT GReturn CreateGOpenGLSurface(SYSTEM::GWindow* _gWin, GOpenGLSurface** _outSurface)
{
	return GW::GRAPHICS::CreateGOpenGLSurface(_gWin, _outSurface);
}

GReturn GW::GRAPHICS::CreateGOpenGLSurface(SYSTEM::GWindow* _gWin, GOpenGLSurface** _outSurface)
{
	if (_outSurface == nullptr)
		return INVALID_ARGUMENT;

	GOpenGL* Surface = new GOpenGL();
	Surface->SetGWindow(_gWin);
	Surface->Initialize();

	_gWin->RegisterListener(Surface, 0);

	if (Surface == nullptr)
		return FAILURE;

	*_outSurface = Surface;

	return SUCCESS;
}
