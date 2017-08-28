#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <CoreAudio/CoreAudio.h>
#import <AudioUnit/AudioUnit.h>
#import <CoreAudio/AudioHardware.h>
#import <AudioToolbox/AudioFileStream.h>

@interface GMacSound : NSObject
{
    @public
    NSSound * mySound;
    
  //  float maxVolume;
}
-(id) initWithPath:(NSString*) _path;
-(bool) SetPCMShader:(const char *) _data;
-(bool) SetChannelVolumes:(float *) _volumes theNumberOfChannels:(int )_numChannels;
-(bool) SetVolume:(float) _newVolume;
-(bool) PlaySound;
-(bool) PauseSound;
-(bool) ResumeSound;
-(bool) StopSound;
-(bool) Unload;

@end
@implementation GMacSound
-(id)initWithPath:(NSString*) _path
{

    self = [super init];
    if(self)
    {
        
        self->mySound = [[NSSound alloc] initWithContentsOfFile:_path byReference:YES];
    }
    return self;
}
-(bool) SetPCMShader:(const char *) _data
{
       NSLog(@"bettter not see this");
    return false;
}
-(bool) SetChannelVolumes:(float *) _volumes theNumberOfChannels:(int )_numChannels
{
       NSLog(@"Hi my names becky");

    NSArray * temp = nil;
    [mySound setChannelMapping:temp];
    return false;
}
-(bool) SetVolume:(float) _newVolume
{
    
    if(_newVolume <= 0)
        return false;
   
 
     [mySound setVolume:(_newVolume)];
     float check = [mySound volume];
         if(check == _newVolume)
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
}
-(bool) PlaySound
{

    return [mySound play];
    
}
-(bool) PauseSound
{
    
    return [mySound pause];
}
-(bool) ResumeSound
{
    
    return [mySound resume];
}
-(bool) StopSound
{
   
    return [mySound stop];
}
-(bool) Unload
{

       NSLog(@"peace");
    bool macresult = false;
    if(mySound != nil)
    {
        if([mySound isPlaying] == true)
        {
            [mySound stop];
        }
        [mySound release];
        macresult = true;
    }
    return macresult;
}

@end

@interface GMacMusic : NSObject
{
    @public
    AudioFileStreamID *myStream;
    uint8_t * myData;
    AudioFileStream_PropertyListenerProc myListener;
    AudioFileStream_PacketsProc myPackProc;
    AudioFileTypeID myHint;
    
}
-(id) initWithPath:(CFURLRef*) _path;
-(bool) SetPCMShader:(const char *) _data;
-(bool) SetChannelVolumes:(float *) _volumes theNumberOfChannels:(int )_numChannels;
-(bool) SetVolume:(float) _newVolume;
-(bool) StreamStart;
-(bool) PauseStream;
-(bool) ResumeStream;
-(bool) StopStream;
-(bool) Unload;
@end

@implementation GMacMusic
-(id)initWithPath:(CFURLRef*) _url
{
   
    self = [super init];
    if(self)
    {
        AudioFileStreamOpen(myData, myListener, myPackProc, myHint, myStream);
    }
    return self;
}
-(bool) SetPCMShader:(const char *) _data
{
    return false;
}
-(bool) SetChannelVolumes:(float *) _volumes theNumberOfChannels:(int )_numChannels
{
    return false;
}
-(bool) SetVolume:(float) _newVolume
{
    return false;
}
-(bool) StreamStart
{
    return false;
}
-(bool) PauseStream
{
    return false;
}
-(bool) ResumeStream
{
    return false;
}
-(bool) StopStream
{
    return false;
}
-(bool) Unload
{
    return false;
}

@end


@interface GMacAudio : NSObject
-(bool) Init;
-(bool) CreateSound:(const char *) _path soundPtrPtr:(GMacSound ** )_outSound;
-(bool) CreateMusicStream:(const char *) _path soundPtrPtr:(GMacMusic ** )_outMusic;
-(bool) SetMasterVolume:(float) _newVolume;
-(bool) SetMasterVolumeChannels:(const float *) _values theNumberOfChannels:(int)_numChannels;
-(bool) PauseAll;
-(bool) ResumeAll;
-(bool) Unload;
@end

@implementation GMacAudio
-(bool) Init
{
    NSLog(@"Hi");
    //setup
    AudioComponent myComp;
    AudioComponentDescription mydesc;
    AudioComponentInstance myHAL;
    mydesc.componentType = kAudioUnitType_Output;
    mydesc.componentSubType = kAudioUnitSubType_HALOutput;
    mydesc.componentManufacturer = kAudioUnitManufacturer_Apple;
    mydesc.componentFlags = 0;
    mydesc.componentFlagsMask = 0;
    
    myComp = AudioComponentFindNext(NULL, &mydesc);
    if(myComp == NULL)
    {
       return false;
    }
    AudioComponentInstanceNew(myComp, &myHAL);
    
    //Enabling IO
    UInt32 enableIO = 0;
    UInt32 size = 0;
    enableIO = 0;
    AudioUnit myUnit = nullptr;
    AudioUnitSetProperty(myUnit, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Output, 0, &enableIO, sizeof(enableIO));
    //SettingCurrDevic
    size = sizeof(AudioDeviceID);
    AudioDeviceID myDevice;
    AudioObjectPropertyAddress myAddress = {kAudioHardwarePropertyDefaultOutputDevice, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster};
    OSStatus err = noErr;
    err = AudioObjectGetPropertyData(kAudioObjectSystemObject, &myAddress, 0, NULL, &size, &myDevice);
    if(err)
    {
        return false;
    }
    
    err = AudioUnitSetProperty(myUnit, kAudioOutputUnitProperty_CurrentDevice, kAudioUnitScope_Global, 0, &myDevice, sizeof(myDevice));
    
    return false;
}
-(bool) CreateSound:(const char *) _path soundPtrPtr:(GMacSound ** )_outSound
{
       NSLog(@"oh i did tht");
    return false;
}
-(bool) CreateMusicStream:(const char *) _path soundPtrPtr:(GMacMusic ** )_outMusic
{
    return false;
}
-(bool) SetMasterVolume:(float) _newVolume
{
       NSLog(@"masta??");
    return false;
}
-(bool) SetMasterVolumeChannels:(const float *) _values theNumberOfChannels:(int)_numChannels
{
       NSLog(@"multimastas");
    return false;
}
-(bool) PauseAll
{
       NSLog(@"freeze mo");
    return false;
}
-(bool) ResumeAll
{
       NSLog(@"getup");
    return false;
}
-(bool) Unload
{
    return false;
}
#include "GAudio.cpp"
@end
