#include "../Unit Tests/Common.h"

#pragma comment (lib, "D3D11.lib")
#include <d3d11.h>

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
GWindow*				gWnd_DX;
GDirectX11Surface*		dx11Surface = nullptr;
ID3D11Device*			device;
ID3D11DeviceContext*	context;
IDXGISwapChain*			swapChain;
unsigned int			surfaceWidth;
unsigned int			surfaceHeight;

// TEST CASES

TEST_CASE("Create GDirectX11Surface Object.", "[CreateGDirectX11Surface]")
{
	REQUIRE(G_SUCCESS(CreateGWindow(0, 0, 1000, 1000, WINDOWEDBORDERED, &gWnd_DX)));

	CHECK(CreateGDirectX11Surface(gWnd_DX, &dx11Surface) == SUCCESS);
}

TEST_CASE("Querying DXSurface Information.", "[GetDevice], [GetContext], [GetSwapchain]")
{
	CHECK(dx11Surface->GetDevice((void**)&device) == SUCCESS);
	CHECK(dx11Surface->GetContext((void**)&context) == SUCCESS);
	CHECK(dx11Surface->GetSwapchain((void**)&swapChain) == SUCCESS);
}

//TEST_CASE("Querying Swap Chain.")
//{
//	unsigned int testWidth;
//	unsigned int testHeight;
//
//	if (swapChain != nullptr)
//	{
//		ID3D11Texture2D* testTex;
//		swapChain->GetBuffer(0, __uuidof(testTex), reinterpret_cast<void**>(&testTex));
//		
//		D3D11_TEXTURE2D_DESC testTexDesc;
//		testTex->GetDesc(&testTexDesc);
//
//		surfaceWidth = testTexDesc.Width;
//		surfaceHeight = testTexDesc.Height;
//
//		gWnd_DX->GetClientWidth(testWidth);
//		gWnd_DX->GetClientHeight(testHeight);
//
//		REQUIRE(surfaceWidth == testWidth);
//		REQUIRE(surfaceHeight == testHeight);
//
//		if (context != nullptr)
//		{
//			ID3D11RenderTargetView* surfaceRTV = nullptr;
//			const float color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
//
//			dx11Surface->GetRenderTarget((void**)&surfaceRTV);
//
//			context->ClearRenderTargetView(surfaceRTV, color);
//			swapChain->Present(0, 0);
//		}
//
//		testTex->Release();
//
//	}
//}

TEST_CASE("Testing Window Events.")
{

	unsigned int testWidth;
	unsigned int testHeight;

	// Checking Current Size of Window
	gWnd_DX->GetClientWidth(testWidth);
	gWnd_DX->GetClientHeight(testHeight);

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
			ID3D11RenderTargetView* surfaceRTV = nullptr;
			const float color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

			dx11Surface->GetRenderTarget((void**)&surfaceRTV);

			context->ClearRenderTargetView(surfaceRTV, color);
			swapChain->Present(0, 0);
		}

		testTex->Release();

	}
}