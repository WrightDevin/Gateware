
#include "../../Interface/G_System/GInput.h"
#include "GKeyDefines.h"
#include <map>


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

	unsigned int n_Keys[256];

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
				n_Keys[_data] = raw->data.keyboard.Flags;

			}
			else if (raw->header.dwType == RIM_TYPEMOUSE)
			{

				//Set Code
				switch (raw->data.mouse.usButtonData){
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

class Input : public GInput {

private:

	/* GInterface */

	//! Total number of active refrences to this object.
	unsigned int n_refrenceCount;
	void * hWnd;

public:

	/* Input */

	Input();
	~Input();

	GRETURN InitializeWindows(void * _data);
	GRETURN InitializeLinux(void * _data);
	GRETURN InitializeMac(void * _data);

	/* GInput */

	//GRETURN Update();
	GRETURN GetKeyState(int _keyCode, bool &_outValue);
	GRETURN GetMousePosition(double &x, double &y);


	/* GInterface */

	//! Return the total number of active refrences to this object 
	GRETURN GetCount(unsigned int &_outCount);

	//! Increase the total number of active refrences to this object 
	//! End users should only call this operation if they are familiar with reference counting behavior 
	GRETURN IncrementCount();

	//! Decrease the total number of active refrences to this object 
	//! Once the internal count reaches zero this object will be deallocated and your pointer will become invalid 
	GRETURN DecrementCount();

	//! Requests an interface that may or may not be supported by this object  
	GRETURN RequestInterface(const GUUIID &_interfaceID, void** _outputInterface);
};

GRETURN CreateGInput(GInput** _outFpointer, void * _data) {

	if (_outFpointer == nullptr || _data == nullptr) {
		return INVALID_ARGUMENT;
	}

	Input * _mInput = new Input();

	if (_mInput == nullptr) {
		return FAILURE;
	}

#ifdef _WIN32
	_mInput->InitializeWindows(_data);
#elif __APPLE__
	_mInput->InitializeMac(_data);
#elif __linux__
	_mInput->InitializeLinux(_data);
#endif

#ifdef _WIN32
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) DispatchMessage(&msg);
#elif __linux__
	XEvent e;
	unsigned int _event = 0;
	unsigned int code = 0;
	unsigned short state = 0;
	while (1) {
		XNextEvent(_linuxWindow.Display, &e);
		switch (e.type) {
		case KeyPress:
			code = e.xkey.keycode;
			state = KeyPressed;
			break;
		case KeyRelease:
			code = e.xkey.keycode;
			state = KeyReleased;
			break;
		case ButtonPress:
			code = e.xbutton.button;
			state = KeyPressed;
			break;
		}
		case ButtonRelease:
			code = e.xbutton.button;
			state = KeyReleased;
			break;
}
	std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin;
	for (; iter != _listeners.end(); ++iter) {
		iter->first->OnEvent(GBufferedInputUUIID, state, &_event);
	}
}

	}
#elif __APPPLE__

#endif

	//Todo call my intiialize
	(*_outFpointer) = _mInput;

	return SUCCESS;

}

Input::Input() {
	n_refrenceCount = 1;
}

Input::~Input() {

}

GRETURN Input::GetCount(unsigned int &_outCount) {

	_outCount = n_refrenceCount;

	return SUCCESS;
}

GRETURN Input::IncrementCount() {

	n_refrenceCount += 1;

	return SUCCESS;
}

GRETURN Input::DecrementCount() {

	n_refrenceCount -= 1;

	if (n_refrenceCount == 0) {
		delete this;
	}

	return SUCCESS;
}

GRETURN Input::RequestInterface(const GUUIID &_interfaceID, void** _outputInterface) {
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	if (_interfaceID == GInputUUIID)
	{
		GInput * convert = reinterpret_cast<GInput*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GSingleThreadedUUIID)
	{
		GSingleThreaded* convert = reinterpret_cast<GSingleThreaded*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GInterfaceUUIID)
	{
		GInterface* convert = reinterpret_cast<GInterface*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else
		return INTERFACE_UNSUPPORTED;

	return SUCCESS;
}

GRETURN Input::InitializeWindows(void * _data) {
#ifdef _WIN32
	_userWinProc = SetWindowLongPtr((HWND)_data, GWLP_WNDPROC, (LONG_PTR)GWinProc);

	if (_userWinProc == NULL) {
		//The user has not setup a windows proc prior to this point.
	}

	//Getting Raw Input Devices.

	UINT numDevices;
	PRAWINPUTDEVICELIST pRawInputDeviceList;

	//Get Number of Devices.
	if (GetRawInputDeviceList(NULL, &numDevices, sizeof(RAWINPUTDEVICELIST)) != 0) {

	}

	//Allocate the list of devices.
	if ((pRawInputDeviceList = (PRAWINPUTDEVICELIST)malloc(sizeof(RAWINPUTDEVICELIST) * numDevices)) == NULL) {

	}

	int nNoOfDevices = 0;
	//Using the new List and number of devices.
	//Populate the raw input device list.
	if ((nNoOfDevices = GetRawInputDeviceList(pRawInputDeviceList, &numDevices, sizeof(RAWINPUTDEVICELIST))) == ((UINT)-1)) {

	}


	RID_DEVICE_INFO rdi;
	rdi.cbSize = sizeof(RID_DEVICE_INFO);

	//For all of the devices display there correspondant information.
	for (int i = 0; i < nNoOfDevices; i++) {

		UINT size = 256;
		TCHAR tBuffer[256] = { 0 };
		tBuffer[0] = '\0';


		//FInd the device name.
		if (GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, tBuffer, &size) < 0) {

		}

		UINT cbSize = rdi.cbSize;
		//Get the device information.
		if (GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &rdi, &cbSize) < 0) {

		}

		//Display the device information.

		//Check if its a mouse.
		//std::cout << std::endl << "Device Name: " << tBuffer << std::endl;
		if (rdi.dwType == RIM_TYPEMOUSE) {

		}

		//Check if its a Keyboard.
		else if (rdi.dwType == RIM_TYPEKEYBOARD) {

		}
		//Check if its a vendor.
		else if (rdi.dwType == RIM_TYPEHID) {

		}

	}

	//Register the raw input devices.
	RAWINPUTDEVICE rID[2];

	//KeyBoard
	rID[0].usUsagePage = 0x01;
	rID[0].usUsage = 0x06;
	rID[0].dwFlags = RIDEV_NOLEGACY;
	rID[0].hwndTarget = (HWND)_data;

	//Mouse
	rID[1].usUsagePage = 0x01;
	rID[1].usUsage = 0x02;
	rID[1].dwFlags = RIDEV_NOLEGACY;
	rID[1].hwndTarget = (HWND)_data;

	if (RegisterRawInputDevices(rID, 2, sizeof(rID[0])) == false) {
		//std::cout << "\n\n*******************\nRegistering Devices Failed.\n*******************\n";
	}
#endif

	return SUCCESS;
}

GRETURN Input::InitializeLinux(void * _data) {

#ifdef __linux__

	(*_linuxWindow) = (LINUX_WINDOW*)_data;
	//memcpy(&_linuxWindow, data, 64);
	XSelectInput(_linuxWindow.Display, _linuxWindow.Window, ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyReleaseMask | KeyPressMask);
#endif

	return SUCCESS;

}

GRETURN Input::InitializeMac(void * _data) {

	return SUCCESS;
}

GRETURN Input::GetKeyState(int _keyCode, bool &_outValue) {
	_outValue = bool(n_Keys[_keyCode]);
	return SUCCESS;
}

GRETURN Input::GetMousePosition(double &x, double &y) {
	POINT p;
	if (!GetCursorPos(&p))
	{
		return FAILURE;
	}
	if (!ScreenToClient(HWND(hWnd), &p))
	{
		return FAILURE;
	}

	return SUCCESS;

}
