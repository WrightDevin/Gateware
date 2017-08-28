
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
GReturn PlatformLoadSoundData(const char* _path, GMacSound * &_outSoundData)
{
	GReturn result = GReturn::FAILURE;
  

#if __APPLE__
 
    NSString * nsPath = [[[NSString alloc] initWithUTF8String:_path] autorelease];
    _outSoundData  = [[GMacSound alloc]initWithPath:nsPath];
 //  = static_cast<GMacSound *>(realSound);
    if(_outSoundData != nullptr)
    {
        result = SUCCESS;
    }
    else
    {
        result = FAILURE;
    }
#endif
	return result;
}
GReturn PlatformLoadMusicStreamData(const char* _path, void * & _outMusicData)
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
#if __APPLE__
#endif

	return result;
}
GReturn PlatformSetMasterChannelVolumes(const float * _values, int _numChannels)
{
	GReturn result = GReturn::FAILURE; 
#if __APPLE__
#endif

	return result;
}
GReturn PlatformUnloadALL()
{
	GReturn result = GReturn::FAILURE; 
#if __APPLE__

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
GReturn PlatformSetSoundVolume(float _newVolume, GMacSound * & _outSound)
{
	GReturn result = GReturn::FAILURE;
    if(_outSound == nullptr)
    {
        return INVALID_ARGUMENT;
    }
#if __APPLE__
    bool bresult = [_outSound SetVolume:_newVolume];
    if(bresult == true)
        result = SUCCESS;
    else
        result = FAILURE;
#endif

	return result;
}
GReturn PlatformPlaySound(GMacSound * & _outSound)
{
    
	GReturn result = FAILURE;
    bool check = false;
#if __APPLE__
    check = [_outSound PlaySound];
#endif
if(check == true)
{
    result = SUCCESS;
}

	return result;
}
GReturn PlatformPauseSound(GMacSound * & _outSound)
{
	GReturn result = GReturn::FAILURE;
        bool check = false;
#if __APPLE__
   check = [_outSound PauseSound];
#endif
    if(check == true)
    {
        result = SUCCESS;
    }

	return result;
}
GReturn PlatformResumeSound(GMacSound * & _outSound)
{
	GReturn result = GReturn::FAILURE;
        bool check = false;
#if __APPLE__
   check = [_outSound ResumeSound];
#endif
    if(check == true)
    {
        result = SUCCESS;
    }

	return result;
}
GReturn PlatformStopSound(GMacSound * & _outSound)
{
	GReturn result = GReturn::FAILURE;
    bool check = false;
#if __APPLE__
  check =  [_outSound StopSound];
#endif
    if(check == true)
    {
        result = SUCCESS;
    }

	return result;
}
GReturn PlatformUnloadGSound(GMacSound * & _outSound)
{
	GReturn result = GReturn::FAILURE;
       bool check = false;
#if __APPLE__
    check =  [_outSound Unload];
#endif
    
    if(check == true)
    {
        result = SUCCESS;
    }

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
