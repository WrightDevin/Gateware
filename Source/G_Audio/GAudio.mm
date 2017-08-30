#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <CoreAudio/CoreAudio.h>
#import <AVFoundation/AVFoundation.h>
#import <AVFoundation/AVFAudio.h>

@interface GMacSound : NSObject
{
    @public
    AVAudioPlayerNode * mySound;

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
        
        self->mySound = [[AVAudioPlayerNode alloc] init];
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

    //NSArray * temp = nil;
   // [mySound setChannelMapping:temp];
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

     [mySound play];
    return [mySound isPlaying];
    
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

-(id) initWithPath:(CFURLRef*) _path;
-(bool) SetPCMShader:(const char *) _data;
-(bool) SetChannelVolumes:(float *) _volumes theNumberOfChannels:(int )_numChannels;
-(bool) SetVolume:(float) _newVolume;
-(bool) StreamStart;
-(bool) Parse;
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
     //   AudioFileStreamOpen(myData, myListener, myPackProc, myHint, myStream);
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
-(bool) Parse
{
    //AudioFileStreamParseBytes(myStream, , , )
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
    //OSStatus result = AudioFileStreamClose(*(myStream));
    //if(result == noErr)
    //{
      //  return true;
    //}
    return false;
}
-(bool) Unload
{
    return false;
}

@end


@interface GMacAudio : NSObject
{
    @public
    AVAudioEngine * myAudio;
}

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

    bool result;
    NSError *err;
   myAudio = [[AVAudioEngine alloc]init];
    
    [myAudio prepare];
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
