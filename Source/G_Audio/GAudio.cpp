#ifdef _WIN32
#include"GAudioWin.hpp"
#elif __linux__
#include"GAudioLinux.hpp"
//#elif __APPLE__
//#import "GAudioMac.hpp"
#endif

using namespace GW;
using namespace AUDIO;

class AppSound : public GSound
{
public:
	GReturn SetPCMShader(const char* _data);
	GReturn SetChannelVolumes(float *_values, int _numChannels);
	GReturn SetVolume(float _newVolume);
	GReturn PlaySound();
	GReturn Pause();
	GReturn Resume();
	GReturn StopSound();

	~AppSound();

};

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
	GReturn result = PlatformSetSoundVolume(_newVolume);

	return result;
}
GReturn AppSound::PlaySound()
{
	GReturn result = PlatformPlaySound();

	return result;
}
GReturn AppSound::Pause()
{
	GReturn result = PlatformPauseSound();

	return result;
}
GReturn AppSound::Resume()
{
	GReturn result = PlatformResumeSound();

	return result;
}
GReturn AppSound::StopSound()
{
	GReturn result = PlatformStopSound();

	return result;
}
AppSound::~AppSound()
{
	PlatformUnloadGSound();
}
//End of GSound implementation 

class AppMusic : public GMusic
{
public:
	GReturn SetPCMShader(const char* _data);
	GReturn SetChannelVolumes(float *_values, int _numChannels);
	GReturn SetVolume(float _newVolume);
	GReturn StreamStart();
	GReturn PauseStream();
	GReturn ResumeStream();
	GReturn StopStream();

	~AppMusic();

};
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

};
//Start of GAudio implementation
GReturn AppAudio::Init()
{

	GReturn result = PlatformInit();

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

	result = PlatformLoadSound(_path, (GSound **)&snd);

	*_outSound = snd;
	if (result == INVALID_ARGUMENT)
		return result;

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

	result = PlatformLoadMusicStream(_path, (GMusic **)&msc);

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
	return FAILURE; 
}
GReturn GW::AUDIO::CreateGAudio(GAudio** _outAudio)
{
	GReturn result = FAILURE;
	if (_outAudio == nullptr)
	{
		result = INVALID_ARGUMENT;
		return result;
	}
	AppAudio* audio = new AppAudio();

	if (audio == nullptr)
	{
		result = FAILURE;
		return result;
	}
	 result = audio->Init();

	if (result == INVALID_ARGUMENT)
		return result;

	*_outAudio = audio;

	return result;
}
//End of GAudio implementation 

