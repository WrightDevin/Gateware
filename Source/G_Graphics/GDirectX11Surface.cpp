#include "../DLL_Export_Symbols.h"
#include "../../Interface/G_Graphics/GDirectX11Surface.h"
#include "../../Source/G_System/GUtility.h"



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
	unsigned int refCount;

	GWindow*					gWnd;
	ID3D11Device*				device;
	ID3D11DeviceContext*		context;
	IDXGISwapChain*				swapChain;
	ID3D11RenderTargetView*		rtv;
	float						width;
	float						height;
	float						aspectRatio;

#ifdef _WIN32

	HWND surfaceWindow;

#elif __linux__
#elif __APPLE__
#endif

public:
	GDirectX11();
	virtual ~GDirectX11();
	void	SetGWindow(GWindow* _window);
	GReturn Initialize();
	GReturn	GetAspectRatio(float& _outRatio);

	GReturn GetDevice(void** _outDevice);
	GReturn GetContext(void** _outContext);
	GReturn GetSwapchain(void** _outSwapchain);
	GReturn GetRenderTarget(void** _outRenderTarget);

	GReturn GetCount(unsigned int& _outCount);
	GReturn IncrementCount();
	GReturn DecrementCount();
	GReturn RequestInterface(const GUUIID& _interfaceID, void** _outputInterface);
	GReturn OnEvent(const GUUIID& _senderInerface, unsigned int _eventID, void* _eventData, unsigned int _dataSize);
};

GDirectX11::GDirectX11()
{
	ZeroMemory(&surfaceWindow, sizeof(HWND));
}

GDirectX11::~GDirectX11()
{
	gWnd->DeregisterListener(this);
	DecrementCount();
}

void GDirectX11::SetGWindow(GWindow* _window)
{
	gWnd = _window;
}

GReturn GDirectX11::Initialize()
{
#ifdef _WIN32

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

	buffer->Release();

	D3D11_VIEWPORT viewport;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	gWnd->GetClientTopLeft((unsigned int&)viewport.TopLeftX, (unsigned int&)viewport.TopLeftY);

	context->RSSetViewports(1, &viewport);
	
#elif __linux__
#elif __APPLE__
#endif

	return SUCCESS;
}

GReturn GDirectX11::GetDevice(void** _outDevice)
{
#ifdef _WIN32

	*_outDevice = device;

#elif __linux__
#elif __APPLE__
#endif

	return SUCCESS;
}

GReturn GDirectX11::GetContext(void ** _outContext)
{
#ifdef _WIN32

	*_outContext = context;

#elif __linux__
#elif __APPLE__
#endif

	return SUCCESS;
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

GReturn GDirectX11::GetRenderTarget(void** _outRenderTarget)
{
	*_outRenderTarget = rtv;

	return SUCCESS;
}

GReturn GDirectX11::GetAspectRatio(float& _outRatio)
{
	_outRatio = aspectRatio;

	return SUCCESS;
}

GReturn GDirectX11::GetCount(unsigned int & _outCount)
{
	_outCount = refCount;

	return SUCCESS;
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

GReturn GDirectX11::RequestInterface(const GUUIID & _interfaceID, void ** _outputInterface)
{
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	if (_interfaceID == GWindowUUIID)
	{
		GWindow* convert = reinterpret_cast<GWindow*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GBroadcastingUUIID)
	{
		GBroadcasting* convert = reinterpret_cast<GBroadcasting*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GMultiThreadedUUIID)
	{
		GMultiThreaded* convert = reinterpret_cast<GMultiThreaded*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GInterfaceUUIID)
	{
		GInterface* convert = reinterpret_cast<GInterface*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GDirectX11SurfaceUUIID)
	{
		GDirectX11Surface* convert = reinterpret_cast<GDirectX11Surface*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else
		return INTERFACE_UNSUPPORTED;

	return SUCCESS;
}

GReturn GDirectX11::OnEvent(const GUUIID & _senderInerface, unsigned int _eventID, void * _eventData, unsigned int _dataSize)
{

	if (_senderInerface == GWindowUUIID)
	{

		GWINDOW_EVENT_DATA* eventStruct = (GWINDOW_EVENT_DATA*)_eventData;

		switch (_eventID)
		{
		case GW::SYSTEM::NOTIFY:
			break;
		case GW::SYSTEM::MINIMIZE:
			break;
		case GW::SYSTEM::MAXIMIZE:
		{
			unsigned int maxWidth;
			unsigned int maxHeight;

			gWnd->GetWidth(maxWidth);
			gWnd->GetHeight(maxHeight);

			aspectRatio = maxWidth / maxHeight;
			swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
		}
			break;
		case GW::SYSTEM::RESIZE:
		{

			unsigned int newWidth;
			unsigned int newHeight;

			gWnd->GetWidth(newWidth);
			gWnd->GetHeight(newHeight);

			aspectRatio = newWidth / newHeight;

			if (swapChain)
			{
				rtv->Release();

				HRESULT result = swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

				if (result != S_OK)
					return FAILURE;

				ID3D11Texture2D* newRTVBuffer;
				result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&newRTVBuffer));

				if (result != S_OK)
					return FAILURE;

				result = device->CreateRenderTargetView(newRTVBuffer, NULL, &rtv);

				if (result != S_OK)
					return FAILURE;

				newRTVBuffer->Release();

				D3D11_VIEWPORT viewport;
				viewport.Width = newWidth;
				viewport.Height = newHeight;
				viewport.MinDepth = 0.0f;
				viewport.MaxDepth = 1.0f;				
				gWnd->GetClientTopLeft((unsigned int&)viewport.TopLeftX, (unsigned int&)viewport.TopLeftY);

				context->RSSetViewports(1, &viewport);
			}

		}
			break;
		case GW::SYSTEM::MOVE:
			break;
		case GW::SYSTEM::DESTROY:
			break;
		}

	}

	return SUCCESS;
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
	Surface->Initialize();

	_gWin->RegisterListener(Surface, 0);

	if (Surface == nullptr)
		return FAILURE;

	*_outSurface = Surface;

	return SUCCESS;
}