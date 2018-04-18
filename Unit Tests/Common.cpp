#include "Common.h"
#include <thread>
#include <condition_variable>

#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#endif // _DEBUG


#ifdef _WIN32

	HWND window = nullptr;
	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		return 0;
	}

#elif __linux__
    GW::SYSTEM::LINUX_WINDOW window; //= new GW::SYSTEM::LINUX_WINDOW();

	Window mainWindow;
	Display* display = nullptr;

#endif

	void Initialize(std::condition_variable& condition, bool& conditionMet)
	{
#		ifdef _DEBUG
		//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		// this function call will set a breakpoint at the location of a leaked block
		// set the parameter to the identifier for a leaked block
		//	_CrtSetBreakAlloc();
		#endif  //_DEBUG

		//We will do our platform specific window creation here....
		//Note: Window create starts an event loop. This event loop will block.
		//CATCH Runs on a seperate thread though and we will notify it to start
		//when the window is created

	#ifdef _WIN32
		//=================================================================================
		//WINDOWS
		//=================================================================================

		//Windows window information
		WNDCLASSEX  wndClass;
		ZeroMemory(&wndClass, sizeof(WNDCLASSEX));

		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.lpszClassName = L"RasterSurfaceApplication";
		wndClass.hInstance = GetModuleHandleW(0);
		wndClass.hCursor = LoadCursorW(0, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
		wndClass.hIcon = LoadIconW(0, IDI_APPLICATION);

		//Register the window
		RegisterClassExW(&wndClass);

		//Adjust window size
		//We will need to ensure window covers the entire screen
		RECT window_size = { 0, 0, 1920, 1080 };
		AdjustWindowRect(&window_size, WS_OVERLAPPEDWINDOW, false);

		//Create the window
		window = CreateWindowW(L"RasterSurfaceApplication", L"Raster Surface",
			WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),
			CW_USEDEFAULT, CW_USEDEFAULT, window_size.right - window_size.left,
			window_size.bottom - window_size.top,
			NULL, NULL, GetModuleHandleW(0), 0);

		if (window)
		{
			//If window was created we will show the window and notify CATCH
			//that it can start its testing.
			//We will then entire the message loop until we get a WM_DESTROY Message
			ShowWindow(window, SW_SHOW);


			//TODO: Initialize any other things you need before the notify_all() call

			conditionMet = true;
			condition.notify_all(); //Notify CATCH

			//Enter message loop
			MSG msg; ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{	// Handles ANY message on this thread (not just ones bound to the HWND)
				if (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE)) // HWND NULL to listen for "PostThreadMessage"
				{
					// We assume all messages are directed at our window
					if (msg.hwnd == NULL) // This is a cross-thread message
						msg.hwnd = window;
					// The below funtions will not operate on NULL HWND messages
					TranslateMessage(&msg);
					DispatchMessageW(&msg);
				}
			}
		}

	#elif __linux__
		//=================================================================================
		//LINUX
		//=================================================================================
		//XKeyEvent event;


		display = XOpenDisplay(NULL);

		//We make sure the window will encompass the whole screen
		mainWindow = XCreateSimpleWindow(display, RootWindow(display, 0), 10, 10, 1920, 1080, 1, BlackPixel(display, 0), WhitePixel(display, 0));

        window.display = (void*)display;
        window.window = (void*)mainWindow;

		XStoreName(display, mainWindow, "Gateware");

		XMapWindow(display, mainWindow);

		//TODO: Initialize any other things you need before the notify_all() call

		//Notify CATCH
		conditionMet = true;
		condition.notify_all();

		while (true)
		{

		}

	#elif __APPLE__
		//=================================================================================
		//APPLE
		//=================================================================================

		// Autorelease Pool:
		// Objects declared in this scope will be automatically
		// released at the end of it, when the pool is "drained".
		pool = [[NSAutoreleasePool alloc] init];

		// Create a shared app instance.
		// This will initialize the global variable
		// 'NSApp' with the application instance.
		[NSApplication sharedApplication];


		NSUInteger windowStyle = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;

		// Window bounds (x, y, width, height).
		NSRect windowRect = NSMakeRect(100, 100, 400, 400);
		window = [[NSWindow alloc] initWithContentRect:windowRect
			styleMask : windowStyle
			backing : NSBackingStoreBuffered
			defer : NO];
		[window autorelease];

		[window makeKeyAndOrderFront : nil];

		//TODO: Initialize any other things you need before the notify_all() call

		conditionMet = true;
		condition.notify_all();

		[NSApp run];

		[pool drain];
	#endif

	}

	void Shutdown()
	{
	#ifdef _WIN32
		//=================================================================================
		//WINDOWS
		//=================================================================================
		PostMessage(window, WM_DESTROY, 0, 0); //Send the destroy message to the window

		//TODO: Add any other shutdown operations you need here

	#elif __linux__
		//=================================================================================
		//LINUX
		//=================================================================================
		//system("xdotool getwindowfocus windowkill"); //Send a kill message to the window

		//TODO: Add any other shutdown operations you need here
		exit(0);

	#elif __APPLE__
		//=================================================================================
		//WINDOWS
		//=================================================================================

		//TODO: Add any other shutdown operations you need here
		//delete window;
		exit(0); //Kill the application

	#endif
	}

	void SimulateInput(unsigned long _flags)
	{
#ifdef _WIN32
		//Create 15 mock inputs
		INPUT key[15];
		ZeroMemory(&key, sizeof(INPUT) * 15);//Zero the structure.

											 //Key 1
		key[0].type = INPUT_KEYBOARD;
		key[0].ki.dwExtraInfo = GetMessageExtraInfo();
		key[0].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(0x31, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[0].ki.dwFlags = _flags;

		//Key 2
		key[1].type = INPUT_KEYBOARD;
		key[1].ki.dwExtraInfo = GetMessageExtraInfo();
		key[1].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(0x32, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[1].ki.dwFlags = _flags;

		//Key 3
		key[2].type = INPUT_KEYBOARD;
		key[2].ki.dwExtraInfo = GetMessageExtraInfo();
		key[2].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(0x33, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[2].ki.dwFlags = _flags;

		//Key 4
		key[3].type = INPUT_KEYBOARD;
		key[3].ki.dwExtraInfo = GetMessageExtraInfo();
		key[3].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(0x34, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[3].ki.dwFlags = _flags;

		//Key A
		key[4].type = INPUT_KEYBOARD;
		key[4].ki.dwExtraInfo = GetMessageExtraInfo();
		key[4].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(0x41, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[4].ki.dwFlags = _flags;

		//Key S
		key[5].type = INPUT_KEYBOARD;
		key[5].ki.dwExtraInfo = GetMessageExtraInfo();
		key[5].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(0x53, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[5].ki.dwFlags = _flags;

		//Key D
		key[6].type = INPUT_KEYBOARD;
		key[6].ki.dwExtraInfo = GetMessageExtraInfo();
		key[6].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(0x44, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[6].ki.dwFlags = _flags;

		//Key W
		key[7].type = INPUT_KEYBOARD;
		key[7].ki.dwExtraInfo = GetMessageExtraInfo();
		key[7].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(0x57, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[7].ki.dwFlags = _flags;

		//Key Left Arrow
		key[8].type = INPUT_KEYBOARD;
		key[8].ki.dwExtraInfo = GetMessageExtraInfo();
		key[8].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(VK_LEFT, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[8].ki.dwFlags = _flags;

		//Key Right Arrow
		key[9].type = INPUT_KEYBOARD;
		key[9].ki.dwExtraInfo = GetMessageExtraInfo();
		key[9].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(VK_RIGHT, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[9].ki.dwFlags = _flags;

		//Key Up Arrow
		key[10].type = INPUT_KEYBOARD;
		key[10].ki.dwExtraInfo = GetMessageExtraInfo();
		key[10].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(VK_UP, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[10].ki.dwFlags = _flags;

		//Key Down Arrow
		key[11].type = INPUT_KEYBOARD;
		key[11].ki.dwExtraInfo = GetMessageExtraInfo();
		key[11].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(VK_DOWN, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[11].ki.dwFlags = _flags;

		///Mouse Buttons
		//Mouse Button Right
		key[12].type = INPUT_MOUSE;
		key[12].ki.dwExtraInfo = GetMessageExtraInfo();
		key[12].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(VK_RBUTTON, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[12].ki.dwFlags = _flags;

		//Mouse Button Left
		key[13].type = INPUT_MOUSE;
		key[13].ki.dwExtraInfo = GetMessageExtraInfo();
		key[13].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(VK_LBUTTON, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[13].ki.dwFlags = _flags;

		//Mouse Button Middle
		key[14].type = INPUT_MOUSE;
		key[14].ki.dwExtraInfo = GetMessageExtraInfo();
		key[14].ki.wScan = static_cast<WORD>(MapVirtualKeyEx(VK_MBUTTON, MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		key[14].ki.dwFlags = _flags;


		//Send the inputs
		SendInput(15, &key[0], sizeof(INPUT));

#elif __linux__
		if (_flags)
		{
			//Numbers
			system("xdotool search --name Gateware keydown 1");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keydown 2");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keydown 3");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keydown 4");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			//Letters
			system("xdotool search --name Gateware keydown A");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keydown S");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keydown D");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keydown W");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			//Arrow keys
			system("xdotool search --name Gateware keydown Left");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keydown Right");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keydown Up");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keydown Down");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
		else
		{
			system("xdotool search --name Gateware keyup 1");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keyup 2");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keyup 3");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keyup 4");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			//Letters
			system("xdotool search --name Gateware keyup A");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keyup S");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keyup D");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keyup W");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keyup Left");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keyup Right");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keyup Up");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			system("xdotool search --name Gateware keyup Down");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));

		}

#elif __APPLE__
		[window becomeMainWindow];
		[NSApp activateIgnoringOtherApps : YES];

		NSEvent* fakeEvent;

		if (_flags)
		{
			//Key 1
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 18];

			[NSApp sendEvent : fakeEvent];

			//Key 2
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 19];

			[NSApp sendEvent : fakeEvent];

			//Key 3
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 20];

			[NSApp sendEvent : fakeEvent];

			//Key 4
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 21];

			[NSApp sendEvent : fakeEvent];

			//Key A
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 0];

			[NSApp sendEvent : fakeEvent];

			//Key S
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 1];

			[NSApp sendEvent : fakeEvent];

			//Key D
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 2];

			[NSApp sendEvent : fakeEvent];

			//Key W
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 13];

			[NSApp sendEvent : fakeEvent];

			//Key Left Arreow
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 123];

			[NSApp sendEvent : fakeEvent];

			//Key Right Arrow
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 124];

			[NSApp sendEvent : fakeEvent];

			//Key up arrow
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 126];

			[NSApp sendEvent : fakeEvent];

			//Key down arrow
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyDown
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 125];

			[NSApp sendEvent : fakeEvent];

		}
		else
		{
			//Key 1
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 18];

			[NSApp sendEvent : fakeEvent];

			//Key 2
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 19];

			[NSApp sendEvent : fakeEvent];

			//Key 3
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 20];

			[NSApp sendEvent : fakeEvent];

			//Key 4
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 21];

			[NSApp sendEvent : fakeEvent];

			//Key A
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 0];

			[NSApp sendEvent : fakeEvent];

			//Key S
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 1];

			[NSApp sendEvent : fakeEvent];

			//Key D
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 2];

			[NSApp sendEvent : fakeEvent];

			//Key W
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 13];

			[NSApp sendEvent : fakeEvent];

			//Key Left Arreow
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 123];

			[NSApp sendEvent : fakeEvent];

			//Key Right Arrow
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 124];

			[NSApp sendEvent : fakeEvent];

			//Key up arrow
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 126];

			[NSApp sendEvent : fakeEvent];

			//Key down arrow
			fakeEvent = [NSEvent keyEventWithType : NSEventTypeKeyUp
				location : NSZeroPoint
				modifierFlags : 0
				timestamp : 0
				windowNumber : [[NSApp mainWindow] windowNumber]
				context : nil
				characters : @"1"
				charactersIgnoringModifiers : @"a"
				isARepeat : NO
				keyCode : 125];

			[NSApp sendEvent : fakeEvent];
		}
#endif

	}
