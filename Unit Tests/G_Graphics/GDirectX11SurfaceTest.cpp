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
float					surfaceWidth;
float					surfaceHeight;

// TEST CASES

TEST_CASE("Create GDirectX11Surface Object.", "[CreateGDirectX11Surface]")
{
	REQUIRE(G_SUCCESS(CreateGWindow(100, 100, 500, 500, WINDOWEDBORDERED, &gWnd)));

	CHECK(CreateGDirectX11Surface(gWnd, &dx11Surface) == SUCCESS);
}

TEST_CASE("Initialize GDirectX11Surface.", "[Initialize]")
{
	CHECK(dx11Surface->Initialize() == SUCCESS);
}

TEST_CASE("Querying Surface Information.", "[GetDevice], [GetContext], [GetSwapchain], [GetAspectRatio]")
{
	CHECK(dx11Surface->GetDevice((void**)&device) == SUCCESS);
	CHECK(dx11Surface->GetContext((void**)&context) == SUCCESS);
	CHECK(dx11Surface->GetSwapchain((void**)&swapChain) == SUCCESS);

	//CHECK(dx11Surface->GetAspectRatio() == SUCCESS);
}

TEST_CASE("Querying Swap Chain.")
{
	DXGI_SWAP_CHAIN_DESC testDesc;
	RECT testRect;

	if (swapChain != nullptr)
	{
		swapChain->GetDesc(&testDesc);
		GetClientRect((&testDesc)->OutputWindow, &testRect);
		
		surfaceWidth = (&testRect)->right - (&testRect)->left;
		surfaceHeight = (&testRect)->bottom - (&testRect)->top;
		float testWidth = (float)gWnd->GetClientWidth();
		float testHeight = (float)gWnd->GetClientHeight();

		REQUIRE(surfaceWidth == (float)gWnd->GetClientWidth());
		REQUIRE(surfaceHeight == (float)gWnd->GetClientHeight());
	}
}

//TEST_CASE("Testing Window Events.")
//{
//	// Resizing Window
//	gWnd->ResizeWindow(250, 250);
//
//	// Checking Size of Surface with New Window
//	DXGI_SWAP_CHAIN_DESC* testDesc;
//	RECT* testRect;
//
//	if (swapChain != nullptr)
//	{
//		swapChain->GetDesc(testDesc);
//		GetClientRect(testDesc->OutputWindow, testRect);
//
//		testRect->right = surfaceWidth;
//		testRect->bottom = surfaceHeight;
//
//		CHECK(surfaceWidth == (float)gWnd->GetClientWidth());
//		CHECK(surfaceHeight == (float)gWnd->GetClientHeight());
//	}
//}