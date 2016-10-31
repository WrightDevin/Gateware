#include "../../Interface/G_System/GInput.h"; 

using namespace GW;
using namespace CORE;

class Input : public GInput {

private:

	/* GInterface */

	//! Total number of active refrences to this object. 
	unsigned int n_refrenceCount;

	/* GInput */

	//! Type KeyCode  Flags 
	//! 0000 00000000 0000 
	short n_Keys[256];



public:

	/* Input */

	Input();
	~Input();

	/* GInput */


	/* GInterface */

	//! Return the total number of active refrences to this object 
	GRETURN GetCount(unsigned int &_outCount);

	//! Increase the total number of active refrences to this object 
	//! End users should only call this operation if they are familiar with reference counting behavior 
	GRETURN IncrementCount();

	//! Decrease the total number of active refrences to this object 
	//! Once the internal count reaches zero this object will be deallocated and your pointer will become invalid 
	GRETURN DecrementCount();

	//! Requests an interface that may or may not be supported by this object  
	GRETURN RequestInterface(const GUUIID &_interfaceID, void** _outputInterface);


	/* GBroadcasting */

	//! Any listener added to this class must receive all events unless otherwise specified by the _eventMask (optional) 
	//! Listeners registered to a broadcaster will have their refrence counts increased by one until deregistered 
	GRETURN RegisterListener(GListener *_addListener, unsigned long long _eventMask);

	//! A successfully deregistered listener will no longer receive events and have it's refrence count decremented by one  
	GRETURN DeregisterListener(GListener *_removeListener);

};

Input::Input() {
	n_refrenceCount = 1;
}

Input::~Input() {

}

GRETURN Input::GetCount(unsigned int &_outCount) {

	_outCount = n_refrenceCount;

	return SUCCESS;
}

GRETURN Input::IncrementCount() {

	n_refrenceCount += 1;

	return SUCCESS;
}

GRETURN Input::DecrementCount() {

	n_refrenceCount -= 1;

	if (n_refrenceCount == 0) {
		delete this;
	}

	return SUCCESS;
}

GRETURN Input::RequestInterface(const GUUIID &_interfaceID, void** _outputInterface) {

}


GRETURN RegisterListener(GListener *_addListener, unsigned long long _eventMask) {

}

GRETURN DeregisterListener(GListener *_removeListener) {

}