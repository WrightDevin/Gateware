#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>



@interface GIResponder : NSResponder
{
    NSUInteger flags;
}
//Overide Functions for the Responder
-(bool)acceptFirstResponder;

-(bool)acceptsFirstMouse:(NSEvent *)event;

-(void)keyDown:(NSEvent *)theEvent;
-(void)keyUp:(NSEvent *)theEvent;

-(void)mouseDown:(NSEvent *)theEvent;
-(void)mouseUp:(NSEvent *)theEvent;

-(void)rightmouseDown:(NSEvent *)theEvent;
-(void)rightmouseUp:(NSEvent *)theEvent;

-(void)othermouseDown:(NSEvent *)theEvent;
-(void)othermouseUp:(NSEvent *)theEvent;
-(void)mouseMoved:(NSEvent *)theEvent;
-(void)GetKeyMask:(NSEvent *)theEvent;

@end

#include "../../Source/G_System/GI_Callback.cpp"

@implementation GIResponder

-(bool)acceptFirstResponder{
    return YES;
}

-(bool)acceptsFirstMouse:(NSEvent *)event{
    return YES;
}

-(void)keyDown:(NSEvent *)theEvent{
    n_Keys[Keycodes[[theEvent keyCode]][2]] = 1;
    [self GetKeyMask:theEvent];
}

-(void)keyUp:(NSEvent *)theEvent{
    n_Keys[Keycodes[[theEvent keyCode]][2]] = 0;
    [self GetKeyMask:theEvent];
}

-(void)mouseDown:(NSEvent *)theEvent{
    n_Keys[G_BUTTON_LEFT] = 1;
    [self GetKeyMask:theEvent];
}

-(void)mouseUp:(NSEvent *)theEvent{
    n_Keys[G_BUTTON_LEFT] = 0;
    [self GetKeyMask:theEvent];
}

-(void)rightmouseDown:(NSEvent *)theEvent{
    n_Keys[G_BUTTON_RIGHT] = 1;
    [self GetKeyMask:theEvent];
}
-(void)rightmouseUp:(NSEvent *)theEvent{
    n_Keys[G_BUTTON_RIGHT] = 0;
    [self GetKeyMask:theEvent];
}

-(void)othermouseDown:(NSEvent *)theEvent{
    n_Keys[G_BUTTON_MIDDLE] = 1;
    [self GetKeyMask:theEvent];
}

-(void)othermouseUp:(NSEvent *)theEvent{
    n_Keys[G_BUTTON_MIDDLE] = 0;
    [self GetKeyMask:theEvent];
}


-(void)mouseMoved:(NSEvent *)theEvent{
    NSPoint mousePosition = [theEvent locationInWindow];
    _mousePositionX = mousePosition.x;
    _mousePositionY = mousePosition.y;
}

-(void)GetKeyMask:(NSEvent *)theEvent{
    _keyMask = 0;
    NSUInteger flags = [theEvent modifierFlags];
    if (flags & NSEventModifierFlagShift) {
        TURNON_BIT(_keyMask, G_MASK_SHIFT);
    }
    if (flags & NSEventModifierFlagOption) {
        TURNON_BIT(_keyMask, G_MASK_ALT);
    }
    if (flags & NSEventModifierFlagCommand) {
        TURNON_BIT(_keyMask, G_MASK_COMMAND);
    }
    if (flags & NSEventModifierFlagControl) {
        TURNON_BIT(_keyMask, G_MASK_CONTROL);
    }
    if (flags & NSEventModifierFlagCapsLock) {
        TURNON_BIT(_keyMask, G_MASK_CAPS_LOCK);
    }
    if (flags & NSEventModifierFlagFunction) {
        TURNON_BIT(_keyMask, G_MASK_FUNCTION);
    }
    if (flags & NSEventModifierFlagNumericPad) {
        TURNON_BIT(_keyMask, G_MASK_NUM_LOCK);
    }
    
}


#include "../../Source/G_System/GInput.cpp"

@end

