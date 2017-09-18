#include "../DLL_Export_Symbols.h"
#include "../../Interface/G_Graphics/GOpenGLESSurface.h"

#include <atomic>
#include <mutex>
#include <thread>

using namespace GW;
using namespace CORE;
using namespace GRAPHICS;

class GOpenGLES : public GOpenGLESSurface
{
private:
	// declare all necessary members (platform specific)

	float aspectRatio;

#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif
	
public:
	GOpenGLES();
	virtual ~GOpenGLES();
	GReturn Initialize();
	GReturn GetContext(void** _outContext);
	float GetAspectRatio();

	GReturn RegisterListener(GListener* _addListener, unsigned long long _eventMask);
	GReturn DeregisterListener(GListener* _removeListener);
	GReturn GetCount(unsigned int& _outCount);
	GReturn IncrementCount();
	GReturn DecrementCount();
	GReturn RequestInterface(const GUUIID& _interfaceID, void** _outInterface);
	GReturn OnEvent(const GUUIID& _senderInterface, unsigned int _eventID, void* _eventData, unsigned int _dataSize);
};

GOpenGLES::GOpenGLES()
{
}

GOpenGLES::~GOpenGLES()
{
}

GReturn GOpenGLES::Initialize()
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

GReturn GOpenGLES::GetContext(void ** outContext)
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif

	return FAILURE;
}

float GOpenGLES::GetAspectRatio()
{
	return aspectRatio;
}

GReturn GOpenGLES::RegisterListener(GListener* _addListener, unsigned long long _eventMask)
{
	return GReturn();
}

GReturn GOpenGLES::DeregisterListener(GListener * _removeListener)
{
	return GReturn();
}

GReturn GOpenGLES::GetCount(unsigned int & _outCount)
{
#ifdef _WIN32
#elif __linux__
#elif __APPLE__
#endif
	return FAILURE;
}

GReturn GOpenGLES::IncrementCount()
{
	return FAILURE;
}

GReturn GOpenGLES::DecrementCount()
{
	return FAILURE;
}

GReturn GOpenGLES::RequestInterface(const GUUIID & _interfaceID, void ** _outInterface)
{
	return FAILURE;
}

GReturn GOpenGLES::OnEvent(const GUUIID & _senderInterface, unsigned int _eventID, void * _eventData, unsigned int _dataSize)
{
	return FAILURE;
}

GATEWARE_EXPORT_EXPLICIT GReturn CreateGOpenGLESSurface(const SYSTEM::GWindow* gWin, GOpenGLESSurface* _outSurface)
{
	return GW::GRAPHICS::CreateGOpenGLESSurface(gWin, _outSurface);
}

GReturn GW::GRAPHICS::CreateGOpenGLESSurface(const SYSTEM::GWindow* gWin, GOpenGLESSurface* _outSurface)
{
	if (_outSurface == nullptr)
		return INVALID_ARGUMENT;

	GOpenGLES* Surface = new GOpenGLES();

	if (Surface == nullptr)
		return FAILURE;

	return FAILURE;
}