#ifndef GCONTROLLER_H
#define GCONTROLLER_H

/*!
File: GController.h
Purpose: A Gateware interface handles controller input and provides disconnection and connection events
Author: Devin Wright
Contributors: N/A
Last Modified: 11/29/2018
Interface Status: Pre-Alpha
Copyright: 7thGate Software LLC.
License: MIT
*/

//! GController inherits directly from GBroadcasting.
#include "../G_Core/GBroadcasting.h"
#include "../G_System/GControllerInputDefines.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all Gateware library interfaces must belong.
	namespace SYSTEM
	{


//! Ensure identical binary padding for structures on all platforms.
#pragma pack(push, 1)

		//! GCONTROLLER_EVENT_DATA will hold the information about a controller event 
		/*
		*	If the corresponding event is an Input Event inputCode and inputValue will contain the input code and value 
		*	respectively for the detected input. If the corresponding event is an Connection event inputCode and inputValue will be 0. 
		*	
		*/
		struct GCONTROLLER_EVENT_DATA
		{
			int controllerIndex; /*!< The Controller index where the event took place */ 
			int inputCode;		 /*!< The Code repsenting the Detected input */
			float inputValue;	 /*!< The value of the detected input */
			bool isConnected	 /*!< Value indicating whether the controller is connected */
		};
#pragma pack(pop)

		//! GControllerEvents holds the possible events that can be sent from GController
		enum GControllerEvents
		{
			BUTTONPRESSED,			/*!< Input event for button press */
			BUTTONRELEASED,			/*!< Input event for button released */
			AXISVALUECHANGED,		/*!< Input event for axis value changed */
			CONTROLLERCONNECTED,	/*!< Connection event for a controller being connected */
			CONTROLLERDISCONNECTED	/*!< Connection event for a controller being disconnected */
		};

		//! Unique Identifier for this interface. {ABD3CB16-4210-4CC6-B0D0-AD0FFCC7E2D2}
		static const GUUIID GControllerUUIID = 
		{
			0xabd3cb16, 0x4210, 0x4cc6,{ 0xb0, 0xd0, 0xad, 0xf, 0xfc, 0xc7, 0xe2, 0xd2 } 
		};
		//! A multi-threaded controller input library.
		/*!
		*	This library can be used to poll the current state of connected controllers.
		*	The controllers are assigned indices in a array for the lifetime that they are connected.
		*	It also provides events for controller connections and disconnections,
		*	which a GListener can be writen to receive.
		*/
		class GController : public CORE::GBroadcasting
		{
		public:
			//! Used to poll the current state of a button or axis on a controller
			/*
			*	Use an Inputcode to check the state of a button or axis on the controller
			*	at the selected index. If a button is being checked the _outState will be 0 for 
			*	up and 1 for down. If a axis is being checked the _outState will be between -1 and 1 inclusively.
			*
			*	\param [in] _controllerIndex The controller index to check
			*	\param [in] _inputCode The input code for the button/axis to check
			*	\param [out] _outState Is a reference to a float to store the state.
			*
			*	\retval SUCCESS The button/axis state was was successfully stored in the out-param
			*	\retval FAILURE	No controller is connected at the chosen index.
			*	\retval INVALID_ARGUMENT Ether _controllerIndex is out of range or _inputCode is invaild. 
			*/
			virtual GReturn GetState(int _controllerIndex, int _inputCode, float& _outState) = 0;

			//! Used to check if a controller is connected at a specified index
			/*
			*	\param [in] _controllerIndex The controller index to check.
			*	\param [out] _outIsConnected Is a reference to a bool to store whether a controller is at the index.
			*
			*	\retval SUCCESS The out-param was successfully filled out
			*	\retval INVALID_ARGUMENT _controllerIndex was out of range.
			*/
			virtual GReturn IsConnected(int _controllerIndex, bool& _outIsConnected) = 0;

			//! Outputs the max index of the array of controllers.
			/*
			*	The controllers will be stored in a constant array where the size of the array
			*	is the maxium amnout of supported controllers.
			*
			*	\param [out] _outMax is a reference to a int to store the max index.
			*
			*	\retval SUCCESS The max index was successfully stored in the out-param
			*/
			virtual GReturn GetMaxIndex(int &_outMax) = 0;

			//! Outputs the number of controllers connected
			/*
			*	The number returned will be how many controllers are currently stored in the 
			*	controller array.
			*
			*	\param [out] _outConnectedCount is a reference to a int to store the count of connected controllers
			*
			*	\retval SUCCESS The count of connected controllers was successfully stored in the out-param
			*/
			virtual GReturn GetNumConnected(int &_outConnectedCount) = 0;

		
		} //end GController class

		//! Creates a new GController object
		/*
		*	Initializes a handle to a GConntroller object of the type specified.
		*	Created GConntroller object will have its reference count initialized to one.
		*
		*	\param [in] _controllerType The type of Controller to be supported
		*	\param [out] _outController Will contain GConntroller object if successfully created.
		*
		*	\retval SUCCESS GConntroller was successfully created
		*	\retval	FAILURE GConntroller was not created. _outController will be NULL.
		*	\retval	INVALID_ARGUMENT _controllerType is invaild or GController is NULL.
		*	\retval	FEATURE_UNSUPPORTED	_controllerType is not currently supported. _outController will be NULL.
		*/
		GATEWARE_EXPORT_IMPLICIT GReturn CreateGController(int _controllerType, GController** _outController);
	} // end of SYSTEM namespace
} // end of GW namespace
#endif 

