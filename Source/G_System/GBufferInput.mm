#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include "../../Source/G_System/GBI_Callback.cpp"

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
    int keycode = [theEvent keycode];
	n_Keys[keycode] = 1;
}

-(void)keyUp:(NSEvent *)theEvent{
    int keycode = [theEvent keycode];
	n_Keys[keycode] = 0;
}

-(void)mouseDown:(NSEvent *)theEvent{
    
}

-(void)mouseUp:(NSEvent *)theEvent{
    
}

-(void)rightmouseDown:(NSEvent *)theEvent{
    
}

#include "../../Source/G_System/GBufferInput.cpp"

@end


