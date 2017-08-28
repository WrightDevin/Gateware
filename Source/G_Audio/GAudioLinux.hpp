// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"

#include "../../Interface/G_Audio/GAudio.h"

using namespace GW;
using namespace AUDIO;

//Start of GAudio implementation for Linux 
GReturn PlatformInit()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformLoadSoundData(const char* _path, void * _outSoundData)
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformLoadMusicStreamData(const char* _path, void * _outMusicData)
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformPauseAll()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformResumeAll()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformSetMasterVolume(float _value)
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformSetMasterChannelVolumes(const float * _values, int _numChannels)
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformUnloadALL()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
//End of GAudio implementation for Linux 

//Start of GSound implementation for Linux 
GReturn PlatformSetSoundPCMShader(const char* _data)
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformSetSoundChannelVolumes(float * _values, int _numChannels)
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformSetSoundVolume(float _newVolume)
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformPlaySound()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformPauseSound()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformResumeSound()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformStopSound()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformUnloadGSound()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
//End of GSound implementation for Linux 

//Start of GMusic implementation for Linux 
GReturn PlatformSetMusicPCMShader(const char* _data)
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformSetMusicChannelVolumes(float * _values, int _numChannels)
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformSetMusicVolume(float _newVolume)
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformStartStream()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformPauseStream()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformResumeStream()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformStopStream()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn PlatformUnloadGMusic()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
//End of GMusic implementation for Linux 
