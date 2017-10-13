// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"

#include "../../Interface/G_Audio/GAudio.h"

using namespace GW;
using namespace AUDIO;
#include <iostream>
#include <time.h>
#include <vector>
#include <thread>
#include <mutex>

#include <string.h>
#include <pulse/mainloop.h>
#include <pulse/thread-mainloop.h>
#include <pulse/context.h>
#include <pulse/stream.h>
#include <pulse/error.h>
#include <pulse/scache.h>
#include <pulse/introspect.h>

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
volatile int didFinish = -1;
pa_threaded_mainloop * myMainLoop = nullptr;
void(*streamOperationSucceed)(pa_stream*,int,void*);
void(*contextOperationSucceed)(pa_context*,int,void*);
pa_stream_success_cb_t cbSucceed;
pa_stream_request_cb_t streamReaquestSucceed;
pa_context_success_cb_t cbContextSucceed;
pa_operation * myOperation = nullptr;
};
void FinishedContextGeneral(pa_context *c, int success, void *userdata)
{
TJCALLBACK * theCallback = reinterpret_cast<TJCALLBACK*>(userdata);
theCallback->didFinish =1;

}
void FinishedDrain(pa_stream *s, int success, void *userdata)
{
TJCALLBACK * theCallback = reinterpret_cast<TJCALLBACK*>(userdata);
theCallback->didFinish =1;

}
void FinishedWrite(pa_stream *s, int success, void *userdata)
{

TJCALLBACK * theCallback = reinterpret_cast<TJCALLBACK*>(userdata);
pa_threaded_mainloop_lock(theCallback->myMainLoop);
theCallback->didFinish =1;
 pa_threaded_mainloop_signal(theCallback->myMainLoop,0);
 pa_threaded_mainloop_unlock(theCallback->myMainLoop);
}
int LoadWavFormatOnly(const char * path, PCM_FORMAT_INFO & returnedInfo, unsigned long & _fileSize)
{
    int result = 0; //zero is good
unsigned long dwChunktype = 0;
unsigned long dwChunkDataSize = 0;
unsigned long dwRiffDataSize = 0;
unsigned long dwFileType = 0;
unsigned long bytesRead = 0;
unsigned long dwOffset = 0;
unsigned long throwAway;

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
                result = -1;
                break;
            }
            bytesRead += dwRead;

             dwRead = fread(&dwChunkDataSize,1,4,someWaveFile);
            if(dwRead!= 4)
            {
               result = -1;
                break;
            }
            bytesRead += dwRead;

            switch(dwChunktype)
            {
                case fourRIFFcc:
                {
                dwRiffDataSize = dwChunkDataSize;
                dwChunkDataSize = 4;
                _fileSize = dwRiffDataSize;
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

                    dwRead = fread(&throwAway,1,4,someWaveFile);
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
                   dwRead = fread(&returnedInfo,1, dwChunkDataSize,someWaveFile);
                  if(dwRead!= dwChunkDataSize)
                    {
                        result = -1;
                        break;
                    }
                    bytesRead += dwRead;
                   result = 1; // break out of loop
                break;
                }


        }

    }
  fclose(someWaveFile);
if(result > 0)
    result = 0;
return result;
    }
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
public:
    int index = -1;
    char * myFilePath;
    LinuxAppAudio * audio = nullptr;
    pa_channel_map * myMap = nullptr;
    pa_stream * myStream = nullptr;
    std::thread* streamThread = nullptr;
    char * streamName = "Sound";
    unsigned long fileSize = 0;
    pa_sample_format myPulseFormat;

    PCM_FORMAT_INFO myPCMFormat;
    PCM_BUFFER myBuffers[MAX_BUFFER_COUNT];
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
    GReturn StreamMusic();
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
    std::thread* streamThread = nullptr;
   // pa_mainloop * myMainLoop = nullptr;
   pa_threaded_mainloop * myThreadedMainLoop = nullptr;
    pa_context * myContext = nullptr;
    int request = 0;
    bool isIterating = false;
    float maxVolume = 1;
    int maxChannels = 0;
    int quitVal = 0;
    GReturn Init();
    GReturn CreateSound(const char* _path, GSound** _outSound);
    GReturn CreateMusicStream(const char* _path, GMusic** _outMusic);
    GReturn SetMasterVolume(float _value);
    GReturn SetMasterChannelVolumes(const float * _values, int _numChannels);
    GReturn PauseAll();
    GReturn ResumeAll();
    GReturn StopAll();
    void Iterate();
    ~LinuxAppAudio();

};

static bool WaitForConnectionEstablished(pa_threaded_mainloop * mainLoop, pa_context * aContext, time_t timeOut)
{
time_t timeLimit = time(NULL) + timeOut;
    while(timeLimit >= time (NULL))
    {

    //int yo = pa_mainloop_iterate(mainLoop,0,NULL);
        if(PA_CONTEXT_READY == pa_context_get_state(aContext))
        {
        return true;
        }
    }

    return false;
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
     GReturn result = INVALID_ARGUMENT;
    if (_numChannels <= 0)
        return result;
    if (audio == nullptr)
        return result;

    if (_values == nullptr)
        return result;
        pa_volume_t * newValues = new pa_volume_t[_numChannels];
        pa_cvolume theVolume;
    theVolume.channels = _numChannels;

    result = FAILURE;
    for (int i = 0; i < _numChannels; i++)
    {
            if (_values[i] > audio->maxVolume)
            {
                _values[i] = audio->maxVolume;
            }
            newValues[i] = _values[i];
            theVolume.values[i] = newValues[i];
    }
    TJCALLBACK theCallback;
    theCallback.contextOperationSucceed = FinishedContextGeneral;
    theCallback.cbContextSucceed = theCallback.contextOperationSucceed;
    uint32_t index = pa_stream_get_device_index(myStream);
    pa_context_set_sink_input_volume(audio->myContext,index,&theVolume, theCallback.cbContextSucceed, &theCallback);

    result = SUCCESS;
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
GReturn LinuxAppSound::StreamSound()
{
    GReturn theResult = SUCCESS;
std::mutex myMutex;
TJCALLBACK myCallback;
myCallback.streamOperationSucceed = FinishedDrain;
myCallback.cbSucceed = myCallback.streamOperationSucceed;

TJCALLBACK writeCallback;
writeCallback.streamOperationSucceed = FinishedWrite;
writeCallback.cbSucceed = writeCallback.streamOperationSucceed;
writeCallback.myMainLoop = audio->myThreadedMainLoop;
const time_t t0 = time(nullptr);
unsigned int playBackPt = 0;
 pa_stream_state_t state;
time_t prevT = time(nullptr) -1;
pa_stream_set_write_callback(myStream,writeCallback.streamReaquestSucceed,&writeCallback);
        isPlaying = true;
        isPaused = false;
        bool writeSizeWasZero = false;


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
                    pa_threaded_mainloop_lock(audio->myThreadedMainLoop);
             state =  pa_stream_get_state(myStream);
                            pa_threaded_mainloop_unlock(audio->myThreadedMainLoop);
         if(PA_STREAM_READY == state)
            {

                      pa_threaded_mainloop_lock(audio->myThreadedMainLoop);
                const size_t writeableSize = pa_stream_writable_size(myStream);
                const size_t sizeRemain = myFile.myBuffer.byteSize - playBackPt;
                const size_t writeSize = (sizeRemain < writeableSize ? sizeRemain : writeableSize);

                if(writeSize > 0)
                {

                    pa_stream_write(myStream, myFile.myBuffer.bytes + playBackPt , writeSize,nullptr, 0, PA_SEEK_RELATIVE);
                    playBackPt +=writeSize;
                    pa_threaded_mainloop_wait(audio->myThreadedMainLoop);

                }
                else if (writeableSize > 0 &&myCallback.didFinish != 1)
                {
                      myCallback.myOperation = pa_stream_drain(myStream,myCallback.cbSucceed,&myCallback);
                       pa_threaded_mainloop_unlock(audio->myThreadedMainLoop);
                       break;
                }

          pa_threaded_mainloop_unlock(audio->myThreadedMainLoop);
            }

if(writeCallback.didFinish == 1)
{
     pa_threaded_mainloop_accept(audio->myThreadedMainLoop);
}

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

        }
    }
    return theResult;
}
GReturn LinuxAppSound::Play()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;
    if(myStream == nullptr)
        return result;

if (!isPlaying)
    {
        stopFlag = false;
        streamThread = new std::thread(&LinuxAppSound::StreamSound, this);
        result = SUCCESS;
    }
    else
    {
        result = REDUNDANT_OPERATION;
    }

    return result;
}
GReturn LinuxAppSound::Pause()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;
    TJCALLBACK myCallback;
    if(isPlaying)
    {
        pa_stream_cork(myStream, 1, myCallback.cbSucceed,&myCallback );
        int value = pa_stream_is_corked(myStream);
        if(value == 1)
        {
            isPaused = true;
            isPlaying = false;
        }
    }
    if (!isPaused)
    {
        isPlaying = false;
        isPaused = true;
    }
    result = SUCCESS;
    return result;

}
GReturn LinuxAppSound::Resume()
{

    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;
    TJCALLBACK myCallback;
    if(!isPlaying)
    {
        pa_stream_cork(myStream, 0, myCallback.cbSucceed,&myCallback );
        int value = pa_stream_is_corked(myStream);
        if(value == 1)
        {
            isPaused = false;
            isPlaying = true;
        }
    }
    if (isPaused)
    {
        isPlaying = true;
        isPaused = false;
    }
    result = SUCCESS;
    return result;

}
GReturn LinuxAppSound::StopSound()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;
   if (streamThread == nullptr)
        return result;
    result = REDUNDANT_OPERATION;
    if(stopFlag == true)
        return result;
    stopFlag = true;
    streamThread->join();

    isPlaying = false;
    isPaused = true;

    delete streamThread;
    streamThread = nullptr;

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
GReturn result = GReturn::INVALID_ARGUMENT;
 if(audio == nullptr)
        return result;
     result = REDUNDANT_OPERATION;
    if(myStream != nullptr)
        return result;
    if(myMap != nullptr)
        return result;
    result = FAILURE;
    switch(myPCMFormat.mBitsPerSample)
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
    int rate = myPCMFormat.mSamples;
    int Channels = myPCMFormat.mNumChannels;

    pa_sample_spec mySampleSpec = {myPulseFormat,rate,Channels};
    int paCheck = 0;
    paCheck = pa_channels_valid(mySampleSpec.channels);
    myMap = new pa_channel_map();
    myMap = pa_channel_map_init_extend(myMap, mySampleSpec.channels,PA_CHANNEL_MAP_WAVEEX);
    if(myMap == nullptr)
        return result;

    myBuffers[0].bytes = new uint8_t[STREAMING_BUFFER_SIZE];
     myBuffers[1].bytes = new uint8_t[STREAMING_BUFFER_SIZE];
      myBuffers[2].bytes = new uint8_t[STREAMING_BUFFER_SIZE];

 myBuffers[0].byteSize = fileSize;
 myBuffers[1].byteSize = fileSize;
 myBuffers[2].byteSize = fileSize;
    myStream = pa_stream_new(audio->myContext,"Music",&mySampleSpec,nullptr);
    if(myStream == nullptr)
        return result;
    int pcheck = pa_stream_connect_playback(myStream,NULL,NULL,(pa_stream_flags_t)0,NULL,NULL);
     pa_stream_state_t state =  pa_stream_get_state(myStream);
    if(pa_stream_get_context(myStream) != audio->myContext)
    {
        return result;
    }

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
        pa_volume_t * newValues = new pa_volume_t[_numChannels];
        pa_cvolume theVolume;
    theVolume.channels = _numChannels;

    result = FAILURE;
    for (int i = 0; i < _numChannels; i++)
    {
            if (_values[i] > audio->maxVolume)
            {
                _values[i] = audio->maxVolume;
            }
            newValues[i] = _values[i];
            theVolume.values[i] = newValues[i];
    }
    TJCALLBACK theCallback;
    theCallback.contextOperationSucceed = FinishedContextGeneral;
    theCallback.cbContextSucceed = theCallback.contextOperationSucceed;
    uint32_t index = pa_stream_get_device_index(myStream);
    pa_context_set_sink_input_volume(audio->myContext,index,&theVolume, theCallback.cbContextSucceed, &theCallback);

    result = SUCCESS;
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
    if(myFilePath == nullptr)
    {
        return result;
    }
    result = INVALID_ARGUMENT;
    if (returnedChannelNum <= 0)
        return result;

    returnedChannelNum = myPCMFormat.mNumChannels;
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
GReturn LinuxAppMusic::StreamMusic()
{
GReturn theResult = SUCCESS;



TJCALLBACK myCallback;
myCallback.streamOperationSucceed = FinishedDrain;
myCallback.cbSucceed = myCallback.streamOperationSucceed;
const time_t t0 = time(nullptr);
unsigned int playBackPt = 0;
unsigned int currplayBackPt = 0;

        FILE * someWaveFile = NULL;
someWaveFile = fopen(myFilePath, "r");

    if(someWaveFile == NULL)
   {
       return FAILURE;
   }
    int yo = 0;
   unsigned long dwChunktype = 0;
unsigned long dwChunkDataSize = 0;
unsigned long bytesRead = 0;
unsigned long throwAway = 0;
   unsigned long dwRead = 0;
   unsigned int breakOut = -1;
PCM_FORMAT_INFO throwAwayInfo;
std::mutex MyMutex;

    // read the first 12 bytes for the file for RIFF data
   if(someWaveFile != NULL)
    {
        while(breakOut == -1)
        {
        unsigned long dwRead = 0;
        dwRead = fread(&dwChunktype,1,4,someWaveFile);
            if(dwRead!= 4)
            {
                return FAILURE;
            }
            bytesRead += dwRead;

             dwRead = fread(&dwChunkDataSize,1,4,someWaveFile);
            if(dwRead!= 4)
            {
                  return FAILURE;
            }
            bytesRead += dwRead;

            switch(dwChunktype)
            {
                case fourRIFFcc:
                {

                dwChunkDataSize = 4;

                dwRead = fread(&throwAway,1,4,someWaveFile);
                    if(dwRead!= 4)
                    {
                           return FAILURE;
                    }
                bytesRead += dwRead;
                 break;
                }
                case fourWAVEcc:
                {

                    dwRead = fread(&throwAway,1,4,someWaveFile);
                    if(dwRead!= 4)
                    {
                           return FAILURE;
                    }
                    bytesRead += dwRead;

                    break;
                }
                case fourFMTcc:
                {
                   dwRead = fread(&throwAwayInfo,1, dwChunkDataSize,someWaveFile);
                  if(dwRead!= dwChunkDataSize)
                    {
                          return FAILURE;
                    }
                    bytesRead += dwRead;
                    breakOut = 1;
                break;
                }
        }

    }
      fread(myBuffers[0].bytes,1,STREAMING_BUFFER_SIZE,someWaveFile);
            fread(myBuffers[1].bytes,1,STREAMING_BUFFER_SIZE,someWaveFile);
                  fread(myBuffers[2].bytes,1,STREAMING_BUFFER_SIZE,someWaveFile);

    }
int prevbuffer = 2;
int nextBuffer = 1;
unsigned int readSize = (STREAMING_BUFFER_SIZE * 3 < fileSize-playBackPt? STREAMING_BUFFER_SIZE : fileSize - playBackPt);
time_t prevT = time(nullptr) -1;
unsigned int currentBuffer = 0;
isPlaying = true;
isPaused = false;
bool writeSizeWasZero = false;
bool ready = false;
 pa_stream_state_t state;
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
            MyMutex.lock();
         state  =  pa_stream_get_state(myStream);
            MyMutex.unlock();
         if(PA_STREAM_READY == state)
            {


                const size_t writeableSize = pa_stream_writable_size(myStream);
                const size_t sizeRemain = STREAMING_BUFFER_SIZE - currplayBackPt;
                const size_t writeSize = (sizeRemain < writeableSize ? sizeRemain : writeableSize);
                readSize = (STREAMING_BUFFER_SIZE < fileSize-playBackPt? STREAMING_BUFFER_SIZE : fileSize - playBackPt);
                if(writeSize > 0)
                {
                    pa_stream_write(myStream, myBuffers[currentBuffer].bytes + currplayBackPt , writeSize,nullptr, 0, PA_SEEK_RELATIVE);
                    playBackPt +=writeSize;
                    currplayBackPt += writeSize;
                  //  ready = true;
                }
                else if(writeableSize > 0 && fileSize - playBackPt > 0 )
                {
                    ready = true;
                    currplayBackPt = 0;
                }
                else if (writeableSize > 0 &myCallback.didFinish != 1)
                {
                      myCallback.myOperation = pa_stream_drain(myStream,myCallback.cbSucceed,&myCallback);
                      //  pa_mainloop_iterate(audio->myMainLoop,0,nullptr);
                     MyMutex.lock();
  audio->request++;
    MyMutex.unlock();
                       break;
                }


            }

            if(PA_STREAM_FAILED == state)
            {
                const char * err = pa_strerror(pa_context_errno(audio->myContext));
                int  i = 0;


            }

    if(ready)
    {
                      currentBuffer++;
                    if(currentBuffer >= MAX_BUFFER_COUNT)
                        currentBuffer = 0;

                           prevbuffer++;
                    if(prevbuffer >= MAX_BUFFER_COUNT)
                        prevbuffer = 0;

                                      nextBuffer++;
                    if(nextBuffer >= MAX_BUFFER_COUNT)
                        nextBuffer = 0;
                    fread(myBuffers[nextBuffer].bytes,1,readSize,someWaveFile);
                    ready = false;
    }

   // pa_mainloop_iterate(audio->myMainLoop,0,nullptr);
  MyMutex.lock();
  audio->request++;
    MyMutex.unlock();
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
       MyMutex.lock();
  audio->request++;
    MyMutex.unlock();
        }
    }
    fclose(someWaveFile);
    return theResult;
}
GReturn LinuxAppMusic::StreamStart()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;
    if(myStream == nullptr)
        return result;

if (!isPlaying)
    {
        stopFlag = false;


      streamThread = new std::thread(&LinuxAppMusic::StreamMusic,this);
        result = SUCCESS;
    }
    else
    {
        result = REDUNDANT_OPERATION;
    }

    return result;
}
GReturn LinuxAppMusic::PauseStream()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;
    TJCALLBACK myCallback;
    if(isPlaying)
    {
        pa_stream_cork(myStream, 1, myCallback.cbSucceed,&myCallback );
        int value = pa_stream_is_corked(myStream);
        if(value == 1)
        {
            isPaused = true;
            isPlaying = false;
        }
    }
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
        result = SUCCESS;
    }
    else
    {
        result = REDUNDANT_OPERATION;
    }
    return result;
}
GReturn LinuxAppMusic::StopStream()
{
    GReturn result = GReturn::FAILURE;
    if (audio == nullptr)
        return result;

    if (streamThread == nullptr)
        return result;
    result = REDUNDANT_OPERATION;
    if(stopFlag == true)
        return result;
    stopFlag = true;
    streamThread->join();

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
   // myMainLoop = pa_mainloop_new();
   myThreadedMainLoop = pa_threaded_mainloop_new();
    if(NULL == myThreadedMainLoop)
    {
        return result;
    }
    myContext = pa_context_new(pa_threaded_mainloop_get_api(myThreadedMainLoop),"StartAudio");
    if(NULL == myContext)
    {
        return result;
    }
    pa_context_connect(myContext, NULL, (pa_context_flags_t)0,NULL);
    pa_threaded_mainloop_start(myThreadedMainLoop);
    bool connected = WaitForConnectionEstablished(myThreadedMainLoop, myContext, 45);
    if(connected)
    {
        result = SUCCESS;
    }
//   streamThread = new std::thread(&LinuxAppAudio::Iterate, this);

   // pa_mainloop_run(myMainLoop,NULL);
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
    int check = LoadWavFormatOnly(_path,msc->myPCMFormat, msc->fileSize);
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
    int len = strlen(_path) + 1;
    msc->myFilePath = new char[len];
    strncpy(msc->myFilePath, _path, len);

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
void LinuxAppAudio::Iterate()
{
    std::mutex MyMutex;
    int result = 0;
    while(true)
    {

        if(request > 0)
        {

            if(!isIterating)
            {
                if(isIterating == true)
                {
                continue;
                }
                      if(request <= 0)
                      {
                          continue;
                      }
                      MyMutex.lock();
//                result = pa_mainloop_prepare(myMainLoop, 0);
                MyMutex.unlock();
                if(result >=0)
                {


                isIterating = true;
                    if(request<=0)
                    {
                    continue;
                    }
MyMutex.lock();
//               result = pa_mainloop_poll(myMainLoop);
               MyMutex.unlock();
               if(result >= 0)
               {
                   MyMutex.lock();
//               pa_mainloop_dispatch(myMainLoop);
               MyMutex.unlock();
                request--;
                isIterating = false;
               }

                }
        }

   // MyMutex.lock();

     // pa_mainloop_iterate(myMainLoop, 0, &quitVal);
     // request--;
       // MyMutex.unlock();
        }

    }

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
