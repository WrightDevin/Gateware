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

		//! Unique Identifier for this interface. {A5D7746F-FAAE-42BF-AC16-5C25551CA7B6}.
		static const GUUIID GWindowUUIID =
		{
			0xa5d7746f, 0xfaae, 0x42bf,{ 0xac, 0x16, 0x5c, 0x25, 0x55, 0x1c, 0xa7, 0xb6 } 
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
			
			//! Creates and displays a window.
			/*!
			*	The window is displayed with the size, position and style specified in the parameters.
			*   If width and height are greater than the native resolution, the passed in
			*   GWindowStyle will be overwritten to be the fullscreen version if it is not already.
			*
			*	\param [in] _x The x position of the window on the screen.
			*	\param [in] _y The y position of the window on the screen.
			*	\param [in] _width The width of the window.
			*	\param [in] _height The height of the window.
			*	\param [in] _style The style of the window. (see GWindowStyle for style options)
			*
			*	\retval SUCCESS The window was successfully created and displayed.
			*	\retval INVALID_ARGUMENT One of the size parameters are outside the limits of the hardware
			*							 or the style specified is not a valid GWindowStyle.
			*	\retval FAILURE The window could not be created.
			*/
			virtual GReturn CreateWindow(int _x, int _y, int _width, int _height, GWindowStyle _style) = 0;

			//! Gives the currently opened window the specified size, position and style
			/*!
			*	If width and height are greater than the native resolution, the passed in
			*	GWindowStyle will be overwritten to be the fullscreen version if it is not already.
			*
			*	\param [in] _x The x position on screen to move the window to.
			*	\param [in] _y The y position on screen to move the window to.
			*	\param [in] _width The width to give the window.
			*	\param [in] _height The height to give the window.
			*	\param [in] _style The style to give to the window. (see GWindowStyle for style options)
			*
			*	\retval SUCCESS The window successfully had its attributes changed.
			*	\retval INVALID_ARGUMENT One of the size parameters are outside the limits of the hardware
			*							 or the style specified is not a valid GWindowStyle.
			*	\retval REDUNDANT_OPERATION No window exists to edit. 
			*/
			virtual GReturn ReconfigureWindow(int _x, int _y, int _width, int _height, GWindowStyle _style) = 0;

			//! Repositions the currently opened window to the specified x and y pixels on screen.
			/*!
			*	X and Y upper-limits are based on the native resolution of the user.
			*
			*	\param [in] _x The x position on screen to move the window to.
			*	\param [in] _y The y position on screen to move the window to.
			*
			*	\retval SUCCESS The window was successfully moved.
			*	\retval INVALID_ARGUMENT One of the position parameters are outside the limits of the hardware.
			*   \retval REDUNDANT_OPERATION No window exists to move.
			*	
			*/	
			virtual GReturn MoveWindow(int _x, int _y) = 0;

			//! Resizes the currently opened window to the specified width and height.
			/*!
			*	If width and height are greater than the native resolution, the GWindowStyle 
			*	will be overwritten to be the fullscreen version if it is not already.
			*
			*	\param [in] _x The width to resize the window to.
			*	\param [in] _y The height to resize the window to.
			*
			*	\retval SUCCESS The window was successfully resized.
			*	\retval INVALID_ARGUMENT One of the size parameters are less than or equal to 0.
			*   \retval REDUNDANT_OPERATION No window exists to resize.
			*
			*/
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