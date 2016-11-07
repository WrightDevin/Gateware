#include "../../Interface/G_System/GBufferedInput.h"; 
#include "../../Source/G_System/GBIGlobalNamespace.h"
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


#define GETMASK(index, size) (((1 << (size)) - 1) << (index))
#define READFROM(data, index, size) (((data) & GETMASK((index), (size))) >> (index))
#define WRITETO(data, index, size, value) ((data) = ((data) & (~GETMASK((index), (size)))) | ((value) << (index)))

using namespace GW;
using namespace CORE;

struct LINUX_WINDOW {
	void * Window;
	void * Display;
};

enum GINPUT_EVENTS {
	KeyPressed = 1,
	KeyReleased = 2,
};

class BufferedInput : public GBufferedInput {

private:

	/* GInput */

	//! Total number of active refrences to this object. 
	std::atomic_uint32_t n_refrenceCount;

	//! Type 3 bits KeyCode 9 bits (512 Unique)    Reserved 20 bits 
	//! 000			00000000-0					   00000000-00000000-0000
	std::atomic_uint32_t n_Keys[512];

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
	GRETURN InitializeWindows(void * _window);

	GRETURN InitializeLinux(void * _window);
	GRETURN InitializeMac(void * _window);

	//! While there are still events read the events. And update the buffer.
	GRETURN Update();

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

GRETURN CreateGBufferedInput(GBufferedInput** _outPointer, void * _window) {

	if (_outPointer == nullptr) {
		return INVALID_ARGUMENT;
	}

	BufferedInput * _mInput = new BufferedInput();

	if (_mInput == nullptr) {
		return FAILURE;
	}

#ifdef _WIN32
	_mInput->InitializeWindows(_window);
#elif __APPLE__
	_mInput->InitializeMac(_window);
#elif __linux__
	_mInput->InitializeLinux(_window);
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

GRETURN BufferedInput::InitializeWindows(void * _window) {
#ifdef _WIN32
	_userWinProc = SetWindowLongPtr((HWND)_window, GWLP_WNDPROC, (LONG_PTR)GWinProc);

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
	for (unsigned int i = 0; i < nNoOfDevices; i++) {

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
	rID[0].hwndTarget = (HWND)_window;

	//Mouse
	rID[1].usUsagePage = 0x01;
	rID[1].usUsage = 0x02;
	rID[1].dwFlags = RIDEV_NOLEGACY;
	rID[1].hwndTarget = (HWND)_window;

	if (RegisterRawInputDevices(rID, 2, sizeof(rID[0])) == false) {
		//std::cout << "\n\n*******************\nRegistering Devices Failed.\n*******************\n";
	}
#endif
}

GRETURN BufferedInput::InitializeLinux(void * data) {

#ifdef __linux__
	memcpy(&_linuxWindow, data, 64);
	XSelectInput(_linuxWindow.Display, _linuxWindow.Window, ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyReleaseMask | KeyPressMask);
#endif
}

GRETURN BufferedInput::InitializeMac(void * hWnd) {

}

GRETURN BufferedInput::Update() {

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

}

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

			unsigned int _event = 0;
			unsigned short state = 0;
			unsigned int code = 0;

			if (raw->header.dwType == RIM_TYPEKEYBOARD)
			{
				//Set Code
				code = raw->data.keyboard.VKey;
				
				//Set state released or pressed.
				state = raw->data.keyboard.Flags;
			}
			else if (raw->header.dwType == RIM_TYPEMOUSE)
			{
				//Set Code
				code = raw->data.keyboard.VKey;

				switch (code) {
				//Mouse Pressed
				case 1:
				case 4:
				case 32:
					state = KeyPressed;
					break;
				//Mouse Released
				case 2:
				case 8:
				case 16:
					state = KeyReleased;
					break;
				}

			}
			std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin;
			for (; iter != _listeners.end(); ++iter) {
				iter->first->OnEvent(GBufferedInputUUIID, state, &_event);
			}


			delete[] lpb;
		}
		break;


		default:
			return CallWindowProcW((WNDPROC)_userWinProc, window, msg, wp, lp);
			break;
		}
	}
#endif

}