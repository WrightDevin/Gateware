#include "GControllerTestListener.h"
#include "../Unit Tests/Common.h"
#include "G_System\GControllerInputDefines.h"

CONTROLLER_STATE event_controllers[4];

GW::GReturn GControllerTestListener::OnEvent(const GW::GUUIID &_senderInterface, unsigned int _eventID, void *_eventData, unsigned int _sizeOfData)
{
	if (_senderInterface == GW::SYSTEM::GControllerUUIID)
	{
		GW::SYSTEM::GCONTROLLER_EVENT_DATA data;
		memcpy(&data, _eventData, _sizeOfData);
		switch (_eventID)
		{
		case GW::SYSTEM::CONTROLLERBUTTONPRESSED:
		{
			switch (data.inputCode & 0xFF)
			{
			case G_SOUTH_BTN:
			{
				event_controllers[data.controllerIndex].southBTN = data.inputValue;
				break;
			}
			case G_DPAD_DOWN_BTN:
			{
				event_controllers[data.controllerIndex].dpadDown = data.inputValue;
				break;
			}
			case G_LEFT_SHOULDER_BTN:
			{
				event_controllers[data.controllerIndex].leftShoulder = data.inputValue;
				break;
			}
			case G_RIGHT_THUMB_BTN:
			{
				event_controllers[data.controllerIndex].rightThumb = data.inputValue;
				break;
			}
			case G_START_BTN:
			{
				event_controllers[data.controllerIndex].start = data.inputValue;
			}
			}
			break;
		}
		case GW::SYSTEM::CONTROLLERBUTTONRELEASED:
		{
			switch (data.inputCode & 0xFF)
			{
			case G_SOUTH_BTN:
			{
				event_controllers[data.controllerIndex].southBTN = data.inputValue;
				break;
			}
			case G_DPAD_DOWN_BTN:
			{
				event_controllers[data.controllerIndex].dpadDown = data.inputValue;
				break;
			}
			case G_LEFT_SHOULDER_BTN:
			{
				event_controllers[data.controllerIndex].leftShoulder = data.inputValue;
				break;
			}
			case G_RIGHT_THUMB_BTN:
			{
				event_controllers[data.controllerIndex].rightThumb = data.inputValue;
				break;
			}
			case G_START_BTN:
			{
				event_controllers[data.controllerIndex].start = data.inputValue;
			}
			}
			break;
		}
		case GW::SYSTEM::CONTROLLERAXISVALUECHANGED:
		{
			switch (data.inputCode & 0xFF)
			{
			case G_LX_AXIS:
			{
				event_controllers[data.controllerIndex].LX = data.inputValue;
				break;
			}
			case G_LY_AXIS:
			{
				event_controllers[data.controllerIndex].LY = data.inputValue;
				break;
			}
			case G_LEFT_TRIGGER_AXIS:
			{
				event_controllers[data.controllerIndex].leftTrigger = data.inputValue;
				break;
			}
			case G_PS4_RIGHT_TRIGGER_AXIS:
			{
				event_controllers[data.controllerIndex].rightTrigger = data.inputValue;
				break;
			}
			}
			break;
		}
		case GW::SYSTEM::CONTROLLERCONNECTED:
		{
			event_controllers[data.controllerIndex].isConnected = data.isConnected;
			break;
		}
		case GW::SYSTEM::CONTROLLERDISCONNECTED:
		{
			event_controllers[data.controllerIndex].isConnected = data.isConnected;
			break;
		}

		}


		return GW::SUCCESS;
	}
	else
		return GW::FAILURE;
}

//GInterface overrides
GW::GReturn GControllerTestListener::GetCount(unsigned int& _outCount)
{
	_outCount = m_refCount;
	return GW::SUCCESS;
}

GW::GReturn GControllerTestListener::IncrementCount()
{
	//May wanna do some testing to ensure ref count is not going to overflow
	if (m_refCount == 0xFFFFFFFF)
		return GW::FAILURE;
	++m_refCount;

	return GW::SUCCESS;
}

GW::GReturn GControllerTestListener::DecrementCount()
{
	//May wanna do some testing to ensure ref count is not going to underflow
	if (m_refCount == 0) {
		return GW::FAILURE;
	}
	--m_refCount;

	if (m_refCount == 0) {
		delete this;
	}

	return GW::SUCCESS;
}

GW::GReturn GControllerTestListener::RequestInterface(const GW::GUUIID& _interfaceID, void** _outputInterface)
{
	//NOT IMPLEMENTED
	return GW::SUCCESS;
}