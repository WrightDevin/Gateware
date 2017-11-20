#ifndef GOPENGLSURFACE_H
#define GOPENGLSURFACE_H

/*!
File: GOpenGLSurface.h
Purpose: A Gateware interface initializes an OpenGL rendering surface and manages it's core resources.
Author: Andre Reid
Contributors: N/A
Last Modified: 11/17/2017
Interface Status: Early Stage Development
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

		//! Unique Identifier for this interface. {523DD98C-B39B-4843-BBEC-FF19DF8E5CCF}
		static const GUUIID GOpenGLSurfaceUUIID =
		{
			0x523dd98c, 0xb39b, 0x4843,{ 0xbb, 0xec, 0xff, 0x19, 0xdf, 0x8e, 0x5c, 0xcf } 
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

			//! Initializes and creates the OpenGL Context.
			/*!
			*	This function will open an existing GWindow and
			*	create an OpenGL rendering context that is tied
			*	to it.
			*
			*	This function accepts a bit mask that can hold
			*	supported 'GGraphicsInitOptions', which will
			*	be taken into account when creating the context.
			*	To ignore this mask, simply pass in 0 when calling
			*	this function and the context will be created with
			*	default settings.
			*
			*	\param [in] _initMask The bit mask that can hold special initialization options.
			*
			*	\retval SUCCESS An OpenGL context was successfully created (with the requested options, if any).
			*	\retval FAILURE An existing GWindow is not present or the context did not created successfully.
			*	\retval FEATURE_UNSUPPORTED A requested initialization option is not supported or could not be applied.
			*/
			virtual GReturn Initialize(unsigned char _initMask) = 0;
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
			virtual GReturn EnableSwapControl(bool& _toggle) = 0;

		}; // end GOpenGLSurface class
	
		   //! Creates and outputs a new GOpenGLSurface object.
		   /*!
		   *	Initializes a handle to a GOpenGLSurface object with an existing GWindow.
		   *	The created GOpenGLSurface object will have its reference count initialized 
		   *	to one and register as a listener to the provided GWindow object.
		   *
		   *	\param [in] _gWin A pointer to an existing GWindow object.
		   *	\param [out] _outSurface Will contain the GOpenGLSurface object if successfully created.
		   *
		   *	\retval SUCCESS  GOpenGLSurface was successfully created.
		   *	\retval FAILURE  GOpenGLSurface was not created. _outSurface will be null.
		   *	\retval INVALID_ARGUMENT Either one or both arguments are nullptrs.
		   */
		GATEWARE_EXPORT_IMPLICIT GReturn CreateGOpenGLSurface(SYSTEM::GWindow* _gWin, GOpenGLSurface** _outSurface);
	
	} // end GRAPHICS namespace
} // end GW namespace

#endif
