#ifndef GWINDOW_H
#define GWINDOW_H

/*!
	File: GWindow.h
	Purpose: A Gateware interface that creates a window and handles its properties.
	Author: Nic Russell
	Contributors: N/A
	Last Modified: 5/8/2017
	Interface Status: Early Stage Development
	Copyright: 7thGate Software LLC.
	License: MIT
*/

//! GWindow inherits directly from GBroadcasting.
#include "../G_Core/GBroadcasting.h"
#include "../G_System/GKeyDefines.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all Gateware library interfaces must belong.
	namespace SYSTEM
	{

//! Ensure identical binary padding for structures on all platforms.
#pragma pack(push, 1)

		// !GWINDOW_EVENT_DATA holds the properties of the window the event was sent from.
		struct GWINDOW_EVENT_DATA
		{
			unsigned int eventFlags;
			unsigned int height;
			unsigned int width;
			int windowX;
			int windowY;
			void* windowHandle;
		};

#pragma pack(pop)

		//! GWindowStyle holds the possible types of window GWindow can create.
		enum GWindowStyle
		{
			WINDOWEDBORDERED,
			WINDOWEDBORDERLESS,
			FULLSCREENBORDERED,
			FULLSCREENBORDERLESS,
		};

		//! GWindowInputEvents holds the possible events a GWindow window can broadcast.
		enum GWindowInputEvents
		{
			NOTIFY,
			MINIMIZE,
			MAXIMIZE,
			RESIZE,
			MOVE,
			DESTROY,
		};

		//! Unique Identified for this interface. { }
		static const GUUIID GWindowUUIID =
		{

		};

		//! A thread-safe window creation and management library.
		/*!
		*	This library is used to create, move, resize, and destroy
		*	a window. Methods exist to query information from the 
		*	window as well. The window is also a broadcaster, meaning
		*	a GListener can be written to receive events from it.
		*/
		class GWindow : public CORE::GBroadcasting 
		{

		public:
			
			virtual GReturn CreateWindow(int _x, int _y, int _width, int _height, GWindowStyle _style) = 0;

			virtual GReturn ReconfigureWindow(int _x, int _y, int _width, int _height, GWindowStyle _style) = 0;

			virtual GReturn MoveWindow(int _x, int _y) = 0;

			virtual GReturn ResizeWindow(int _width, int _height) = 0;

			virtual GReturn Maximize() = 0;

			virtual GReturn Minimize() = 0;

			virtual GReturn ChangeWindowStyle(GWindowStyle _style) = 0;

			virtual int GetWidth() = 0;

			virtual int GetHeight() = 0;

			virtual int GetX() = 0;

			virtual int GetY() = 0;

			virtual void* GetWindowHandle() = 0;

			virtual bool IsFullscreen() = 0;

		}; // end GWindow class

		GATEWARE_EXPORT_IMPLICIT GReturn CreateGWindow(int _x, int _y, int _width, int _height, GWindowStyle _style, GWindow** _outWindow);
	} // end SYSTEM namespace
} // end GW namespace

#endif