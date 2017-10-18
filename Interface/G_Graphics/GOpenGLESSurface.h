#ifndef GOPENGLESSURFACE_H
#define GOPENGLESSURFACE_H

#include "../../Interface/G_Core/GListener.h"
#include "../../Interface/G_System/GWindow.h"

namespace GW
{
	namespace GRAPHICS
	{

		static const GUUIID GOpenGLESSurfaceUUIID = 
		{
			0x752bc1a0, 0x44d8, 0x4c03,{ 0xb2, 0xeb, 0x27, 0x4f, 0x80, 0x5c, 0xd9, 0xc9 }
		};

		class GOpenGLESSurface : public CORE::GListener
		{

		public:
			virtual GReturn Initialize() = 0;

			virtual GReturn GetContext(void** _outContext) = 0;

			virtual GReturn GetDeviceContextHandle(void** _outHDC) = 0;

		};
	
		GATEWARE_EXPORT_IMPLICIT GReturn CreateGOpenGLESSurface(SYSTEM::GWindow* _gWin, GOpenGLESSurface** _outSurface);
	
	}
}

#endif
