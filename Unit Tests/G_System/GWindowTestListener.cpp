#include "GWindowTestListener.h"
#include "../Unit Tests/Common.h"
#include <cstring>

//Used to test the broadcasting of GWindow
int windowTestValue = 0;

GW::GReturn GWindowTestListener::OnEvent(const GW::GUUIID &_senderInterface, unsigned int _eventID, void *_eventData, unsigned int _sizeOfData)
{
	if (_senderInterface == GW::SYSTEM::GWindowUUIID)
	{
		GW::SYSTEM::GWINDOW_EVENT_DATA data;
		memcpy(&data, _eventData, _sizeOfData);

		switch (_eventID)
		{
		case GW::SYSTEM::NOTIFY:
			break;

		case GW::SYSTEM::MINIMIZE:
			break;

		case GW::SYSTEM::MAXIMIZE:
			windowTestValue = 1;
			break;

		case GW::SYSTEM::RESIZE:
			windowTestValue = 1;
			break;

		case GW::SYSTEM::MOVE:
			break;

		case GW::SYSTEM::DESTROY:
			break;
		}
	}
	else
		return GW::FAILURE;

	return GW::SUCCESS;
}

//GInterface overrides
GW::GReturn GWindowTestListener::GetCount(unsigned int& _outCount)
{
	_outCount = m_refCount;
	return GW::SUCCESS;
}

GW::GReturn GWindowTestListener::IncrementCount()
{
	//May wanna do some testing to ensure ref count is not going to overflow
	++m_refCount;

	return GW::SUCCESS;
}

GW::GReturn GWindowTestListener::DecrementCount()
{
	//May wanna do some testing to ensure ref count is not going to underflow
	--m_refCount;

	return GW::SUCCESS;
}

GW::GReturn GWindowTestListener::RequestInterface(const GW::GUUIID& _interfaceID, void** _outputInterface)
{
	//NOT IMPLEMENTED
	return GW::SUCCESS;
}

int GWindowTestListener::GetWindowTestValue()
{
	return windowTestValue;
}
