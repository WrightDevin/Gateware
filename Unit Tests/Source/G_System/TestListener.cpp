#include "TestListener.h"
#include "Common.h"
#include <cstring>

//GListener Overrides

bool keys[256]; //Will be used to keep track of rather keys were pressed or released

//Used to keep track of what the library says my mouse position is
int mouseX = 0;
int mouseY = 0;

//Used to test the broadcasting of GWindow
int windowTestValue = 0;

GW::GReturn TestListener::OnEvent(const GW::GUUIID &_senderInterface, unsigned int _eventID, void *_eventData, unsigned int _sizeOfData)
{
	GW::SYSTEM::GBUFFEREDINPUT_EVENT_DATA data;
	memcpy(&data, _eventData, _sizeOfData);

	switch (_eventID)
	{
	case GW::SYSTEM::KEYPRESSED:
		switch (data.data)
		{
		case G_KEY_A:
			keys['A'] = true;
			break;
		case G_KEY_S:
			keys['S'] = true;
			break;
		case G_KEY_D:
			keys['D'] = true;
			break;
		case G_KEY_W:
			keys['W'] = true;
			break;
		case G_KEY_1:
			keys['1'] = true;
			break;
		case G_KEY_2:
			keys['2'] = true;
			break;
		case G_KEY_3:
			keys['3'] = true;
			break;
		case G_KEY_4:
			keys['4'] = true;
			break;
		case G_KEY_LEFT:
			keys[0] = true;
			break;
		case G_KEY_RIGHT:
			keys[1] = true;
			break;
		case G_KEY_UP:
			keys[2] = true;
			break;
		case G_KEY_DOWN:
			keys[3] = true;
			break;
		}
		break;
	case GW::SYSTEM::KEYRELEASED:
		switch (data.data)
		{
		case G_KEY_A:
			keys['A'] = false;
			break;
		case G_KEY_S:
			keys['S'] = false;
			break;
		case G_KEY_D:
			keys['D'] = false;
			break;
		case G_KEY_W:
			keys['W'] = false;
			break;
		case G_KEY_1:
			keys['1'] = false;
			break;
		case G_KEY_2:
			keys['2'] = false;
			break;
		case G_KEY_3:
			keys['3'] = false;
			break;
		case G_KEY_4:
			keys['4'] = false;
			break;
		case G_KEY_LEFT:
			keys[0] = false;
			break;
		case G_KEY_RIGHT:
			keys[1] = false;
			break;
		case G_KEY_UP:
			keys[2] = false;
			break;
		case G_KEY_DOWN:
			keys[3] = false;
			break;
		}
		break;

		// GWindowTests uses this case to test the Broadcasting functionality
		// of the GWindow class. BUTTONPRESSED == 2 and MAXIMIZE == 2
	case GW::SYSTEM::BUTTONPRESSED:
	{
		windowTestValue = 1;
		switch (data.data)
		{
		case G_BUTTON_LEFT:
			keys[4] = true;
			break;
		case G_BUTTON_MIDDLE:
			keys[5] = true;
			break;
		case G_BUTTON_RIGHT:
			keys[6] = true;
			break;
		}
		break;
	}
	case GW::SYSTEM::BUTTONRELEASED:
		switch (data.data)
		{
		case G_BUTTON_LEFT:
			keys[4] = false;
			break;
		case G_BUTTON_MIDDLE:
			keys[5] = false;
			break;
		case G_BUTTON_RIGHT:
			keys[6] = false;
			break;
		}
		break;
	}

	mouseX = data.screenX;
	mouseY = data.screenY;

	return GW::SUCCESS;
}

//GInterface overrides
GW::GReturn TestListener::GetCount(unsigned int& _outCount)
{
	_outCount = m_refCount;
	return GW::SUCCESS;
}

GW::GReturn TestListener::IncrementCount()
{
	//May wanna do some testing to ensure ref count is not going to overflow
	++m_refCount;

	return GW::SUCCESS;
}

GW::GReturn TestListener::DecrementCount()
{
	//May wanna do some testing to ensure ref count is not going to underflow
	--m_refCount;

	return GW::SUCCESS;
}

GW::GReturn TestListener::RequestInterface(const GW::GUUIID& _interfaceID, void** _outputInterface)
{
	//NOT IMPLEMENTED
	return GW::SUCCESS;
}

int TestListener::GetWindowTestValue()
{
	return windowTestValue;
}
