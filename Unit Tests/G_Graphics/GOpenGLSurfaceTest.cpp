#include "../Unit Tests/Common.h"
#include "../Interface/G_System/GKeyDefines.h"

#ifdef _WIN32

#pragma comment(lib, "OpenGL32.lib")
#include <gl\GL.h>
#include "../../Source/G_Graphics/gl3.h"

#elif __linux__

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

#elif __APPLE__
#endif


#include <iostream>

///=============================================================================
//==============================TEST CASES======================================
///=============================================================================

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES

using namespace GW;
using namespace CORE;
using namespace SYSTEM;
using namespace GRAPHICS;

// GLOBAL VARIABLES
GWindow*			gWnd_OGL;
GOpenGLSurface*		oglSurface;

#ifdef _WIN32

HDC*				hdc;
HGLRC*				context;

#elif __linux__

    Display*                dsp;
    Window                  wnd;
    GLXContext              OGLcontext;
    LINUX_WINDOW*           lWnd;

#elif __APPLE__
#endif


TEST_CASE("Create GOpenGLESSurface Object.", "[GOpenGLESSurface]")
{
	REQUIRE(G_SUCCESS(CreateGWindow(0, 0, 800, 500, WINDOWEDBORDERED, &gWnd_OGL)));

	CHECK(CreateGOpenGLSurface(gWnd_OGL, &oglSurface) == SUCCESS);
}

TEST_CASE("Querying OGLSurface Information.", "[GetContext], [GetDeviceContextHandle]")
{

#ifdef _WIN32

	std::cout << "\n" << "OPENGL INFORMATION" << "\n\n";
	std::cout << "OPENGL VERSION: " << (char*)glGetString(GL_VERSION) << std::endl;
	std::cout << "OPENGL RENDERER: " << (char*)glGetString(GL_RENDERER) << std::endl;

	CHECK(oglSurface->GetContext((void**)&context) == SUCCESS);

#elif __linux__

	CHECK(oglSurface->GetContext((void**)&OGLcontext) == SUCCESS);

#elif __APPLE__
#endif
}

TEST_CASE("Testing OGLSurface Events")
{

	unsigned int clientX, clientY, width, height;
	gWnd_OGL->GetClientTopLeft(clientX, clientY);
	gWnd_OGL->GetWidth(width);
	gWnd_OGL->GetHeight(height);

#ifdef _WIN32

    // Test OGL Functions with current settings.
    glViewport(clientX, clientY, width, height);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	oglSurface->UniversalSwapBuffers();

#elif __linux__

    // Test OGL Functions with current settings.
    glViewport(clientX, clientY, width, height);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	oglSurface->UniversalSwapBuffers();

#elif __APPLE__
#endif

	// Manipulate GWindow and Retest OGL Functions.
	gWnd_OGL->ResizeWindow(1500, 1000);

#ifdef _WIN32

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	oglSurface->UniversalSwapBuffers();

#elif __linux__

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	oglSurface->UniversalSwapBuffers();

#elif __APPLE__
#endif

}
