#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

@interface GMacSound : NSObject
-(bool) SetPCMShader:(const char *) _data;
-(bool) SetChannelVolumes:(float *) _volumes theNumberOfChannels:(int )_numChannels;
-(bool) SetVolume:(float) _newVolume;
-(bool) PlaySound;
-(bool) Pause;
-(bool) Resume;
-(bool) StopSound;
-(bool) Unload;

@end
@implementation GMacSound

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
-(bool) PlaySound
{
    return false;
}
-(bool) Pause
{
    return false;
}
-(bool) Resume
{
    return false;
}
-(bool) StopSound
{
    return false;
}
-(bool) Unload
{
    return false;
}

@end

@interface GMacMusic : NSObject
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
    return false;
}
-(bool) CreateSound:(const char *) _path soundPtrPtr:(GMacSound ** )_outSound
{
    return false;
}
-(bool) CreateMusicStream:(const char *) _path soundPtrPtr:(GMacMusic ** )_outMusic
{
    return false;
}
-(bool) SetMasterVolume:(float) _newVolume
{
    return false;
}
-(bool) SetMasterVolumeChannels:(const float *) _values theNumberOfChannels:(int)_numChannels
{
    return false;
}
-(bool) PauseAll
{
    return false;
}
-(bool) ResumeAll
{
    return false;
}
-(bool) Unload
{
    return false;
}
#include "GAudio.cpp"
@end
