// Override export symbols for DLL builds (must be included before interface code)
#include "../DLL_Export_Symbols.h"

#ifndef __APPLE__
#include "../../Source/G_System/GI_Callback.cpp"
#endif

#include <mutex>
#include <atomic>
#include <thread>
#include <cstring>
#include <iostream>
#include <time.h>

class Input : public SYSTEM::GInput {

private:

	/* GInterface */

	void * hWnd;

	unsigned int m_referenceCount;

	std::atomic_bool m_threadOpen;

	std::thread * m_inputThread;

#ifdef _WIN32
#elif __linux__
	LINUX_WINDOW _linuxWindow;
#elif __APPPLE__

#endif

public:

	/* Input */

	Input();
	virtual ~Input();

	void InputThread();

	GRETURN InitializeWindows(void * _data);
	GRETURN InitializeLinux(void * _data);
	GRETURN InitializeMac(void * _data);

	/* GInput */

	float GetState(int _keyCode, GRETURN * errorCode);
	GRETURN GetMouseDelta(float &x, float &y);
	GRETURN GetMousePosition(float &x, float &y);
	unsigned int GetKeyMask();

	/* GInterface */

	GRETURN GetCount(unsigned int &_outCount);
	GRETURN IncrementCount();
	GRETURN DecrementCount();
	GRETURN RequestInterface(const GUUIID &_interfaceID, void** _outputInterface);
};

// This is an DLL exported version of the create function, the name is not mangled for explicit linking.
GATEWARE_EXPORT_EXPLICIT GRETURN CreateGInput(GW::SYSTEM::GInput** _outPointer, void * _data)
{
	// This is NOT a recursive call, this is a call to the actual C++ name mangled version below
	return GW::SYSTEM::CreateGInput(_outPointer, _data);
}

GRETURN GW::SYSTEM::CreateGInput(GInput** _outFpointer, void * _data) {

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


	//Todo call my intialize
	(*_outFpointer) = _mInput;

	return SUCCESS;

}

Input::Input() {
	m_referenceCount = 1;
}

Input::~Input() {

}

GRETURN Input::GetCount(unsigned int &_outCount) {

	_outCount = m_referenceCount;

	return SUCCESS;
}

GRETURN Input::IncrementCount() {

	m_referenceCount += 1;

	return SUCCESS;
}

GRETURN Input::DecrementCount() {

	m_referenceCount -= 1;

	if (m_referenceCount == 0) {
		delete this;
	}

	return SUCCESS;
}

GRETURN Input::RequestInterface(const GUUIID &_interfaceID, void** _outputInterface) {
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	if (_interfaceID == SYSTEM::GInputUUIID)
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

	}

	//Getting Raw Input Devices. #include <time.h>

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

	//For all of the devices, display their correspondent information.
	for (int i = 0; i < nNoOfDevices; i++) {

		UINT size = 256;
		TCHAR tBuffer[256] = { 0 };
		tBuffer[0] = '\0';


		//Find the device name.
		if (GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, tBuffer, &size) < 0) {

		}

		UINT cbSize = rdi.cbSize;
		//Get the device information.
		if (GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &rdi, &cbSize) < 0) {

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
	}

	//Capslock
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) {
		TURNON_BIT(_keyMask, G_MASK_CAPS_LOCK);
	}

	//Numlock
	if ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) {
		TURNON_BIT(_keyMask, G_MASK_NUM_LOCK);
	}

	//ScrollLock
	if ((GetKeyState(VK_SCROLL) & 0x0001) != 0) {
		TURNON_BIT(_keyMask, G_MASK_SCROLL_LOCK);
	}
#endif

	return SUCCESS;
}

GRETURN Input::InitializeLinux(void * _data) {

#ifdef __linux__
	//Copy _data into a LINUX_WINDOW(void * display, void * window) structure.
	memcpy(&_linuxWindow, _data, sizeof(LINUX_WINDOW));
	Display * _display;
	//Cast the void* _linuxWindow._Display to a display pointer to pass to XSelectInput.
	_display = (Display *)(_linuxWindow._Display);
	//Copy void* _linuxWindow._Window into a Window class to pass to XSelectInput.
	memcpy(&_window, _linuxWindow._Window, sizeof(_window));
	//Select the type of Input events we wish to recieve.
	//XSelectInput(_display, _window, ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyReleaseMask | KeyPressMask | LockMask | ControlMask | ShiftMask);

#endif

    ///XAutoRepeatOff(_display);

	//Set our thread to open.
	m_threadOpen = true;
	//Create the Linux Input thread.
	m_inputThread = new std::thread(&Input::InputThread, this);

	return SUCCESS;

}

GRETURN Input::InitializeMac(void * _data) {

#ifdef __APPLE__

    //Need to convert data back into an NSWindow*
    NSWindow * currentResponder = ((__bridge NSWindow*)_data);

    //We only want to process the message and pass it on. So if there is already     <--- (Already what? - Nic Russell)
    //so we set the our responders next responder to be the current next responder
    [responder setNextResponder:currentResponder.nextResponder];

    //We then set out responder to the next responder of the window
    [currentResponder setNextResponder:responder];

    //We also need to make our responder the first responder of the window
    [currentResponder makeFirstResponder:responder];

    //In order to get mouse button presses we need to set our responder to be
    //The next responder in the contentView as well
    [currentResponder.contentView setNextResponder:responder];


#endif

	return SUCCESS;
}

float Input::GetState(int _keyCode, GRETURN * errorCode) {

	if (errorCode != nullptr) {
		*errorCode = GRETURN::SUCCESS;
		if (_keyCode == G_MOUSE_SCROLL_DOWN || _keyCode == G_MOUSE_SCROLL_UP) {
			*errorCode = GRETURN::FEATURE_UNSUPPORTED;
		}
	}

	return (float)n_Keys[_keyCode];

}

GRETURN Input::GetMouseDelta(float &x, float &y) {

	x = _mouseDeltaX;
	y = _mouseDeltaY;

	return SUCCESS;
}

GRETURN Input::GetMousePosition(float &x, float &y) {

	x = _mousePositionX;
	y = _mousePositionY;

	return SUCCESS;
}

unsigned int Input::GetKeyMask() {
	return _keyMask;
}

void Input::InputThread()
{

#ifdef __linux__
	int _code = -1;

	while (_threadOpen)
	{
        //Cast the void* _linuxWindow. _Display to a display pointer to pass to XNextEvent.
		Display * _display = (Display*)(_linuxWindow._Display);
		char keys_return[32];
        XQueryKeymap(_display, keys_return);
        for(unsigned int i = 0; i < 128; i++){
            _code = Keycodes[i][1];
            if(keys_return[(i >> 3)] & (1 << (i & 7))){
                n_Keys[_code] = 1;
            }else{
                n_Keys[_code] = 0;
            }
        }


        Window a, b;
        XQueryPointer(_display, _window, &a, &b, &_mouseScreenPositionX, &_mouseScreenPositionY, &_mousePositionX, &_mousePositionY, &_keyMask);
        //printf("KeyMask: %d\n", _keyMask);

        if(_keyMask & Button1Mask){
            //printf("Left\n");
            n_Keys[G_BUTTON_LEFT];

        }
        if(_keyMask & Button3Mask){
            //printf("Right\n");
            n_Keys[G_BUTTON_RIGHT];
        }

        if(_keyMask & Button2Mask){
            //printf("Middle\n");
            n_Keys[G_BUTTON_MIDDLE];
        }

	    timespec delay = { 0, 3333333 }; // 300Hz
	    //while(nanosleep(&delay, &delay)); // Throttle thread to 300Hz

        //Set the change in mouse position.
        _mouseDeltaX = _mousePrevX - _mousePositionX;
        _mouseDeltaY = _mousePrevY - _mousePositionY;

        //Set the previous mouse position as the current.
        _mousePrevX = _mousePositionX;
        _mousePrevY = _mousePositionY;


	}
#endif

}


