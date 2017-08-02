
#include "GDirectX11Surface.h"

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
using namespace GRAPHICS;

class GDirectX11 : public GDirectX11Surface
{
private:
	// declare all necessary members (platform specific)

	float aspectRatio;

#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

public:
	GDirectX11();
	virtual ~GDirectX11();
	GReturn Initialize();
	GReturn GetContext(void** _outContext);
	float GetAspectRatio();

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

GReturn GDirectX11::Initialize()
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

GReturn GDirectX11::RegisterListener(GListener * _addListener, unsigned long long _eventMask)
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

GReturn GDirectX11::DeregisterListener(GListener * _removeListener)
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

GReturn GDirectX11::GetContext(void ** _outContext)
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
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

GATEWARE_EXPORT_EXPLICIT GReturn CreateGDirectX11Surface(const SYSTEM::GWindow* gWin, GDirectX11Surface* _outSurface)
{
	return GW::GRAPHICS::CreateGDirectX11Surface(gWin, _outSurface);
}

GReturn GW::GRAPHICS::CreateGDirectX11Surface(const SYSTEM::GWindow* gWin, GDirectX11Surface* _outSurface)
{
	if (_outSurface == nullptr)
		return INVALID_ARGUMENT;

	GDirectX11* Surface = new GDirectX11();

	if (Surface == nullptr)
		return FAILURE;

	return FAILURE;
}