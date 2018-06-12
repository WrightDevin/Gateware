#pragma once
#include "../../Interface/G_System/GWindow.h"
#include "GUtility.h"

#ifdef __linux
#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <X11/Xutil.h>
#include "unistd.h"
#include <map>

#elif __APPLE__
#include <map>

#endif

using namespace GW;
using namespace CORE;
using namespace SYSTEM;

namespace
{
    // GWindow global variables.
	GWindowInputEvents LastEvent;

    //! Map of Listeners to send event information to.
    std::map<GListener *, unsigned long long> listeners;
    int testInt;

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
				LastEvent = GWindowInputEvents::MAXIMIZE;
			}
			break;

			case SIZE_MINIMIZED:
			{
				eventStruct.eventFlags = MINIMIZE;
				LastEvent = GWindowInputEvents::MINIMIZE;
			}
			break;

			case SIZE_RESTORED:
			{
				eventStruct.eventFlags = RESIZE;
				LastEvent = GWindowInputEvents::RESIZE;

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

			LastEvent = GWindowInputEvents::MOVE;

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

			LastEvent = GWindowInputEvents::DESTROY;

			if (eventStruct.eventFlags != -1)
			{

				std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
				for (; iter != listeners.end(); ++iter)
					iter->first->OnEvent(GWindowUUIID, eventStruct.eventFlags, &eventStruct, sizeof(GWINDOW_EVENT_DATA));
			}
		}
		break;
		case WM_DESTROY:
		{
			LastEvent = GWindowInputEvents::DESTROY;
		}
		default:
		{
            Sleep(0);
			return DefWindowProcW(window, msg, wp, lp);
			break;
		}
		//return CallWindowProcW((WNDPROC)userWinProc, window, msg, wp, lp);
		}
		return DefWindowProcW(window, msg, wp, lp);
	}
#endif // __WIN32

#ifdef __linux__
    void LinuxWndProc(Display * _display, Window _window)
    {
        Atom prop = 0;
        unsigned char * propRet = NULL;
		XEvent event;
		GWINDOW_EVENT_DATA eventStruct;
        Window rootRet = 0;
        int x = 0;     int y = 0;
        int prevX = 0; int prevY = 0;
        unsigned int width = 0;     unsigned int height = 0; unsigned int borderHeight = 0; unsigned int depth = 0;
        unsigned int prevWidth = 0; unsigned int prevHeight = 0;
        unsigned int eventFlag = 0;
        int status = 0;

        //ZeroMemory the structs
        memset(&event, 0, sizeof(event));
        memset(&eventStruct, 0, sizeof(eventStruct));

       Atom propType = XInternAtom(_display, "_NET_WM_STATE", true);
       Atom propHidden = XInternAtom(_display, "_NET_WM_STATE_HIDDEN", true);
       Atom propFull = XInternAtom(_display, "_NET_WM_STATE_FULLSCREEN", true);
       Atom propClose = XInternAtom(_display, "_NET_WM_ACTION_CLOSE", true); // WM_DESTROY_WINDOW

        Atom actual_type = 0;
        unsigned long nitems = 0;
        unsigned long bytes_after = 0;
        int actual_format = 0;

		while (true)
		{
		    propRet = nullptr;

		    //Also flushes the request buffer if xlib's queue does not contain an event and waits for an event to arrive from server connection
            XNextEvent(_display, &event);

			switch (event.type)
			{
			    case Expose:
                    {
                        //Expose, when a window becomes visible on the screen, after being obscured or unmapped.

                        //printf("\n\n EXPOSE EVENT \n\n");
                        break;
                    }
                case PropertyNotify:
                    {
                    //PropertyNotify, when a client wants info about property changes for a specified window
                    //To receive PropertyNotify events, set the PropertyChangeMask bit in the event-mask attribute of the window.

                    //printf("\n\n PROPERTYNOTIFY EVENT \n\n");

                    status = XGetWindowProperty(event.xproperty.display, event.xproperty.window, propType, 0L, sizeof(Atom),
                                        false, AnyPropertyType, &actual_type, &actual_format, &nitems, &bytes_after, &propRet);

                        if(status == Success && propRet && nitems > 0)
                        {
                            prop = ((Atom *)propRet)[0];
                            XGetGeometry(_display, _window, &rootRet, &x, &y, &width, &height, &borderHeight, &depth);

                            if(prop == propHidden)
                            {
                             eventFlag = MINIMIZE;
                             LastEvent = GWindowInputEvents::MINIMIZE;
                            }


                            else if(prop == 301 || prop == 302 || prop == propFull)
                            {
                            eventFlag = MAXIMIZE;
                            LastEvent = GWindowInputEvents::MAXIMIZE;
                            }

                            else if(prevX != x || prevY != y)
                            {
                            eventFlag = MOVE;
                            LastEvent = GWindowInputEvents::MOVE;
                            }


                            else if(prevHeight != height || prevWidth != width)
                            {
                            eventFlag = RESIZE;
                            LastEvent = GWindowInputEvents::RESIZE;
                            }

                            else if(prop == propClose)
                            {
                            eventFlag = DESTROY;
                            LastEvent = GWindowInputEvents::DESTROY;
                            }


                            eventStruct.eventFlags = eventFlag;
                            eventStruct.width = width;
                            eventStruct.height = height;
                            eventStruct.windowX = x;
                            eventStruct.windowY = y;
                            eventStruct.windowHandle = _display;

                            prevX = x; prevY = y; prevHeight = height; prevWidth = width;

                            if (eventStruct.eventFlags != -1 && listeners.size() > 0)
                            {
                            std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
                            for (; iter != listeners.end(); ++iter)
                                iter->first->OnEvent(GWindowUUIID, eventStruct.eventFlags, &eventStruct, sizeof(GWINDOW_EVENT_DATA));
                            }

                        }
                        XFree(propRet);
                        break;
                }
                case ConfigureNotify:
                    {
                        //ConfigureNotify, when a client wants info about the actual changes to a window's state,
                        //such as size, position, border, and stacking order.

                        //printf("\n\n CONFIGURENOTIFY EVENT \n\n");

                        //Sets current window data to the events data about the window
                        width = event.xconfigure.width;
                        height = event.xconfigure.height;
                        x = event.xconfigure.x;
                        y = event.xconfigure.y;

                        if(prevX != x || prevY != y) //if the previous position is not equal to the current position then we moved.
                        {
                        eventFlag = MOVE;
                        LastEvent = GWindowInputEvents::MOVE;
                        }
                        if(prevHeight != height || prevWidth != width) //if the previous width/height are not equal to the current width/height then we resized.
                        {
                        eventFlag = RESIZE;
                        LastEvent = GWindowInputEvents::RESIZE;
                        }

                        //Inform the listeners of this event
                        eventStruct.eventFlags = eventFlag;
                        eventStruct.width = width;
                        eventStruct.height = height;
                        eventStruct.windowX = x;
                        eventStruct.windowY = y;
                        eventStruct.windowHandle = _display;

                        prevX = x; prevY = y; prevHeight = height; prevWidth = width;

                        if (eventStruct.eventFlags != -1 && listeners.size() > 0)
                        {
                            std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
                            for (; iter != listeners.end(); ++iter)
                                iter->first->OnEvent(GWindowUUIID, eventStruct.eventFlags, &eventStruct, sizeof(GWINDOW_EVENT_DATA));
                        }


                    break;
                }
                case MapNotify:
                    {
                        //MapNotify, when clients want info about which windows are mapped.
                        //The change of a window's state from unmapped to mapped

                       // printf("\n\n MAPNOTIFY EVENT \n\n");

                        eventFlag = MAXIMIZE;
                        LastEvent = GWindowInputEvents::MAXIMIZE;

                        //Inform the listeners of this event
                        eventStruct.eventFlags = eventFlag;
                        eventStruct.width = width;
                        eventStruct.height = height;
                        eventStruct.windowX = x;
                        eventStruct.windowY = y;
                        eventStruct.windowHandle = _display;

                        prevX = x; prevY = y; prevHeight = height; prevWidth = width;

                        if (eventStruct.eventFlags != -1 && listeners.size() > 0)
                        {
                            std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
                            for (; iter != listeners.end(); ++iter)
                                iter->first->OnEvent(GWindowUUIID, eventStruct.eventFlags, &eventStruct, sizeof(GWINDOW_EVENT_DATA));
                        }


                    }
                case ButtonPress:
                    {
                        //Respond to button press

                       // printf("\n\n BUTTONPRESS EVENT \n\n");
                        break;
                    }
                case ClientMessage:
                    {
                        /* Primarily used for transferring selection data,
                        also might be used in a private interclient
                        protocol; otherwise, not needed in event loop */

                        //printf("\n\n CLIENTMESSAGE EVENT \n\n");
                        break;
                    }
                case SelectionClear:
                    {
                        //Clients losing ownership of a selection.

                       // printf("\n\n SELECTIONCLEAR EVENT \n\n");
                        break;
                    }
                case SelectionNotify:
                    {
                        //A response to a ConvertSelection request when there is no owner for the selection

                       // printf("\n\n SELECTIONNOTIFY EVENT \n\n");
                        break;
                    }
                case SelectionRequest:
                    {
                        //A client requests a selection conversion by calling XConvertSelection() for the owned selection.

                       // printf("\n\n SELECTIONREQUEST EVENT \n\n");
                        break;
                    }
                case NoExpose:
                    {
                        //Generates this event whenever a destination region could not be computed due to an obscured
                        //or out-of-bounds source region.

                        //printf("\n\n NOEXPOSE EVENT \n\n");
                        break;
                    }
                case DestroyNotify:
                    {
                    //The Destroy event gets called when a client wants info about which windows are destroyed.

                    //printf("\n\n DESTROYNOTIFY EVENT \n\n");

                    XGetGeometry(_display, _window, &rootRet, &x, &y, &width, &height, &borderHeight, &depth);

                    LastEvent = GWindowInputEvents::DESTROY;

                    eventStruct.eventFlags = DESTROY;
                    eventStruct.width = width;
                    eventStruct.height = height;
                    eventStruct.windowX = x;
                    eventStruct.windowY = y;
                    eventStruct.windowHandle = _display;

                    if (eventStruct.eventFlags != -1)
                    {
                    std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
                    for (; iter != listeners.end(); ++iter)
                        iter->first->OnEvent(GWindowUUIID, eventStruct.eventFlags, &eventStruct, sizeof(GWINDOW_EVENT_DATA));
                    }
                    break;
                    }

			}

		}



    }
#endif // __linux__

#ifdef __APPLE__

    GWResponder* responder = [GWResponder alloc];
    GWDelegate*  delegate = [GWDelegate alloc];
    GWAppDelegate* appDel = [GWAppDelegate alloc];
#endif
}
