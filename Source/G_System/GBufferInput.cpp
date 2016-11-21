#include "../../Interface/G_System/GBufferedInput.h"
#include "GKeyDefines.h"
#include <map>
#include <mutex> 
#include <atomic>
#include <queue>

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#elif __APPPLE__

#endif

using namespace GW;
using namespace CORE;


#ifdef __linux__
struct LINUX_WINDOW {
	Window _Window;
	Display * _Display;
};
#endif

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
			unsigned int _data = 0;

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

				unsigned int buttonData = raw->data.mouse.ulButtons;
				//Set Code
				switch (buttonData) {
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

				unsigned int buttonFlags = raw->data.mouse.usButtonFlags;


				switch (buttonFlags) {
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
				}

			}
			std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
			for (; iter != _listeners.end(); ++iter) {
				iter->first->OnEvent(GBufferedInputUUIID, _event, (void*)_data);
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

class BufferedInput : public GBufferedInput {

private:

	/* GInput */

	//! Total number of active refrences to this object. 
	std::atomic_uint32_t n_refrenceCount;

	//! A mutex for locking and unlocking.
	std::mutex _Mutex;


#ifdef _WIN32
#elif __linux__
	LINUX_WINDOW _linuxWindow;
#elif __APPPLE__

#endif
public:

	/* Input */

	BufferedInput();
	~BufferedInput();

	//! Initialized the RAW_INPUT for windows alongside the Win Proc.
	GRETURN InitializeWindows(void * _data);
	GRETURN InitializeLinux(void * _data);
	GRETURN InitializeMac(void * _data);

	//! While there are still events read the events. And update the buffer.
	//GRETURN Update();

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


	/* GBroadcasting */

	//! Any listener added to this class must receive all events unless otherwise specified by the _eventMask (optional) 
	//! Listeners registered to a broadcaster will have their refrence counts increased by one until deregistered 
	GRETURN RegisterListener(GListener *_addListener, unsigned long long _eventMask);

	//! A successfully deregistered listener will no longer receive events and have it's refrence count decremented by one  
	GRETURN DeregisterListener(GListener *_removeListener);

};

GRETURN GW::CORE::CreateGBufferedInput(GBufferedInput** _outPointer, void * _data) {

	if (_outPointer == nullptr || _data == nullptr) {
		return INVALID_ARGUMENT;
	}

	BufferedInput * _mInput = new BufferedInput();

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
	//MSG msg;
	//while (GetMessage(&msg, 0, 0, 0)) DispatchMessage(&msg);
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

	(*_outPointer) = _mInput;

	return SUCCESS;

}

#pragma region BufferedInput

BufferedInput::BufferedInput() {
	n_refrenceCount = 1;
}

BufferedInput::~BufferedInput() {

}

GRETURN BufferedInput::InitializeWindows(void * _data) {
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

GRETURN BufferedInput::InitializeLinux(void * _data) {

#ifdef __linux__

	(*_linuxWindow) = (LINUX_WINDOW*)_data;
	//memcpy(&_linuxWindow, data, 64);
	XSelectInput(_linuxWindow.Display, _linuxWindow.Window, ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyReleaseMask | KeyPressMask);
#endif

	return SUCCESS;

}

GRETURN BufferedInput::InitializeMac(void * _data) {

	return SUCCESS;
}
//
//GRETURN BufferedInput::Update() {
//
//
//	return SUCCESS;
//
//}

#pragma endregion

#pragma region GInterface

GRETURN BufferedInput::GetCount(unsigned int &_outCount) {

	_outCount = n_refrenceCount;

	return SUCCESS;
}

GRETURN BufferedInput::IncrementCount() {

	n_refrenceCount += 1;

	return SUCCESS;
}

GRETURN BufferedInput::DecrementCount() {

	n_refrenceCount -= 1;

	if (n_refrenceCount == 0) {
		delete this;
	}

	return SUCCESS;
}

GRETURN BufferedInput::RequestInterface(const GUUIID &_interfaceID, void** _outputInterface) {
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	if (_interfaceID == GBufferedInputUUIID)
	{
		GBufferedInput * convert = reinterpret_cast<GBufferedInput*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GBroadcastingUUIID)
	{
		GBroadcasting* convert = reinterpret_cast<GBroadcasting*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GMultiThreadedUUIID)
	{
		GMultiThreaded* convert = reinterpret_cast<GMultiThreaded*>(this);
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

#pragma endregion

#pragma region GBroadcasting

GRETURN BufferedInput::RegisterListener(GListener *_addListener, unsigned long long _eventMask) {
	//Check if listner is already in the map of listeners. Return Redundent_Operation.
	_Mutex.lock();

	std::map<GListener *, unsigned long long>::const_iterator iter = _listeners.find(_addListener);
	if (iter != _listeners.end()) {
		return REDUNDENT_OPERATION;
	}

	//Otherwise add the listener to the map with the event mask.
	_listeners[_addListener] = _eventMask;
	IncrementCount();

	_Mutex.unlock();

	return SUCCESS;

}

GRETURN BufferedInput::DeregisterListener(GListener *_removeListener) {
	//Check if listner exists.
	_Mutex.lock();
	std::map<GListener *, unsigned long long>::const_iterator iter = _listeners.find(_removeListener);
	if (iter != _listeners.end()) {
		_listeners.erase(iter);
		_Mutex.unlock();
		DecrementCount();
	}
	//If the listener doesnt exist just return failure.
	else {
		_Mutex.unlock();
		return FAILURE;
	}


	return SUCCESS;
}

#pragma endregion



