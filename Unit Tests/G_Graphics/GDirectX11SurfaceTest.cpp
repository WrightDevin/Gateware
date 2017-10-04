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
GWindow*				gWnd;
GDirectX11Surface*		dx11Surface = nullptr;
ID3D11Device*			device;
ID3D11DeviceContext*	context;
IDXGISwapChain*			swapChain;
unsigned int			surfaceWidth;
unsigned int			surfaceHeight;

// TEST CASES

TEST_CASE("Create GDirectX11Surface Object.", "[CreateGDirectX11Surface]")
{
	REQUIRE(G_SUCCESS(CreateGWindow(100, 100, 1000, 1000, WINDOWEDBORDERED, &gWnd)));

	CHECK(CreateGDirectX11Surface(gWnd, &dx11Surface) == SUCCESS);
}

TEST_CASE("Initialize GDirectX11Surface.", "[Initialize]")
{
	CHECK(dx11Surface->Initialize() == SUCCESS);

	gWnd->MoveWindow(0, 0);
}

TEST_CASE("Querying Surface Information.", "[GetDevice], [GetContext], [GetSwapchain]")
{
	CHECK(dx11Surface->GetDevice((void**)&device) == SUCCESS);
	CHECK(dx11Surface->GetContext((void**)&context) == SUCCESS);
	CHECK(dx11Surface->GetSwapchain((void**)&swapChain) == SUCCESS);
}

TEST_CASE("Querying Swap Chain.")
{
	DXGI_SWAP_CHAIN_DESC testDesc;
	RECT testRect;
	unsigned int testWidth;
	unsigned int testHeight;

	if (swapChain != nullptr)
	{
		swapChain->GetDesc(&testDesc);
		GetClientRect((&testDesc)->OutputWindow, &testRect);
		
		surfaceWidth = (&testRect)->right - (&testRect)->left;
		surfaceHeight = (&testRect)->bottom - (&testRect)->top;

		gWnd->GetClientWidth(testWidth);
		gWnd->GetClientHeight(testHeight);

		REQUIRE(surfaceWidth == testWidth);
		REQUIRE(surfaceHeight == testHeight);

		if (context != nullptr)
		{
			ID3D11RenderTargetView* surfaceRTV = nullptr;
			const float color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

			dx11Surface->GetRenderTarget((void**)&surfaceRTV);

			context->ClearRenderTargetView(surfaceRTV, color);
			swapChain->Present(0, 0);
		}

	}
}

TEST_CASE("Testing Window Events.")
{
	// Resizing Window
	gWnd->ResizeWindow(500, 500);
	gWnd->MoveWindow(0, 0);

	// Checking Size of Surface with New Window
	DXGI_SWAP_CHAIN_DESC testDesc;
	RECT testRect;
	unsigned int testWidth;
	unsigned int testHeight;

	if (swapChain != nullptr)
	{
		swapChain->GetDesc(&testDesc);
		GetClientRect((&testDesc)->OutputWindow, &testRect);

		surfaceWidth = (&testRect)->right - (&testRect)->left;
		surfaceHeight = (&testRect)->bottom - (&testRect)->top;

		gWnd->GetClientWidth(testWidth);
		gWnd->GetClientHeight(testHeight);

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

	}
}