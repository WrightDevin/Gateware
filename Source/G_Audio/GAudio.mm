#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <CoreAudio/CoreAudio.h>
#import <AVFoundation/AVFoundation.h>
#import <AVFoundation/AVFAudio.h>
#import <AudioToolbox/AudioToolbox.h>

@interface GMacSound : NSObject
{
    @public
    AVAudioEngine * myAudio;
    AVAudioPlayerNode * mySound;
    AVAudioMixerNode * myMixer;
    AVAudioFile * myFile;
    AVAudioPCMBuffer * myBuffer;
    bool loops ;
    bool isPlaying;
    bool isPaused;
    float volume ;
}
-(id) initWithPath:(NSString*) _path;
-(bool) SetPCMShader:(const char *) _data;
-(unsigned int) GetChannels;
-(bool) SetChannelVolumes:(float *) _volumes theNumberOfChannels:(int )_numChannels;
-(bool) SetVolume:(float) _newVolume;
-(bool) PlaySound;
-(bool) PauseSound;
-(bool) ResumeSound;
-(bool) StopSound;


@end
@implementation GMacSound
-(id)initWithPath:(NSString*) _path
{
    NSError *testError;
    self = [super init];
    if(self)
    {
        
        self->mySound = [[AVAudioPlayerNode alloc] init];
        
         self->myMixer = [[AVAudioMixerNode alloc] init];
     
        NSURL * filePath =[[NSURL alloc] initFileURLWithPath:_path];
        self->myFile = [[AVAudioFile alloc] initForReading:filePath commonFormat:AVAudioPCMFormatFloat32 interleaved:false error:&testError];
        self->myBuffer =[[AVAudioPCMBuffer alloc] initWithPCMFormat:[self->myFile processingFormat] frameCapacity:[self->myFile length]];
      
        bool success = [self->myFile readIntoBuffer:self->myBuffer error:&testError];
        if(!success)
        {
            NSAssert(success, @"could nor read file into buffer", [testError localizedDescription]);
        }
    }
    return self;
}
-(bool) SetPCMShader:(const char *) _data
{
       NSLog(@"bettter not see this");
    return false;
}
-(unsigned int) GetChannels
{
    if(!myAudio)
        return 0;
    return [myFile processingFormat].channelCount;
}
-(bool) SetChannelVolumes:(float *) _volumes theNumberOfChannels:(int )_numChannels
{
    NSMutableArray * theValues = [[[NSMutableArray alloc] init] autorelease];
    for (int i = 0; i < _numChannels; i++)
    {
        [theValues addObject:[NSNumber numberWithFloat:_volumes[i]]];
    }
    if(theValues.count == 1)
    {
        mySound.pan = -1 * _volumes[0];
    }
    else if(theValues.count > 1)
    {
        float newVal = _volumes[1] -  _volumes[0];
        if(newVal > 1.0f)
            newVal = 1.0f;
        if(newVal < -1.0f)
            newVal = -1.0f;
        mySound.pan = newVal;
    }
    else
    {
        return false;
    }
    return true;
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


     [mySound play];
    [mySound scheduleBuffer:myBuffer atTime:nil options:AVAudioPlayerNodeBufferInterrupts completionHandler:nil];

    bool returnValue = [mySound isPlaying];
 
        return returnValue;
   
 
 //   AudioBufferList
}
-(bool) PauseSound
{
    
     [mySound pause];
    return ![mySound isPlaying];
}
-(bool) ResumeSound
{
    
     [mySound playAtTime:nil];
      return [mySound isPlaying];
}
-(bool) StopSound
{
   
     [mySound stop];
        return ![mySound isPlaying];
}
-(bool) Unload
{

   
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
//#define  MAX_BUFFER_COUNT = 3;
#define  STREAMING_BUFFER_SIZE = 65536;
@interface GMacMusic : NSObject
{
@public

    AVAudioEngine * myAudio;
    AVAudioPlayerNode * mySound;
    AVAudioMixerNode * myMixer;
    AVAudioFile * myFile;
    AVAudioPCMBuffer * myLastBuffer;
    AVAudioPCMBuffer * myBuffer;
    AVAudioPCMBuffer * myNextBuffer;
    NSThread * myScheduler;
    bool loops ;
    bool isPlaying;
    bool isPaused;
    float volume ;
    AVAudioFrameCount MaxPosition;
    AVAudioFrameCount CurrentPosition;
}
-(id) initWithPath:(NSString*) _path;
-(bool) SetPCMShader:(const char *) _data;
-(bool) SetChannelVolumes:(float *) _volumes theNumberOfChannels:(int )_numChannels;
-(bool) SetVolume:(float) _newVolume;
-(unsigned int) GetChannels;
-(bool) StreamStart:(bool) _loops;
-(bool) PauseStream;
-(bool) ResumeStream;
-(bool) StopStream;
-(void) ScheduleBuffers;
-(void) UpdateBuffers;
@end

@implementation GMacMusic
-(id)initWithPath:(NSString*) _path
{

    NSError *testError;
    self = [super init];
    if(self)
    {
        AVAudioFrameCount bufferLength = 63553;
        self->mySound = [[AVAudioPlayerNode alloc] init];
        
        self->myMixer = [[AVAudioMixerNode alloc] init];
        
        NSURL * filePath =[[NSURL alloc] initFileURLWithPath:_path];
        self->myFile = [[AVAudioFile alloc] initForReading:filePath commonFormat:AVAudioPCMFormatFloat32 interleaved:false error:&testError];
        self->myBuffer =[[AVAudioPCMBuffer alloc] initWithPCMFormat:[self->myFile processingFormat] frameCapacity:bufferLength];
        self->myLastBuffer =[[AVAudioPCMBuffer alloc] initWithPCMFormat:[self->myFile processingFormat] frameCapacity:bufferLength ];
        self->myNextBuffer =[[AVAudioPCMBuffer alloc] initWithPCMFormat:[self->myFile processingFormat] frameCapacity:bufferLength];
        
        bool success = [self->myFile readIntoBuffer:self->myBuffer error:&testError];
        success = [self->myFile readIntoBuffer:self->myNextBuffer error:&testError];
        if(!success)
        {
            NSAssert(success, @"could nor read file into buffer", [testError localizedDescription]);
        }
        MaxPosition = myFile.length;
        volume = 1;
       // myScheduler = [[NSThread alloc] initWithBlock:^{[self ScheduleBuffers];}];
     
    }
    return self;
}
-(bool) SetPCMShader:(const char *) _data
{
   
    return false;
}
-(unsigned int) GetChannels
{
    if(!myAudio)
        return 0;
    return [myFile processingFormat].channelCount;
}
-(bool) SetChannelVolumes:(float *) _volumes theNumberOfChannels:(int )_numChannels
{
    NSMutableArray * theValues = [[[NSMutableArray alloc] init] autorelease];
    for (int i = 0; i < _numChannels; i++)
    {
        [theValues addObject:[NSNumber numberWithFloat:_volumes[i]]];
    }
    if(theValues.count == 1)
    {
        mySound.pan = -1 * _volumes[0];
    }
    else if(theValues.count > 1)
    {
         float first = _volumes[0];
         float second = _volumes[1];
        float newVal = second -first;
        if(newVal > 1.0f)
            newVal = 1.0f;
        if(newVal < -1.0f)
            newVal = -1.0f;
         mySound.pan = newVal;
    }
    else
    {
        return false;
    }
    return true;
}
-(bool) SetVolume:(float) _newVolume
{
    if(_newVolume <= 0)
        return false;
    
    
    [mySound setVolume:(_newVolume)];
    float check = [mySound volume];
    volume = check;
    if(check == _newVolume)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}
-(void) ScheduleBuffers
{
    NSError *testError;
    if(CurrentPosition >= MaxPosition)
    {
        
        if(loops)
        {
            [mySound stop];
            [mySound prepareWithFrameCount:63553];
            
            CurrentPosition = 0;
            myFile.framePosition = 0;
            
        }
        else
        {
            [self StopStream];
        }
    }
    
    AVAudioFrameCount valid = MIN(63553, MaxPosition - CurrentPosition > 0 ? MaxPosition - CurrentPosition:CurrentPosition );
   
    CurrentPosition += valid;
    
        [myFile readIntoBuffer:myNextBuffer frameCount:valid error:&testError];
        [mySound scheduleBuffer:myNextBuffer completionHandler:^{
            [self UpdateBuffers];
        }];
    
  
    

}
-(void) UpdateBuffers
{

    if([mySound isPlaying])
    {
    myLastBuffer = myBuffer;
    myBuffer = myNextBuffer;
    [self ScheduleBuffers];
    }
}
-(bool) StreamStart:(bool) _loops
{
    loops = _loops;
    if(![mySound isPlaying])
    {
    [mySound playAtTime:0];
    //[mySound scheduleBuffer:myBuffer atTime:nil options:AVAudioPlayerNodeBufferInterrupts completionHandler:nil];
       [mySound scheduleBuffer:myBuffer atTime:nil options:AVAudioPlayerNodeBufferInterrupts completionHandler:^{[self UpdateBuffers];}];
    }
    bool returnValue = [mySound isPlaying];
    
    return returnValue;
    
    

}

-(bool) PauseStream
{
    [mySound pause];
    bool returnValue = ![mySound isPlaying];
    
    return returnValue;
}
-(bool) ResumeStream
{
    [mySound play];
    bool returnValue = [mySound isPlaying];
    
    return returnValue;
}
-(bool) StopStream
{
    [mySound stop];
    [mySound prepareWithFrameCount:63553];
   
    CurrentPosition = 0;
    bool returnValue = ![mySound isPlaying];
    
    return returnValue;
}


@end


@interface GMacAudio : NSObject
{
    @public
    AVAudioPlayerNode * inputNode;
    AVAudioEngine * myAudio;
    AVAudioOutputNode * leftSpeaker;
    AVAudioOutputNode * rightSpeaker;
    NSMutableArray *ActiveSounds;
    NSMutableArray *ActiveMusic;

    float MasterVolume ;
}

-(bool) Init;
-(void) SetupOutputs;

-(bool) SetMasterVolume:(float) _newVolume;
-(bool) SetMasterVolumeChannels:(const float *) _values theNumberOfChannels:(int)_numChannels;
-(bool) PauseAll;
-(bool) ResumeAll;
-(bool) StopAll;

@end

@implementation GMacAudio

-(bool) Init
{

    bool result = false;
    NSError *err;
   myAudio = [[AVAudioEngine alloc]init];
    inputNode = [[AVAudioPlayerNode alloc] init];
    ActiveMusic = [[NSMutableArray alloc] init];
    ActiveSounds = [[NSMutableArray alloc] init];
    [myAudio attachNode:inputNode];
       [myAudio connect:inputNode to:myAudio.mainMixerNode format:[inputNode outputFormatForBus:0]];

      [myAudio connect:myAudio.mainMixerNode to:myAudio.outputNode format:[inputNode outputFormatForBus:0]];
    
    [myAudio stop];
 
    result = [myAudio startAndReturnError:&err];
    
    if(myAudio.isRunning)
    {
        return true;
   
    }
    else
    {
        return false;
    }
}
-(void) SetupOutputs
{
  //  AVAudioOutputNode * leftSpeaker = [AVAudioOutputNode alloc];
   // [leftSpeaker out];
    
}

-(bool) SetMasterVolume:(float) _newVolume
{
    if(_newVolume <= 0)
        return false;
    
    
    [myAudio mainMixerNode].outputVolume =_newVolume;
    float check =   [myAudio mainMixerNode].outputVolume;
    if(check == _newVolume)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}
-(bool) SetMasterVolumeChannels:(const float *) _values theNumberOfChannels:(int)_numChannels
{
    NSMutableArray * theValues = [[[NSMutableArray alloc] init] autorelease];
    for (int i = 0; i < _numChannels; i++)
    {
        [theValues addObject:[NSNumber numberWithFloat:_values[i]]];
    }
    if(theValues.count == 1)
    {
        myAudio.mainMixerNode.pan = -1 * _values[0];
    }
    else if(theValues.count > 1)
    {
        float newVal = _values[1] -  _values[0];
        if(newVal > 1.0f)
            newVal = 1.0f;
        if(newVal < -1.0f)
            newVal = -1.0f;
         myAudio.mainMixerNode.pan = newVal;
    }
    else
    {
        return false;
    }
    return true;
}
-(bool) PauseAll
{
    bool returnedResult = true;
    for (int i = 0; i < ActiveSounds.count; i++)
    {
        returnedResult = [ActiveSounds[i] PauseSound];
    }
    for (int i = 0; i < ActiveMusic.count; i++)
    {
        returnedResult = [ActiveMusic[i] PauseStream];
    }
    return returnedResult;
}
-(bool) ResumeAll
{
    bool returnedResult = true;
    for (int i = 0; i < ActiveSounds.count; i++)
    {
        returnedResult = [ActiveSounds[i] ResumeSound];
    }
    for (int i = 0; i < ActiveMusic.count; i++)
    {
        returnedResult = [ActiveMusic[i] ResumeStream];
    }
    return returnedResult;
}
-(bool) StopAll
{
    bool returnedResult = true;
    for (int i = 0; i < ActiveSounds.count; i++)
    {
        returnedResult = [ActiveSounds[i] StopSound];
    }
    for (int i = 0; i < ActiveMusic.count; i++)
    {
        returnedResult = [ActiveMusic[i] StopStream];
    }
    return returnedResult;
}

#include "GAudio.cpp"
@end
