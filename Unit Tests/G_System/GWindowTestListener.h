#ifndef GWINDOWTESTLISTENER_H
#define GWINDOWTESTLISTENER_H

#include <G_Core/GListener.h>
#include <atomic>

extern int windowTestValue;

class GWindowTestListener : public GW::CORE::GListener
{
	//Needed for reference counting. ALL GATEWARE LIBRARY OBJECTS ARE REF COUNTED.
	std::atomic<unsigned int> m_refCount;


public:

    std::atomic<unsigned int> m_testsPending;

	GWindowTestListener() :m_refCount(1), m_testsPending(0) {};
	virtual ~GWindowTestListener() {};

	//GListener overrides
	GW::GReturn OnEvent(const GW::GUUIID &_senderInterface, unsigned int _eventID, void *_eventData, unsigned int _sizeOfData);

	//GInterface overrides
	GW::GReturn GetCount(unsigned int &_outCount);
	GW::GReturn IncrementCount();
	GW::GReturn DecrementCount();
	GW::GReturn RequestInterface(const GW::GUUIID &_interfaceID, void** _outputInterface);

	//Helper function for testing
	GW::GReturn GetWindowTestValue(int& _outWindowTestValue);

};

#endif // TESTLISTENER_H
