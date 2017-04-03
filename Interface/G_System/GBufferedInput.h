#ifndef _GBUFFEREDINPUT_H
#define _GBUFFEREDINPUT_H
/*
	File: GKeyDefines.h
	Purpose: This Interface offers thread safe raw buffered input
	Author: Peter Farber
	Contributors: N/A
	Last Modified: 11/16/2016
	Copyright: 7thGate Software LLC.
	License: MIT
*/

#include "../G_Core/GBroadcasting.h"
#include "../G_System/GKeyDefines.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong
namespace GW
{
	//! The core namespace to which all Gateware fundamental interfaces must belong.
	namespace SYSTEM
	{

// Ensure identical binary padding for structures on all platforms
#pragma pack(push, 1)

		//! G_INPUT_DATA will hold any information you may need about an Input Event.
		struct G_INPUT_DATA
		{
			int _data;				/*!<  Data storing the key/button information. */ 
			int _x;					/*!<  Window Mouse position x when event is sent. */
			int _y;					/*!<  Window Mouse position y when event is sent. */
			int _screenX;			/*!<  Screen Mouse position x when event is sent. */
			int _screenY;			/*!<  Screen Mouse position y when event is sent. */
			unsigned int _keyMask;	/*!<  Bit flags for (CapsLock, NumLock, ScrollLock, Shift, and Control). */
		};

#pragma pack(pop)

		//! GBInput_Events hold the possible events that can be sent from GBufferedInput.
		enum GBInput_Events {
			KEYPRESSED,				/*!<  Key pressed event. */ 
			KEYRELEASED,			/*!<  Key released event. */ 
			BUTTONPRESSED,			/*!<  Button pressed event. */ 
			BUTTONRELEASED,			/*!<  Button released event. */ 
			MOUSESCROLL,			/*!<  Mouse scroll event. */ 
		};

		//! Unique Identifier for this interface. {4CBA9D69-1B32-43DA-B7B2-A421C57818F0}
		static const GUUIID GBufferedInputUUIID =
		{
			0x4cba9d69, 0x1b32, 0x43da,{ 0xb7, 0xb2, 0xa4, 0x21, 0xc5, 0x78, 0x18, 0xf0 }
		};

		//! A Multi-threaded buffered input library.
		/*!
		*	Register with a GBufferedInput to receive mouse and keyboard events.
		*/
		class GBufferedInput : public CORE::GBroadcasting { };

		//! Creates a GBufferedInput Object.
		/*!
		*	Initializes a window based on the void* data passed in. The created 
		*	GBufferedInput object will have its reference count initialized to one.
		*
		*	\param [out] _outBufferedInput
		*	\param [in] _data (Windows) The handle to the window (HWND).
		*	\param [in] _data (Linux) LINUX_WINDOW data.
		*	\param [in] _data (Max) NSWindow data.
		*
		*	\retval SUCCESS no problems found.
		*	\retval FAILURE could not make an BufferedInput Object.
		*	\retval INVALID_ARGUMENT _outInput and or _data is nullptr.
		*/
		GATEWARE_EXPORT_IMPLICIT GRETURN CreateGBufferedInput(GBufferedInput** _outBufferedInput, void * _data);
	} // end SYSTEM namespace
} // end GW namespace

#endif