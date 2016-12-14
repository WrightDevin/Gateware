#include "../../Source/G_System/GI_Callback.cpp"
#include <mutex>
#include <atomic>
#include <thread>
#include <cstring>

class Input : public GInput {

private:

	/* GInterface */

	//! Total number of active refrences to this object.
	unsigned int n_refrenceCount;
	void * hWnd;

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

	//GRETURN Update();
	int GetKeyState(int _keyCode);
	int GetButtonState(int _buttonCode);
	GRETURN GetMouseDelta(float &x, float &y);
	GRETURN GetMousePosition(float &x, float &y);
	float GetMouseScroll();
	unsigned int GetKeyMask();


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
	memcpy(&_linuxWindow, _data, sizeof(LINUX_WINDOW));
	Display * _display;
	_display = (Display *)(_linuxWindow._Display);
	Window _window;
	memcpy(&_window, _linuxWindow._Window, sizeof(_window));
	XSelectInput(_display, _window, ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyReleaseMask | KeyPressMask | LockMask | ControlMask | ShiftMask);
#endif

	_threadOpen = true;
	_inputThread = new std::thread(&Input::InputThread, this);

	return SUCCESS;

}

GRETURN Input::InitializeMac(void * _data) {

	return SUCCESS;
}

int Input::GetKeyState(int _keyCode) {

	return n_Keys[_keyCode];

}

int Input::GetButtonState(int _buttonCode) {
	return n_Keys[_buttonCode];
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

float Input::GetMouseScroll() {

	float direction = 0;
	if (n_Keys[G_MOUSE_SCROLL_UP]) {
		direction = -1;
	}
	else if(n_Keys[G_MOUSE_SCROLL_DOWN]){
		direction = 1;
	}
	return direction;
}


unsigned int Input::GetKeyMask() {
	return _keyMask;
}

void Input::InputThread()
{
	int _code = -1;
	while (_threadOpen)
	{
#ifdef __linux__
		XEvent e;

		Display * _display = (Display*)(_linuxWindow._Display);

		XNextEvent(_display, &e);
		switch (e.type) {
		case KeyPress:
			_code = Keycodes[e.xkey.keycode][1];
			n_Keys[_code] = 1;
			//_event = KEYPRESSED;
			_keyMask = e.xkey.state;
			_mousePositionX = e.xkey.x;
			_mousePositionY = e.xkey.y;
			_mouseDeltaX = e.xkey.x_root;
			_mouseDeltaY = e.xkey.x_root;
			break;
		case KeyRelease:
			_code = Keycodes[e.xkey.keycode][1];
			n_Keys[_code] = 0;
			//_event = KEYRELEASED;
			_keyMask = e.xkey.state;
			_mousePositionX = e.xkey.x;
			_mousePositionY = e.xkey.y;
			_mouseDeltaX = e.xkey.x_root;
			_mouseDeltaY = e.xkey.x_root;
			break;
		case ButtonPress:
			_code = e.xbutton.button;
			//_event = BUTTONPRESSED;
			_keyMask = e.xkey.state;
			_mousePositionX = e.xkey.x;
			_mousePositionY = e.xkey.y;
			_mouseDeltaX = e.xkey.x_root;
			_mouseDeltaY = e.xkey.x_root;
			n_Keys[_code] = 1;
			break;
		case ButtonRelease:
			_code = e.xbutton.button;
			//_event = BUTTONRELEASED;
			_keyMask = e.xkey.state;
			_mousePositionX = e.xkey.x;
			_mousePositionY = e.xkey.y;
			_mouseDeltaX = e.xkey.x_root;
			_mouseDeltaY = e.xkey.x_root;
			n_Keys[_code] = 0;

			break;
		}

		if (e.type == ButtonPress || e.type == ButtonRelease) {

			switch (_code) {
			case 1:
				_code = G_BUTTON_LEFT;
				break;
			case 3:
				_code = G_BUTTON_RIGHT;
				break;
			case 2:
				_code = G_BUTTON_MIDDLE;
				break;
			case 4:
				_code = G_MOUSE_SCROLL_UP;
				break;
			case 5:
				_code = G_MOUSE_SCROLL_DOWN;
				break;
			default:
				_code = -1;
				break;
			}

		}

		if (_code != G_MOUSE_SCROLL_UP) {
			n_Keys[G_MOUSE_SCROLL_UP] = 0;
		}
		if (_code != G_MOUSE_SCROLL_DOWN) {
			n_Keys[G_MOUSE_SCROLL_DOWN] = 0;
		}

		_mouseDeltaX = _mousePrevX - _mousePositionX;
		_mouseDeltaY = _mousePrevY - _mousePositionY;

		_mousePrevX = _mousePositionX;
		_mousePrevY = _mousePositionY;

#endif
	}
}
