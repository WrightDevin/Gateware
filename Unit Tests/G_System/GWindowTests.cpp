#include "../Unit Tests/Common.h"
//#include "GWindowTestListener.h"
#include "GWindowTestListener.h"
#include <iostream>

#ifdef __linux__
#include <unistd.h> //Allows for linux side "sleep()" calls
#endif
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
GWindow* tstWindow = nullptr; //Our 2nd window object.
GWindowTestListener* windowListener = nullptr; // Our listener object.

											   // ALL DEVELOPERS!!! USE THIS AS AN EXAMPLE OF HOW TO DO CORE GINTERFACE TESTING!!!
GW::SYSTEM::GWindow *GWindow_specific = nullptr;
GW::CORE::GInterface *GWindow_generic = nullptr;
// CORE GINTERFACE TEST BATTERY. ALL GATEWARE INTERFACES MUST BE ABLE TO PASS THESE TESTS.
TEST_CASE("GWindow core test battery", "[CreateGWindow], [RequestInterface], [IncrementCount], [DecrementCount], [GetCount]")
{
	// CATCH WARNING!!!
	// Any variables declared here will be REPLICATED to EACH SECTION.
	// If you need connectivity between sections your variables will need to be global or static.
	unsigned int countS = 0, countG = 0;
	const GW::GUUIID notAnValidInterface = { 0, };

	// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
	SECTION("Creation Tests", "[CreateGWindow]")
	{
		CHECK(GW::SYSTEM::CreateGWindow(100, 100, 500, 500, WINDOWEDBORDERED, nullptr) == GW::INVALID_ARGUMENT);
		// TODO: Add additonal Creation parameter testing here as nessasary.
		REQUIRE(G_SUCCESS(GW::SYSTEM::CreateGWindow(100, 100, 500, 500, WINDOWEDBORDERED, &GWindow_specific)));
		REQUIRE(GWindow_specific != nullptr);
	}
	// The following tests can be copied verbatim as they are completly GWindow_generic for all interfaces
	SECTION("Interface Request Tests", "[RequestInterface]")
	{
		CHECK(GWindow_specific->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GWindow_specific->RequestInterface(notAnValidInterface, (void**)&GWindow_generic) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GWindow_generic == nullptr); // should not have changed yet
		REQUIRE(G_SUCCESS(GWindow_specific->RequestInterface(GW::CORE::GInterfaceUUIID, (void**)&GWindow_generic)));
		REQUIRE(GWindow_generic != nullptr);
		// memory addresses should match
		REQUIRE(reinterpret_cast<std::uintptr_t>(GWindow_generic) == reinterpret_cast<std::uintptr_t>(GWindow_specific));
	}
	// Test reference counting behavior
	SECTION("Reference Counting Tests", "[GetCount], [IncrementCount], [DecrementCount]")
	{
		REQUIRE(G_SUCCESS(GWindow_specific->GetCount(countS)));
		REQUIRE(G_SUCCESS(GWindow_generic->GetCount(countG)));
		CHECK(countS == countG);
		CHECK(countS == 2); // should be exactly 2 references at this point
		REQUIRE(G_SUCCESS(GWindow_specific->IncrementCount())); // 3
		REQUIRE(G_SUCCESS(GWindow_generic->IncrementCount())); // 4
		GWindow_specific->GetCount(countS);
		GWindow_generic->GetCount(countG);
		CHECK(countS == countG);
		CHECK(countS == 4); // should be exactly 4 references at this point
		REQUIRE(G_SUCCESS(GWindow_specific->DecrementCount())); // 3
		REQUIRE(G_SUCCESS(GWindow_generic->DecrementCount())); // 2
													   // Free GWindow_specific pointer (user simulation of interface deletion)
		CHECK(G_SUCCESS(GWindow_specific->DecrementCount())); // 1
		GWindow_specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
		GWindow_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle
	}
	// Finally test interface Forward Compatibilty
	SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
	{
		CHECK(GWindow_generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
		CHECK(GWindow_generic->RequestInterface(notAnValidInterface, (void**)&GWindow_specific) == GW::INTERFACE_UNSUPPORTED);
		CHECK(GWindow_specific == nullptr); // should not have changed yet
									// TODO: Check that GWindow_generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
		REQUIRE(G_SUCCESS(GWindow_generic->RequestInterface(GW::SYSTEM::GWindowUUIID, (void**)&GWindow_specific))); // 2
		CHECK(GWindow_specific != nullptr); // GWindow_specific pointer is valid again
		GW::CORE::GSingleThreaded *singleSupport = nullptr;
		GW::CORE::GMultiThreaded *multiSupport = nullptr;
		REQUIRE(G_FAIL(GWindow_generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));
		CHECK(singleSupport == nullptr); // GWindow is NOT singlethreaded
		REQUIRE(G_SUCCESS(GWindow_generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport))); // 3
		CHECK(multiSupport != nullptr); // GWindow IS multithreaded
										// Check final count VS expectations
		REQUIRE(G_SUCCESS(multiSupport->GetCount(countS)));
		CHECK(countS == 3); // three valid handles should exist now
							// Free all handles, all should succeed
		REQUIRE(G_SUCCESS(multiSupport->DecrementCount())); // 2
		REQUIRE(G_SUCCESS(GWindow_specific->DecrementCount())); // 1
		GWindow_generic->GetCount(countG);
		REQUIRE(countG == 1); // should be last remaining handle (again)
		REQUIRE(G_SUCCESS(GWindow_generic->DecrementCount())); // 0
	}
	// done with standard tests, the memory for the object should be released at this point and all pointers should be invalid
}

// Custom Unit Tests specific to this interface follow..


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
	LINUX_WINDOW* l_appWindow = new LINUX_WINDOW();
	LINUX_WINDOW* l_unopenedWindow =new LINUX_WINDOW();
	unsigned int l_windowSize = sizeof(LINUX_WINDOW);
#elif __APPLE__
    NSWindow* m_appWindow; // = [NSWindow alloc];
    NSWindow* m_unopenedWindow; // = [NSWindow alloc];
	unsigned int m_windowSize = sizeof(NSWindow*);
#endif

	appWindow->IsFullscreen(appWindowIsFullscreen);
    CHECK(appWindowIsFullscreen == false);
	// Fail cases
	CHECK(G_FAIL(appWindow->GetWidth(appWindowWidth) == INVALID_ARGUMENT));
	CHECK(G_FAIL(unopenedWindow->GetHeight(unopenedWindowHeight)));
	CHECK(G_FAIL(unopenedWindow->GetWidth(unopenedWindowWidth)));
	CHECK(G_FAIL(unopenedWindow->GetX(unopenedWindowPosX)));
	CHECK(G_FAIL(unopenedWindow->GetY(unopenedWindowPosY)));

#ifdef _WIN32
	CHECK(G_FAIL(unopenedWindow->GetWindowHandle(windowHandleSize, (void**)&unopenedWindowHandle)));
#elif __linux__
	CHECK(G_FAIL(unopenedWindow->GetWindowHandle(l_windowSize, (void**)l_unopenedWindow)));
#elif __APPLE__
	CHECK(G_FAIL(unopenedWindow->GetWindowHandle(m_windowSize, (void**)&m_unopenedWindow)));
#endif

	CHECK(G_FAIL(appWindowIsFullscreen == true));

	// Resize windows for pass tests
	REQUIRE(G_SUCCESS(appWindow->ReconfigureWindow(0, 0, 1920, 1080, FULLSCREENBORDERED)));
	//REQUIRE(G_SUCCESS(appWindow->ReconfigureWindow(0, 0, 1920, 1080, FULLSCREENBORDERLESS)));

	REQUIRE(G_SUCCESS(appWindow->IsFullscreen(appWindowIsFullscreen)));
	//CHECK(appWindowIsFullscreen == true); //Commented-out do to known linux isFullscreen() bug.

	// Pass cases
	REQUIRE(G_SUCCESS(appWindow->GetHeight(appWindowHeight)));
	REQUIRE(G_SUCCESS(appWindow->GetWidth(appWindowWidth)));
	REQUIRE(G_SUCCESS(appWindow->GetX(appWindowPosX)));
	REQUIRE(G_SUCCESS(appWindow->GetY(appWindowPosY)));


#ifdef _WIN32
    REQUIRE(appWindowIsFullscreen == true);
	REQUIRE(G_SUCCESS(appWindow->GetWindowHandle(windowHandleSize, (void**)appWindowHandle)));
	delete appWindowHandle;
	delete unopenedWindowHandle;
#elif __linux__
    //REQUIRE(appWindowIsFullscreen == true);
    //Because ubuntu has a side bar and the auto-fullscreen cannot cover it.
    //We should write code to force window to become the true fullscreen(cover side bar).
    //Please refer this website:  http://bit.ly/2kBCgWH

	REQUIRE(G_SUCCESS(appWindow->GetWindowHandle(l_windowSize, (void**)l_appWindow)));
	delete l_appWindow;
	delete l_unopenedWindow;
#elif __APPLE__
    REQUIRE(appWindowIsFullscreen == true);
	REQUIRE(G_SUCCESS(appWindow->GetWindowHandle(m_windowSize, (void**)&m_appWindow)));
    //delete m_appWindow;
    //[m_appWindow release];
    //[m_unopenedWindow release];

#endif


}

TEST_CASE("Querying Client Information.", "[GetClientWidth], [GetClientHeight], [GetClientTopLeft]")
{
    /*
    [GetClientWidth], [GetClientHeight], [GetClientTopLeft]
    Causes the app to hang until you click a window.
    This is bc the function calls XGetGeometry() (the location of the hang)
    */

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
	#ifdef __linux__
	sleep(0.001);
	#endif
	CHECK(windowTestValue == 1);

#ifdef _WIN32
	// Tell window to maximize
	appWindow->GetWindowHandle(windowHandleSize, (void**)&appWindowHandle);
	ShowWindowAsync(appWindowHandle, SW_SHOWMAXIMIZED);
#elif __linux__
	appWindow->GetWindowHandle(l_windowSize, (void**)&l_appWindow);
	//ShowWindowAsync(l_appWindow, SW_SHOWMAXIMIZED);
#elif __APPLE__
	appWindow->GetWindowHandle(m_windowSize, (void**)&m_appWindow);
	//ShowWindowAsync(m_appWindow, SW_SHOWMAXIMIZED);
#endif

	// Pass case
	windowListener->GetWindowTestValue(windowTestValue);
    #ifdef __linux__
	sleep(0.001);
	#endif
	REQUIRE(windowTestValue == 1);
}

TEST_CASE("GetLastEvent tests.", "[GetLastEvent]")
{
	/*
	The following code is slightly modified to pass the unit tests.
	The reason is when you call the minimize() it changes the style of the window which affects the
	checks for Resize and Maximize. Changing the style to something other than minimize allows the maximize
	check to work. Its a known task to change it from the style enum to excude the minimize and put it on its own
	WindowState enum or variable.
    */

	GWindowInputEvents curEvent;

	//Calls Init, which should set the init event to DESTORY.
	REQUIRE(G_SUCCESS(CreateGWindow(300, 300, 300, 300, WINDOWEDBORDERED, &tstWindow)));
	REQUIRE(tstWindow != nullptr);
#ifndef _WIN32
    //sleep(0.001);
#endif // __WIN32__
	REQUIRE(G_SUCCESS(tstWindow->GetLastEvent(curEvent)));
	REQUIRE(curEvent == GWindowInputEvents::DESTROY);

	//Calls OpenWindow, the last event should be NOTIFY if the style is not MINIMIZE in the CreateGWindow().
	REQUIRE(G_SUCCESS(tstWindow->OpenWindow()));
#ifndef _WIN32
    //sleep(0.001);
#endif // __WIN32__
	REQUIRE(G_SUCCESS(tstWindow->GetLastEvent(curEvent)));
	REQUIRE(curEvent == GWindowInputEvents::NOTIFY);


	REQUIRE(G_SUCCESS(tstWindow->Minimize()));
	REQUIRE(G_SUCCESS(tstWindow->GetLastEvent(curEvent)));
#ifndef __linux__
	REQUIRE(curEvent == GWindowInputEvents::MINIMIZE);
#endif 

	REQUIRE(G_SUCCESS(tstWindow->Maximize()));
	REQUIRE(G_SUCCESS(tstWindow->ResizeWindow(700,700)));
	REQUIRE(G_SUCCESS(tstWindow->GetLastEvent(curEvent)));
#ifndef __linux__
	REQUIRE(curEvent == GWindowInputEvents::RESIZE);
#endif 

    REQUIRE(G_SUCCESS(tstWindow->MoveWindow(500, 500)));
	REQUIRE(G_SUCCESS(tstWindow->GetLastEvent(curEvent)));
#ifndef __linux__
	REQUIRE(curEvent == GWindowInputEvents::MOVE); //Move while fullscreen/maximize won't call the move event. inside will call maximize last.
#endif 

	REQUIRE(G_SUCCESS(tstWindow->ChangeWindowStyle(WINDOWEDBORDERED)));
	REQUIRE(G_SUCCESS(tstWindow->Maximize()));
	REQUIRE(G_SUCCESS(tstWindow->GetLastEvent(curEvent)));
#ifndef __linux__
	REQUIRE(curEvent == GWindowInputEvents::MAXIMIZE); //Have to set the style to something else rather than minimize to have the maximize event be called
#endif 

	REQUIRE(G_SUCCESS(tstWindow->Minimize()));
	REQUIRE(G_SUCCESS(tstWindow->GetLastEvent(curEvent)));
#ifndef __linux__
	REQUIRE(curEvent == GWindowInputEvents::MINIMIZE);
#endif 

	REQUIRE(G_SUCCESS(tstWindow->ChangeWindowStyle(FULLSCREENBORDERED)));
	REQUIRE(G_SUCCESS(tstWindow->GetLastEvent(curEvent)));
#ifndef __linux__
	REQUIRE(curEvent == GWindowInputEvents::MAXIMIZE); //Changing the WindowStyle to any Fullscreen calls the maximize.
#endif 

//Testing the Close event by destroying the window. Replace if a GWindow windowShutdown function exists.
#ifdef _WIN32
	std::atomic<HWND> appWindowHandle;
	unsigned int windowHandleSize = sizeof(HWND);
	tstWindow->GetWindowHandle(windowHandleSize, (void**)&appWindowHandle);

	DestroyWindow(appWindowHandle);
    delete appWindowHandlw;

#elif __APPLE__
	//TODO add apple destroy window
    NSWindow* m_appWindow;
    unsigned int m_windowSize = sizeof(NSWindow*);

    tstWindow->GetWindowHandle(m_windowSize, (void**)&m_appWindow);

    //[m_appWindow performClose: m_appWindow];
    [m_appWindow close];
    [m_appWindow release];
    //sleep(0.001);


#elif __linux__
	//TODO add linux destroy window
    LINUX_WINDOW* l_appWindow = new LINUX_WINDOW();
    unsigned int l_windowSize = sizeof(LINUX_WINDOW);

	REQUIRE(G_SUCCESS(tstWindow->GetWindowHandle(l_windowSize, (void**)l_appWindow)));
	//XDestroyWindow((Display*)l_appWindow->display, (Window)l_appWindow->window);
    XCloseDisplay((Display*)l_appWindow->display);

    delete l_appWindow;
    sleep(0.001);
#endif

	REQUIRE(G_SUCCESS(tstWindow->GetLastEvent(curEvent)));
#ifdef _WIN32
	REQUIRE(curEvent == GWindowInputEvents::DESTROY);
#endif
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
	unopenedWindow->DecrementCount();
	tstWindow->DecrementCount();
}


