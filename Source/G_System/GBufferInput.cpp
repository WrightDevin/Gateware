#include "../../Source/G_System/GBI_Static.cpp"
#include <mutex> 
#include <atomic>
#include <queue>
#include <thread>


class BufferedInput : public GBufferedInput {

private:


	std::atomic_uint32_t n_refrenceCount;

	std::atomic_bool _threadOpen;

	std::thread * _inputThread;

	std::mutex _Mutex;



#ifdef _WIN32
#elif __linux__
	LINUX_WINDOW _linuxWindow;
#elif __APPPLE__

#endif

public:

	BufferedInput();
	~BufferedInput();

	void InputThread();


	GRETURN InitializeWindows(void * _data);
	GRETURN InitializeLinux(void * _data);
	GRETURN InitializeMac(void * _data);

	GRETURN GetCount(unsigned int &_outCount);
	GRETURN IncrementCount();
	GRETURN DecrementCount();
	GRETURN RequestInterface(const GUUIID &_interfaceID, void** _outputInterface);
	GRETURN RegisterListener(GListener *_addListener, unsigned long long _eventMask);
	GRETURN DeregisterListener(GListener *_removeListener);

};


BufferedInput::BufferedInput() {
	n_refrenceCount = 1;
}

BufferedInput::~BufferedInput() {

}

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
		_threadOpen = false;
		_inputThread->join();
		delete _inputThread;
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

GRETURN BufferedInput::RegisterListener(GListener *_addListener, unsigned long long _eventMask) {

	if (_addListener == nullptr) {
		return INVALID_ARGUMENT;
	}

	_Mutex.lock();

	std::map<GListener *, unsigned long long>::const_iterator iter = _listeners.find(_addListener);
	if (iter != _listeners.end()) {
		return REDUNDENT_OPERATION;
	}

	_listeners[_addListener] = _eventMask;
	IncrementCount();

	_Mutex.unlock();

	return SUCCESS;

}

GRETURN BufferedInput::DeregisterListener(GListener *_removeListener) {
	if (_removeListener == nullptr) {
		return INVALID_ARGUMENT;
	}
	_Mutex.lock();
	std::map<GListener *, unsigned long long>::const_iterator iter = _listeners.find(_removeListener);
	if (iter != _listeners.end()) {
		_listeners.erase(iter);
		_Mutex.unlock();
		DecrementCount();
	}
	else {
		_Mutex.unlock();
		return FAILURE;
	}


	return SUCCESS;
}




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

	(*_outPointer) = _mInput;

	return SUCCESS;

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

	_inputThread = new std::thread(&BufferedInput::InputThread, this);

	_threadOpen = true;

	return SUCCESS;

}

GRETURN BufferedInput::InitializeMac(void * _data) {

	return SUCCESS;
}



void BufferedInput::InputThread()
{
	unsigned int _event = 0;
	unsigned int _code = 0;
	unsigned short _state = 0;
	while (_threadOpen)
	{
#ifdef __linux__
		XEvent e;

		XPeekEvent(_linuxWindow.Display, &e);
		switch (e.type) {
		case KeyPress:
			_code = e.xkey.keycode;
			_state = KEYPRESSED;
			break;
		case KeyRelease:
			_code = e.xkey.keycode;
			_state = KEYRELEASED;
			break;
		case ButtonPress:
			_code = e.xbutton.button;
			_state = KEYPRESSED;
			break;
		case ButtonRelease:
			_code = e.xbutton.button;
			_state = KEYRELEASED;
			break;
		}

		std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin;
		for (; iter != _listeners.end(); ++iter) {
			iter->first->OnEvent(GBufferedInputUUIID, state, &_event);
		}
#endif
	}
}