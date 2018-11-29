// Override export symbols for DLL builds (must be included before interface code).
#include "../../Source/DLL_Export_Symbols.h"
#include "../../Interface/G_System/GController.h"


using namespace GW;
using namespace CORE;
using namespace SYSTEM;

// input code key defines

// input codes
#define G_SOUTH_BTN 0x00
#define G_EAST_BTN 0x01
#define G_NORTH_BTN 0x02
#define G_WEST_BTN 0x03
#define G_LEFT_SHOULDER_BTN 0x04
#define G_RIGHT_SHOULDER_BTN 0x05
#define G_LEFT_TRIGGER_AXIS 0x06
#define G_RIGHT_TRIGGER_AXIS 0x07
#define G_DPAD_LEFT_BTN 0x08
#define G_DPAD_RIGHT_BTN 0x09
#define G_DPAD_UP_BTN 0x0A
#define G_DPAD_DOWN_BTN 0x0B
#define G_LEFT_THUMB_BTN 0x0C
#define G_RIGHT_THUMB_BTN 0x0D
#define G_START_BTN 0x0E
#define G_SELECT_BTN 0x0F
#define G_LX_AXIS 0x10
#define G_LY_AXIS 0x11
#define G_RX_AXIS 0x12
#define G_RY_AXIS 0x13

// Axis || Button
#define G_BUTTON 0x0
#define G_AXIS 0x1

// end input code key defines

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