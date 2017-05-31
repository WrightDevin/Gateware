#pragma once

using namespace GW;
using namespace CORE;
using namespace SYSTEM;

#ifdef __WIN32
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
        XEvent event;
        XNextEvent(linuxWnd.display, &event);


    }
#endif // __linux__
