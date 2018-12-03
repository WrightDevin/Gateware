// Override export symbols for DLL builds (must be included before interface code).
#include "../../Source/DLL_Export_Symbols.h"
#include "../../Interface/G_System/GController.h"


using namespace GW;
using namespace CORE;
using namespace SYSTEM;


class GeneralController : public GController
{
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
	return FAILURE;
}

// GeneralController

GeneralController::GeneralController()
{

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
	return FAILURE;
}

GReturn GeneralController::GetMaxIndex(int &_outMax)
{
	return FAILURE;
}

GReturn GeneralController::GetNumConnected(int &_outConnectedCount)
{
	return FAILURE;
}

GReturn GeneralController::RegisterListener(GListener* _addListener, unsigned long long _eventMask)
{
	return FAILURE;
}

GReturn GeneralController::DeregisterListener(GListener* _removeListener)
{
	return FAILURE;
}

GReturn GeneralController::GetCount(unsigned int& _outCount)
{
	return FAILURE;
}

GReturn GeneralController::IncrementCount()
{
	return FAILURE;
}

GReturn GeneralController::DecrementCount()
{
	return FAILURE;
}

GReturn GeneralController::RequestInterface(const GUUIID& _interfaceID, void** _outputInterface)
{
	return FAILURE;
}