#ifndef GDIRECTX11SURFACE_H
#define GDIRECTX11SURFACE_H

#include "../../Interface/G_Core/GListener.h"
#include "../../Interface/G_System/GWindow.h"

namespace GW
{
	namespace GRAPHICS
	{

		static const GUUIID GDirectX11SurfaceUUIID = 
		{
			0xbf02260e, 0x1c03, 0x4e16,{ 0xa6, 0xf3, 0x79, 0x69, 0xcd, 0xe4, 0x4f, 0x84 }
		};

		class GDirectX11Surface : public CORE::GListener
		{

		public:

			virtual GReturn GetDevice(void** _outDevice) = 0;

			virtual GReturn GetContext(void** _outContext) = 0;

			virtual GReturn GetSwapchain(void** _outSwapchain) = 0;

			virtual GReturn GetRenderTarget(void** _outRenderTarget) = 0;

			virtual GReturn GetDepthStencilView(void** _outDepthStencilView) = 0;

		};

		GATEWARE_EXPORT_IMPLICIT GReturn CreateGDirectX11Surface(SYSTEM::GWindow* _gWin, GDirectX11Surface** _outSurface);

	}
}

#endif