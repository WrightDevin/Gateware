#ifndef COMMON_H
#define COMMON_H

#include "CATCH.hpp"

//Include all the headers needed for tests

#ifndef __APPLE__
#include <G_System/GKeyDefines.h>
#include <G_System/GBufferedInput.h>
#include <G_System/GInput.h>
#include <G_System/GLog.h>
#include <G_System/GFile.h>
#include <G_System/GWindow.h>
#include <G_System/GController.h>
#include <G_System/GControllerInputDefines.h>
#include <G_Graphics/GDirectX11Surface.h>
#include <G_Graphics/GOpenGLSurface.h>
#include <G_Math/GVector.h>
#include <G_Math/GMatrix.h>
#include <G_Math/GQuaternion.h>
#include <G_Audio/GAudio.h>

#else
#include <../../gateware.git.0/Interface/G_System/GKeyDefines.h>
#include <../../gateware.git.0/Interface/G_System/GBufferedInput.h>
#include <../../gateware.git.0/Interface/G_System/GInput.h>
#include <../../gateware.git.0/Interface/G_System/GLog.h>
#include <../../gateware.git.0/Interface/G_System/GFile.h>
#include <../../gateware.git.0/Interface/G_System/GWindow.h>
#include <../../gateware.git.0/Interface/G_System/GController.h>
#include <../../gateware.git.0/Interface/G_System/GControllerInputDefines.h>
#include <../../gateware.git.0/Interface/G_Graphics/GDirectX11Surface.h>
#include <../../gateware.git.0/Interface/G_Graphics/GOpenGLSurface.h>
#include <../../gateware.git.0/Interface/G_Audio/GAudio.h>
#include <../../gateware.git.0/Interface/G_Math/GVector.h>
#include <../../gateware.git.0/Interface/G_Math/GMatrix.h>
#include <../../gateware.git.0/Interface/G_Math/GQuaternion.h>

#endif

//TODO: Add your library headers


#ifdef _WIN32

	#define WIN32_LEAN_AND_MEAN //Exclude rarely used things from Windows.h
	#include <Windows.h>

	//Handle to the window
	extern HWND window;

	//WNDPROC for the window
	extern LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//TODO: Add other necessary resources needed for Windows testing

#elif __linux__
	#include <X11/Xlib.h>

	extern GW::SYSTEM::LINUX_WINDOW window;

	extern Window mainWindow;
	extern Display* display;

	//TODO: Add other necessary resources needed for Linux testing

#elif __APPLE__

	#import <Foundation/Foundation.h>
	#import <Cocoa/Cocoa.h>

	NSWindow* window = nullptr;
	NSAutoreleasePool* pool = nullptr;

	//TODO: Add other necessary resources needed for Apple testing

#endif

	//Needed by GInput and GBufferedInput
	extern void SimulateInput(unsigned long flags);

	extern void SimulateControllerInput(unsigned long flags);

	//TODO: Add any other necessary non-platform dependent functionality here.


#endif
