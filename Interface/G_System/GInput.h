#ifndef _GINPUT_H
#define _GINPUT_H

/*
File: GInput.h
Purpose: A Gateware interface that handles high-speed keyboard and mouse input (placeholder description, written by Nic Russell) 
Author: ?????????
Contributors: N/A
Last Modified: ????????????
Copyright: 7thGate Software LLC.
License: MIT
*/

#include "../G_Core/GSingleThreaded.h"
#include "../G_System/GKeyDefines.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong
namespace GW
{
	//! The core namespace to which all Gateware fundamental interfaces must belong.
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
			*	of a particular key or button
			*
			*	\param [in] _keyCode The key code of the key to check
			*	\param [out] errorCode If function fails this will hold the errorCode
			*
			*	\retval 0 The Key is not pressed.
			*	\retval 1 The Key is pressed.
			*/
			virtual float GetState(int _keyCode, GRETURN * errorCode = nullptr) = 0;

			//! Get the change in mouse position.
			/*!
			* 
			*	\param [out] x a reference to a float to store the mouse delta position x.
			*	\param [out] y a reference to a float to store the mouse delta position y.
			*
			*	\retval SUCCESS no problems found. Values stored in x and y
			*/
			virtual GRETURN GetMouseDelta(float &x, float &y) = 0;

			//! Get the most recent mouse position.
			/*!
			*
			*	\param [out] x a reference to a float to store the mouse position x.
			*	\param [out] y a reference to a float to store the mouse position y.
			*
			*	\retval SUCCESS no problems found. Values stored in x and y
			*/
			virtual GRETURN GetMousePosition(float &x, float &y) = 0;



			//! Get the key mask.
			/*!
			*	The key mask lets the input object know which of the functions below are  
			*	active by manipulating individual bits of an unsigned int
			*
			*	\retval G_MASK (_SHIFT, _CONTROL, _CAPS_LOCK, _NUM_LOCK, _SCROLL_LOCK).
			*/
			virtual unsigned int GetKeyMask() = 0;
		};

		//! Creates a GInput Object.
		/*!
		*	Initializes a window based on the void* data passed in. The created 
		*	GInput object will have its reference count initialized to one.
		*
		*	\param [out] _outInput
		*	\param [in] _data (Windows) The handle to the window (HWND).
		*	\param [in] _data (Linux) Not Yet Implemented.
		*	\param [in] _data (Max) Not Yet Implemented.
		*
		*	\retval SUCCESS no problems found.
		*	\retval FAILURE could not make an Input Object.
		*	\retval INVALID_ARGUMENT _outInput and or _data is nullptr.
		*/
		GATEWARE_EXPORT_IMPLICIT GRETURN CreateGInput(GInput** _outInput, void * _data);
	} // end SYSTEM namespace
} // end GW namespace

#endif