#ifndef GOPENGLSURFACE_H
#define GOPENGLSURFACE_H

#include "../../Interface/G_Core/GListener.h"
#include "../../Interface/G_System/GWindow.h"
#include "../../Interface/G_System/GKeyDefines.h"

namespace GW
{
	namespace GRAPHICS
	{

		static const GUUIID GOpenGLSurfaceUUIID = 
		{
			0x752bc1a0, 0x44d8, 0x4c03,{ 0xb2, 0xeb, 0x27, 0x4f, 0x80, 0x5c, 0xd9, 0xc9 }
		};

		class GOpenGLSurface : public CORE::GListener
		{

		public:
			virtual GReturn Initialize(unsigned char _initMask) = 0;

			virtual GReturn GetContext(void** _outContext) = 0;

			virtual GReturn UniversalSwapBuffers() = 0;

			virtual GReturn QueryExtensionFunction(const char* _extension, const char* _funcName, void** _outFuncAddress) = 0;

			virtual GReturn EnableSwapControl(bool& _toggle) = 0;

		};
	
		GATEWARE_EXPORT_IMPLICIT GReturn CreateGOpenGLSurface(SYSTEM::GWindow* _gWin, GOpenGLSurface** _outSurface);
	
	}
}

#endif
