#ifdef _WIN32
#include"GAudioWin.hpp"

#elif __linux__
#include"GAudioLinux.hpp"
#elif __APPLE__
#include "GAudioMac.hpp"
#endif

using namespace GW;
using namespace AUDIO;

class AppSound : public GSound
{
public:
    GReturn Init(const char* _path);
	GReturn SetPCMShader(const char* _data);
	GReturn SetChannelVolumes(float *_values, int _numChannels);
	GReturn SetVolume(float _newVolume);
	GReturn Play();
	GReturn Pause();
	GReturn Resume();
	GReturn StopSound();
	~AppSound();

#if __APPLE__
    GMacSound * mac_snd = nullptr;
#elif _WIN32
	 WindowAppSound * wind_snd = nullptr;
#endif
    
};
GReturn AppSound::Init(const char * _path)
{
    
    GReturn result = FAILURE;
#if __APPLE__
    
    result = PlatformLoadSoundData(_path,  mac_snd);
#endif
    return result;
}
//Start of GSound implementation 
GReturn AppSound::SetPCMShader(const char* _data)
{
	GReturn result = PlatformSetSoundPCMShader(_data);

	return result;
}
GReturn AppSound::SetChannelVolumes(float * _values, int _numChannels)
{
	GReturn result = PlatformSetSoundChannelVolumes(_values, _numChannels);

	return result;
}
GReturn AppSound::SetVolume(float _newVolume)
{
    GReturn result = FAILURE;
#if __APPLE__
    	result = PlatformSetSoundVolume(_newVolume, mac_snd);
#elif Win32
     result = PlatformSetSoundVolume(_newVolume);
#endif

	return result;
}
GReturn AppSound::Play()
{

    GReturn result = FAILURE;

#if __APPLE__
    result = PlatformPlaySound(mac_snd);
#elif Win32
    result = PlatformPlaySound();
#endif
  
    return result;
}
GReturn AppSound::Pause()
{
        GReturn result = FAILURE;

#if __APPLE__
    result = PlatformPauseSound(mac_snd);
#elif Win32
    result = PlatformPauseSound();
#endif
	return result;
}
GReturn AppSound::Resume()
{
        GReturn result = FAILURE;
	
#if __APPLE__
    result = PlatformResumeSound(mac_snd);
#elif Win32
    result = PlatformResumeSound();
#endif
	return result;
}
GReturn AppSound::StopSound()
{
        GReturn result = FAILURE;

#if __APPLE__
    result = PlatformStopSound(mac_snd);
#elif Win32
    result = PlatformStopSound();
#endif
	return result;
}
AppSound::~AppSound()
{
	GReturn result = FAILURE;
#if __APPLE__
	if (mac_snd == nullptr)
	{
		return;
	}
     PlatformUnloadGSound(mac_snd);
  //  delete mac_snd;
    mac_snd = nullptr;
#else

    result = PlatformUnloadGSound();
#endif

}
//End of GSound implementation

class AppMusic : public GMusic
{

public:
    GReturn Init(const char* _path);
	GReturn SetPCMShader(const char* _data);
	GReturn SetChannelVolumes(float *_values, int _numChannels);
	GReturn SetVolume(float _newVolume);
	GReturn StreamStart();
	GReturn PauseStream();
	GReturn ResumeStream();
	GReturn StopStream();
	~AppMusic();
    
#if __APPLE__
    GMacMusic * mac_msc = nullptr;
#endif
    

};
GReturn AppMusic::Init(const char* _path)
{
    GReturn result = FAILURE;
#if __APPLE__
    void * dataPtr = &mac_msc;
    result = PlatformLoadMusicStreamData(_path,  dataPtr);
#endif
        return result;
}
//Start of GMusic implementation
GReturn AppMusic::SetPCMShader(const char* _data)
{
	GReturn result = PlatformSetMusicPCMShader(_data);

	return result;
}
GReturn AppMusic::SetChannelVolumes(float * _values, int _numChannels)
{
	GReturn result = PlatformSetMusicChannelVolumes(_values, _numChannels);

	return result;
}
GReturn AppMusic::SetVolume(float _newVolume)
{
	GReturn result = PlatformSetMusicVolume(_newVolume);

	return result;
}
GReturn AppMusic::StreamStart()
{
	GReturn result = PlatformStartStream();

	return result;
}
GReturn AppMusic::PauseStream()
{
	GReturn result = PlatformPauseStream();

	return result;
}
GReturn AppMusic::ResumeStream()
{
	GReturn result = PlatformResumeStream();

	return result;
}
GReturn AppMusic::StopStream()
{
	GReturn result = PlatformStopStream();

	return result;
}
AppMusic::~AppMusic()
{
	PlatformUnloadGMusic();
}
//End of GMusic implementation 

class AppAudio : public GAudio
{
public:
	GReturn Init();
	GReturn CreateSound(const char* _path, GSound** _outSound);
	GReturn CreateMusicStream(const char* _path, GMusic** _outMusic);
	GReturn SetMasterVolume(float _value);
	GReturn SetMasterChannelVolumes(const float * _values, int _numChannels);
	GReturn PauseAll();
	GReturn ResumeAll();
	~AppAudio();
    
#if __APPLE__
    GMacAudio * mac_audio = nullptr;
#endif

};
//Start of GAudio implementation
GReturn AppAudio::Init()
{

	GReturn result = FAILURE;

	return result;
}
GReturn AppAudio::CreateSound(const char* _path, GSound** _outSound)
{
  
		GReturn result = FAILURE;
	if (_outSound == nullptr)
	{
		result = INVALID_ARGUMENT;
		return result;
	}
	AppSound* snd = new AppSound();

	if (snd == nullptr)
	{
        
		result = FAILURE;
		return result;
	}
   result = snd->Init(_path);
	*_outSound = snd;
	if (result == INVALID_ARGUMENT)
    {
 
		return result;
    }

	return result;
}
GReturn AppAudio::CreateMusicStream(const char* _path, GMusic** _outMusic)
{
	GReturn result = FAILURE;
	if (_outMusic == nullptr)
	{
		result = INVALID_ARGUMENT;
		return result;
	}
	AppMusic* msc = new AppMusic();

	if (msc == nullptr)
	{
		result = FAILURE;
		return result;
	}
    msc->Init(_path);
	*_outMusic = msc;
	if (result == INVALID_ARGUMENT)
		return result;

	return result;
}
GReturn AppAudio::SetMasterVolume(float _value)
{
	GReturn result = PlatformSetMasterVolume(_value);

	return result;
}
GReturn AppAudio::SetMasterChannelVolumes(const float * _values, int _numChannels)
{
	GReturn result = PlatformSetMasterChannelVolumes(_values, _numChannels);

	return result;
}
GReturn AppAudio::PauseAll()
{
	GReturn result = PlatformPauseAll();

	return result;
}
GReturn AppAudio::ResumeAll()
{
	GReturn result = PlatformResumeAll();

	return result;
}
AppAudio::~AppAudio()
{
	PlatformUnloadALL();
}
GATEWARE_EXPORT_EXPLICIT GReturn CreateGAudio(GAudio** _outAudio) 
{
	return GW::AUDIO::CreateGAudio(_outAudio); 
}
GReturn GW::AUDIO::CreateGAudio(GAudio** _outAudio)
{
	GReturn result = FAILURE;
	if (_outAudio == nullptr)
	{
		result = INVALID_ARGUMENT;
		return result;
	}

	 result = PlatformGetAudio(_outAudio);

	return result;
}
//End of GAudio implementation 

