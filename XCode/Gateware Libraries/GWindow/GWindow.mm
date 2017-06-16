#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

// The GWDelegate will be the delegate of the main window which will receive
// window events
@interface GWDelegate : NSObject
-(NSSize) windowWillResize:(NSWindow *)sender
                    toSize:(NSSize)frameSize;

-(void) windowDidResize:(NSNotification*)notification;
-(void) windowDidMove:(NSNotification*)notification;
-(void) windowDidMiniaturize:(NSNotification*)notification;
-(void) windowDidDeminiaturize:(NSNotification*)notification;
-(void) windowDidEnterFullScreen:(NSNotification*)notification;
-(void) windowWillClose:(NSNotification*)notification;

@end

// The GWResponder is our interpretation of the NSResponder that will propagate
// window messages to other responders
@interface GWResponder : NSResponder

-(bool) acceptFirstResponder;
-(bool) acceptsFirstMouse:(NSEvent*)event;

@end

#include "../../../Source/G_System/GWindow_Callback.hpp"
extern std::map<GListener *, unsigned long long> listeners;

@implementation GWDelegate
-(NSSize) windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize
{
    GWINDOW_EVENT_DATA eventData;
    
    eventData.eventFlags = RESIZE;
    eventData.height = frameSize.height;
    eventData.width = frameSize.width;
    eventData.windowX = sender.frame.origin.x;
    eventData.windowY = sender.frame.origin.y;
    eventData.windowHandle = (__bridge void*)sender;
    
    std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
    for (; iter != listeners.end(); ++iter)
        iter->first->OnEvent(GWindowUUIID, eventData.eventFlags, (void*)&eventData, sizeof(GWINDOW_EVENT_DATA));
    
    return frameSize;

}

-(void) windowDidResize:(NSNotification *)notification
{
    NSWindow* window = notification.object;
    
    GWINDOW_EVENT_DATA eventData;
    
    eventData.eventFlags = RESIZE;
    eventData.height = window.frame.size.height;
    eventData.width = window.frame.size.width;
    eventData.windowX = window.frame.origin.x;
    eventData.windowY = window.frame.origin.y;
    eventData.windowHandle = (__bridge void*)window;
    
    std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
    for (; iter != listeners.end(); ++iter)
        iter->first->OnEvent(GWindowUUIID, eventData.eventFlags, (void*)&eventData, sizeof(GWINDOW_EVENT_DATA));
}

-(void) windowDidMove:(NSNotification *)notification
{
    NSWindow* window = notification.object;
    
    GWINDOW_EVENT_DATA eventData;
    
    eventData.eventFlags = MOVE;
    eventData.height = window.frame.size.height;
    eventData.width = window.frame.size.width;
    eventData.windowX = window.frame.origin.x;
    eventData.windowY = window.frame.origin.y;
    eventData.windowHandle = (__bridge void*)window;
    
    std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
    for (; iter != listeners.end(); ++iter)
        iter->first->OnEvent(GWindowUUIID, eventData.eventFlags, (void*)&eventData, sizeof(GWINDOW_EVENT_DATA));
}

-(void) windowDidMiniaturize:(NSNotification *)notification
{
    NSWindow* window = notification.object;
    
    GWINDOW_EVENT_DATA eventData;
    
    eventData.eventFlags = MINIMIZE;
    eventData.height = window.frame.size.height;
    eventData.width = window.frame.size.width;
    eventData.windowX = window.frame.origin.x;
    eventData.windowY = window.frame.origin.y;
    eventData.windowHandle = (__bridge void*)window;
    
    std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
    for (; iter != listeners.end(); ++iter)
        iter->first->OnEvent(GWindowUUIID, eventData.eventFlags, (void*)&eventData, sizeof(GWINDOW_EVENT_DATA));
}

-(void) windowDidDeminiaturize:(NSNotification *)notification
{
    NSWindow* window = notification.object;
    
    GWINDOW_EVENT_DATA eventData;
    
    eventData.eventFlags = RESIZE;
    eventData.height = window.frame.size.height;
    eventData.width = window.frame.size.width;
    eventData.windowX = window.frame.origin.x;
    eventData.windowY = window.frame.origin.y;
    eventData.windowHandle = (__bridge void*)window;
    
    std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
    for (; iter != listeners.end(); ++iter)
        iter->first->OnEvent(GWindowUUIID, eventData.eventFlags, (void*)&eventData, sizeof(GWINDOW_EVENT_DATA));}

-(void) windowDidEnterFullScreen:(NSNotification *)notification
{
    NSWindow* window = notification.object;
    
    GWINDOW_EVENT_DATA eventData;
    
    eventData.eventFlags = MAXIMIZE;
    eventData.height = window.frame.size.height;
    eventData.width = window.frame.size.width;
    eventData.windowX = window.frame.origin.x;
    eventData.windowY = window.frame.origin.y;
    eventData.windowHandle = (__bridge void*)window;
    
    std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
    for (; iter != listeners.end(); ++iter)
        iter->first->OnEvent(GWindowUUIID, eventData.eventFlags, (void*)&eventData, sizeof(GWINDOW_EVENT_DATA));
}

-(void) windowWillClose:(NSNotification *)notification
{
    NSWindow* window = notification.object;
    
    GWINDOW_EVENT_DATA eventData;
    
    eventData.eventFlags = DESTROY;
    eventData.height = window.frame.size.height;
    eventData.width = window.frame.size.width;
    eventData.windowX = window.frame.origin.x;
    eventData.windowY = window.frame.origin.y;
    eventData.windowHandle = (__bridge void*)window;
    
    std::map<GListener *, unsigned long long>::iterator iter = listeners.begin();
    for (; iter != listeners.end(); ++iter)
        iter->first->OnEvent(GWindowUUIID, eventData.eventFlags, (void*)&eventData, sizeof(GWINDOW_EVENT_DATA));
}
@end

@implementation GWResponder

-(bool)acceptFirstResponder
{
    return YES;
}

-(bool)acceptsFirstMouse:(NSEvent *)event
{
    return YES;
}
@end
