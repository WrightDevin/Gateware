#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <IOKit/hid/IOHIDLib.h>



#include "../../Source/G_System/GController_Callback.hpp"
static void Handle_IOHIDDeviceInputValueCallback(
                                                 
                                                 void *          inContext,      // context from IOHIDDeviceRegisterInputValueCallback
                                                 
                                                 IOReturn        inResult,       // completion result for the input value operation
                                                 
                                                 void *          inSender,       // IOHIDDeviceRef of the device this element is from
                                                 
                                                 IOHIDValueRef   inIOHIDValueRef // the new element value

) {
    double_t scaledValue = IOHIDValueGetScaledValue(inIOHIDValueRef,
                                                    kIOHIDValueScaleTypePhysical);
    
    IOHIDElementRef tIOHIDElementRef = IOHIDValueGetElement(inIOHIDValueRef);
    uint32_t usage = IOHIDElementGetUsage(tIOHIDElementRef);
    HIDMANAGER* manager = (__bridge HIDMANAGER*)inContext;
    int controllerIndex = 0;
    bool controllerFound = false;
    for(; controllerIndex < MAX_CONTROLLER_INDEX; ++controllerIndex)
    {
        if(manager->controllers[controllerIndex].device == (IOHIDDeviceRef)inSender)
        {
            controllerFound = true;
            break;
        }
    }
    
    if(controllerFound)
    {
         // switch on controller type
        
    }
    
}

static void gamepadWasAdded(void* inContext, IOReturn inResult, void* inSender, IOHIDDeviceRef device) {
    
    NSLog(@"Gamepad was plugged in");
   
    HIDMANAGER* manager = (__bridge HIDMANAGER*)inContext;
    if(*(manager->isRunning))
    {
        
        manager->controllersMutex->lock();
    
        int controllerIndex = FindEmptyControllerIndex(MAX_CONTROLLER_INDEX, manager->controllers);
    
        if(controllerIndex != -1)
        {
            IOReturn res = IOHIDDeviceOpen(device,kIOHIDOptionsTypeNone);
            if(kIOReturnSuccess == res)
            {
                 manager->controllers[controllerIndex].isConnected = 1;
                 manager->controllers[controllerIndex].device = device;
                 // send controller connected event
                
                 GCONTROLLER_EVENT_DATA eventData;
                 std::map<GListener*, unsigned long long>::iterator iter;
                
                 eventData.controllerIndex = controllerIndex;
                 eventData.inputCode = 0;
                 eventData.inputValue = 0;
                 eventData.isConnected = 1;
        
                 manager->listenerMutex->lock();
                 for (iter = listeners.begin(); iter != listeners.end(); ++iter)
                     iter->first->OnEvent(GControllerUUIID, CONTROLLERCONNECTED, &eventData,        sizeof(GCONTROLLER_EVENT_DATA));
                 manager->listenerMutex->unlock();
                 IOHIDDeviceRegisterInputValueCallback(device, Handle_IOHIDDeviceInputValueCallback, (__bridge void*)manager);
            }
        }
    
        manager->controllersMutex->unlock();
    }
    
}

static void gamepadWasRemoved(void* inContext, IOReturn inResult, void* inSender, IOHIDDeviceRef device)
{
    NSLog(@"Gamepad was unplugged");
    
    IOReturn res = IOHIDDeviceClose(device, kIOHIDOptionsTypeNone);
    HIDMANAGER* manager = (__bridge HIDMANAGER*)inContext;
    if(*(manager->isRunning))
    {
        
        manager->controllersMutex->lock();
        
        int controllerIndex = 0;
        for(; controllerIndex < MAX_CONTROLLER_INDEX; ++controllerIndex)
        {
            if(device == manager->controllers[controllerIndex].device)
            {
                manager->controllers[controllerIndex].isConnected = 0;
                
                // send controller connected event
                
                GCONTROLLER_EVENT_DATA eventData;
                std::map<GListener*, unsigned long long>::iterator iter;
                
                eventData.controllerIndex = controllerIndex;
                eventData.inputCode = 0;
                eventData.inputValue = 0;
                eventData.isConnected = 0;
                
                manager->listenerMutex->lock();
                for (iter = listeners.begin(); iter != listeners.end(); ++iter)
                    iter->first->OnEvent(GControllerUUIID, CONTROLLERDISCONNECTED, &eventData, sizeof(GCONTROLLER_EVENT_DATA));
                manager->listenerMutex->unlock();
            }
        }
        manager->controllersMutex->unlock();
        }
       
}




#ifdef __APPLE__
IOHIDManagerRef hidManager;
NSThread* runLoopThread;
#endif
@implementation HIDMANAGER : NSObject

-(void) InitManagerAndRunLoop
{


hidManager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDManagerOptionNone);


IOHIDManagerRegisterDeviceMatchingCallback(hidManager, gamepadWasAdded, (__bridge void*)self);
IOHIDManagerRegisterDeviceRemovalCallback(hidManager, gamepadWasRemoved, (__bridge void*)self);


IOHIDManagerScheduleWithRunLoop(hidManager, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);

CFMutableArrayRef criteria = CreateHIDManagerCriteria();
IOHIDManagerSetDeviceMatchingMultiple(hidManager, criteria);

CFRelease(criteria);

IOReturn tIOReturn = IOHIDManagerOpen(hidManager, kIOHIDOptionsTypeNone);
CFTimeInterval timer = 1;
Boolean runLoopReturn = true;
while(*isRunning)
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, timer, runLoopReturn);
    
int d = 0;

}

-(void) StopRunLoop
{
    CFRunLoopStop(managerRunLoop);
}

-(void) SetControllerLock:(std::unique_lock<std::mutex>*) lock
{
   // controllersMutex = lock;
}
-(void) SetListenerLock: (std::unique_lock<std::mutex>*) lock
{
    //listenerMutex = lock;
}

-(void) SetIsRunning: (std::atomic<bool>*) _IsRunning
{
    isRunning = _IsRunning;
}

@end

#include "GController.cpp"
