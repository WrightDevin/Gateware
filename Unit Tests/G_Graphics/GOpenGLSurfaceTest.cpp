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
#include <string.h>
//#include <string>

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

	GLint red, green, blue, alpha, depth, stencil;
	glGetIntegerv(GL_RED_BITS, &red);
	glGetIntegerv(GL_GREEN_BITS, &green);
	glGetIntegerv(GL_BLUE_BITS, &blue);
	glGetIntegerv(GL_ALPHA_BITS, &alpha);
	glGetIntegerv(GL_DEPTH_BITS, &depth);
	glGetIntegerv(GL_STENCIL_BITS, &stencil);

	std::cout << "\n" << "OPENGL INFORMATION" << std::endl;
	std::cout << "OPENGL VERSION: " << (char*)glGetString(GL_VERSION) << "\n";
	//std::cout << "OPENGL RENDERER: " << (char*)glGetString(GL_RENDERER) << "\n";

	std::cout << "\n" << "OPENGL: COLOR INFORMATION" << std::endl;
	//std::cout << "\n" << "STRING TEST: " << (char*)glGetString(GL_RED_INTEGER) << std::endl;
	std::cout << "RED BITS: " << red << "\n";
	std::cout << "GREEN BITS: " << green << "\n";
	std::cout << "BLUE BITS: " << blue << "\n";
	std::cout << "ALPHA BITS: " << alpha << std::endl;

	std::cout << "\n" << "OPENGL: DEPTH INFORMATION" << std::endl;
	std::cout << "DEPTH BITS: " << depth << "\n";
	std::cout << "STENCIL BITS: " << stencil << "\n";

	CHECK(oglSurface->GetContext((void**)&context) == SUCCESS);

#elif __linux__

    printf("%s \n", "OPENGL INFORMATON");
    printf("%s %s \n", "OPENGL VERSION: ", (char*)glGetString(GL_VERSION));
    //printf("%s %s \n", "OPENGL RENDERER: ", (char*)glGetString(GL_RENDERER));


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
