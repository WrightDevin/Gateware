#include "../DLL_Export_Symbols.h"
#include "../../Interface/G_Graphics/GDirectX11Surface.h"

#ifdef _WIN32
#pragma comment (lib, "D3D11.lib")
#include <d3d11.h>

#include <atomic>
#include <mutex>
#include <thread>
#elif __linux__
#elif __APPLE__
#endif

using namespace GW;
using namespace CORE;
using namespace SYSTEM;
using namespace GRAPHICS;

class GDirectX11 : public GDirectX11Surface
{
private:
	// declare all necessary members (platform specific)
	GWindow*				gWnd;
	ID3D11Device*			device;
	ID3D11DeviceContext*	context;
	IDXGISwapChain*			swapChain;
	float					width;
	float					height;
	float					aspectRatio;

#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

public:
	GDirectX11();
	virtual ~GDirectX11();
	void	SetGWindow(GWindow* _window);
	GReturn Initialize();
	GReturn GetDevice(void** _outDevice);
	GReturn GetContext(void** _outContext);
	GReturn GetSwapchain(void** _outSwapchain);
	float	GetAspectRatio();

	GReturn RegisterListener(GListener* _addListener, unsigned long long _eventMask);
	GReturn DeregisterListener(GListener* _removeListener);
	GReturn GetCount(unsigned int& _outCount);
	GReturn IncrementCount();
	GReturn DecrementCount();
	GReturn RequestInterface(const GUUIID& _interfaceID, void** _outInterface);
	GReturn OnEvent(const GUUIID& _senderInerface, unsigned int _eventID, void* _eventData, unsigned int _dataSize);
};

GDirectX11::GDirectX11()
{
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
#ifdef _WIN32

	gWnd->OpenWindow();
	HWND surfaceWindow = (HWND)gWnd->GetWindowHandle();
	RECT windowRect;
	GetWindowRect(surfaceWindow, &windowRect);
	width = windowRect.right - windowRect.left;
	height = windowRect.bottom - windowRect.top;

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

	if (hr == S_OK)
		return SUCCESS;
	else
		return FAILURE;

#elif __linux__
#elif __APPLE__
#endif

	return SUCCESS;
}

GReturn GDirectX11::RegisterListener(GListener* _addListener, unsigned long long _eventMask)
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

GReturn GDirectX11::DeregisterListener(GListener* _removeListener)
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

GReturn GDirectX11::GetDevice(void** _outDevice)
{
#ifdef _WIN32

	*_outDevice = device;

#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

GReturn GDirectX11::GetContext(void ** _outContext)
{
#ifdef _WIN32

	*_outContext = context;

#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

GReturn GDirectX11::GetSwapchain(void** _outSwapchain)
{
#ifdef _WIN32

	*_outSwapchain = swapChain;

#elif __linux__
#elif __APPLE__
#endif

	return SUCCESS;
}

float GDirectX11::GetAspectRatio()
{
	return aspectRatio;
}

GReturn GDirectX11::GetCount(unsigned int & _outCount)
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

GReturn GDirectX11::IncrementCount()
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

GReturn GDirectX11::DecrementCount()
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

GReturn GDirectX11::RequestInterface(const GUUIID & _interfaceID, void ** _outInterface)
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

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