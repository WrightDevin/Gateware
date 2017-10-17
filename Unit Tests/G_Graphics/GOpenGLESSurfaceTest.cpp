#include "../Unit Tests/Common.h"

#pragma comment(lib, "OpenGL32.lib")
#include <gl\GL.h>
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
GOpenGLESSurface*	oglSurface = nullptr;
HDC*				hdc;
HGLRC*				context;

TEST_CASE("Create GOpenGLESSurface Object.", "[GOpenGLESSurface]")
{
	REQUIRE(G_SUCCESS(CreateGWindow(0, 0, 500, 500, WINDOWEDBORDERED, &gWnd_OGL)));

	CHECK(CreateGOpenGLESSurface(gWnd_OGL, &oglSurface) == SUCCESS);
}

TEST_CASE("Initialize GOpenGLESSurface.", "[Initialize]")
{
	CHECK(oglSurface->Initialize() == SUCCESS);
}

TEST_CASE("Querying OGLSurface Information.", "[GetContext], [GetDeviceContextHandle]")
{

#ifdef _WIN32

	std::cout << "\n" << "OPENGL INFORMATION" << "\n\n";
	std::cout << "OPENGL VERSION: " << (char*)glGetString(GL_VERSION) << std::endl;
	std::cout << "OPENGL RENDERER: " << (char*)glGetString(GL_RENDERER) << std::endl;

#elif __linux__
#elif __APPLE__
#endif

	CHECK(oglSurface->GetContext((void**)&context) == SUCCESS);
	CHECK(oglSurface->GetDeviceContextHandle((void**)&hdc) == SUCCESS);
}

TEST_CASE("Testing OGLSurface Events")
{

	unsigned int clientX, clientY, width, height;
	gWnd_OGL->GetClientTopLeft(clientX, clientY);
	gWnd_OGL->GetWidth(width);
	gWnd_OGL->GetHeight(height);

	// Test OGL Functions with current settings.
	glViewport(clientX, clientY, width, height);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SwapBuffers(*hdc);

	// Manipulate GWindow and Retest OGL Functions.
	gWnd_OGL->ResizeWindow(1500, 1500);

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SwapBuffers(*hdc);

}