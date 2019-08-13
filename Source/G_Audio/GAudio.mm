#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <CoreAudio/CoreAudio.h>
#import <AVFoundation/AVFoundation.h>
#import <AVFoundation/AVFAudio.h>
#import <AudioToolbox/AudioToolbox.h>

#include <atomic>

class MacAppAudio;
class MacAppMusic;
class MacAppSound;

@interface GMacAudio : NSObject
{
@public
    MacAppAudio * gAudio;
    AVAudioEngine * engine;
    AVAudioPlayerNode * output;
    AVAudioPlayerNode * surroundOutput;
    AVAudioPlayerNode * centerBassOutput;
    NSMutableArray *ActiveSounds;
    NSMutableArray *ActiveMusic;
    float MasterVolume;
}
@property (readonly) int maxChannels;
-(bool) Init;
-(bool) SetMasterVolume:(float) _newVolume;
-(bool) SetMasterVolumeChannels:(const float *) _values theNumberOfChannels:(int)_numChannels;
-(bool) PauseAll;
-(bool) ResumeAll;
-(bool) StopAll;
-(bool) CleanUpSound;
-(bool) CleanUpMusic;
@end

@interface GMacSound : NSObject
{
@public
    MacAppSound * gSound;
    GMacAudio * audio;
    AVAudioPlayerNode * player;
    AVAudioFile * file;
    AVAudioPCMBuffer * buffer;
    bool loops;
    bool isPlaying;
    bool isPaused;
    float volume;
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

@interface GMacMusic : NSObject
{
@public
    MacAppMusic * gMusic;
    GMacAudio * audio;
    AVAudioPlayerNode * player;
    AVAudioFile * file;
    AVAudioPCMBuffer * buffers[3];
    AVAudioFrameCount CurrentPosition;
    AVAudioFrameCount MaxPosition;
    std::atomic<int> buffersQueued;
    std::atomic<bool> stopFlag;
    NSThread * scheduler;
    int currentBufferIndex;
    int index;
    bool loops;
    bool isPlaying;
    bool isPaused;
    float volume;
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
-(void) StreamMusic;
-(void) setBuffersQueued:(int) _value;
@end

@implementation GMacSound
-(id)initWithPath:(NSString*) _path
{
    NSError *testError;
    self = [super init];
    if(self)
    {
        // setting up player
        self->player = [[AVAudioPlayerNode alloc] init];
        [audio->engine attachNode:player];
        
        // setting up buffer
        NSURL * filePath = [[NSURL alloc] initFileURLWithPath:_path];
        self->file = [[AVAudioFile alloc] initForReading:filePath commonFormat:AVAudioPCMFormatFloat32 interleaved:false error:&testError];
        self->buffer = [[AVAudioPCMBuffer alloc] initWithPCMFormat:[self->file processingFormat] frameCapacity:[self->file length]];
        bool success = [self->file readIntoBuffer:self->buffer error:&testError];
        if(!success)
            NSAssert(success, @"could nor read file into buffer", [testError localizedDescription]);
        
        // setting up mixer
        [audio->engine connect:player to:audio->engine.mainMixerNode format:buffer.format];
        
        [audio->ActiveSounds addObject:self];
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
    if(!audio->engine)
        return 0;
    return [file processingFormat].channelCount;
}

-(bool) SetChannelVolumes:(float *) _volumes theNumberOfChannels:(int)_numChannels
{
    NSMutableArray * theValues = [[[NSMutableArray alloc] init] autorelease];
    for (int i = 0; i < _numChannels; i++)
    {
        [theValues addObject:[NSNumber numberWithFloat:_volumes[i]]];
    }
    if(theValues.count == 1)
    {
        player.pan = -1 * _volumes[0];
    }
    else if(theValues.count > 1)
    {
        float newVal = _volumes[1] - _volumes[0];
        if(newVal > 1.0f)
            newVal = 1.0f;
        if(newVal < -1.0f)
            newVal = -1.0f;
        player.pan = newVal;
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
    {
        return false;
    }
    [player setVolume:(_newVolume)];
    float check = [player volume];
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
    [player play];
    [player scheduleBuffer:buffer atTime:nil options:AVAudioPlayerNodeBufferInterrupts completionHandler:
     ^{
         if ([audio CleanUpSound] == false)
             NSLog(@"sound cleanup failed");
     }];
    bool returnValue = [player isPlaying];
    isPlaying = returnValue;
    isPaused = !returnValue;
    return returnValue;
}

-(bool) PauseSound
{
    [player pause];
    bool returnValue = [player isPlaying];
    isPlaying = returnValue;
    isPaused = !returnValue;
    return isPaused;
}

-(bool) ResumeSound
{
    [player playAtTime:nil];
    bool returnValue = [player isPlaying];
    isPlaying = returnValue;
    isPaused = !returnValue;
    return returnValue;
}

-(bool) StopSound
{
    [player stop];
    bool returnValue = [player isPlaying];
    isPlaying = returnValue;
    isPaused = !returnValue;
    return isPaused;
}

-(bool) Unload
{
    bool macresult = false;
    if(player != nil)
    {
        if([player isPlaying] == true)
        {
            [player stop];
        }
        [player release];
        macresult = true;
    }
    return macresult;
}
@end

@implementation GMacMusic
-(id)initWithPath:(NSString*) _path
{
    self = [super init];
    
    if(self)
    {
        AVAudioFrameCount bufferLength = 63553;
        self->player = [[AVAudioPlayerNode alloc] init];
        [audio->engine attachNode:player];
        
        NSError * error;
        NSURL * filePath =[[NSURL alloc] initFileURLWithPath:_path];
        self->file = [[AVAudioFile alloc] initForReading:filePath commonFormat:AVAudioPCMFormatFloat32 interleaved:false error:&error];
        self->buffers[0] =[[AVAudioPCMBuffer alloc] initWithPCMFormat:[self->file processingFormat] frameCapacity:bufferLength];
        self->buffers[1] =[[AVAudioPCMBuffer alloc] initWithPCMFormat:[self->file processingFormat] frameCapacity:bufferLength ];
        self->buffers[2] =[[AVAudioPCMBuffer alloc] initWithPCMFormat:[self->file processingFormat] frameCapacity:bufferLength];
        
        [audio->engine connect:player to:audio->engine.mainMixerNode format:file.processingFormat];
        
        currentBufferIndex = 0;
        buffersQueued = 0;
        stopFlag = false;
        MaxPosition = file.length;
        volume = 1;
        
        [audio->ActiveMusic addObject:self];
    }
    
    return self;
}

-(bool) SetPCMShader:(const char *) _data
{
   
    return false;
}

-(unsigned int) GetChannels
{
    if(!audio->engine)
        return 0;
    return [file processingFormat].channelCount;
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
        player.pan = -1 * _volumes[0];
    }
    else if(theValues.count > 1)
    {
        float first = _volumes[0];
        float second = _volumes[1];
        float newVal = second - first;
        if(newVal > 1.0f) newVal = 1.0f;
        if(newVal < -1.0f) newVal = -1.0f;
        player.pan = newVal;
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
    
    [player setVolume:(_newVolume)];
    float check = [player volume];
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

-(void) StreamMusic
{
    if(stopFlag == true)
        return;
    
    NSError *testError;
    AVAudioFrameCount valid = MIN(63553, MaxPosition - CurrentPosition > 0 ? MaxPosition - CurrentPosition : CurrentPosition );
    CurrentPosition += valid;
 
    AVAudioPCMBuffer * currentBuffer = buffers[currentBufferIndex];
    [file readIntoBuffer:currentBuffer frameCount:valid error:&testError];

    while(buffersQueued >= 2)
    {
        sleep(1);
    }
    [self setBuffersQueued:(buffersQueued + 1)];
    
    [player scheduleBuffer:currentBuffer completionHandler:^{
        if ([audio CleanUpMusic] == false)
        {
            NSLog(@"music cleanup failed");
        }
        [self setBuffersQueued:(buffersQueued - 1)];
    }];
    
    currentBufferIndex++;
    if(currentBufferIndex > 2) currentBufferIndex = 0;
    
    //This following code is simillar to needed code down below in an attempt to stop
    //breaks in music when starting playback from begining
    if(valid != 63553)
    {
        if(loops)
        {
            CurrentPosition = 0;
            file.framePosition = 0;
        }
    }
    
    //checks if we are at end of the song
    if(CurrentPosition >= MaxPosition)
    {
        //if looping reset file pointer and our current position
        if(loops)
        {
            CurrentPosition = 0;
            file.framePosition = 0;
        }
        else
        {
            // this fixes bug where no files less than three seconds would play
            if (MaxPosition < 3 * 63553)
                sleep(3);
            
            [self StopStream];
        }
    }
    
    [self StreamMusic];

}

-(bool) StreamStart:(bool) _loops
{
    loops = _loops;
    if(![player isPlaying])
    {
    [player playAtTime:0];
        CurrentPosition = 0;
        file.framePosition = 0;
    }
    stopFlag = false;
    bool returnValue = [player isPlaying];
    isPlaying = returnValue;
    isPaused = !returnValue;
    return returnValue;
}

-(bool) PauseStream
{
    [player pause];
    bool returnValue = ![player isPlaying];
    isPlaying = returnValue;
    isPaused = !returnValue;
    return returnValue;
}

-(bool) ResumeStream
{
    [player play];
    bool returnValue = [player isPlaying];
    isPlaying = returnValue;
    isPaused = !returnValue;
    return returnValue;
}

-(bool) StopStream
{
    [player stop];
    [player prepareWithFrameCount:63553];
    stopFlag = true;
    CurrentPosition = 0;
    buffersQueued = 0;
    bool returnValue = ![player isPlaying];
    isPlaying = returnValue;
    isPaused = !returnValue;
    return returnValue;
}

-(void) setBuffersQueued:(int) _value
{
    buffersQueued = _value;
}
@end

@implementation GMacAudio
-(int)maxChannels
{
    return gAudio->maxChannels;
}

-(bool) Init
{
    bool result = false;
    
    engine = [[AVAudioEngine alloc] init];
    
    output = [[AVAudioPlayerNode alloc] init];
    [engine attachNode:output];
    [engine connect:output to:engine.mainMixerNode format:[output outputFormatForBus:0]];
    [engine connect:engine.mainMixerNode to:engine.outputNode format:[output outputFormatForBus:0]];
    
    ActiveMusic = [[[NSMutableArray alloc] init]  autorelease];
    ActiveSounds = [[[NSMutableArray alloc] init] autorelease];
    
    NSError *err;
    [engine startAndReturnError:&err];
    
    return result = (engine.isRunning ? true : false);
}

-(bool) SetMasterVolume:(float) _newVolume
{
    if(_newVolume <= 0)
    {
        return false;
    }
    [engine mainMixerNode].outputVolume =_newVolume;
    float check = [engine mainMixerNode].outputVolume;
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
        engine.mainMixerNode.pan = -1 * _values[0];
    }
    else if(theValues.count > 1)
    {
        float newVal = _values[1] - _values[0];
        if(newVal > 1.0f) newVal = 1.0f;
        if(newVal < -1.0f) newVal = -1.0f;
        engine.mainMixerNode.pan = newVal;
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

-(bool) CleanUpSound
{
    bool returnedResult = true;
    for (int i = 0; i < ActiveSounds.count; i++)
    {
        GMacSound * gMacSound = ActiveSounds[i];
        unsigned int soundCount = 0;
        bool safetyCheck = gMacSound->gSound->GetCount(soundCount);
        if (safetyCheck == false) returnedResult = false;
        if (soundCount == 1)
        {
            MacAppSound * macAppSound = gMacSound->gSound;
            [ActiveSounds removeObjectAtIndex:i];
            i--;
            macAppSound->DecrementCount();
            gAudio->DecrementCount();
        }
    }
    return returnedResult;
}

-(bool) CleanUpMusic
{
    bool returnedResult = true;
    for (int i = 0; i < ActiveMusic.count; i++)
    {
        GMacMusic * gMacMusic = ActiveMusic[i];
        unsigned int musicCount = 0;
        bool safetyCheck = gMacMusic->gMusic->GetCount(musicCount);
        if (safetyCheck == false) returnedResult = false;
        if (musicCount == 1)
        {
            MacAppMusic * macAppMusic = gMacMusic->gMusic;
            [ActiveMusic removeObjectAtIndex:i];
            i--;
            macAppMusic->DecrementCount();
            gAudio->DecrementCount();
        }
    }
    return returnedResult;
}

#include "GAudio.cpp"
@end
