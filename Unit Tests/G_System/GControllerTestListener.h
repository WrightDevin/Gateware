#ifndef GCONTROLLERLISTERNER_H
#define GCONTROLLERLISTERNER_H

#include <G_Core/GListener.h>
#include <atomic>

struct CONTROLLER_STATE
{
	int isConnected;
	float southBTN;
	float dpadDown;
	float leftShoulder;
	float rightThumb;
	float LX;
	float LY;
	float leftTrigger;
	float rightTrigger;
	float start;
};

extern CONTROLLER_STATE event_controllers[4]; // Used to keep track of controller data from events

class GControllerTestListener : public GW::CORE::GListener
{
	//Needed for reference counting. ALL GATEWARE LIBRARY OBJECTS ARE REF COUNTED.
	std::atomic<unsigned int> m_refCount;

public:
	GControllerTestListener() :m_refCount(1) {};
	virtual ~GControllerTestListener() {};

	//GListener overrides
	GW::GReturn OnEvent(const GW::GUUIID &_senderInterface, unsigned int _eventID, void *_eventData, unsigned int _sizeOfData);

	//GInterface overrides
	GW::GReturn GetCount(unsigned int &_outCount);
	GW::GReturn IncrementCount();
	GW::GReturn DecrementCount();
	GW::GReturn RequestInterface(const GW::GUUIID &_interfaceID, void** _outputInterface);
};
#endif // !GCONTROLLERLISTERNER_H
