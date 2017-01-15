#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>



@interface GResponder : NSResponder

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
-(void)scrollWheel:(NSEvent *)theEvent;

-(void)GetKeyMask:(NSEvent *)theEvent;
/*-(void)SendEvent:(unsigned int)Data;*/

@end

#include "../../Source/G_System/GBI_Callback.cpp"

@implementation GResponder

-(bool)acceptFirstResponder{
    return YES;
}

-(bool)acceptsFirstMouse:(NSEvent *)event{
    return YES;
}

-(void)keyDown:(NSEvent *)theEvent{
    G_INPUT_DATA _dataStruct;
    _dataStruct._data = Keycodes[[theEvent keyCode]][2];
    [self GetKeyMask:theEvent];
    _dataStruct._keyMask = _keyMask;
    NSPoint mousePosition = [theEvent locationInWindow];
    _dataStruct._x = mousePosition.x;
    _dataStruct._y = mousePosition.y;
    NSPoint screenMousePosition = [NSEvent mouseLocation];
    _dataStruct._screenX = screenMousePosition.x;
    _dataStruct._screenY = screenMousePosition.y;
    std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
    for (; iter != _listeners.end(); ++iter) {
        iter->first->OnEvent(GBufferedInputUUIID, KEYPRESSED, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
    }

}

-(void)keyUp:(NSEvent *)theEvent{
    G_INPUT_DATA _dataStruct;
    _dataStruct._data = Keycodes[[theEvent keyCode]][2];
    [self GetKeyMask:theEvent];
    _dataStruct._keyMask = _keyMask;
    NSPoint mousePosition = [theEvent locationInWindow];
    _dataStruct._x = mousePosition.x;
    _dataStruct._y = mousePosition.y;
    NSPoint screenMousePosition = [NSEvent mouseLocation];
    _dataStruct._screenX = screenMousePosition.x;
    _dataStruct._screenY = screenMousePosition.y;
    std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
    for (; iter != _listeners.end(); ++iter) {
        iter->first->OnEvent(GBufferedInputUUIID, KEYRELEASED, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
    }
}

-(void)mouseDown:(NSEvent *)theEvent{
    G_INPUT_DATA _dataStruct;
    _dataStruct._data = G_BUTTON_LEFT;
    [self GetKeyMask:theEvent];
    _dataStruct._keyMask = _keyMask;
    NSPoint mousePosition = [theEvent locationInWindow];
    _dataStruct._x = mousePosition.x;
    _dataStruct._y = mousePosition.y;
    NSPoint screenMousePosition = [NSEvent mouseLocation];
    _dataStruct._screenX = screenMousePosition.x;
    _dataStruct._screenY = screenMousePosition.y;
    std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
    for (; iter != _listeners.end(); ++iter) {
        iter->first->OnEvent(GBufferedInputUUIID, BUTTONPRESSED, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
    }
}

-(void)mouseUp:(NSEvent *)theEvent{
    G_INPUT_DATA _dataStruct;
    _dataStruct._data = G_BUTTON_LEFT;
    [self GetKeyMask:theEvent];
    _dataStruct._keyMask = _keyMask;
    NSPoint mousePosition = [theEvent locationInWindow];
    _dataStruct._x = mousePosition.x;
    _dataStruct._y = mousePosition.y;
    NSPoint screenMousePosition = [NSEvent mouseLocation];
    _dataStruct._screenX = screenMousePosition.x;
    _dataStruct._screenY = screenMousePosition.y;
    std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
    for (; iter != _listeners.end(); ++iter) {
        iter->first->OnEvent(GBufferedInputUUIID, BUTTONRELEASED, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
    }
}

-(void)rightmouseDown:(NSEvent *)theEvent{
    G_INPUT_DATA _dataStruct;
    _dataStruct._data = G_BUTTON_RIGHT;
    [self GetKeyMask:theEvent];
    _dataStruct._keyMask = _keyMask;
    NSPoint mousePosition = [theEvent locationInWindow];
    _dataStruct._x = mousePosition.x;
    _dataStruct._y = mousePosition.y;
    NSPoint screenMousePosition = [NSEvent mouseLocation];
    _dataStruct._screenX = screenMousePosition.x;
    _dataStruct._screenY = screenMousePosition.y;
    std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
    for (; iter != _listeners.end(); ++iter) {
        iter->first->OnEvent(GBufferedInputUUIID, BUTTONPRESSED, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
    }
}
-(void)rightmouseUp:(NSEvent *)theEvent{
    G_INPUT_DATA _dataStruct;
    _dataStruct._data = G_BUTTON_RIGHT;
    [self GetKeyMask:theEvent];
    _dataStruct._keyMask = _keyMask;
    NSPoint mousePosition = [theEvent locationInWindow];
    _dataStruct._x = mousePosition.x;
    _dataStruct._y = mousePosition.y;
    NSPoint screenMousePosition = [NSEvent mouseLocation];
    _dataStruct._screenX = screenMousePosition.x;
    _dataStruct._screenY = screenMousePosition.y;
    std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
    for (; iter != _listeners.end(); ++iter) {
        iter->first->OnEvent(GBufferedInputUUIID, BUTTONRELEASED, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
    }
}

-(void)othermouseDown:(NSEvent *)theEvent{
    G_INPUT_DATA _dataStruct;
    _dataStruct._data = G_BUTTON_MIDDLE;
    [self GetKeyMask:theEvent];
    _dataStruct._keyMask = _keyMask;
    NSPoint mousePosition = [theEvent locationInWindow];
    _dataStruct._x = mousePosition.x;
    _dataStruct._y = mousePosition.y;
    NSPoint screenMousePosition = [NSEvent mouseLocation];
    _dataStruct._screenX = screenMousePosition.x;
    _dataStruct._screenY = screenMousePosition.y;
    std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
    for (; iter != _listeners.end(); ++iter) {
        iter->first->OnEvent(GBufferedInputUUIID, BUTTONPRESSED, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
    }
}

-(void)othermouseUp:(NSEvent *)theEvent{
    G_INPUT_DATA _dataStruct;
    _dataStruct._data = G_BUTTON_MIDDLE;
    [self GetKeyMask:theEvent];
    _dataStruct._keyMask = _keyMask;
    NSPoint mousePosition = [theEvent locationInWindow];
    _dataStruct._x = mousePosition.x;
    _dataStruct._y = mousePosition.y;
    NSPoint screenMousePosition = [NSEvent mouseLocation];
    _dataStruct._screenX = screenMousePosition.x;
    _dataStruct._screenY = screenMousePosition.y;
    std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
    for (; iter != _listeners.end(); ++iter) {
        iter->first->OnEvent(GBufferedInputUUIID, BUTTONRELEASED, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
    }
}

-(void)scrollWheel:(NSEvent *)theEvent{
    G_INPUT_DATA _dataStruct;
    if([theEvent scrollingDeltaY] > 0){
        _dataStruct._data = G_MOUSE_SCROLL_UP;
    }
    if([theEvent scrollingDeltaY] < 0){
        _dataStruct._data = G_MOUSE_SCROLL_DOWN;
    }
    [self GetKeyMask:theEvent];
    _dataStruct._keyMask = _keyMask;
    NSPoint mousePosition = [theEvent locationInWindow];
    _dataStruct._x = mousePosition.x;
    _dataStruct._y = mousePosition.y;
    NSPoint screenMousePosition = [NSEvent mouseLocation];
    _dataStruct._screenX = screenMousePosition.x;
    _dataStruct._screenY = screenMousePosition.y;
    if(_dataStruct._data){
        std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
        for (; iter != _listeners.end(); ++iter) {
            iter->first->OnEvent(GBufferedInputUUIID, MOUSESCROLL, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
        }
    }
    
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

/*-(void)SendEvent:(unsigned int)Type, Data{
    std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
    for (; iter != _listeners.end(); ++iter) {
        iter->first->OnEvent(GBufferedInputUUIID, Data, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
    }
}*/

#include "../../Source/G_System/GBufferInput.cpp"

@end
