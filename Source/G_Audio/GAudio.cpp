#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pulse/mainloop.h>
#include <pulse/context.h>
#include <pulse/stream.h>
#include <pulse/error.h>
#include <pulse/scache.h>
#elif __APPLE__

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#endif
#endif
