#include "../../Interface/G_System/GBufferedInput.h"
#include <map>

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
struct LINUX_WINDOW {
	Window _Window;
	Display * _Display;
};
#elif __APPPLE__

#endif



using namespace GW;
using namespace CORE;

static const unsigned int Keycodes[][2] = {
	//Windows Scancodes		//Linux Other
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, // 0
	{ G_KEY_ESCAPE,			G_KEY_UNKNOWN }, // 1
	{ G_KEY_1,				G_KEY_UNKNOWN }, // 2
	{ G_KEY_2,				G_KEY_UNKNOWN }, // 3
	{ G_KEY_3,				G_KEY_UNKNOWN }, // 4
	{ G_KEY_4,				G_KEY_UNKNOWN }, // 5
	{ G_KEY_5,				G_KEY_UNKNOWN }, // 6
	{ G_KEY_6,				G_KEY_UNKNOWN }, // 7
	{ G_KEY_7,				G_KEY_UNKNOWN }, // 8
	{ G_KEY_8,				G_KEY_UNKNOWN }, // 9
	{ G_KEY_9,				G_KEY_UNKNOWN }, // 10
	{ G_KEY_0,				G_KEY_UNKNOWN }, // 11
	{ G_KEY_MINUS,			G_KEY_UNKNOWN }, // 12
	{ G_KEY_EQUALS,			G_KEY_UNKNOWN }, // 13
	{ G_KEY_BACKSPACE,		G_KEY_UNKNOWN }, // 14
	{ G_KEY_TAB,			G_KEY_UNKNOWN }, // 15
	{ G_KEY_Q,				G_KEY_UNKNOWN }, // 16
	{ G_KEY_W,				G_KEY_UNKNOWN }, // 17
	{ G_KEY_E,				G_KEY_UNKNOWN }, // 18
	{ G_KEY_R,				G_KEY_UNKNOWN }, // 19
	{ G_KEY_T,				G_KEY_UNKNOWN }, // 20
	{ G_KEY_Y,				G_KEY_UNKNOWN }, // 21
	{ G_KEY_U,				G_KEY_UNKNOWN }, // 22
	{ G_KEY_I,				G_KEY_UNKNOWN }, // 23
	{ G_KEY_O,				G_KEY_UNKNOWN }, // 24
	{ G_KEY_P,				G_KEY_UNKNOWN }, // 25
	{ G_KEY_BRACKET_OPEN,	G_KEY_UNKNOWN }, // 26
	{ G_KEY_BRACKET_CLOSE,	G_KEY_UNKNOWN }, // 27
	{ G_KEY_ENTER,			G_KEY_UNKNOWN }, // 28
	{ G_KEY_CONTROL,		G_KEY_UNKNOWN }, // 29
	{ G_KEY_A,				G_KEY_UNKNOWN }, // 30
	{ G_KEY_S,				G_KEY_UNKNOWN }, // 31
	{ G_KEY_D,				G_KEY_UNKNOWN }, // 32
	{ G_KEY_F,				G_KEY_UNKNOWN }, // 33
	{ G_KEY_G,				G_KEY_UNKNOWN }, // 34
	{ G_KEY_H,				G_KEY_UNKNOWN }, // 35
	{ G_KEY_J,				G_KEY_UNKNOWN }, // 36
	{ G_KEY_K,				G_KEY_UNKNOWN }, // 37
	{ G_KEY_L,				G_KEY_UNKNOWN }, // 38
	{ G_KEY_COLON,			G_KEY_UNKNOWN }, // 39
	{ G_KEY_QUOTE,			G_KEY_UNKNOWN }, // 40
	{ G_KEY_TILDE,			G_KEY_UNKNOWN }, // 41
	{ G_KEY_LEFTSHIFT,		G_KEY_UNKNOWN }, // 42
	{ G_KEY_BACKSLASH,		G_KEY_UNKNOWN }, // 43
	{ G_KEY_Z,				G_KEY_UNKNOWN }, // 44
	{ G_KEY_X,				G_KEY_UNKNOWN }, // 45
	{ G_KEY_C,				G_KEY_UNKNOWN }, // 46
	{ G_KEY_V,				G_KEY_UNKNOWN }, // 47
	{ G_KEY_B,				G_KEY_UNKNOWN }, // 48
	{ G_KEY_N,				G_KEY_UNKNOWN }, // 49
	{ G_KEY_COMMA,			G_KEY_UNKNOWN }, // 50
	{ G_KEY_PERIOD,			G_KEY_UNKNOWN }, // 51
	{ G_KEY_FOWARDSLASH,	G_KEY_UNKNOWN }, // 52
	{ G_KEY_RIGHTSHIFT,		G_KEY_UNKNOWN }, // 53
	{ G_KEY_PRINTSCREEN,	G_KEY_UNKNOWN }, // 54
	{ G_KEY_LEFTALT,		G_KEY_UNKNOWN }, // 55
	{ G_KEY_RIGHTALT,		G_KEY_UNKNOWN }, // 56
	{ G_KEY_SPACE,			G_KEY_UNKNOWN }, // 57
	{ G_KEY_CAPSLOCK,		G_KEY_UNKNOWN }, // 58
	{ G_KEY_F1,				G_KEY_UNKNOWN }, // 59
	{ G_KEY_F2,				G_KEY_UNKNOWN }, // 60
	{ G_KEY_F3,				G_KEY_UNKNOWN }, // 61
	{ G_KEY_F4,				G_KEY_UNKNOWN }, // 62
	{ G_KEY_F5,				G_KEY_UNKNOWN }, // 63
	{ G_KEY_F6,				G_KEY_UNKNOWN }, // 64
	{ G_KEY_F7,				G_KEY_UNKNOWN }, // 65
	{ G_KEY_F8,				G_KEY_UNKNOWN }, // 66
	{ G_KEY_F9,				G_KEY_UNKNOWN }, // 67
	{ G_KEY_F10,			G_KEY_UNKNOWN }, // 68
	{ G_KEY_NUMLOCK,		G_KEY_UNKNOWN }, // 69
	{ G_KEY_SCROLL_LOCK,	G_KEY_UNKNOWN }, // 70
	{ G_KEY_HOME,			G_KEY_UNKNOWN }, // 71
	{ G_KEY_UP,				G_KEY_UNKNOWN }, // 72
	{ G_KEY_PAGEUP,			G_KEY_UNKNOWN }, // 73
	{ G_KEY_NUMPAD_MINUS,	G_KEY_UNKNOWN }, // 74
	{ G_KEY_LEFT,			G_KEY_UNKNOWN }, // 75
	{ G_KEY_CENTER,			G_KEY_UNKNOWN }, // 76
	{ G_KEY_RIGHT,			G_KEY_UNKNOWN }, // 77
	{ G_KEY_NUMPAD_PLUS,	G_KEY_UNKNOWN }, // 78
	{ G_KEY_END,			G_KEY_UNKNOWN }, // 79
	{ G_KEY_DOWN,			G_KEY_UNKNOWN }, // 80
	{ G_KEY_PAGEDOWN,		G_KEY_UNKNOWN }, // 81
	{ G_KEY_INSERT,			G_KEY_UNKNOWN }, // 82
	{ G_KEY_DELETE,			G_KEY_UNKNOWN }, // 83

	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, // 84
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, // 85
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, // 86

	{ G_KEY_F12,			G_KEY_UNKNOWN }, //87
	{ G_KEY_F12,			G_KEY_UNKNOWN }, //88

};

namespace {

#ifdef _WIN32
	//Variables

	//! Store the users implementation of the windows procedure.
	LONG_PTR _userWinProc;

	//! Map of Listeners to send event information to.
	std::map<GListener *, unsigned long long> _listeners;

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

			int _event = -1;
			int _data = -1;

			G_INPUT_DATA _dataStruct;

			if (raw->header.dwType == RIM_TYPEKEYBOARD)
			{
				//Get G_KEY
				_data = Keycodes[raw->data.keyboard.MakeCode][0];

				//Set state released or pressed.
				switch (raw->data.keyboard.Message) {
				case 256:
					_event = KEYPRESSED;
					break;
				case 257:
					_event = KEYRELEASED;
					break;
				}
			}
			else if (raw->header.dwType == RIM_TYPEMOUSE)
			{

				//Set Code
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
					//Mouse Pressed
				case 1:
				case 4:
				case 32:
					_event = BUTTONPRESSED;
					break;
					//Mouse Released
				case 2:
				case 8:
				case 16:
					_event = BUTTONRELEASED;
					break;
					//Scroll
				case 1024:
					_event = MOUSESCROLL;
					break;
				}

			}
			_dataStruct._data = _data;

			POINT p;
			if (GetCursorPos(&p))
			{
				_dataStruct._screenX = p.x;
				_dataStruct._screenY = p.y;
			}
			if (ScreenToClient(window, &p))
			{
				_dataStruct._x = p.x;
				_dataStruct._y = p.y;
			}
			if (_dataStruct._data != -1 && _event != -1) {
				std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
				for (; iter != _listeners.end(); ++iter) {
					iter->first->OnEvent(GBufferedInputUUIID, _event, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
				}
			}


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

}