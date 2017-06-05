#pragma once
#include "../../Interface/G_System/GWindow.h"
#include "GUtility.h"

#ifdef __linux
#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <X11/Xutil.h>

#include <map>

//extern std::map<GListener *, unsigned long long> listeners;

#endif

using namespace GW;
using namespace CORE;
using namespace SYSTEM;

#ifdef _WIN32
	//Methods
	LRESULT CALLBACK GWindowProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
		case WM_SIZE:
		{
			GWINDOW_EVENT_DATA eventStruct;

			RECT windowRect;
			GetWindowRect(window, &windowRect);

			eventStruct.eventFlags = -1;
			eventStruct.height = (unsigned int)HIWORD(lp);
			eventStruct.width = (unsigned int)LOWORD(lp);
			eventStruct.windowHandle = window;
			eventStruct.windowX = windowRect.left;
			eventStruct.windowY = windowRect.top;

			switch (wp)
			{
			case SIZE_MAXIMIZED:
			{
				eventStruct.eventFlags = MAXIMIZE;
			}
			break;

			case SIZE_MINIMIZED:
			{
				eventStruct.eventFlags = MINIMIZE;
			}
			break;

			case SIZE_RESTORED:
			{
				eventStruct.eventFlags = RESIZE;
			}
			break;
			}

			if (eventStruct.eventFlags != -1)
			{
				std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
				for (; iter != listeners.end(); ++iter)
					iter->first->OnEvent(GWindowUUIID, eventStruct.eventFlags, &eventStruct, sizeof(GWINDOW_EVENT_DATA));
			}

		}
		break;

		case WM_MOVE:
		{
			GWINDOW_EVENT_DATA eventStruct;

			RECT windowRect;
			GetWindowRect(window, &windowRect);

			eventStruct.eventFlags = MOVE;
			eventStruct.height = windowRect.top - windowRect.bottom;
			eventStruct.width = windowRect.right - windowRect.left;
			eventStruct.windowHandle = window;
			eventStruct.windowX = (int)LOWORD(lp);
			eventStruct.windowY = (int)HIWORD(lp);

			if (eventStruct.eventFlags != -1)
			{
				std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
				for (; iter != listeners.end(); ++iter)
					iter->first->OnEvent(GWindowUUIID, eventStruct.eventFlags, &eventStruct, sizeof(GWINDOW_EVENT_DATA));
			}
		}
		break;

		case WM_CLOSE:
		{
			GWINDOW_EVENT_DATA eventStruct;

			RECT windowRect;
			GetWindowRect(window, &windowRect);

			eventStruct.eventFlags = DESTROY;
			eventStruct.height = windowRect.top - windowRect.bottom;
			eventStruct.width = windowRect.right - windowRect.left;
			eventStruct.windowHandle = window;
			eventStruct.windowX = windowRect.left;
			eventStruct.windowY = windowRect.top;

			if (eventStruct.eventFlags != -1)
			{
				std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
				for (; iter != listeners.end(); ++iter)
					iter->first->OnEvent(GWindowUUIID, eventStruct.eventFlags, &eventStruct, sizeof(GWINDOW_EVENT_DATA));
			}
		}
		break;

		default:
		{
			return DefWindowProcW(window, msg, wp, lp);
			break;
		}
		//return CallWindowProcW((WNDPROC)userWinProc, window, msg, wp, lp);
		}
		//Sleep(0);

	}
#endif // __WIN32

#ifdef __linux__
    void LinuxWndProc(LINUX_WINDOW linuxWnd)
    {
        Atom propType, propHidden, prop;
        unsigned char * propRet = NULL;
		XEvent event;
		GWINDOW_EVENT_DATA eventStruct;
		Display * display = (Display*)linuxWnd.display;
		Window window = (Window)linuxWnd.window;

        int status;

        propType = XInternAtom(display, "_NET_WM_STATE", true);
        propHidden = XInternAtom(display, "_NET_WM_STATE_HIDDEN", true);

		while (true)
		{
            XNextEvent(display, &event);
			switch (event.type)
			{
			case ConfigureNotify:
                status = XGetWindowProperty(display, window, propType, 0L, sizeof(Atom),
                                            false, AnyPropertyType, nullptr, nullptr, nullptr,
                                            nullptr, &propRet);
                if(status == Success && propRet)
                {
                     prop = ((Atom *)propRet)[0];

                     if(prop == propHidden)
                     {
                        //status = XGetGeometry(display, )
                        eventStruct.eventFlags = MINIMIZE;

                        if (eventStruct.eventFlags != -1)
                        {
                            int a = testInt;
                            std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
                            for (; iter != listeners.end(); ++iter)
                                iter->first->OnEvent(GWindowUUIID, eventStruct.eventFlags, &eventStruct, sizeof(GWINDOW_EVENT_DATA));
                        }
                     }
                }
				break;
			}
		}
    }
#endif // __linux__
