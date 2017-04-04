// Override export symbols for DLL builds (must be included before interface code)
#include "../DLL_Export_Symbols.h"

#ifndef __APPLE__
#include "../../Source/G_System/GBI_Callback.cpp"
#endif

#include <mutex>
#include <atomic>
#include <queue>
#include <thread>
#include <iostream>
#include <cstring>

class BufferedInput : public GBufferedInput {

private:

	//The atomic value is for thread safety.(Like a mutex without using a mutex).
	std::atomic<unsigned int> referenceCount;

	std::atomic_bool threadOpen;

	std::thread* inputThread;

	std::mutex mutex;

#ifdef _WIN32
#elif __linux__
	LINUX_WINDOW _linuxWindow;
#elif __APPLE__

#endif

public:

	BufferedInput();
	virtual ~BufferedInput();

	void InputThread();


	GReturn InitializeWindows(void * data);
	GReturn InitializeLinux(void * data);
	GReturn InitializeMac(void * data);

	GReturn GetCount(unsigned int &_outCount);
	GReturn IncrementCount();
	GReturn DecrementCount();
	GReturn RequestInterface(const GUUIID &_interfaceID, void** _outputInterface);
	GReturn RegisterListener(GListener *_addListener, unsigned long long _eventMask);
	GReturn DeregisterListener(GListener *_removeListener);

};


BufferedInput::BufferedInput() {
	referenceCount = 1;
}

BufferedInput::~BufferedInput() {

}

GReturn BufferedInput::GetCount(unsigned int &_outCount) {

	_outCount = referenceCount;

	return SUCCESS;
}

GReturn BufferedInput::IncrementCount() {

	referenceCount += 1;

	return SUCCESS;
}

GReturn BufferedInput::DecrementCount() {

	referenceCount -= 1;

	if (referenceCount == 0) {

#ifdef __linux__
		_threadOpen = false;
		_inputThread->join();
		delete _inputThread;
#endif
		delete this;
	}

	return SUCCESS;
}

GReturn BufferedInput::RequestInterface(const GUUIID &_interfaceID, void** _outputInterface) {
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	if (_interfaceID == SYSTEM::GBufferedInputUUIID)
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

GReturn BufferedInput::RegisterListener(GListener *_addListener, unsigned long long _eventMask) {

	if (_addListener == nullptr) {
		return INVALID_ARGUMENT;
	}

	mutex.lock();

	std::map<GListener *, unsigned long long>::const_iterator iter = _listeners.find(_addListener);
	if (iter != _listeners.end()) {
		return REDUNDANT_OPERATION;
	}

	_listeners[_addListener] = _eventMask;
	IncrementCount();

	mutex.unlock();

	return SUCCESS;

}

GReturn BufferedInput::DeregisterListener(GListener *_removeListener) {

	if (_removeListener == nullptr) {
		return INVALID_ARGUMENT;
	}
	mutex.lock();
	std::map<GListener *, unsigned long long>::const_iterator iter = _listeners.find(_removeListener);
	if (iter != _listeners.end()) {
		_listeners.erase(iter);
		mutex.unlock();
		DecrementCount();
	}
	else {
		mutex.unlock();
		return FAILURE;
	}

	return SUCCESS;
}

// This is an DLL exported version of the create function, the name is not mangled for explicit linking.
GATEWARE_EXPORT_EXPLICIT GReturn CreateGBufferedInput(GBufferedInput** _outPointer, void * data)
{
	// This is NOT a recursive call, this is a call to the actual C++ name mangled version below
	return GW::SYSTEM::CreateGBufferedInput(_outPointer, data);
}

GReturn GW::SYSTEM::CreateGBufferedInput(GBufferedInput** _outPointer, void * data) {


	if (_outPointer == nullptr || data == nullptr) {
		return INVALID_ARGUMENT;
	}

	BufferedInput * _mInput = new BufferedInput();

	if (_mInput == nullptr) {
		return FAILURE;
	}

#ifdef _WIN32
	_mInput->InitializeWindows(data);
#elif __APPLE__
	_mInput->InitializeMac(_data);
#elif __linux__
	_mInput->InitializeLinux(_data);
#endif

	(*_outPointer) = _mInput;

	return SUCCESS;

}

GReturn BufferedInput::InitializeWindows(void * data) {

#ifdef _WIN32

	keyMask = 0;
	_userWinProc = SetWindowLongPtr((HWND)data, GWLP_WNDPROC, (LONG_PTR)GWinProc);

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
	//Using the new List and number of devices,
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
	rID[0].hwndTarget = (HWND)data;

	//Mouse
	rID[1].usUsagePage = 0x01;
	rID[1].usUsage = 0x02;
	rID[1].dwFlags = RIDEV_NOLEGACY;
	rID[1].hwndTarget = (HWND)data;

	if (RegisterRawInputDevices(rID, 2, sizeof(rID[0])) == false) {

	}

	//Capslock
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) {
		TURNON_BIT(keyMask, G_MASK_CAPS_LOCK);
	}

	//Numlock
	if ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) {
		TURNON_BIT(keyMask, G_MASK_NUM_LOCK);
	}

	//ScrollLock
	if ((GetKeyState(VK_SCROLL) & 0x0001) != 0) {
		TURNON_BIT(keyMask, G_MASK_SCROLL_LOCK);
	}
#endif



	return SUCCESS;
}

GReturn BufferedInput::InitializeLinux(void * data) {

#ifdef __linux__
	//Copy data into a LINUX_WINDOW(void * display, void * window) structure.
    memcpy(&_linuxWindow, _data, sizeof(LINUX_WINDOW));
    Display * _display;
	//Cast the void* _linuxWindow.display to a display pointer to pass to XSelectInput.
    _display = (Display *)(_linuxWindow._Display);
	//Copy void* _linuxWindow.window into a Window class to pass to XSelectInput.
    memcpy(&_window, _linuxWindow._Window, sizeof(_window));
	//Select the type of Input events we wish to receive.
	//XSelectInput(_display, _window, ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyReleaseMask | KeyPressMask | LockMask | ControlMask | ShiftMask);
#endif

	//Set our thread to open.
    threadOpen = true;
	//Create the Linux Input thread.
	inputThread = new std::thread(&BufferedInput::InputThread, this);



	return SUCCESS;

}

GReturn BufferedInput::InitializeMac(void * data) {

#ifdef __APPLE__
    //Need to convert data back into an NSWindow*
    NSWindow * currentResponder = ((__bridge NSWindow*)_data);

	//We only want to process the message and pass it on. So if there is already   
	//a responder we set our responders next responder to be the current next responder
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

void BufferedInput::InputThread()
{
#ifdef __linux__
    int _event = -1;
    int _code = -1;
    G_INPUT_DATA _dataStruct;

	while (_threadOpen)
	{

        std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();

        Display * _display = (Display*)_linuxWindow._Display;

        Window a, b;
        XQueryPointer(_display, _window, &a, &b, &_dataStruct._screenX, &_dataStruct._screenY, &_dataStruct._x, &_dataStruct._y, &_dataStruct._keyMask);
        //printf("Pos ( %d, %d), Mask: (%d)\n", screenx, screeny, mask);

        char keys_return[32];
        //Get the current state of all keys
        XQueryKeymap(_display, keys_return);
        //Loop through all the keys and check to see if they match the saved state of all the keys.
        for(unsigned int i = 5; i < 126; i++){
            _code = Keycodes[i][1];
            _dataStruct._data = _code;
            //Save the state of current key.
            unsigned int key = keys_return[(i >>3)] & (1 << (i & 7));
            //If a key does not match send an event saying it has been updated.
            if(key != n_Keys[_code]){
                if(key == 0){
                    _event = KEYPRESSED;
                }else{
                    _event = KEYRELEASED;
                }
                printf("%d\n", _code);
                //Send the event to all registered listeners.
                for (; iter != _listeners.end(); ++iter) {
                    iter->first->OnEvent(GBufferedInputUUIID, _event, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
                }
            }
            n_Keys[_code] = key;
        }

        if(_dataStruct._keyMask & Button1Mask){
            if(!n_Keys[G_BUTTON_LEFT]){
                _dataStruct._data = G_BUTTON_LEFT;
                _event = BUTTONPRESSED;
                n_Keys[G_BUTTON_LEFT] = 1;
                for (; iter != _listeners.end(); ++iter) {
                    iter->first->OnEvent(GBufferedInputUUIID, _event, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
                }
            }
        }else{
            if(n_Keys[G_BUTTON_LEFT] ){
                _dataStruct._data = G_BUTTON_LEFT;
                _event = BUTTONRELEASED;
                n_Keys[G_BUTTON_LEFT] = 0;
                for (; iter != _listeners.end(); ++iter) {
                    iter->first->OnEvent(GBufferedInputUUIID, _event, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
                }
            }
        }
        if(_dataStruct._keyMask & Button3Mask){
            if(!n_Keys[G_BUTTON_RIGHT]){
                _dataStruct._data = G_BUTTON_RIGHT;
                _event = BUTTONPRESSED;
                n_Keys[G_BUTTON_RIGHT] = 1;
                for (; iter != _listeners.end(); ++iter) {
                    iter->first->OnEvent(GBufferedInputUUIID, _event, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
                }
            }
        }else{
            if(n_Keys[G_BUTTON_RIGHT]){
                _dataStruct._data = G_BUTTON_RIGHT;
                _event = BUTTONRELEASED;
                n_Keys[G_BUTTON_RIGHT] = 0;
                for (; iter != _listeners.end(); ++iter) {
                    iter->first->OnEvent(GBufferedInputUUIID, _event, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
                }
            }
        }
        if(_dataStruct._keyMask & Button2Mask){
            if(!n_Keys[G_BUTTON_MIDDLE]){
                _dataStruct._data = G_BUTTON_MIDDLE;
                _event = BUTTONPRESSED;
                n_Keys[G_BUTTON_MIDDLE] = 1;
                for (; iter != _listeners.end(); ++iter) {
                    iter->first->OnEvent(GBufferedInputUUIID, _event, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
                }
            }
        }else{
            if(n_Keys[G_BUTTON_MIDDLE]){
                _dataStruct._data = G_BUTTON_MIDDLE;
                _event = BUTTONRELEASED;
                n_Keys[G_BUTTON_MIDDLE] = 0;
                for (; iter != _listeners.end(); ++iter) {
                    iter->first->OnEvent(GBufferedInputUUIID, _event, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
                }
            }
        }

        printf("Keymask: %d \n", _dataStruct._keyMask);


	}
#endif

}
