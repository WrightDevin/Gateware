#include "../../Source/G_System/GI_Callback.cpp"


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
	int GetKeyState(int _keyCode);
	int GetButtonState(int _buttonCode);
	GRETURN GetMouseDelta(float &x, float &y);
	GRETURN GetMousePosition(float &x, float &y);
	float GetMouseScroll();


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
