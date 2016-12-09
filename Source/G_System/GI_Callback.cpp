#include "../../Source/G_System/GI_Static.cpp"
#include "../../Interface/G_System/GInput.h"

using namespace GW;
using namespace CORE;

namespace {


unsigned int n_Keys[256];
float _mousePrevX = 0;
float _mousePrevY = 0;
float _mousePositionX = 0;
float _mousePositionY = 0;
float _mouseDeltaX = 0;
float _mouseDeltaY = 0;
unsigned int _keyMask;


#ifdef _WIN32
	//Variables

	//! Store the users implementation of the windows procedure.
	LONG_PTR _userWinProc;

	//Methods
	LRESULT CALLBACK GWinProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp) {
		switch (msg)
		{

		case WM_INPUT:
		{
			UINT dwSize;

			//Get the size of RawInput
			GetRawInputData((HRAWINPUT)lp, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

			LPBYTE lpb = new BYTE[dwSize];

			if (GetRawInputData((HRAWINPUT)lp, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize) {
				//std::cout << "GetRawInputData does not return correct size.\n";
			}

			RAWINPUT* raw = (RAWINPUT*)lpb;

			unsigned int _event = 0;
			unsigned int _data = 0;

			if (raw->header.dwType == RIM_TYPEKEYBOARD)
			{
				//Get G_KEY
				_data = Keycodes[raw->data.keyboard.MakeCode][0];
				//Set state released or pressed.
				switch (raw->data.keyboard.Message) {
				case 256:
					n_Keys[_data] = 1;
					switch (_data) {
					case G_KEY_RIGHTSHIFT:
					case G_KEY_LEFTSHIFT:
						TURNON_BIT(_keyMask, G_MASK_SHIFT);
						break;
					case G_KEY_CONTROL:
						TURNON_BIT(_keyMask, G_MASK_CONTROL);
						break;
					case G_KEY_CAPSLOCK:
						TOGGLE_BIT(_keyMask, G_MASK_CAPS_LOCK);
						break;
					case G_KEY_NUMLOCK:
						TOGGLE_BIT(_keyMask, G_MASK_NUM_LOCK);
						break;
					case G_KEY_SCROLL_LOCK:
						TOGGLE_BIT(_keyMask, G_MASK_SCROLL_LOCK);
						break;
					}
					break;
				case 257:
					n_Keys[_data] = 0;
					switch (_data) {
					case G_KEY_RIGHTSHIFT:
					case G_KEY_LEFTSHIFT:
						TURNOFF_BIT(_keyMask, G_MASK_SHIFT);
						break;
					case G_KEY_CONTROL:
						TURNOFF_BIT(_keyMask, G_MASK_CONTROL);
						break;
					}
					break;
				}

			}
			else if (raw->header.dwType == RIM_TYPEMOUSE)
			{

				switch (raw->data.mouse.ulButtons) {
				case 1:
				case 2:
					_data = G_BUTTON_LEFT;
					break;
				case 4:
				case 8:
					_data = G_BUTTON_RIGHT;
					break;
				case 16:
				case 32:
					_data = G_BUTTON_MIDDLE;
					break;
				}

				switch (raw->data.mouse.usButtonData) {
				case 120:
					_data = G_MOUSE_SCROLL_UP;
					break;
				case 65416:
					_data = G_MOUSE_SCROLL_DOWN;
					break;
				}

				switch (raw->data.mouse.usButtonFlags) {
					//pressed
				case 1:
				case 4:
				case 16:
					n_Keys[_data] = 1;
					break;
					//Released
				case 2:
				case 8:
				case 32:
					n_Keys[_data] = 0;
					break;
				case 1024:
					n_Keys[_data] = 1;
					break;
				}


			}

			if (_data != G_MOUSE_SCROLL_UP) {
				n_Keys[G_MOUSE_SCROLL_UP] = 0;
			}
			if (_data != G_MOUSE_SCROLL_DOWN) {
				n_Keys[G_MOUSE_SCROLL_DOWN] = 0;
			}

			POINT p;
			if (GetCursorPos(&p))
			{

			}
			if (ScreenToClient(window, &p))
			{
				_mousePositionX = (float)p.x;
				_mousePositionY = (float)p.y;
			}

			_mouseDeltaX = _mousePrevX - _mousePositionX;
			_mouseDeltaY = _mousePrevY - _mousePositionY;

			_mousePrevX = _mousePositionX;
			_mousePrevY = _mousePositionY;


			delete[] lpb;
		}
		break;


		default:
			return CallWindowProcW((WNDPROC)_userWinProc, window, msg, wp, lp);
			break;
		}
		return 0;
	}
#endif

#ifdef __linux__

	bool LinuxPredicate(Display *display, XEvent *e, XPointer arg) {

	}


#endif

}

