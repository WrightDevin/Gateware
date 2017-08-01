#ifndef TESTLISTENER_H
#define TESTLISTENER_H

#include <G_Core/GListener.h>
#include <atomic>

extern bool keys[256]; //Will be used to keep track of whether keys were pressed or released

//Used to keep track of what the library says my mouse position is
extern int mouseX;
extern int mouseY;
extern int windowTestValue;

class TestListener : public GW::CORE::GListener
{
	//Needed for reference counting. ALL GATEWARE LIBRARY OBJECTS ARE REF COUNTED.
	std::atomic<unsigned int> m_refCount;

public:
  TestListener():m_refCount(1){};
  virtual ~TestListener() {};

  //GListener overrides
  GW::GReturn OnEvent(const GW::GUUIID &_senderInterface, unsigned int _eventID, void *_eventData, unsigned int _sizeOfData);

  //GInterface overrides
  GW::GReturn GetCount(unsigned int &_outCount);
  GW::GReturn IncrementCount();
  GW::GReturn DecrementCount();
  GW::GReturn RequestInterface(const GW::GUUIID &_interfaceID, void** _outputInterface);

  //Helper function for testing
  int GetWindowTestValue();
};

#endif // TESTLISTENER_H
