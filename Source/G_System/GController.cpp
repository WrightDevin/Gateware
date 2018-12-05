// Override export symbols for DLL builds (must be included before interface code).
#include "../../Source/DLL_Export_Symbols.h"
#include "../../Interface/G_System/GController.h"

#include <mutex>
#include <atomic>
#include <thread>
#include <map>

#define MAX_CONTROLLER_INDEX 16
#define MAX_XBOX_CONTROLLER_INDEX 4

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
}
//end

class GeneralController : public GController
{
private:
	std::atomic<unsigned int> referenceCount;
	std::mutex mutex;

protected:
	CONTROLLER_STATE* controllers;

public:
	//GeneralController
	GeneralController();
	virtual ~GeneralController();

	GReturn CreateGeneralController(GController** _outController);

	// GController
	GReturn GetState(int _controllerIndex, int _inputCode, float& _outState);
	GReturn IsConnected(int _controllerIndex, bool& _outIsConnected);
	GReturn GetMaxIndex(int &_outMax);
	GReturn GetNumConnected(int &_outConnectedCount);

	// GBroadcasting
	GReturn RegisterListener(GListener* _addListener, unsigned long long _eventMask);
	GReturn DeregisterListener(GListener* _removeListener);
	
	// GInterface
	GReturn GetCount(unsigned int& _outCount);
	GReturn IncrementCount();
	GReturn DecrementCount();
	GReturn RequestInterface(const GUUIID& _interfaceID, void** _outputInterface);
};

GATEWARE_EXPORT_IMPLICIT GReturn CreateGController(int _controllerType, GController** _outController)
{
	return GW::SYSTEM::CreateGController(_controllerType, _outController);
}

GReturn GW::SYSTEM::CreateGController(int _controllerType, GController** _outController)
{	
	//replace with a better check for vaild _controllertype
	if(_outController == nullptr || (_controllerType != G_GENERAL_CONTROLLER && _controllerType != G_XBOX_CONTROLLER && _controllerType != G_PS4_CONTROLLER))
		return INVALID_ARGUMENT;

#ifdef _WIN32
	// Add cases for each supported controller for _WIN32
	switch (_controllerType)
	{
	case G_GENERAL_CONTROLLER: // not truly supported until directinput is added
	{
		GeneralController* genController = new GeneralController;
		if (genController == nullptr)
			return FAILURE;
		(*_outController) = genController;
		break;
	}
	default:
	{
		return FEATURE_UNSUPPORTED;
	}
	}
#elif __linux__
	// Add  cases for each supported controller for Linux
#elif __APPLE__
	// Add  cases for each supported controller for Mac
#endif


	return SUCCESS;
	
}

// GeneralController

GeneralController::GeneralController()
{
	referenceCount = 1;

	controllers = new CONTROLLER_STATE[MAX_CONTROLLER_INDEX];
	for (unsigned int i = 0; i < MAX_CONTROLLER_INDEX; ++i)
	{
		controllers[i].isConnected = 0;
		// create inputs for controller
	}
}

GeneralController::~GeneralController()
{

}

GReturn GeneralController::CreateGeneralController(GController** _outController)
{
	return FAILURE;
}

GReturn GeneralController::GetState(int _controllerIndex, int _inputCode, float& _outState)
{
	return FAILURE;
}

GReturn GeneralController::IsConnected(int _controllerIndex, bool& _outIsConnected)
{
	if (_controllerIndex < 0 || _controllerIndex >= MAX_CONTROLLER_INDEX)
		return INVALID_ARGUMENT;

	_outIsConnected = controllers->isConnected == 0 ? false : true;

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

	mutex.lock();

	std::map<GListener*, unsigned long long>::const_iterator iter = listeners.find(_addListener);
	if (iter != listeners.end()) {
		return REDUNDANT_OPERATION;
	}

	listeners[_addListener] = _eventMask;
	_addListener->IncrementCount();

	mutex.unlock();

	return SUCCESS;
}

GReturn GeneralController::DeregisterListener(GListener* _removeListener)
{
	if (_removeListener == nullptr) {
		return INVALID_ARGUMENT;
	}

	mutex.lock();

	std::map<GListener*, unsigned long long>::const_iterator iter = listeners.find(_removeListener);
	if (iter != listeners.end()) {
		iter->first->DecrementCount();
		listeners.erase(iter);
		mutex.unlock();
	}
	else {
		mutex.unlock();
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