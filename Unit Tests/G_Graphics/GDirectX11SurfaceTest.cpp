#include "../Unit Tests/Common.h"

#pragma comment (lib, "D3D11.lib")
#include <d3d11.h>
#include <iostream>

///=============================================================================
//==============================TEST CASES======================================
///=============================================================================

//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES

using namespace GW;
using namespace CORE;
using namespace SYSTEM;
using namespace GRAPHICS;

// GLOBAL VARIABLES
GWindow*					gWnd_DX;
GDirectX11Surface*			dx11Surface = nullptr;
ID3D11Device*				device;
ID3D11DeviceContext*		context;
IDXGISwapChain*				swapChain;
ID3D11DepthStencilView*		zBuffer;
ID3D11DepthStencilState*	stencilState;
unsigned int				surfaceWidth;
unsigned int				surfaceHeight;

namespace { // nameless namespace to isolate below test vars

	// TEST CASES
	// ALL DEVELOPERS!!! USE THIS AS AN EXAMPLE OF HOW TO DO CORE GINTERFACE TESTING!!!
	GW::GRAPHICS::GDirectX11Surface *specific = nullptr;
	GW::CORE::GInterface *generic = nullptr;
	// CORE GINTERFACE TEST BATTERY. ALL GATEWARE INTERFACES MUST BE ABLE TO PASS THESE TESTS.
	TEST_CASE("GDirectX11Surface core test battery", "[CreateGDirectX11Surface], [RequestInterface], [IncrementCount], [DecrementCount], [GetCount]")
	{
		// GWindow Required to test
		unsigned char initMask = DEPTH_BUFFER_SUPPORT | DEPTH_STENCIL_SUPPORT;
		REQUIRE(G_SUCCESS(CreateGWindow(0, 0, 1000, 1000, WINDOWEDBORDERED, &gWnd_DX)));

		// CATCH WARNING!!! 
		// Any variables declared here will be REPLICATED to EACH SECTION.
		// If you need connectivity between sections your variables will need to be global or static.
		unsigned int countS = 0, countG = 0;
		const GW::GUUIID notAnValidInterface = { 0, };

		// THE CREATION FUNCTION IS UNIQUE MOST EVERYTHING BELOW THIS SHOULD BE THE SAME FOR ALL INTERFACES
		SECTION("Creation Tests", "[CreateGDirectX11Surface]")
		{
			CHECK(GW::GRAPHICS::CreateGDirectX11Surface(nullptr, 0, &specific) == GW::INVALID_ARGUMENT);
			CHECK(GW::GRAPHICS::CreateGDirectX11Surface(gWnd_DX, 0, 0) == GW::INVALID_ARGUMENT);
			// TODO: Add additonal Creation parameter testing here as nessasary.
			REQUIRE(G_SUCCESS(GW::GRAPHICS::CreateGDirectX11Surface(gWnd_DX, initMask, &specific)));
			REQUIRE(specific != nullptr);
		}
		// The following tests can be copied verbatim as they are completly generic for all interfaces
		SECTION("Interface Request Tests", "[RequestInterface]")
		{
			CHECK(specific->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
			CHECK(specific->RequestInterface(notAnValidInterface, (void**)&generic) == GW::INTERFACE_UNSUPPORTED);
			CHECK(generic == nullptr); // should not have changed yet
			REQUIRE(G_SUCCESS(specific->RequestInterface(GW::CORE::GInterfaceUUIID, (void**)&generic)));
			REQUIRE(generic != nullptr);
			// memory addresses should match
			REQUIRE(reinterpret_cast<std::uintptr_t>(generic) == reinterpret_cast<std::uintptr_t>(specific));
		}
		// Test reference counting behavior
		SECTION("Reference Counting Tests", "[GetCount], [IncrementCount], [DecrementCount]")
		{
			REQUIRE(G_SUCCESS(specific->GetCount(countS)));
			REQUIRE(G_SUCCESS(generic->GetCount(countG)));
			CHECK(countS == countG);
			CHECK(countS == 3); // should be exactly 3 references at this point (+1 Due to GWindow)
			REQUIRE(G_SUCCESS(specific->IncrementCount())); // 4
			REQUIRE(G_SUCCESS(generic->IncrementCount())); // 5
			specific->GetCount(countS);
			generic->GetCount(countG);
			CHECK(countS == countG);
			CHECK(countS == 5); // should be exactly 5 references at this point
			REQUIRE(G_SUCCESS(specific->DecrementCount())); // 4
			REQUIRE(G_SUCCESS(generic->DecrementCount())); // 3
			// Free specific pointer (user simulation of interface deletion)
			CHECK(G_SUCCESS(specific->DecrementCount())); // 2
			specific = nullptr; // this pointer should not longer be valid from users standpoint (though it is)
			generic->GetCount(countG);
			REQUIRE(countG == 2); // should be last remaining handle aside from internal GWindow listener handle
		}
		// Finally test interface Forward Compatibilty
		SECTION("Forward Compatibility Tests", "[RequestInterface], [GetCount], [DecrementCount]")
		{
			CHECK(generic->RequestInterface(notAnValidInterface, nullptr) == GW::INVALID_ARGUMENT);
			CHECK(generic->RequestInterface(notAnValidInterface, (void**)&specific) == GW::INTERFACE_UNSUPPORTED);
			CHECK(specific == nullptr); // should not have changed yet
			// TODO: Check that generic interface supports upgrading to ALL relevant interfaces in the class heirarchy chain
			REQUIRE(G_SUCCESS(generic->RequestInterface(GW::GRAPHICS::GDirectX11SurfaceUUIID, (void**)&specific))); // 3
			CHECK(specific != nullptr); // specific pointer is valid again
			GW::CORE::GSingleThreaded *singleSupport = nullptr;
			GW::CORE::GMultiThreaded *multiSupport = nullptr;
			REQUIRE(G_FAIL(generic->RequestInterface(GW::CORE::GSingleThreadedUUIID, (void**)&singleSupport)));
			CHECK(singleSupport == nullptr); // GDirectX11Surface is NOT singlethreaded
			REQUIRE(G_SUCCESS(generic->RequestInterface(GW::CORE::GMultiThreadedUUIID, (void**)&multiSupport))); // 4 
			CHECK(multiSupport != nullptr); // GDirectX11Surface IS multithreaded
											// Check final count VS expectations
			REQUIRE(G_SUCCESS(multiSupport->GetCount(countS)));
			CHECK(countS == 4); // four valid handles should exist now
			// Free all handles, all should succeed
			REQUIRE(G_SUCCESS(multiSupport->DecrementCount())); // 3
			REQUIRE(G_SUCCESS(specific->DecrementCount())); // 2
			generic->GetCount(countG);
			REQUIRE(countG == 2); // should be last remaining handle (again, aside from GWindow's +1)
			REQUIRE(G_SUCCESS(generic->DecrementCount())); // 1
		}
		// done with standard tests, the memory for the object should be released at this point and all pointers should be invalid
	}

}// end nameless namespace for standard test battery

TEST_CASE("Create GDirectX11Surface Object.", "[CreateGDirectX11Surface]")
{
	unsigned char initMask = DEPTH_BUFFER_SUPPORT | DEPTH_STENCIL_SUPPORT;

	CHECK(CreateGDirectX11Surface(gWnd_DX, initMask, &dx11Surface) == SUCCESS);
}

TEST_CASE("Querying DXSurface Information.", "[GetDevice], [GetContext], [GetSwapchain]")
{
	CHECK(dx11Surface->GetDevice((void**)&device) == SUCCESS);
	CHECK(dx11Surface->GetContext((void**)&context) == SUCCESS);
	CHECK(dx11Surface->GetSwapchain((void**)&swapChain) == SUCCESS);

	DXGI_SWAP_CHAIN_DESC tempDesc;
	swapChain->GetDesc(&tempDesc);
	char* format;

	if (tempDesc.BufferDesc.Format == DXGI_FORMAT_R8G8B8A8_UNORM)
		format = "8-BIT COLOR (DXGI_FORMAT_R8G8B8A8_UNORM)";
	else if (tempDesc.BufferDesc.Format == DXGI_FORMAT_R10G10B10A2_UNORM)
		format = "10-BIT COLOR (DXGI_FORMAT_R10G10B10A2_UNORM)";

	std::cout << "\n" << "DIRECTX 11 INFORMATION" << "\n";
	std::cout << "COLOR FORMAT: " << format << "\n";
	std::cout << "DEPTH BUFFER ENABLED: ";

	if (dx11Surface->GetDepthStencilView((void**)&zBuffer) == SUCCESS)
		std::cout << "YES" << "\n";
	else
		std::cout << "NO" << "\n";
	// release DX handles as soon as we no longer need them
	zBuffer->Release();
}

TEST_CASE("Testing Window Events.")
{

	unsigned int testWidth;
	unsigned int testHeight;

	// Checking Current Size of Window
	gWnd_DX->GetClientWidth(testWidth);
	gWnd_DX->GetClientHeight(testHeight);

	ID3D11RenderTargetView* surfaceRTV = nullptr;
	float color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	dx11Surface->GetRenderTarget((void**)&surfaceRTV);

	context->ClearRenderTargetView(surfaceRTV, color);
	swapChain->Present(0, 0);
	// Immediately release RTV when done using
	surfaceRTV->Release();

	// Resizing Window
	gWnd_DX->ResizeWindow(500, 500);

	// Checking New Size of Window After Resize
	gWnd_DX->GetClientWidth(testWidth);
	gWnd_DX->GetClientHeight(testHeight);

	if (swapChain != nullptr)
	{
		ID3D11Texture2D* testTex;
		HRESULT result = swapChain->GetBuffer(0, __uuidof(testTex), reinterpret_cast<void**>(&testTex));

		D3D11_TEXTURE2D_DESC testTexDesc;
		testTex->GetDesc(&testTexDesc);

		surfaceWidth = testTexDesc.Width;
		surfaceHeight = testTexDesc.Height;

		REQUIRE(surfaceWidth == testWidth);
		REQUIRE(surfaceHeight == testHeight);

		if (context != nullptr)
		{
			color[0] = 0.0f;
			color[1] = 1.0f;
			// Surface must be re-aquired after resize above
			dx11Surface->GetRenderTarget((void**)&surfaceRTV);

			context->ClearRenderTargetView(surfaceRTV, color);
			// again get rid of your handles as soon as you are done with them
			surfaceRTV->Release();

			swapChain->Present(0, 0);
		}

		testTex->Release();

	}
	// release all main test handles
	context->Release();
	device->Release();
	swapChain->Release();

	// Release our surface
	REQUIRE(G_SUCCESS(dx11Surface->DecrementCount()));
	// Release GWindow!!! (otherwise our count will not fully decrease!)
	REQUIRE(G_SUCCESS(gWnd_DX->DecrementCount()));
}