#include "../Unit Tests/Common.h"

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
GOpenGLESSurface*	oglSurface = nullptr;
HDC					hdc;
HGLRC*				context;

//TEST_CASE("Create GOpenGLESSurface Object.", "[GOpenGLESSurface]")
//{
//	REQUIRE(G_SUCCESS(CreateGWindow(100, 100, 500, 500, WINDOWEDBORDERED, &gWnd)));
//
//	CHECK(CreateGOpenGLESSurface(gWnd, &oglSurface) == SUCCESS);
//}
//
//TEST_CASE("Initialize GOpenGLESSurface.", "[Initialize]")
//{
//	CHECK(oglSurface->Initialize() == SUCCESS);
//}
//
//TEST_CASE("Querying Surface Information.", "[GetContext]")
//{
//	CHECK(oglSurface->GetContext((void**)&context) == SUCCESS);
//}