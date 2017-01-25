#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>


//The GResponder is our interpretation of the NSReponder to recieve events.
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
	//Get the key from the static list of keys.
    _dataStruct._data = Keycodes[[theEvent keyCode]][2];
	//Call the GetKeyMask Function passing the event passed to this functions.
    [self GetKeyMask:theEvent];
	//Set the keymask.
    _dataStruct._keyMask = _keyMask;
	//Get the mouse position relative to the window.
    NSPoint mousePosition = [theEvent locationInWindow];
    _dataStruct._x = mousePosition.x;
    _dataStruct._y = mousePosition.y;
	//Get the mouse position relative to the screen.
    NSPoint screenMousePosition = [NSEvent mouseLocation];
    _dataStruct._screenX = screenMousePosition.x;
    _dataStruct._screenY = screenMousePosition.y;
	//Send off the event.
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
	//Check wether the its a scroll up or down event.
    if([theEvent scrollingDeltaY] > 0){
        _dataStruct._data = G_MOUSE_SCROLL_UP;
    }
    if([theEvent scrollingDeltaY] < 0){
        _dataStruct._data = G_MOUSE_SCROLL_DOWN;
    }
	//Get the keymask using the getkeymask function/
    [self GetKeyMask:theEvent];
	//Set the keymask.
    _dataStruct._keyMask = _keyMask;
	//Get the mouse position relative to the window.
    NSPoint mousePosition = [theEvent locationInWindow];
    _dataStruct._x = mousePosition.x;
    _dataStruct._y = mousePosition.y;
	//Get the mouse position relative to the screen.
    NSPoint screenMousePosition = [NSEvent mouseLocation];
    _dataStruct._screenX = screenMousePosition.x;
    _dataStruct._screenY = screenMousePosition.y;
	//Make sure theres data to send and send the data to all registered listeners.
    if(_dataStruct._data){
        std::map<GListener *, unsigned long long>::iterator iter = _listeners.begin();
        for (; iter != _listeners.end(); ++iter) {
            iter->first->OnEvent(GBufferedInputUUIID, MOUSESCROLL, (void*)&_dataStruct, sizeof(G_INPUT_DATA));
        }
    }
    
}

-(void)GetKeyMask:(NSEvent *)theEvent{
    _keyMask = 0;
	//Get the unsigned int of all the modifier flags.
    NSUInteger flags = [theEvent modifierFlags];
	//Check individual modifier flags and turn them on respectivly to our keymask(unsigned int).
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

#include "../../Source/G_System/GBufferedInput.cpp"

@end
