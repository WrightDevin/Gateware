#include "Common.h"
//#include "GWindowTestListener.h"
#include "GWindowTestListener.h"
///=============================================================================
//==============================TEST CASES======================================
///=============================================================================

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES.
using namespace GW;
using namespace SYSTEM;
using namespace CORE;

// Global variables needed for all Test Cases.
GWindow* appWindow = nullptr; // Our window object.
GWindow* unopenedWindow = nullptr; // Window object that doesn't get opened to test for redundant operations.
GWindowTestListener* windowListener = nullptr; // Our listener object.

TEST_CASE("Create GWindow object.", "[CreateGWindow]")
{
	// Fail cases
	CHECK(CreateGWindow(100, 100, 500, 500, WINDOWEDBORDERED, nullptr) == INVALID_ARGUMENT);

	
	// Pass cases
	REQUIRE(G_SUCCESS(CreateGWindow(0, 0, 800, 500, WINDOWEDBORDERED, &appWindow)));
	REQUIRE(G_SUCCESS(CreateGWindow(1100, 1100, 200, 200, WINDOWEDBORDERED, &unopenedWindow)));
	REQUIRE(appWindow != nullptr);
	REQUIRE(unopenedWindow != nullptr);
}

TEST_CASE("Open a Window.", "[OpenWindow]")
{
	// Pass case
	REQUIRE(G_SUCCESS(appWindow->OpenWindow()));

	// Fail case
	REQUIRE(appWindow->OpenWindow() == REDUNDANT_OPERATION);
}

TEST_CASE("GWindow Register Listeners.", "[RegisterListener]")
{
	// Create our new test listener
	windowListener = new GWindowTestListener();

	// Fail case
	CHECK(appWindow->RegisterListener(nullptr, 0) == GW::INVALID_ARGUMENT);

	// Pass case
	REQUIRE(G_SUCCESS(appWindow->RegisterListener(windowListener, 0)));
}

TEST_CASE("Reconfigure the open Window.", "[ReconfigureWindow]")
{
	// Fail cases
	CHECK(appWindow->ReconfigureWindow(-1, -1, -1, -1, (GWindowStyle)20) == INVALID_ARGUMENT);
	CHECK(unopenedWindow->ReconfigureWindow(250, 500, 1000, 1000, WINDOWEDBORDERED) == FAILURE);

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->ReconfigureWindow(250, 500, 1000, 1000, WINDOWEDBORDERED)));
}

TEST_CASE("Moving Window.", "[MoveWindow]")
{
	// Fail cases
	CHECK(unopenedWindow->MoveWindow(42, 42) == FAILURE);

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->MoveWindow(42, 42)));
}

TEST_CASE("Resizing Window.", "[ResizeWindow]")
{
	// Fail cases
	CHECK(unopenedWindow->ResizeWindow(300, 300) == FAILURE);
	CHECK(unopenedWindow->Maximize() == FAILURE);
	CHECK(unopenedWindow->Minimize() == FAILURE);

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->ResizeWindow(300, 300)));
	REQUIRE(G_SUCCESS(appWindow->Maximize()));
	REQUIRE(G_SUCCESS(appWindow->Minimize()));
}

TEST_CASE("Changing Window style.", "[ChangeWindowStyle]")
{
	// Fail case
	CHECK(unopenedWindow->ChangeWindowStyle(FULLSCREENBORDERED) == FAILURE);

	// Pass case
	REQUIRE(G_SUCCESS(appWindow->ChangeWindowStyle(WINDOWEDBORDERED)));
}

TEST_CASE("Querying Window information.", "[GetWidth], [GetHeight], [GetX], [GetY]")
{
	// Set window parameters for query tests
	REQUIRE(G_SUCCESS(appWindow->ReconfigureWindow(250, 500, 500, 500, WINDOWEDBORDERED)));
	bool appWindowIsFullscreen = false;
	bool unopenedWindowIsFullscreen = false;
	unsigned int appWindowHeight = 0;
	unsigned int appWindowWidth = 0;
	unsigned int appWindowPosX = 0;
	unsigned int appWindowPosY = 0;
	unsigned int unopenedWindowHeight = 0;
	unsigned int unopenedWindowWidth = 0;
	unsigned int unopenedWindowPosX = 0;
	unsigned int unopenedWindowPosY = 0;
	std::atomic<HWND> appWindowHandle;
	std::atomic<HWND> unopenedWindowHandle;

	appWindow->IsFullscreen(appWindowIsFullscreen);

	// Fail cases
	CHECK(G_FAIL(appWindow->GetWidth(appWindowWidth) == FAILURE));
	CHECK(unopenedWindow->GetHeight(unopenedWindowHeight) == FAILURE);
	CHECK(unopenedWindow->GetWidth(unopenedWindowWidth) == FAILURE);
	CHECK(unopenedWindow->GetX(unopenedWindowPosX) == FAILURE);
	CHECK(unopenedWindow->GetY(unopenedWindowPosY) == FAILURE);
	CHECK(unopenedWindow->GetWindowHandle(unopenedWindowHandle, sizeof(unopenedWindowHandle)) == FAILURE);
	CHECK(G_FAIL(appWindowIsFullscreen == true));
	

	// Resize windows for pass tests
	REQUIRE(G_SUCCESS(appWindow->ReconfigureWindow(0, 0, 1920, 1080, FULLSCREENBORDERED)));
	appWindow->IsFullscreen(appWindowIsFullscreen);

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->GetHeight(appWindowHeight)));
	REQUIRE(G_SUCCESS(appWindow->GetWidth(appWindowWidth)));  
	REQUIRE(G_SUCCESS(appWindow->GetX(appWindowPosX)));	
	REQUIRE(G_SUCCESS(appWindow->GetY(appWindowPosY)));	
	REQUIRE(appWindowIsFullscreen == true);
	REQUIRE(G_SUCCESS(appWindow->GetWindowHandle(appWindowHandle,sizeof(appWindowHandle))));
}

TEST_CASE("Sending events to listeners.", "")
{
	int windowTestValue = 0;
	std::atomic<HWND> appWindowHandle;

	// Fail case
	windowListener->GetWindowTestValue(windowTestValue);
	CHECK(windowTestValue == 1);

#ifdef _WIN32
	// Tell window to maximize
	(HWND)appWindow->GetWindowHandle(appWindowHandle,sizeof(appWindowHandle));
	ShowWindowAsync(appWindowHandle, SW_SHOWMAXIMIZED);
#endif

	// Pass case
	windowListener->GetWindowTestValue(windowTestValue);
	REQUIRE(windowTestValue == 1);
}

TEST_CASE("GWindow Unregistering listener", "[DeregisterListener]")
{
	unsigned int refCount = 0;

	// Fail case
	CHECK(appWindow->DeregisterListener(nullptr) == GW::INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->DeregisterListener(windowListener)));
	windowListener->GetCount(refCount);

	CHECK(refCount == 1);

	windowListener->DecrementCount();
	appWindow->DecrementCount();
}
