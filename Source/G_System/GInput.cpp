#ifndef __APPLE__
#include "../../Source/G_System/GI_Callback.cpp"
#endif


#include <mutex>
#include <atomic>
#include <thread>
#include <cstring>
#include <iostream>

class Input : public GInput {

private:

	/* GInterface */

	void * hWnd;

	unsigned int n_refrenceCount;

	std::atomic_bool _threadOpen;

	std::thread * _inputThread;

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

GRETURN GW::CORE::CreateGInput(GInput** _outFpointer, void * _data) {

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
	//Cast the void* _linuxWidnow._Display to a display pointer to pass to XSelectInput.
	_display = (Display *)(_linuxWindow._Display);
	Window _window;
	//Copy void* _linuxWindow._Window into a Window class to pass to XSelectInput.
	memcpy(&_window, _linuxWindow._Window, sizeof(_window));
	//Select the type of Input events we wish to recieve.
	XSelectInput(_display, _window, ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyReleaseMask | KeyPressMask | LockMask | ControlMask | ShiftMask);
#endif

	//Set our thread to open.
	_threadOpen = true;
	//Create the Linux Input thread.
	_inputThread = new std::thread(&Input::InputThread, this);

	return SUCCESS;

}

GRETURN Input::InitializeMac(void * _data) {

#ifdef __APPLE__
    
	//Create an NSReponder *. (NSResponder is the class that we use to recieve events on mac).
	NSResponder * windowResponder = [NSResponder alloc];
	//Cast the _data(NSWindow) to a NSReponder. (NSWindow Derives From NSResponder).
	windowResponder = (__bridge NSResponder *)_data;
	//Set the next responder to the our Responder(GResponder) responder is declared in GBI_Callback.cpp.
	//Setting the nextResponder allows us to piggy back on the events being sent to the main program.
	//So we get a copy of the original events.
	windowResponder.nextResponder = responder;

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
		//To store the current event from XNextEvent.
		XEvent e;

		//Cast the void* _linuxWidnow._Display to a display pointer to pass to XNextEvent.
		Display * _display = (Display*)(_linuxWindow._Display);

		//Gets the next event and removes it from the queue.
		XNextEvent(_display, &e);

		//Check what type of event it is ( KeyPress, KeyRelease, ButtonPress, ButtonRelease).
		switch (e.type) {
		case KeyPress:
			//Get the keycode from the static table of G_KEYS.
			_code = Keycodes[e.xkey.keycode][1];
			//Set the key in the buffer of keys to 1 for pressed.
			n_Keys[_code] = 1;
			//Set the keymask to check if(CapsLock, NumLock, Shift, Control, etc...) are currently on.
			_keyMask = e.xkey.state;
			//Set the cursor position relative to the window.
			_mousePositionX = e.xkey.x;
			_mousePositionY = e.xkey.y;
			//Set the cursor position relative to the screen.
			_mouseDeltaX = e.xkey.x_root;
			_mouseDeltaY = e.xkey.y_root;
			break;
		case KeyRelease:
			_code = Keycodes[e.xkey.keycode][1];
			n_Keys[_code] = 0;
			_keyMask = e.xkey.state;
			_mousePositionX = e.xkey.x;
			_mousePositionY = e.xkey.y;
			_mouseDeltaX = e.xkey.x_root;
			_mouseDeltaY = e.xkey.y_root;
			break;
		case ButtonPress:
			_code = e.xbutton.button;
			_keyMask = e.xkey.state;
			_mousePositionX = e.xkey.x;
			_mousePositionY = e.xkey.y;
			_mouseDeltaX = e.xkey.x_root;
			_mouseDeltaY = e.xkey.y_root;

			//Check the code and set the corresponding button to pressed.
            switch (_code) {
			case 1:
				 n_Keys[G_BUTTON_LEFT] = 1;
				break;
			case 2:
                n_Keys[G_BUTTON_MIDDLE] = 1;
				break;
			case 3:
                n_Keys[G_BUTTON_RIGHT] = 1;
				break;
			}
			break;
		case ButtonRelease:
			_code = e.xbutton.button;
			_keyMask = e.xkey.state;
			_mousePositionX = e.xkey.x;
			_mousePositionY = e.xkey.y;
			_mouseDeltaX = e.xkey.x_root;
			_mouseDeltaY = e.xkey.y_root;

			//Check the code and set the corresponding button to released.
            switch (_code) {
			case 1:
				 n_Keys[G_BUTTON_LEFT] = 0;
				break;
			case 2:
                n_Keys[G_BUTTON_MIDDLE] = 0;
				break;
			case 3:
                n_Keys[G_BUTTON_RIGHT] = 0;
				break;
			}
			break;
		}

		//Set the change in mouse position.
		_mouseDeltaX = _mousePrevX - _mousePositionX;
		_mouseDeltaY = _mousePrevY - _mousePositionY;

		//Set the previous mouse position as the current.
		_mousePrevX = _mousePositionX;
		_mousePrevY = _mousePositionY;

	}
#endif

}
