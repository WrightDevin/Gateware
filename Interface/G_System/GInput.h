#ifndef GINPUT_H
#define GINPUT_H

/*!
	File: GInput.h
	Purpose: A Gateware interface that handles high-speed keyboard and mouse input.
	Author: Peter Farber
	Contributors: N/A
	Last Modified: 2/1/2017
	Interface Status: Beta
	Copyright: 7thGate Software LLC.
	License: MIT
*/

//! GInput inherits directly from GSingleThreaded.
#include "../G_Core/GSingleThreaded.h"
#include "../G_System/GKeyDefines.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all Gateware library interfaces must belong.
	namespace SYSTEM
	{
		//! Unique Identifier for this interface. {C669B79D-FFE7-4A22-B382-CBC23CE012C2}
		static const GUUIID GInputUUIID =
		{
			0xc669b79d, 0xffe7, 0x4a22,{ 0xb3, 0x82, 0xcb, 0xc2, 0x3c, 0xe0, 0x12, 0xc2 }
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
			*	Use keycodes in GKeyDefines as input to this function to check the state
			*	of a particular key or button.
			*
			*	\param [in] _keyCode The key code of the key to check.
			*	\param [out] _errorCode If function fails this will hold the errorCode. (optional)
			*
			*	\retval 0 The Key is not pressed.
			*	\retval 1 The Key is pressed.
			*/
			virtual GReturn GetState(int _keyCode, float _outState) = 0;

			//! Get the change in mouse position.
			/*!
			* 
			*	\param [out] _x a reference to a float to store the mouse delta position x.
			*	\param [out] _y a reference to a float to store the mouse delta position y.
			*
			*	\retval SUCCESS no problems found. Values stored in _x and _y.
			*/
			virtual GReturn GetMouseDelta(float& _x, float& _y) = 0;

			//! Get the most recent mouse position.
			/*!
			*
			*	\param [out] _x a reference to a float to store the mouse position x.
			*	\param [out] _y a reference to a float to store the mouse position y.
			*
			*	\retval SUCCESS no problems found. Values stored in _x and _y.
			*/
			virtual GReturn GetMousePosition(float& _x, float& _y) = 0;

			//! Get the key mask.
			/*!
			*	The key mask lets the input object know which of the functions below are  
			*	active by manipulating individual bits of an unsigned int.
			*	Values for G_MASK can be found in GKeyDefines.
			*
			*	\retval G_MASK (_SHIFT, _CONTROL, _CAPS_LOCK, _NUM_LOCK, _SCROLL_LOCK).
			*/
			virtual GReturn GetKeyMask(unsigned int& _outKeyMask) = 0;
		};

		//! Creates a GInput Object.
		/*!
		*	Initializes a handle to a window based on the void* data passed in. The  
		*	created GInput object will have its reference count initialized to one.
		*
		*	\param [in] _windowHandle (Windows) The handle to the window (HWND).
		*	\param [in] _windowHandle (Linux) LINUX_WINDOW data.
		*	\param [in] _windowHandle (Mac) NSWindow data.
		*	\param [in] _handleSize The size of the handle to the window in bytes.
		*	\param [out] _outInput Will contain the GInput object if successfully created.
		*
		*	\retval SUCCESS no problems found.
		*	\retval FAILURE could not make an Input Object.
		*	\retval INVALID_ARGUMENT _outInput and or _windowHandle is nullptr.
		*/
		GATEWARE_EXPORT_IMPLICIT GReturn CreateGInput(void* _windowHandle, unsigned int _handleSize, GInput** _outInput);
	} // end SYSTEM namespace
} // end GW namespace

#endif