#ifndef _GINPUT
#define _GINPUT

//Single Thread ( GInput )
// Array of keys with states.
// Derived from Single Tread


//Multithreaded ( GBufferedInput )
// Register Listener

// GBroadcasting Inherits directly from GMultiThreaded 
#include "../G_Core/GSingleThreaded.h"
#include <Windows.h>

//! The core namespace to which all Gateware interfaces/structures/defines must belong
namespace GW
{
	//! The core namespace to which all Gateware fundamental interfaces must belong
	namespace CORE
	{

		//! Unique Identifier for this interface. {4CBA9D69-1B32-43DA-B7B2-A421C57818F0}
		static const GUUIID GInputUUIID =
		{
			0x4cba9d69, 0x1b32, 0x43da,{ 0xb7, 0xb2, 0xa4, 0x21, 0xc5, 0x78, 0x18, 0xf0 } 
		};

		//! The GInput Interface is resposible for recieving and managing the keyboard and mouse.
		class GInput : public GSingleThreaded
		{
		
			// All Gateware API interfaces contain no variables & are pure virtual
		public:


			virtual GRETURN GetKeyState(int _keyCode, int &_keyState) = 0;



		};

		GRETURN CreateGInput(GInput** _outFpointer, void * _hWnd);
		}// end CORE namespace
	};// end GW namespace
#endif