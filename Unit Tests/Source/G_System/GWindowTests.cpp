#include "Common.h"
#include "TestListener.h"

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
TestListener* windowListener = nullptr; // Our listener object.

TEST_CASE("Create GWindow object.", "[CreateGWindow]")
{
	// Fail cases
	CHECK(CreateGWindow(100, 100, 500, 500, WINDOWEDBORDERED, nullptr) == INVALID_ARGUMENT);

	// Pass cases
	REQUIRE(G_SUCCESS(CreateGWindow(0, 0, 1920, 1080, WINDOWEDBORDERED, &appWindow)));
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
	windowListener = new TestListener();

	// Fail case
	CHECK(appWindow->RegisterListener(nullptr, 0) == GW::INVALID_ARGUMENT);

	// Pass case
	REQUIRE(G_SUCCESS(appWindow->RegisterListener(windowListener, 0)));
}

TEST_CASE("Reconfigure the open Window.", "[ReconfigureWindow]")
{
	// Fail cases
	CHECK(appWindow->ReconfigureWindow(-1, -1, -1, -1, (GWindowStyle)20) == INVALID_ARGUMENT);
	CHECK(unopenedWindow->ReconfigureWindow(250, 500, 1000, 1000, WINDOWEDBORDERED) == REDUNDANT_OPERATION);

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->ReconfigureWindow(250, 500, 1000, 1000, WINDOWEDBORDERLESS)));
}

TEST_CASE("Moving Window.", "[MoveWindow]")
{
	// Fail cases
	CHECK(unopenedWindow->MoveWindow(42, 42) == REDUNDANT_OPERATION);

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->MoveWindow(42, 42)));
}

TEST_CASE("Resizing Window.", "[ResizeWindow]")
{
	// Fail cases
	CHECK(unopenedWindow->ResizeWindow(300, 300) == REDUNDANT_OPERATION);
	CHECK(unopenedWindow->Maximize() == REDUNDANT_OPERATION);
	CHECK(unopenedWindow->Minimize() == REDUNDANT_OPERATION);

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->ResizeWindow(300, 300)));
	REQUIRE(G_SUCCESS(appWindow->Maximize()));
	REQUIRE(G_SUCCESS(appWindow->Minimize()));
}

TEST_CASE("Changing Window style.", "[ChangeWindowStyle]")
{
	// Fail case
	CHECK(unopenedWindow->ChangeWindowStyle(FULLSCREENBORDERED) == REDUNDANT_OPERATION);

	// Pass case
	REQUIRE(G_SUCCESS(appWindow->ChangeWindowStyle(WINDOWEDBORDERED)));
}

TEST_CASE("Querying Window information.", "[GetWidth], [GetHeight], [GetX], [GetY]")
{
	// Set window parameters for query tests
	REQUIRE(G_SUCCESS(appWindow->ReconfigureWindow(250, 500, 1000, 1000, WINDOWEDBORDERED)));

	// Fail cases
	CHECK(G_FAIL(appWindow->GetWidth() == 0));
	CHECK(unopenedWindow->GetHeight() == -1);
	CHECK(unopenedWindow->GetWidth() == -1);
	CHECK(unopenedWindow->GetX() == -1);
	CHECK(unopenedWindow->GetY() == -1);
	CHECK(unopenedWindow->GetWindowHandle() == 0);
	CHECK(appWindow->IsFullscreen() == false);

	// Resize windows for pass tests
	REQUIRE(G_SUCCESS(appWindow->ReconfigureWindow(0, 0, 1920, 1080, FULLSCREENBORDERED)));

	// Pass cases
	REQUIRE(appWindow->GetHeight() != -1);
	REQUIRE(appWindow->GetWidth() != -1);
	REQUIRE(appWindow->GetX() != -1);
	REQUIRE(appWindow->GetY() != -1);
	REQUIRE(appWindow->IsFullscreen() == true);
	REQUIRE(appWindow->GetWindowHandle() != nullptr);
}

TEST_CASE("Sending events to listeners.", "")
{
	// Fail case
	CHECK(windowListener->GetWindowTestValue() == 1);

#ifdef _WIN32
	// Tell window to maximize
	ShowWindowAsync((HWND)appWindow->GetWindowHandle(), SW_SHOWMAXIMIZED);
#endif

	// Pass case
	REQUIRE(windowListener->GetWindowTestValue() == 1);
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
