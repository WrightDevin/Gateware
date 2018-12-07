// Override export symbols for DLL builds (must be included before interface code).
#include "../../Source/DLL_Export_Symbols.h"
#include "../../Interface/G_System/GController.h"

#include <mutex>
#include <atomic>
#include <thread>
#include <map>

#ifdef _WIN32
#include <windows.h>
#include <xinput.h>
//#include <direct.h>

#pragma comment(lib, "XInput.lib")
#endif // _WIN32

#define MAX_CONTROLLER_INDEX 16
#define MAX_XBOX_CONTROLLER_INDEX 4
#define MAX_GENENRAL_INPUTS 20 // Can change
#define MAX_XBOX_INPUTS 20
#define MAX_PS4_INPUTS 20

using namespace GW;
using namespace CORE;
using namespace SYSTEM;

//temp move globals to an included file look at GBI AND GWINDOW
//! Map of Listeners to send event information to. 
namespace
{
	std::map<GListener *, unsigned long long> listeners;

	struct CONTROLLER_STATE
	{
		int isConnected;
		int maxInputs; // Hold the size of controllerInputs array
		float* controllerInputs; // controllerInputs is used to hold an array for the input values of the controller
	};

	unsigned int FindEmptyControllerIndex(unsigned int maxIndex, const CONTROLLER_STATE* controllers)
	{
		for (unsigned int i = 0; i < maxIndex; ++i)
		{
			if (controllers[i].isConnected == 0)
				return i;
		}
		return -1;
	}


}
//end

class GeneralController : public GController
{
protected:
	std::atomic<unsigned int> referenceCount;
	std::atomic<bool> isRunning;
	std::mutex controllersMutex;
	std::mutex listenerMutex;
	

	// Lock before using
	CONTROLLER_STATE* controllers;

public:
	//GeneralController
	GeneralController();
	virtual ~GeneralController();

	virtual void Init();

	// GController
	virtual GReturn GetState(int _controllerIndex, int _inputCode, float& _outState);
	virtual GReturn IsConnected(int _controllerIndex, bool& _outIsConnected);
	virtual GReturn GetMaxIndex(int &_outMax);
	virtual GReturn GetNumConnected(int &_outConnectedCount);

	// GBroadcasting
	GReturn RegisterListener(GListener* _addListener, unsigned long long _eventMask);
	GReturn DeregisterListener(GListener* _removeListener);
	
	// GInterface
	GReturn GetCount(unsigned int& _outCount);
	GReturn IncrementCount();
	virtual GReturn DecrementCount();
	GReturn RequestInterface(const GUUIID& _interfaceID, void** _outputInterface);
};

class XboxController : public GeneralController
{
private:

	void XinputLoop();
	float XboxDeadZoneCalc(float _value, bool _isTigger);

    int XControllerSlotIndices[4];
	std::thread* xInputThread;
public:
	// XboxController
	XboxController();
	~XboxController();

	// GController
	void Init();
    GReturn GetState(int _controllerIndex, int _inputCode, float& _outState);
	GReturn GetMaxIndex(int &_outMax);
	GReturn GetNumConnected(int &_outConnectedCount);

	// GInterface
	GReturn DecrementCount();
};

GATEWARE_EXPORT_IMPLICIT GReturn CreateGController(int _controllerType, GController** _outController)
{
	return GW::SYSTEM::CreateGController(_controllerType, _outController);
}

GReturn GW::SYSTEM::CreateGController(int _controllerType, GController** _outController)
{	
	//replace with a better check for vaild _controllertype
	if(_outController == nullptr || (_controllerType >> 12) < 0 || (_controllerType >> 12) > 0xFF)
		return INVALID_ARGUMENT;

#ifdef _WIN32
	// Add cases for each supported controller for _WIN32
	switch (_controllerType)
	{
	case G_GENERAL_CONTROLLER: // not truly supported until directinput is added
	{

#ifdef _WIN32
		return FEATURE_UNSUPPORTED;
#elif
		
		GeneralController* genController = new GeneralController;
		if (genController == nullptr)
			return FAILURE;
		(*_outController) = genController;
#endif // !_WIN32

		
		break;
	}
	case G_XBOX_CONTROLLER:
	{
		XboxController* xController = new XboxController;
		if (xController == nullptr)
			return FAILURE;
		xController->Init();
		(*_outController) = xController;
		break;
	}
	default:
	{
		return FEATURE_UNSUPPORTED;
	}
	}
#elif __linux__
	// Add  cases for each supported controller for Linux
	return FEATURE_UNSUPPORTED;
#elif __APPLE__
	// Add  cases for each supported controller for Mac
	return FEATURE_UNSUPPORTED;
#endif


	return SUCCESS;
	
}

// GeneralController

GeneralController::GeneralController()
{
	referenceCount = 1;
	isRunning = true;
}

GeneralController::~GeneralController()
{

}

void GeneralController::Init()
{
	controllers = new CONTROLLER_STATE[MAX_CONTROLLER_INDEX];
	for (unsigned int i = 0; i < MAX_CONTROLLER_INDEX; ++i)
	{
	controllers[i].isConnected = 0;
	controllers[i].maxInputs = MAX_GENENRAL_INPUTS;
	controllers[i].controllerInputs = new float[MAX_GENENRAL_INPUTS];
	}
}

GReturn GeneralController::GetState(int _controllerIndex, int _inputCode, float& _outState)
{
	return FAILURE;
}

GReturn GeneralController::IsConnected(int _controllerIndex, bool& _outIsConnected)
{
	if (_controllerIndex < 0 || _controllerIndex >= MAX_CONTROLLER_INDEX)
		return INVALID_ARGUMENT;

	controllersMutex.lock();

	_outIsConnected = controllers[_controllerIndex].isConnected == 0 ? false : true;

	controllersMutex.unlock();

	return SUCCESS;
}

GReturn GeneralController::GetMaxIndex(int &_outMax)
{
	_outMax = MAX_CONTROLLER_INDEX;
	return SUCCESS;
}

GReturn GeneralController::GetNumConnected(int &_outConnectedCount)
{
	_outConnectedCount = 0;
	for (unsigned int i = 0; i < MAX_CONTROLLER_INDEX; ++i)
	{
		if (controllers[i].isConnected)
			++_outConnectedCount;
	}
	return SUCCESS;
}

GReturn GeneralController::RegisterListener(GListener* _addListener, unsigned long long _eventMask)
{
	if (_addListener == nullptr) {
		return INVALID_ARGUMENT;
	}

	listenerMutex.lock();

	std::map<GListener*, unsigned long long>::const_iterator iter = listeners.find(_addListener);
	if (iter != listeners.end()) {
		return REDUNDANT_OPERATION;
	}

	listeners[_addListener] = _eventMask;
	_addListener->IncrementCount();

	listenerMutex.unlock();

	return SUCCESS;
}

GReturn GeneralController::DeregisterListener(GListener* _removeListener)
{
	if (_removeListener == nullptr) {
		return INVALID_ARGUMENT;
	}

	listenerMutex.lock();

	std::map<GListener*, unsigned long long>::const_iterator iter = listeners.find(_removeListener);
	if (iter != listeners.end()) {
		iter->first->DecrementCount();
		listeners.erase(iter);
		listenerMutex.unlock();
	}
	else {
		listenerMutex.unlock();
		return FAILURE;
	}

	return SUCCESS;
}

GReturn GeneralController::GetCount(unsigned int& _outCount)
{
	_outCount = referenceCount;

	return SUCCESS;
}

GReturn GeneralController::IncrementCount()
{
	if (referenceCount == 0xFFFFFFFF)
		return FAILURE;

	referenceCount += 1;

	return SUCCESS;
}

GReturn GeneralController::DecrementCount()
{
	if (referenceCount == 0)
		return FAILURE;

	referenceCount -= 1;

	if (referenceCount == 0)
	{
		isRunning = false;
		
		// handle destruction
		delete this;
	}

	return SUCCESS;
}

GReturn GeneralController::RequestInterface(const GUUIID& _interfaceID, void** _outputInterface)
{
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	if (_interfaceID == SYSTEM::GControllerUUIID)
	{
		GController* convert = reinterpret_cast<GController*>(this);
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

// XboxController

XboxController::XboxController()
{

	for (int i = 0; i < 4; ++i)
		XControllerSlotIndices[i] = -1;
}
XboxController::~XboxController()
{

}

void XboxController::Init()
{
	controllers = new CONTROLLER_STATE[MAX_XBOX_CONTROLLER_INDEX];
	for (unsigned int i = 0; i < MAX_XBOX_CONTROLLER_INDEX; ++i)
	{
		controllers[i].isConnected = 0;
		controllers[i].maxInputs = MAX_XBOX_INPUTS;
		controllers[i].controllerInputs = new float[MAX_XBOX_INPUTS];
	}
#ifdef _WIN32
	xInputThread = new std::thread(&XboxController::XinputLoop, this);
	//xInputThread->detach();
#endif // _WIN32
}

GReturn XboxController::GetMaxIndex(int &_outMax)
{
	_outMax = MAX_XBOX_CONTROLLER_INDEX;
	return SUCCESS;
}

GReturn XboxController::GetState(int _controllerIndex, int _inputCode, float& _outState)
{
	if (_controllerIndex < 0 || _controllerIndex > MAX_XBOX_CONTROLLER_INDEX || (_inputCode & 0xFF000) != G_XBOX_CONTROLLER || ((_inputCode & 0xFF) < 0 && (_inputCode & 0xFF) > 19))
		return INVALID_ARGUMENT;
	if (controllers->isConnected == 0)
		return FAILURE;

	_outState = controllers[_controllerIndex].controllerInputs[(_inputCode & 0xff)];

	return SUCCESS;
}

GReturn XboxController::GetNumConnected(int &_outConnectedCount)
{
	_outConnectedCount = 0;
	for (unsigned int i = 0; i < MAX_XBOX_CONTROLLER_INDEX; ++i)
	{
		if (controllers[i].isConnected)
			++_outConnectedCount;
	}
	return SUCCESS;
}

float XboxController::XboxDeadZoneCalc(float _value, bool _isTigger)
{
	return 0.0f;
}

void XboxController::XinputLoop()
{
	DWORD result;
	XINPUT_STATE controllerState;
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	while (isRunning)
	{
		for (int i = 0; i < 4; ++i)
		{
			result = XInputGetState(i, &controllerState);
			if (result == ERROR_SUCCESS)
			{
				if (XControllerSlotIndices[i] < 0)
				{
					controllersMutex.lock();

					XControllerSlotIndices[i] = FindEmptyControllerIndex(MAX_XBOX_CONTROLLER_INDEX, controllers);
					controllers[XControllerSlotIndices[i]].isConnected = 1;

					controllersMutex.unlock();
				}
					

				if (XControllerSlotIndices[i] >= 0) // add checks for events
				{
					controllersMutex.lock();

					// Buttons
					controllers[XControllerSlotIndices[i]].controllerInputs[G_SOUTH_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_EAST_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_NORTH_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_WEST_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_LEFT_SHOULDER_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_RIGHT_SHOULDER_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_DPAD_LEFT_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_DPAD_RIGHT_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_DPAD_UP_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_DPAD_DOWN_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_LEFT_THUMB_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_RIGHT_THUMB_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_START_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0 ? 1.0f : 0.0f;
					controllers[XControllerSlotIndices[i]].controllerInputs[G_SELECT_BTN] = (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0 ? 1.0f : 0.0f;
					// AXES
					controllers[XControllerSlotIndices[i]].controllerInputs[G_LEFT_TRIGGER_AXIS] = XboxDeadZoneCalc(controllerState.Gamepad.bLeftTrigger, true);
					controllers[XControllerSlotIndices[i]].controllerInputs[G_RIGHT_TRIGGER_AXIS] = XboxDeadZoneCalc(controllerState.Gamepad.bRightTrigger, true);
					controllers[XControllerSlotIndices[i]].controllerInputs[G_LX_AXIS] = XboxDeadZoneCalc(controllerState.Gamepad.sThumbLX, false);
					controllers[XControllerSlotIndices[i]].controllerInputs[G_LY_AXIS] = XboxDeadZoneCalc(controllerState.Gamepad.sThumbLY, false);
					controllers[XControllerSlotIndices[i]].controllerInputs[G_RX_AXIS] = XboxDeadZoneCalc(controllerState.Gamepad.sThumbRX, false);
					controllers[XControllerSlotIndices[i]].controllerInputs[G_RY_AXIS] = XboxDeadZoneCalc(controllerState.Gamepad.sThumbRY, false);

					controllersMutex.unlock();
				}
			}
			else // no controller connected
			{
				if (XControllerSlotIndices[i] >= 0)
				{
					controllers[XControllerSlotIndices[i]].isConnected = 0;
					XControllerSlotIndices[i] = -1;
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

GReturn XboxController::DecrementCount()
{
	if (referenceCount == 0)
		return FAILURE;

	referenceCount -= 1;

	if (referenceCount == 0)
	{
		// handle destruction
		isRunning = false;
		xInputThread->join();
		
		delete this;
	}

	return SUCCESS;
}