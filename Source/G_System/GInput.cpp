<<<<<<< HEAD
#include "../../Interface/G_System/GInput.h"; 
#include <map>
=======
#include "../../Interface/G_System/GInput.h";
>>>>>>> PeterFarber

using namespace GW;
using namespace CORE;

class Input : public GInput {

private:

	/* GInterface */

<<<<<<< HEAD
	//! Total number of active refrences to this object. 
=======
	//! Total number of active refrences to this object.
>>>>>>> PeterFarber
	unsigned int n_refrenceCount;

	/* GInput */

<<<<<<< HEAD

	//! Type 3 bits KeyCode 9 bits (512 Unique)    Reserved 20 bits 
	//! 000			00000000-0					   00000000-00000000-0000
	unsigned int n_Keys[512];
=======
	//! Type KeyCode  Flags
	//! 0000 00000000 0000
	short n_Keys[256];

>>>>>>> PeterFarber


public:

	/* Input */

	Input();
	~Input();

<<<<<<< HEAD
	GRETURN Initialize();

	/* GInput */

	GRETURN GetKeyState(int _keyCode, int &_keyState);

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
};

GRETURN CreateGInput(GInput** _outFpointer, void * _hWnd) {

	if (_outFpointer == nullptr) {
		return INVALID_ARGUMENT;
	}

	Input * _mInput = new Input();

	if (_mInput == nullptr) {
		return FAILURE;
	}

	//Todo call my intiialize

	

}

=======
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
>>>>>>> PeterFarber

Input::Input() {
	n_refrenceCount = 1;
}

Input::~Input() {

}

<<<<<<< HEAD

GRETURN Input::GetCount(unsigned int &_outCount) {

	_outCount = n_refrenceCount;

=======
GRETURN Input::GetCount(unsigned int &_outCount) {
	
	_outCount = n_refrenceCount;
	
>>>>>>> PeterFarber
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
<<<<<<< HEAD
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	if (_interfaceID == GInputUUIID)
	{
		GInput * convert = reinterpret_cast<GInput*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GSingleThreadedUUIID)
	{
		GSingleThreaded* convert = reinterpret_cast<GSingleThreaded*>(this);
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

=======

}


GRETURN RegisterListener(GListener *_addListener, unsigned long long _eventMask) {

}

GRETURN DeregisterListener(GListener *_removeListener) {

}
>>>>>>> PeterFarber
