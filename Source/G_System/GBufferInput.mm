#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

@interface GResponder : NSResponder

//Overide Functions for the Responder
-(bool)acceptFirstResponder;

-(bool)acceptsFirstMouse:(NSEvent *)event;

-(void)keyDown:(NSEvent *)theEvent;
-(void)keyUp:(NSEvent *)theEvent;

-(void)mouseDown:(NSEvent *)theEvent;
-(void)mouseUp:(NSEvent *)theEvent;

-(void)rightmouseDown:(NSEvent *)theEvent;

@end

@implementation GResponder

-(bool)acceptFirstResponder{
    return YES;
}

-(bool)acceptsFirstMouse:(NSEvent *)event{
    return YES;
}

-(void)keyDown:(NSEvent *)theEvent{
    NSLog(@"Poop");
}

-(void)keyUp:(NSEvent *)theEvent{
    
}

-(void)mouseDown:(NSEvent *)theEvent{
    
}

-(void)mouseUp:(NSEvent *)theEvent{
    
}

-(void)rightmouseDown:(NSEvent *)theEvent{
    
}

@end

#include "../../Source/G_System/GBI_Callback.cpp"
#include "../../Source/G_System/GBufferInput.cpp"
