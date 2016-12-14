#ifndef _GRESPONDER_H_
#define _GRESPONDER_H_


#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

@interface GResponder : NSResponder

//Overide Functions for the Responder
-(bool)acceptFirstResponder;

-(bool)acceptsFirstMouse:(NSEvent *)event;

-(void)keyDown(NSEvent *)theEvent;
-(void)keyUp(NSEvent *)theEvent;

-(void)mouseDown(NSEvent *)theEvent;
-(void)mouseUp(NSEvent *)theEvent;

-(void)rightmouseDown(NSEvent *)theEvent;

@end


#endif

