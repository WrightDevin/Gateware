
// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"

#include "../../Interface/G_Audio/GAudio.h"

using namespace GW;
using namespace AUDIO;

//Start of GAudio implementation for Windows 
GReturn PlatformInit()
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__

	result = GReturn::SUCCESS;

#endif
	return result;
}
GReturn PlatformLoadSound(const char* _path, GSound** _outSound)
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__


#endif
	return result;
}
GReturn PlatformLoadMusicStream(const char* _path, GMusic** _outMusic)
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__


#endif
	return result;
}
GReturn PlatformPauseAll()
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__


#endif
	return result;
}
GReturn PlatformResumeAll()
{
	GReturn result = GReturn::FAILURE; 
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformSetMasterVolume(float _value)
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__
#endif

	return result;
}
GReturn PlatformSetMasterChannelVolumes(const float * _values, int _numChannels)
{
	GReturn result = GReturn::FAILURE; 
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformUnloadALL()
{
	GReturn result = GReturn::FAILURE; 
#ifdef __APPLE__ 

#endif

	return result;
}
//End of GAudio implementation for Windows 

//Start of GSound implementation for Windows 
GReturn PlatformSetSoundPCMShader(const char* _data)
{
	GReturn result = GReturn::FAILURE; 
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformSetSoundChannelVolumes(float * _values, int _numChannels)
{
	GReturn result = GReturn::FAILURE; 
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformSetSoundVolume(float _newVolume)
{
	GReturn result = GReturn::FAILURE; 
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformPlaySound()
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformPauseSound()
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__
#endif

	return result;
}
GReturn PlatformResumeSound()
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformStopSound()
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__
#endif

	return result;
}
GReturn PlatformUnloadGSound()
{
	GReturn result = GReturn::FAILURE; 
#ifdef __APPLE__
#endif

	return result;
}
//End of GSound implementation for Windows 

//Start of GMusic implementation for Windows 
GReturn PlatformSetMusicPCMShader(const char* _data)
{
	GReturn result = GReturn::FAILURE; 
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformSetMusicChannelVolumes(float * _values, int _numChannels)
{
	GReturn result = GReturn::FAILURE; 
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformSetMusicVolume(float _newVolume)
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformStartStream()
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformPauseStream()
{
	GReturn result = GReturn::FAILURE; 
#ifdef __APPLE__
#endif

	return result;
}
GReturn PlatformResumeStream()
{
	GReturn result = GReturn::FAILURE; 
#ifdef __APPLE__ 
#endif

	return result;
}
GReturn PlatformStopStream()
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__ 

#endif

	return result;
}
GReturn PlatformUnloadGMusic()
{
	GReturn result = GReturn::FAILURE;
#ifdef __APPLE__ 

#endif

	return result;
}
//End of GMusic implementation for Windows 