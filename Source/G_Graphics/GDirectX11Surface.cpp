#include "../DLL_Export_Symbols.h"
#include "../../Interface/G_Graphics/GDirectX11Surface.h"
#include "../../Source/G_System/GUtility.h"



#ifdef _WIN32

#pragma comment (lib, "D3D11.lib")
#include <d3d11.h>
#include <atomic>
#include <mutex>
#include <thread>


using namespace GW;
using namespace CORE;
using namespace SYSTEM;
using namespace GRAPHICS;

class GDirectX11 : public GDirectX11Surface
{
private:
	// declare all necessary members (platform specific)
	unsigned int refCount;

	GWindow*					gWnd;
	HWND surfaceWindow;
	ID3D11Device*				device;
	ID3D11DeviceContext*		context;
	IDXGISwapChain*				swapChain;
	ID3D11RenderTargetView*		rtv;
	float						width;
	float						height;
	float						aspectRatio;

public:
	GDirectX11();
	virtual ~GDirectX11();
	void	SetGWindow(GWindow* _window);
	GReturn Initialize();
	GReturn GetDevice(void** _outDevice);
	GReturn GetContext(void** _outContext);
	GReturn GetSwapchain(void** _outSwapchain);
	GReturn GetRenderTarget(void** _outRenderTarget);
	float	GetAspectRatio();

	GReturn GetCount(unsigned int& _outCount);
	GReturn IncrementCount();
	GReturn DecrementCount();
	GReturn RequestInterface(const GUUIID& _interfaceID, void** _outInterface);
	GReturn OnEvent(const GUUIID& _senderInerface, unsigned int _eventID, void* _eventData, unsigned int _dataSize);
};

GDirectX11::GDirectX11()
{
	ZeroMemory(&surfaceWindow, sizeof(HWND));
}

GDirectX11::~GDirectX11()
{
}

void GDirectX11::SetGWindow(GWindow* _window)
{
	gWnd = _window;
}

GReturn GDirectX11::Initialize()
{

	gWnd->OpenWindow();
	gWnd->GetWindowHandle(&surfaceWindow, sizeof(HWND));
	RECT windowRect;
	GetWindowRect(surfaceWindow, &windowRect);
	width = windowRect.right - windowRect.left;
	height = windowRect.bottom - windowRect.top;
	aspectRatio = width / height;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	D3D11_CREATE_DEVICE_FLAG deviceFlag = D3D11_CREATE_DEVICE_SINGLETHREADED;

#ifdef _DEBUG
	deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	DXGI_SWAP_CHAIN_DESC swapChainStruct;
	swapChainStruct.BufferCount = 1;
	swapChainStruct.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainStruct.BufferDesc.Width = width;
	swapChainStruct.BufferDesc.Height = height;
	ZeroMemory(&swapChainStruct.BufferDesc.RefreshRate, sizeof(swapChainStruct.BufferDesc.RefreshRate));
	ZeroMemory(&swapChainStruct.BufferDesc.Scaling, sizeof(swapChainStruct.BufferDesc.Scaling));
	ZeroMemory(&swapChainStruct.BufferDesc.ScanlineOrdering, sizeof(swapChainStruct.BufferDesc.ScanlineOrdering));
	swapChainStruct.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainStruct.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainStruct.OutputWindow = surfaceWindow;
	swapChainStruct.Windowed = true;
	swapChainStruct.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainStruct.SampleDesc.Count = 1;
	swapChainStruct.SampleDesc.Quality = 0;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		deviceFlag,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&swapChainStruct,
		&swapChain,
		&device,
		nullptr,
		&context
	);	

	ID3D11Resource* buffer;
	swapChain->GetBuffer(0, __uuidof(buffer), reinterpret_cast<void**>(&buffer));
	device->CreateRenderTargetView(buffer, NULL, &rtv);

	return SUCCESS;
}

GReturn GDirectX11::GetDevice(void** _outDevice)
{
	*_outDevice = device;

	return SUCCESS;
}

GReturn GDirectX11::GetContext(void ** _outContext)
{
	*_outContext = context;

	return SUCCESS;
}

GReturn GDirectX11::GetSwapchain(void** _outSwapchain)
{
	*_outSwapchain = swapChain;

	return SUCCESS;
}

GReturn GDirectX11::GetRenderTarget(void** _outRenderTarget)
{
	*_outRenderTarget = rtv;

	return SUCCESS;
}

float GDirectX11::GetAspectRatio()
{
	return aspectRatio;
}

GReturn GDirectX11::GetCount(unsigned int & _outCount)
{
	_outCount = refCount;

	return FAILURE;
}

GReturn GDirectX11::IncrementCount()
{
	if (refCount == G_UINT_MAX)
		return FAILURE;

	++refCount;

	return SUCCESS;
}

GReturn GDirectX11::DecrementCount()
{
	if (refCount == 0)
	{
		delete this;
		return FAILURE;
	}

	--refCount;

	return SUCCESS;
}

GReturn GDirectX11::RequestInterface(const GUUIID & _interfaceID, void ** _outInterface)
{
	return FAILURE;
}

GReturn GDirectX11::OnEvent(const GUUIID & _senderInerface, unsigned int _eventID, void * _eventData, unsigned int _dataSize)
{
	return FAILURE;
}

GATEWARE_EXPORT_EXPLICIT GReturn CreateGDirectX11Surface(SYSTEM::GWindow* _gWin, GDirectX11Surface** _outSurface)
{
	return GW::GRAPHICS::CreateGDirectX11Surface(_gWin, _outSurface);
}

GReturn GW::GRAPHICS::CreateGDirectX11Surface(SYSTEM::GWindow* _gWin, GDirectX11Surface** _outSurface)
{
	if (_outSurface == nullptr)
		return INVALID_ARGUMENT;

	GDirectX11* Surface = new GDirectX11();
	Surface->SetGWindow(_gWin);

	if (Surface == nullptr)
		return FAILURE;

	*_outSurface = Surface;

	return SUCCESS;
}