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
#include "gl3.h"
#include "wgl.h"

#include <atomic>
#include <mutex>
#include <thread>

#elif __linux__

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include "glxext.h"

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

	GLint			numExtensions = 0;
	const char*		glExtensions;

#ifdef _WIN32

	HWND surfaceWindow;
    HDC				hdc;
	HGLRC			OGLcontext;

	/////////////////////////////////////////////////////////
	//				 WGL FUNCTION POINTERS				   //
	/////////////////////////////////////////////////////////
	PFNWGLGETEXTENSIONSSTRINGARBPROC	wglGetExtensionsStringARB;
	PFNWGLGETEXTENSIONSSTRINGEXTPROC	wglGetExtensionsStringEXT;
	PFNWGLCREATECONTEXTATTRIBSARBPROC	wglCreateContextAttribsARB;
	PFNWGLSWAPINTERVALEXTPROC			wglSwapIntervalEXT;


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
    NSWindow*        nsWnd;
    NSView*          view;
    
#endif

public:
	GOpenGL();
	virtual ~GOpenGL();
	GReturn Initialize();
	GReturn	GetContext(void** _outContext);
	GReturn	UniversalSwapBuffers();
	GReturn	QueryExtensionFunction(const char* _extension, const char* _funcName, void** _outFuncAddress);
	GReturn EnableSwapControl(bool& _toggle);

	void	SetGWindow(GWindow* _window);
	float	GetAspectRatio();

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
    
    nsWnd = [NSWindow alloc];
    
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
	UINT pixelCount = 0;
	SetPixelFormat(hdc, pixelFormat, &pfd);

	OGLcontext = wglCreateContext(hdc);
	wglMakeCurrent(hdc, OGLcontext);

	wglGetExtensionsStringARB =		(PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
	wglGetExtensionsStringEXT =		(PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");
	wglCreateContextAttribsARB =	(PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	wglSwapIntervalEXT =			(PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;

	QueryExtensionFunction("WGL_ARB_extensions_string", "wglChoosePixelFormatARB", (void**)&wglChoosePixelFormatARB);

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(OGLcontext);

	const int pixelAttributes[] = 
	{
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 16,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB, GL_FALSE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		0,
	};

	wglChoosePixelFormatARB(hdc, pixelAttributes, NULL, 1, &pixelFormat, &pixelCount);
	SetPixelFormat(hdc, pixelFormat, &pfd);

	// Create an OpenGL 3.0 Context
	const int contextAttributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 0,
		0
	};

	// Create an OpenGL ES 3.0 Context
	//const int contextAttributes[] =
	//{
	//	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	//	WGL_CONTEXT_MINOR_VERSION_ARB, 0,
	//	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_ES2_PROFILE_BIT_EXT,
	//	0
	//};

	OGLcontext = wglCreateContextAttribsARB(hdc, 0, contextAttributes);
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
    
    gWnd->GetWindowHandle((void**)&nsWnd, sizeof(NSWindow*));
    
    unsigned int viewWidth;
    unsigned int viewHeight;
    unsigned int viewX;
    unsigned int viewY;
    
    gWnd->GetClientWidth(viewWidth);
    gWnd->GetClientHeight(viewHeight);
    gWnd->GetX(viewX);
    gWnd->GetY(viewY);
    
    view = [NSView alloc];
    [view initWithFrame:NSMakeRect(viewX, viewY, viewWidth, viewHeight)];
    
    [nsWnd setContentView:view];
    
    NSOpenGLPixelFormatAttribute pixelAttributes[] =
    {
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAColorSize, 32,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADepthSize, 32,
        0,
    };
    
    NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelAttributes];
    
    OGLMcontext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
    [OGLMcontext makeCurrentContext];
    
    [OGLMcontext setView:view];
    
    GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    
    glViewport(viewX, viewY, viewWidth, viewHeight);
    
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    result = glGetError();
    glClear(GL_COLOR_BUFFER_BIT);
    result = glGetError();
    [OGLMcontext flushBuffer];
    
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

GReturn GOpenGL::UniversalSwapBuffers()
{
#ifdef _WIN32

	SwapBuffers(hdc);

#elif __linux__

	glXSwapBuffers((Display*)lWnd->display, (Window)lWnd->window);

#elif __APPLE__

#endif

	return SUCCESS;

}

float GOpenGL::GetAspectRatio()
{
	return aspectRatio;
}

GReturn GOpenGL::QueryExtensionFunction(const char* _extension, const char* _funcName, void** _outFuncAddress)
{

#if _WIN32

	// Invalid Arguments
	if (_funcName == nullptr && _outFuncAddress != nullptr ||
		_funcName != nullptr && _outFuncAddress == nullptr ||
		_extension == nullptr)
		return INVALID_ARGUMENT;

	// User only passed in extension name, without function
	if (_funcName == nullptr && _outFuncAddress == nullptr)
	{
		if (wglGetExtensionsStringEXT)
		{
			glExtensions = wglGetExtensionsStringEXT();

			if (strstr(glExtensions, _extension) != NULL)
				return SUCCESS;
		}

		if (wglGetExtensionsStringARB)
		{
			glExtensions = wglGetExtensionsStringARB(hdc);

			if (strstr(glExtensions, _extension) != NULL)
				return SUCCESS;
		}

		return FAILURE;
	}

	// User passed in extension name and function name
	if (wglGetExtensionsStringEXT)
	{
		glExtensions = wglGetExtensionsStringEXT();

		if (strstr(glExtensions, _extension) != NULL)
		{
			if (_funcName != NULL)
				*_outFuncAddress = wglGetProcAddress(_funcName);
			else
				*_outFuncAddress = wglGetProcAddress(_extension);

			return SUCCESS;
		}
	}

	if (wglGetExtensionsStringARB)
	{
		glExtensions = wglGetExtensionsStringARB(hdc);

		if (strstr(glExtensions, _extension) != NULL)
		{
			if (_funcName != NULL)
				_outFuncAddress = (void**)wglGetProcAddress(_funcName);
			else
				_outFuncAddress = (void**)wglGetProcAddress(_extension);

			return SUCCESS;
		}

	}

#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;

}

GReturn GOpenGL::EnableSwapControl(bool& _toggle)
{
    
#if _WIN32
    
    if (!wglSwapIntervalEXT)
        return FAILURE;
    
    if (_toggle == true)
        wglSwapIntervalEXT(1);
    else
        wglSwapIntervalEXT(0);
    
    return SUCCESS;
    
#elif __linux__
#elif __APPLE__
#endif
    
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
