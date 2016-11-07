#include "../../Interface/G_System/GInput.h"; 
#include <map>

using namespace GW;
using namespace CORE;

class Input : public GInput {

private:

	/* GInterface */

	//! Total number of active refrences to this object. 
	unsigned int n_refrenceCount;

	/* GInput */

	//! Type KeyCode    Reserved  
	//! 000	 000000000  20 Reserved bits.
	unsigned int n_Keys[256];


public:

	/* Input */

	Input();
	~Input();

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

