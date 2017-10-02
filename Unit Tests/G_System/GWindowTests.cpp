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
	CHECK(G_FAIL(unopenedWindow->ReconfigureWindow(250, 500, 1000, 1000, WINDOWEDBORDERED)));

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->ReconfigureWindow(250, 500, 1000, 1000, WINDOWEDBORDERED)));
}

TEST_CASE("Moving Window.", "[MoveWindow]")
{
	// Fail cases
	CHECK(G_FAIL(unopenedWindow->MoveWindow(42, 42)));

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->MoveWindow(42, 42)));
}

TEST_CASE("Resizing Window.", "[ResizeWindow]")
{
	// Fail cases
	CHECK(G_FAIL(unopenedWindow->ResizeWindow(300, 300)));
	CHECK(G_FAIL(unopenedWindow->Maximize()));
	CHECK(G_FAIL(unopenedWindow->Minimize()));

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->ResizeWindow(300, 300)));
	REQUIRE(G_SUCCESS(appWindow->Maximize()));
	REQUIRE(G_SUCCESS(appWindow->Minimize()));
}

TEST_CASE("Changing Window style.", "[ChangeWindowStyle]")
{
	// Fail case
	CHECK(G_FAIL(unopenedWindow->ChangeWindowStyle(FULLSCREENBORDERED)));

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

#ifdef _WIN32
	std::atomic<HWND>* appWindowHandle = new std::atomic<HWND>();
	std::atomic<HWND>* unopenedWindowHandle = new std::atomic<HWND>();
	unsigned int windowHandleSize = sizeof(HWND);
#elif __linux__
	LINUX_WINDOW* l_appWindow;
	LINUX_WINDOW* l_unopenedWindow*;
	unsigned int l_windowSize = sizeof(LINUX_WINDOW);
#elif __APPLE__
	NSWindow* m_appWindow;
	NSWindow* m_unopenedWindow;
	unsigned int m_windowSize = sizeof(NSWindow*);
#endif

	appWindow->IsFullscreen(appWindowIsFullscreen);

	// Fail cases
	CHECK(G_FAIL(appWindow->GetWidth(appWindowWidth) == INVALID_ARGUMENT));
	CHECK(G_FAIL(unopenedWindow->GetHeight(unopenedWindowHeight)));
	CHECK(G_FAIL(unopenedWindow->GetWidth(unopenedWindowWidth)));
	CHECK(G_FAIL(unopenedWindow->GetX(unopenedWindowPosX)));
	CHECK(G_FAIL(unopenedWindow->GetY(unopenedWindowPosY)));

#ifdef _WIN32
	CHECK(G_FAIL(unopenedWindow->GetWindowHandle(unopenedWindowHandle, windowHandleSize)));
#elif __linux__
	CHECK(G_FAIL(unopenedWindow->GetWindowHandle(l_unopenedWindow, l_windowSize)));
#elif __APPLE__
	CHECK(G_FAIL(unopenedWindow->GetWindowHandle(m_unopenedWindow, m_windowSize)));
#endif

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

#ifdef _WIN32
	REQUIRE(G_SUCCESS(appWindow->GetWindowHandle(appWindowHandle, windowHandleSize)));
	delete appWindowHandle;
	delete unopenedWindowHandle;
#elif __linux__
	REQUIRE(G_SUCCESS(appWindow->GetWindowHandle(l_appWindow, l_windowSize)));
	delete l_appWindow;
	delete l_unopenedWindow;
#elif __APPLE__
	REQUIRE(G_SUCCESS(appWindow->GetWindowHandle(m_appWindow, m_windowSize)));
	delete m_appWindow;
	delete m_unopenedWindow;
#endif


}

TEST_CASE("Querying Client Information.", "[GetClientWidth], [GetClientHeight], [GetClientTopLeft]")
{
	unsigned int appWindowClientWidth = 0;
	unsigned int appWindowClientHeight = 0;
	unsigned int appWindowClientPosX = 0;
	unsigned int appWindowClientPosY = 0;

	unsigned int unopenedWindowClientWidth = 0;
	unsigned int unopenedWindowClientHeight = 0;
	unsigned int unopenedWindowClientPosX = 0;
	unsigned int unopenedWindowClientPosY = 0;

	// Fail Cases
	CHECK(G_FAIL(unopenedWindow->GetClientWidth(unopenedWindowClientWidth)));
	CHECK(G_FAIL(unopenedWindow->GetClientHeight(unopenedWindowClientHeight)));
	CHECK(G_FAIL(unopenedWindow->GetClientTopLeft(unopenedWindowClientPosX, unopenedWindowClientPosY)));

	// Pass Cases
	REQUIRE(G_SUCCESS(appWindow->GetClientWidth(appWindowClientWidth)));
	REQUIRE(G_SUCCESS(appWindow->GetClientHeight(appWindowClientHeight)));
	REQUIRE(G_SUCCESS(appWindow->GetClientTopLeft(appWindowClientPosX, appWindowClientPosY)));
}

TEST_CASE("Sending events to listeners.", "")
{
	int windowTestValue = 0;

#ifdef _WIN32
	std::atomic<HWND> appWindowHandle;
	unsigned int windowHandleSize = sizeof(HWND);
#elif __linux__
	LINUX_WINDOW l_appWindow;
	unsigned int l_windowSize = sizeof(LINUX_WINDOW);
#elif __APPLE__ 
	NSWindow* m_appWindow;
	unsigned int m_windowSize = sizeof(NSWindow*);
#endif

	// Fail case
	windowListener->GetWindowTestValue(windowTestValue);
	CHECK(windowTestValue == 1);

#ifdef _WIN32
	// Tell window to maximize
	(HWND)appWindow->GetWindowHandle(&appWindowHandle, windowHandleSize);
	ShowWindowAsync(appWindowHandle, SW_SHOWMAXIMIZED);
#elif __linux__
	(LINUX_WINDOW)appWindow->GetWindowHandle(&l_appWindow, l_windowSize);
	ShowWindowAsync(l_appWindow, SW_SHOWMAXIMIZED);
#elif __APPLE__
	(NSWindow)appWindow->GetWindowHandle(&m_appWindow, m_windowSize);
	ShowWindowAsync(m_appWindow, SW_SHOWMAXIMIZED);
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
