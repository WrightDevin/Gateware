// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"

#include "../../Interface/G_Audio/GAudio.h"

using namespace GW;
using namespace AUDIO;
#include <iostream>
#include <time.h>
#include <vector>
#include <thread>
#include <pulse/mainloop.h>
#include <pulse/context.h>
#include <pulse/stream.h>
#include <pulse/error.h>
#include <pulse/scache.h>

const unsigned long fourRIFFcc = 'FFIR';
const unsigned long fourDATAcc = 'atad';
const unsigned long fourFMTcc = ' tmf';
const unsigned long fourWAVEcc = 'EVAW';
const unsigned long fourXWMAcc = 'AMWX';
const unsigned long fourDPDScc = 'sdpd';

struct PCM_FORMAT_INFO
{
    unsigned short mFormatTag = 0;
    unsigned short mNumChannels = 0;
    unsigned int mSamples = 0;
    unsigned int mAvgBytesPerSec = 0;
    unsigned short mBlockAlign= 0;
    unsigned short mBitsPerSample= 0;
    unsigned short mCbSize= 0;
};
struct PCM_BUFFER
{

    uint32_t byteSize = 0;
    uint8_t * bytes = nullptr;
};
struct WAVE_FILE
{
    PCM_FORMAT_INFO myFormat ;
    PCM_BUFFER myBuffer;
    bool isSigned = false;
};

struct TJCALLBACK
{
int didFinish = -1;
 void(*didSucceed)(pa_stream*,int,void*);
pa_stream_success_cb_t cbSucceed;
pa_operation * myOperation = nullptr;
};
void FinishedDrain(pa_stream *s, int success, void *userdata)
{
TJCALLBACK * theCallback = reinterpret_cast<TJCALLBACK*>(userdata);
theCallback->didFinish =1;
pa_operation_cancel(theCallback->myOperation);
}

int LoadWav(const char * path, WAVE_FILE & returnedWave)
{

int result = 0; //zero is good
unsigned long dwChunktype = 0;
unsigned long dwChunkDataSize = 0;
unsigned long dwRiffDataSize = 0;
unsigned long dwFileType = 0;
unsigned long bytesRead = 0;
unsigned long dwOffset = 0;
unsigned long dwIsWave = 0;
unsigned long throwAwayValue = 0;

FILE * someWaveFile = NULL;
someWaveFile = fopen(path, "r");
   if(someWaveFile == NULL)
   {
       return 1;
   }
    if(someWaveFile != NULL)
    {
        while(result == 0)
        {
        unsigned long dwRead = 0;
        dwRead = fread(&dwChunktype,1,4,someWaveFile);
            if(dwRead!= 4)
            {
                //result = -1;
                break;
            }
            bytesRead += dwRead;

             dwRead = fread(&dwChunkDataSize,1,4,someWaveFile);
            if(dwRead!= 4)
            {
               //result = -1;
                break;
            }
            bytesRead += dwRead;

            switch(dwChunktype)
            {
                case fourRIFFcc:
                {
                dwRiffDataSize = dwChunkDataSize;
                dwChunkDataSize = 4;

                dwRead = fread(&dwFileType,1,4,someWaveFile);
                    if(dwRead!= 4)
                    {
                        result = -1;
                        break;
                    }
                bytesRead += dwRead;
                break;
                }
                case fourWAVEcc:
                {

                    dwRead = fread(&dwIsWave,1,4,someWaveFile);
                    if(dwRead!= 4)
                    {
                        result = -1;
                        break;
                    }
                    bytesRead += dwRead;

                    break;
                }
                case fourFMTcc:
                {
                   dwRead = fread(&returnedWave.myFormat,1, dwChunkDataSize,someWaveFile);
                  if(dwRead!= dwChunkDataSize)
                    {
                        result = -1;
                        break;
                    }
                    bytesRead += dwRead;

                break;
                }
                case fourDATAcc:
                {
                returnedWave.myBuffer.bytes = new uint8_t[dwChunkDataSize];
                   dwRead = fread(returnedWave.myBuffer.bytes,1,dwChunkDataSize,someWaveFile);

                     returnedWave.myBuffer.byteSize = dwChunkDataSize;
                  if(dwRead!= dwChunkDataSize)
                    {
                    result = -1;
                    break;
                    }
                bytesRead += dwRead;
                result = 1; // break us out of loop once we've found data

                break;
                }
                default:
                {
                 dwRead = fread(&throwAwayValue,1,dwChunkDataSize,someWaveFile);
                  if(dwRead!= dwChunkDataSize)
                    {
                    result = -1;
                    }
                    bytesRead += dwRead;
                break;
                }

            }

            dwOffset +=8;
            dwOffset += dwChunkDataSize;

            if(bytesRead - 8 >= dwRiffDataSize)//excludes first 8 bytes
            {
            result = -2;
            }
        }
        fclose(someWaveFile);
    }
result = 0;
if(returnedWave.myFormat.mBitsPerSample == 8)
{
returnedWave.isSigned = false;
}
else
{
returnedWave.isSigned = true;
}
return result;

}


#define STREAMING_BUFFER_SIZE 65536
#define MAX_BUFFER_COUNT 3

class LinuxAppAudio;
class LinuxAppSound : public GSound
{
public:
    int index = -1;
    LinuxAppAudio * audio = nullptr;
    pa_channel_map * myMap = nullptr;
    pa_stream * myStream = nullptr;
    std::thread* streamThread = nullptr;
    char * streamName = "Sound";
    pa_cvolume vol;
    pa_sample_format myPulseFormat;
    WAVE_FILE myFile;
    bool loops = false;
    bool isPlaying = false;
    bool isPaused = false;
    float volume = -1.0f;
    bool stopFlag = false;
    GReturn Init();
    GReturn SetPCMShader(const char* _data);
    GReturn SetChannelVolumes(float *_values, int _numChannels);
    GReturn CheckChannelVolumes(const float *_values, int _numChannels);
    GReturn SetVolume(float _newVolume);
    GReturn GetChannels(unsigned int & returnedChannelNum );
    GReturn Play();
    GReturn Pause();
    GReturn Resume();
    GReturn StopSound();
    GReturn StreamSound();
    ~LinuxAppSound();

};

class LinuxAppMusic : public GMusic
{
private:
    unsigned int buffers[MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE];

public:
    int index = -1;
    LinuxAppAudio * audio = nullptr;
    pa_channel_map * myMap = nullptr;
    pa_stream * myStream = nullptr;
    std::thread* streamThread = nullptr;
    char * streamName = "Sound";
    pa_cvolume vol;
    pa_sample_format myPulseFormat;
    WAVE_FILE myFile;
    bool loops = false;
    bool isPlaying = false;
    bool isPaused = false;
    float volume = -1.0f;
    bool stopFlag = false;
    GReturn Init();
    GReturn SetPCMShader(const char* _data);
    GReturn SetChannelVolumes(float *_values, int _numChannels);
    GReturn CheckChannelVolumes(const float *_values, int _numChannels);
    GReturn GetChannels(unsigned int & returnedChannelNum);
    GReturn SetVolume(float _newVolume);
    GReturn StreamStart();
    GReturn Stream();
    GReturn PauseStream();
    GReturn ResumeStream();
    GReturn StopStream();
    ~LinuxAppMusic();



};


class LinuxAppAudio : public GAudio
{
public:

    std::vector<LinuxAppSound *> activeSounds;
    std::vector<LinuxAppMusic *> activeMusic;
    pa_mainloop * myMainLoop = nullptr;
    pa_context * myContext = nullptr;
    float maxVolume = 1;
    int maxChannels = 0;

    GReturn Init();
    GReturn CreateSound(const char* _path, GSound** _outSound);
    GReturn CreateMusicStream(const char* _path, GMusic** _outMusic);
    GReturn SetMasterVolume(float _value);
    GReturn SetMasterChannelVolumes(const float * _values, int _numChannels);
    GReturn PauseAll();
    GReturn ResumeAll();
    GReturn StopAll();
    ~LinuxAppAudio();

};

static bool WaitForConnectionEstablished(pa_mainloop * mainLoop, pa_context * aContext, time_t timeOut)
{
time_t timeLimit = time(NULL) + timeOut;
    while(timeLimit >= time (NULL))
    {

    int yo = pa_mainloop_iterate(mainLoop,0,NULL);
        if(PA_CONTEXT_READY == pa_context_get_state(aContext))
        {
        return true;
        }
    }

    return false;
}
GReturn LinuxAppSound::StreamSound()
{
    GReturn theResult = SUCCESS;

TJCALLBACK myCallback;
myCallback.didSucceed = FinishedDrain;
myCallback.cbSucceed = myCallback.didSucceed;
const time_t t0 = time(nullptr);
unsigned int playBackPt = 0;
unsigned int loopcount = 0;
time_t prevT = time(nullptr) -1;

        isPlaying = true;
        isPaused = false;
        bool writeSizeWasZero = false;
        // pa_stream_begin_write(myStream, myFile.myBuffer.bytes, myFile.myBuffer.byteSize);
        while(true)
        {
            if(stopFlag == true)
            {
                pa_stream_cancel_write((myStream));

                break;
            }
        if(isPaused != true)
        {


            if(time(nullptr) != prevT)
            {
                prevT = time(nullptr);
            }
            pa_stream_state_t state =  pa_stream_get_state(myStream);
         if(PA_STREAM_READY == state)
            {
                 loopcount++;

                const size_t writeableSize = pa_stream_writable_size(myStream);
                const size_t sizeRemain = myFile.myBuffer.byteSize - playBackPt;
                const size_t writeSize = (sizeRemain < writeableSize ? sizeRemain : writeableSize);

                if(writeSize > 0)
                {

                    pa_stream_write(myStream, myFile.myBuffer.bytes + playBackPt , writeSize,nullptr, 0, PA_SEEK_RELATIVE);
                    playBackPt +=writeSize;

                }
                else if (writeableSize > 0 &&myCallback.didFinish != 1)
                {
                      myCallback.myOperation = pa_stream_drain(myStream,myCallback.cbSucceed,&myCallback);
                        pa_mainloop_iterate(audio->myMainLoop,0,nullptr);

                       break;
                }


            }



      pa_mainloop_iterate(audio->myMainLoop,0,nullptr);

        }
        }
    if(stopFlag == false)
    {


        while(true)
        {
            if(myCallback.didFinish == 1)
            {
            isPlaying = false;
            isPaused = true;
            break;
            }
        pa_mainloop_iterate(audio->myMainLoop,0,nullptr);
        }
    }
    return theResult;
}
//Start of GSound implementation
GReturn LinuxAppSound::Init()
{
    GReturn result = GReturn::FAILURE;
    if(audio == nullptr)
        return result;
     result = REDUNDANT_OPERATION;
    if(myStream != nullptr)
        return result;
    if(myMap != nullptr)
        return result;
    result = FAILURE;
    switch(myFile.myFormat.mBitsPerSample)
    {
    case 8:
    myPulseFormat = PA_SAMPLE_U8;
        break;
    case 16:
    myPulseFormat = PA_SAMPLE_S16LE;
        break;
    default:
    myPulseFormat = PA_SAMPLE_S16LE;
        break;
    }
    int rate = myFile.myFormat.mSamples;
    int Channels = myFile.myFormat.mNumChannels;
    vol.channels = Channels;
    vol.values[0] = 1.0f;
    pa_sample_spec mySampleSpec = {myPulseFormat,rate,Channels};
    int paCheck = 0;
    paCheck = pa_channels_valid(mySampleSpec.channels);
    myMap = new pa_channel_map();
    myMap = pa_channel_map_init_extend(myMap, mySampleSpec.channels,PA_CHANNEL_MAP_DEFAULT);
    if(myMap == nullptr)
        return result;


    myStream = pa_stream_new(audio->myContext,"Sound",&mySampleSpec,nullptr);
    if(myStream == nullptr)
        return result;
    int pcheck = pa_stream_connect_playback(myStream,NULL,NULL,(pa_stream_flags_t)0,NULL,NULL);

    if(pa_stream_get_context(myStream) != audio->myContext)
    {
        return result;
    }
pcheck = pa_stream_get_index(myStream);
pcheck = pa_stream_get_device_index(myStream);

    result = SUCCESS;
    return result;
}
GReturn LinuxAppSound::SetPCMShader(const char* _data)
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;

    return result;
}
GReturn LinuxAppSound::SetChannelVolumes(float * _values, int _numChannels)
{
    GReturn result = GReturn::INVALID_ARGUMENT;
    if (_numChannels <= 0)
        return result;
    if (audio == nullptr)
        return result;

    if (_values == nullptr)
        return result;
    result = GReturn::FAILURE;
    for (int i = 0; i < _numChannels; i++)
    {
        //try
        {
            if (_values[i] > audio->maxVolume)
            {
                _values[i] = audio->maxVolume;
            }
        }


    }

    //if (FAILED(theResult = mySourceVoice->SetChannelVolumes(_numChannels, _values)))

    return result;
}
GReturn LinuxAppSound::CheckChannelVolumes(const float * _values, int _numChannels)
{
    GReturn result = GReturn::FAILURE;
    if (_numChannels <= 0)
        return result;
    if (audio == nullptr)
        return result;

    if (_values == nullptr)
        return result;

    unsigned int currentChannels;
    result = GetChannels(currentChannels);
    if (result != SUCCESS)
        return result;
    float * currentValues = new float[currentChannels];

//    mySourceVoice->GetChannelVolumes(_numChannels, currentValues);
    if (currentValues == nullptr)
        return result;

    bool didChange = false;
    for (int i = 0; i < _numChannels; i++)
    {
        //try
        {
            if (currentValues[i] > _values[i])
            {
                currentValues[i] = _values[i];
                didChange = true;
            }
        }
    }



    if (didChange == true)
    {

    }

    return result;
}
GReturn LinuxAppSound::GetChannels(unsigned int & returnedChannelNum)
{
    GReturn result = FAILURE;
    if (audio == nullptr)
    {
        return result;
    }
//    returnedChannelNum = myWFM.nChannels;
//    result = SUCCESS;
    return result;
}
GReturn LinuxAppSound::SetVolume(float _newVolume)
{
    GReturn result = INVALID_ARGUMENT;
    if (_newVolume < 0.0f)
        return result;
    result = SUCCESS;
    if (audio == nullptr)
        return result;



    if (_newVolume > audio->maxVolume)
    {
        _newVolume = audio->maxVolume;
    }


    return result;
}

GReturn LinuxAppSound::Play()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;
    if(myStream == nullptr)
        return result;
bool checkforunderflow = true;
if (!isPlaying)
    {
        streamThread = new std::thread(&LinuxAppSound::StreamSound, this);

    }

    result = SUCCESS;
    return result;
}
GReturn LinuxAppSound::Pause()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;

    if (!isPaused)
    {
    //TODO insert code
        isPlaying = false;
        isPaused = true;
    }
    //result = SUCCESS;
    return result;

}
GReturn LinuxAppSound::Resume()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;


    if (!isPlaying)
    {

        isPlaying = true;
        isPaused = false;
    }
    //result = SUCCESS;
    return result;
}
GReturn LinuxAppSound::StopSound()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;



    isPlaying = false;
    isPaused = true;

    result = SUCCESS;
    return result;
}
LinuxAppSound::~LinuxAppSound()
{


}
//End of GSound implementation

//Start of GMusic implementation
GReturn LinuxAppMusic::Init()
{
    GReturn result = GReturn::FAILURE;
    if(audio == nullptr)
        return result;
     result = REDUNDANT_OPERATION;
    if(myStream != nullptr)
        return result;
    if(myMap != nullptr)
        return result;
    result = FAILURE;
    switch(myFile.myFormat.mBitsPerSample)
    {
    case 8:
    myPulseFormat = PA_SAMPLE_U8;
        break;
    case 16:
    myPulseFormat = PA_SAMPLE_S16LE;
        break;
    default:
    myPulseFormat = PA_SAMPLE_S16LE;
        break;
    }
    int rate = myFile.myFormat.mSamples;
    int Channels = myFile.myFormat.mNumChannels;
    pa_sample_spec mySampleSpec = {myPulseFormat,rate,Channels};
    int paCheck = 0;
    paCheck = pa_channels_valid(mySampleSpec.channels);
    myMap = new pa_channel_map();
    myMap = pa_channel_map_init_extend(myMap, mySampleSpec.channels,PA_CHANNEL_MAP_DEFAULT);
    if(myMap == nullptr)
        return result;
    static char * name = "sound";
    myStream = pa_stream_new(audio->myContext,name,&mySampleSpec,myMap);
    if(myStream == nullptr)
        return result;
    result = SUCCESS;
    return result;
}
GReturn LinuxAppMusic::SetPCMShader(const char* _data)
{
    GReturn result = FAILURE;

    return result;
}
GReturn LinuxAppMusic::SetChannelVolumes(float * _values, int _numChannels)
{
    GReturn result = INVALID_ARGUMENT;
    if (_numChannels <= 0)
        return result;
    if (audio == nullptr)
        return result;

    if (_values == nullptr)
        return result;
    result = FAILURE;
    for (int i = 0; i < _numChannels; i++)
    {
        //try
        {
            if (_values[i] > audio->maxVolume)
            {
                _values[i] = audio->maxVolume;
            }
        }


    }

    return result;
}
GReturn LinuxAppMusic::CheckChannelVolumes(const float * _values, int _numChannels)
{
    GReturn result = GReturn::INVALID_ARGUMENT;
    if (_numChannels <= 0)
        return result;
    if (audio == nullptr)
        return result;

    if (_values == nullptr)
        return result;

    result = FAILURE;
    unsigned int currentChannels;
    result = GetChannels(currentChannels);
    if (result != SUCCESS)
        return result;
    float * currentValues = new float [currentChannels];

    if (currentValues == nullptr)
        return result;

    bool didChange = false;
    for (int i = 0; i < _numChannels; i++)
    {
        //try
        {
            if (currentValues[i] > _values[i])
            {
                currentValues[i] = _values[i];
                didChange = true;
            }
        }


    }

    if (didChange == true)
    {

    }

    return result;
}
GReturn LinuxAppMusic::GetChannels(unsigned int & returnedChannelNum)
{
    GReturn result = FAILURE;
    if (audio == nullptr)
    {
        return result;
    }
    result = INVALID_ARGUMENT;
    if (returnedChannelNum <= 0)
        return result;
//    returnedChannelNum = myWFM.nChannels;
    result = SUCCESS;
    return result;
}
GReturn LinuxAppMusic::SetVolume(float _newVolume)
{
    GReturn result = FAILURE;
    if (audio == nullptr)
        return result;

    result = INVALID_ARGUMENT;
    if (_newVolume < 0.0f)
        return result;
    result = FAILURE;
    if (_newVolume > audio->maxVolume)
    {
        _newVolume = audio->maxVolume;
    }

    result = SUCCESS;

    return result;
}
GReturn LinuxAppMusic::Stream()
{
}
GReturn LinuxAppMusic::StreamStart()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;


    if (!isPlaying)
    {
        stopFlag = false;

        isPlaying = true;
        isPaused = false;

        //if can't find file for unit tests, use : _wgetcwd to see where to put test file

        //checks the file type, expects a WAVE or XWMA
        //returns false otherwise





        //streamThread = new std::thread(&WindowAppMusic::Stream, this);

        //streamThread->detach();
    }
    //result = SUCCESS;
    return result;
}
GReturn LinuxAppMusic::PauseStream()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;
        return result;

    if (!isPaused)
    {

        isPlaying = false;
        isPaused = true;
    }
    result = SUCCESS;
    return result;
}
GReturn LinuxAppMusic::ResumeStream()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;


    if (!isPlaying)
    {

        isPlaying = true;
        isPaused = false;
    }
    result = SUCCESS;
    return result;
}
GReturn LinuxAppMusic::StopStream()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;

    //if (streamThread == nullptr)
        //return result;

    stopFlag = true;
    //streamThread->join();

    isPlaying = false;
    isPaused = true;

    result = SUCCESS;
    return result;
}
LinuxAppMusic::~LinuxAppMusic()
{

}
//End of GMusic implementation
GReturn LinuxAppAudio::Init()
{
    GReturn result = FAILURE;
    myMainLoop = pa_mainloop_new();
    if(NULL == myMainLoop)
    {
        return result;
    }
    myContext = pa_context_new(pa_mainloop_get_api(myMainLoop),"StartAudio");
    if(NULL == myContext)
    {
        return result;
    }
    pa_context_connect(myContext, NULL, (pa_context_flags_t)0,NULL);
    bool connected = WaitForConnectionEstablished(myMainLoop, myContext, 45);
    if(connected)
    {
        result = SUCCESS;
    }
    return result;
}
GReturn LinuxAppAudio::CreateSound(const char* _path, GSound** _outSound)
{

    GReturn result = FAILURE;
    if (_outSound == nullptr)
    {
        result = INVALID_ARGUMENT;
        return result;
    }
    LinuxAppSound* snd = new LinuxAppSound();

    if (snd == nullptr)
    {
        result = FAILURE;
        return result;
    }

    int check = LoadWav(_path,snd->myFile);
    if(check != 0)
    {
        if(result > 0)
        {
            result = INVALID_ARGUMENT;
        }
        else
        {
            result = FAILURE;
        }
        return result;
    }
    snd->audio = this;
    result = snd->Init();
    if(result != SUCCESS)
    {
        return result;
    }
    activeSounds.push_back(snd);
    *_outSound = snd;

    result = SUCCESS;
    return result;
}
GReturn LinuxAppAudio::CreateMusicStream(const char* _path, GMusic** _outMusic)
{
    GReturn result = FAILURE;

    if (_outMusic == nullptr)
    {
        result = INVALID_ARGUMENT;
        return result;
    }
    LinuxAppMusic* msc = new LinuxAppMusic();

    if (msc == nullptr)
    {
        result = FAILURE;
        return result;
    }
    int check = LoadWav(_path,msc->myFile);
    if(check != 0)
    {
        if(result > 0)
        {
            result = INVALID_ARGUMENT;
        }
        else
        {
            result = FAILURE;
        }
        return result;
    }
    msc->audio = this;
    result = msc->Init();
    if (result != SUCCESS)
    {
        return result;
    }
    result = SUCCESS;
    activeMusic.push_back(msc);
    *_outMusic = msc;

    return result;
}
GReturn LinuxAppAudio::SetMasterVolume(float _value)
{
    GReturn result = INVALID_ARGUMENT;
    if (_value < 0.0)
    {
        return result;
    }
    result = SUCCESS;
    if (_value > 1.0)
    {
        maxVolume = 1.0;
    }
    else
    {
        maxVolume = _value;

    }
    return result;
}
GReturn LinuxAppAudio::SetMasterChannelVolumes(const float * _values, int _numChannels)
{

    GReturn result = INVALID_ARGUMENT;
    if (_values == nullptr)
        return result;
    if (_numChannels < 0)
        return result;
    result = FAILURE;
    unsigned int theirChannels;
    for (int i = 0; i < activeSounds.size(); i++)
    {
        result = activeSounds[i]->GetChannels(theirChannels);
        if (result != SUCCESS)
        {
            result = activeSounds[i]->CheckChannelVolumes(_values, theirChannels);
        }

        if (result != SUCCESS)
        {
    //result = activeSounds[i]->CheckChannelVolumes(_values, theirChannels);
        }
    }
    for (int i = 0; i < activeMusic.size(); i++)
    {
        result = activeMusic[i]->GetChannels(theirChannels);
        if (result != SUCCESS)
        {
                result = activeMusic[i]->CheckChannelVolumes(_values, _numChannels);
        }

        if (result != SUCCESS)
        {
                result = activeMusic[i]->CheckChannelVolumes(_values, _numChannels);
        }
    }
    result = FAILURE;
    return result;
}
GReturn LinuxAppAudio::PauseAll()
{
    GReturn result = FAILURE;
    for (int i = 0; i < activeSounds.size(); i++)
    {
        result = activeSounds[i]->Pause();
        if (result != SUCCESS)
        {

        result = activeMusic[i]->PauseStream();
        }
    }
    for (int i = 0; i < activeMusic.size(); i++)
    {
        if (result != SUCCESS)
        {

        result = activeMusic[i]->PauseStream();
        }
    }
    result = FAILURE;
    return result;
}
GReturn LinuxAppAudio::StopAll()
{
    GReturn result = FAILURE;
//    for (int i = 0; i < activeSounds.size(); i++)
    {
        //result = activeSounds[i]->StopSound();
        if (result != SUCCESS)
        {
            return result;
        }
    }
//    for (int i = 0; i < activeMusic.size(); i++)
    {
        //result = activeMusic[i]->StopStream();
        if (result != SUCCESS)
        {
            return result;
        }
    }
    result = FAILURE;
    return result;
}
GReturn LinuxAppAudio::ResumeAll()
{
    GReturn result = FAILURE;
    //for (int i = 0; i < activeSounds.size(); i++)
    {
        //result = activeSounds[i]->Resume();
        if (result != SUCCESS)
        {
            return result;
        }
    }
    //for (int i = 0; i < activeMusic.size(); i++)
    {
        //result = activeMusic[i]->ResumeStream();
        if (result != SUCCESS)
        {
            return result;
        }
    }
    result = FAILURE;
    return result;
}
LinuxAppAudio::~LinuxAppAudio()
{

}





//Start of GAudio implementation for Windows
GReturn PlatformGetAudio(GAudio ** _outAudio)
{
    GReturn result = FAILURE;
    if (_outAudio == nullptr)
    {
        result = INVALID_ARGUMENT;
        return result;
    }
    LinuxAppAudio* audio = new LinuxAppAudio();

    if (audio == nullptr)
    {
        result = FAILURE;
        return result;
    }
    audio->Init();

    if (result == INVALID_ARGUMENT)
        return result;

    *_outAudio = audio;
    result = SUCCESS;
    return result;
}
//End of GMusic implementation for Windows
