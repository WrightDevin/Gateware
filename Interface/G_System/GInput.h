#ifndef GINPUT_H
#define GINPUT_H

/*
File: GInput.h
Purpose: A Gateware interface that handles high-speed keyboard and mouse input.
Author: Peter Farber
Contributors: N/A
Last Modified: 2/1/2017
Interface Status: Beta
Copyright: 7thGate Software LLC.
License: MIT
*/

#include "../G_Core/GSingleThreaded.h"
#include "../G_System/GKeyDefines.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all Gateware library interfaces must belong.
	namespace SYSTEM
	{
		//! Unique Identifier for this interface. {D68B715F-E73B-44C6-8A7F-97ECC8EB9905}
		static const GUUIID GInputUUIID =
		{
			0xd68b715f, 0xe73b, 0x44c6,{ 0x8a, 0x7f, 0x97, 0xec, 0xc8, 0xeb, 0x99, 0x5 } 
		};


		//! A single threaded input library.
		/*!
		*	The single thread input library is used for high speed game input.
		*	You can use this library to get any mouse or keyboard input.
		*/
		class GInput : public CORE::GSingleThreaded
		{

		public:

			//! Get the current state of any key.
			/*!
			*
			*	Use keycodes in GKeyDefines as input to this function to check the state
			*	of a particular key or button.
			*
			*	\param [in] _keyCode The key code of the key to check.
			*	\param [out] errorCode If function fails this will hold the errorCode.
			*
			*	\retval 0 The Key is not pressed.
			*	\retval 1 The Key is pressed.
			*/
			virtual float GetState(int _keyCode, GReturn* errorCode = nullptr) = 0;

			//! Get the change in mouse position.
			/*!
			* 
			*	\param [out] x a reference to a float to store the mouse delta position x.
			*	\param [out] y a reference to a float to store the mouse delta position y.
			*
			*	\retval SUCCESS no problems found. Values stored in x and y.
			*/
			virtual GReturn GetMouseDelta(float& x, float& y) = 0;

			//! Get the most recent mouse position.
			/*!
			*
			*	\param [out] x a reference to a float to store the mouse position x.
			*	\param [out] y a reference to a float to store the mouse position y.
			*
			*	\retval SUCCESS no problems found. Values stored in x and y.
			*/
			virtual GReturn GetMousePosition(float& x, float& y) = 0;



			//! Get the key mask.
			/*!
			*	The key mask lets the input object know which of the functions below are  
			*	active by manipulating individual bits of an unsigned int.
			*
			*	\retval G_MASK (_SHIFT, _CONTROL, _CAPS_LOCK, _NUM_LOCK, _SCROLL_LOCK).
			*/
			virtual unsigned int GetKeyMask() = 0;
		};

		//! Creates a GInput Object.
		/*!
		*	Initializes a window based on the void* data passed in. The created 
		*	Created GInput object will have its reference count initialized to one.
		*
		*	\param [out] _outInput Will contain the GInput object if successfully created.
		*	\param [in] data (Windows) The handle to the window (HWND).
		*	\param [in] data (Linux) LINUX_WINDOW data.
		*	\param [in] data (Max) NSWindow data.
		*
		*	\retval SUCCESS no problems found.
		*	\retval FAILURE could not make an Input Object.
		*	\retval INVALID_ARGUMENT _outInput and or data is nullptr.
		*/
		GATEWARE_EXPORT_IMPLICIT GReturn CreateGInput(GInput** _outInput, void * data);
	} // end SYSTEM namespace
} // end GW namespace

#endif