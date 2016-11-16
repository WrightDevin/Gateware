#ifndef _GINPUT
#define _GINPUT

//Single Thread ( GInput )
// Array of keys with states.
// Derived from Single Tread


//Multithreaded ( GBufferedInput )
// Register Listener

// GBroadcasting Inherits directly from GMultiThreaded 
#include "../G_Core/GBroadcasting.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong
namespace GW
{
	//! The core namespace to which all Gateware fundamental interfaces must belong
	namespace CORE
	{

		enum GBInput_Events {
			KEYPRESSED,
			KEYRELEASED,
			BUTTONPRESSED,
			BUTTONRELEASED,
			MOUSESCROLL,
		};

		//! Unique Identifier for this interface. {4CBA9D69-1B32-43DA-B7B2-A421C57818F0}
		static const GUUIID GBufferedInputUUIID =
		{
			0x4cba9d69, 0x1b32, 0x43da,{ 0xb7, 0xb2, 0xa4, 0x21, 0xc5, 0x78, 0x18, 0xf0 } 
		};

		//! The GInput Interface is resposible for recieving and managing the keyboard and mouse.
		class GBufferedInput : public GBroadcasting
		{
		
			// All Gateware API interfaces contain no variables & are pure virtual
		public:


		};

		GRETURN CreateGBufferedInput(GBufferedInput** _outPointer, void * _hWnd);
		}// end CORE namespace
	};// end GW namespace
#endif