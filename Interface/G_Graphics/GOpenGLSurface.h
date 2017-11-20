#ifndef GOPENGLSURFACE_H
#define GOPENGLSURFACE_H

/*!
File: GOpenGLSurface.h
Purpose: A Gateware interface initializes an OpenGL rendering surface and manages it's core resources.
Author: Andre Reid
Contributors: N/A
Last Modified: 11/17/2017
Interface Status: Beta
Copyright: 7thGate Software LLC.
License: MIT
*/

//! GOpenGLSurface inherits directly from GListener.
#include "../../Interface/G_Core/GListener.h"
#include "../../Interface/G_System/GWindow.h"
#include "GGraphicsDefines.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all Gateware Graphics library interfaces must belong.
	namespace GRAPHICS
	{
		//! Unique Identifier for this interface. {58D21F9F-2BBA-4678-8AB5-E029D2503475}
		static const GUUIID GOpenGLSurfaceUUIID =
		{ 
			0x58d21f9f, 0x2bba, 0x4678,{ 0x8a, 0xb5, 0xe0, 0x29, 0xd2, 0x50, 0x34, 0x75 } 
		};

		//! A library used to initialize, create, and manage an OpenGL rendering context.
		/*!
		*	This library automates the creation of a standard OpenGL
		*	context, and is capable of accepting special requests that 
		*	can guide the initialization to support requested options.
		*	GOpenGLSurface is a GListener, which allows it to receive
		*	events from a registered broadcaster and react accordingly.
		*/
		class GOpenGLSurface : public CORE::GListener
		{

		public:

			//! Returns the current OpenGL context.
			/*!
			*
			*	\param [out] _outContext Will contain the address of the OpenGL context.
			*
			*	\retval SUCCESS The existing OpenGL context was returned.
			*   \retval FAILURE No OpenGL context exists to retrieve.
			*/
			virtual GReturn GetContext(void** _outContext) = 0;
			//! Returns the aspect ratio for the current window.
			/*!
			*
			*	\param [out] _outRatio Will contain the calculated aspect ratio.
			*
			*	\retval SUCCESS The current aspect ratio was calculated and returned.
			*   \retval FAILURE No active GWindow exists to calculate an aspect ratio from.
			*/
			virtual GReturn GetAspectRatio(float& _outAspectRatio) = 0;
			//! Calls the appropriate method (depending on platform) to swap the front and back buffers.
			/*!

			*	\retval SUCCESS The front and back buffers were successfully swapped.
			*	\retval	FAILURE No valid OpenGL context exists to perform a buffer swap on.
			*/
			virtual GReturn UniversalSwapBuffers() = 0;
			//! Queries if a requested OpenGL extension or function is supported.
			/*!
			*	This funtion accepts either an OpenGL extension or
			*	OpenGL function (or both) and searches the total list
			*	of supported extensions (generated upon creation of
			*	the context) to see if that extension/function is
			*	supported. When a function name is queried, this
			*	function will return it's appropriate address
			*	if supported.
			*
			*	\param [in] _extension The exact name of an OpenGL, WGL, or GLX extension.
			*	\param [in] _funcName The exact name of an OpenGL, WGL, or GLX function.
			*	\param [out] _outFuncAddress The address of a function pointer that matches the queried function (_funcName).
			*
			*	\retval SUCCESS The extension/function is supported, and the address was returned successfully (if requested).
			*	\retval INVALID_ARGUMENT This function was called with an incorrect set of parameters.
			*	\retval FAILURE The requested extension/function is not supported.
			*/
			virtual GReturn QueryExtensionFunction(const char* _extension, const char* _funcName, void** _outFuncAddress) = 0;
			//! Enables or disables v-synchronization in regards to buffer swapping.
			/*!
			*
			*	\param [in] _toggle Determines whether to enable or disable v-sync.
			*
			*	\retval SUCCESS The appropriate function was called to enable v-sync.
			*   \retval FEATURE_UNSUPPORTED The extension required to use this functionality was not supported.
			*	\retval FAILURE No valid OpenGL context exists.
			*/
			virtual GReturn EnableSwapControl(bool& _setSwapControl) = 0;

		}; // end GOpenGLSurface class
	
		   //! Creates and outputs a new GOpenGLSurface object.
		   /*!
		   *	Initializes a handle to a GOpenGLSurface object with an existing GWindow.
		   *	The created GOpenGLSurface object will have its reference count initialized
		   *	to one and register as a listener to the provided GWindow object.
		   *
		   *	This function accepts a bit mask that can hold
		   *	supported 'GGraphicsInitOptions', which will
		   *	be taken into account when creating the context.
		   *	To ignore this mask, simply pass in 0 when calling
		   *	this function and the context will be created with
		   *	default settings.
		   *
		   *	\param [in] _gWin A pointer to an existing GWindow object.
		   *	\param [in] _initMask The bit mask that can hold special initialization options.
		   *	\param [out] _outSurface Will contain the GOpenGLSurface object if successfully created.
		   *
		   *	\retval SUCCESS A GOpenGLSurface object was successfully created.
		   *	\retval FAILURE A GOpenGLSurface object was not created. _outSurface will be null.
		   *	\retval INVALID_ARGUMENT Either the _gWin, _outSurface or both arguments are nullptrs.
		   */
		GATEWARE_EXPORT_IMPLICIT GReturn CreateGOpenGLSurface(SYSTEM::GWindow* _gWin, unsigned long long _initMask, GOpenGLSurface** _outSurface);
	
	} // end GRAPHICS namespace
} // end GW namespace

#endif
