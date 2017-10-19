#pragma once
#ifndef GMUSIC_H
#define GMUSIC_H

/*!
File: GMusic.h
Purpose: A Gateware internal interface that handles music.
Author: TJay Cargle
Contributors: N/A
Last Modified: 8/12/2017
Interface Status: Complete
Copyright: 7thGate Software LLC.
License: MIT
*/

#include "../G_Core/GDefines.h"
#include "../G_Core/GMultiThreaded.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all Gateware library interfaces must belong.
	namespace AUDIO
	{

		//! Ensure identical binary padding for structures on all platforms.
#pragma pack(push, 1)

#pragma pack(pop)



		//! Unique Identifier for this interface.  {9E2F8F9D-9786-4EA2-B955-B1F9E807F816}.
		static const GUUIID GMusicUUIID =
		{
		
		 0x9e2f8f9d, 0x9786, 0x4ea2,{ 0xb9, 0x55, 0xb1, 0xf9, 0xe8, 0x7, 0xf8, 0x16 }

		};
		class GMusic
		{

		public:
		
			virtual GReturn SetPCMShader(const char* _data) = 0;//function ptr
			virtual GReturn SetChannelVolumes(float * _values, int _numChannels) = 0;
			virtual GReturn SetVolume(float _newVolume) = 0;
			virtual GReturn StreamStart(bool _loop = false) = 0;
			virtual GReturn PauseStream() = 0;
			virtual GReturn ResumeStream() = 0;
			virtual GReturn StopStream() = 0;
			virtual GReturn GetStreamSourceChannels(unsigned int & returnedChannelNum) = 0;
			virtual GReturn GetStreamOutputChannels(unsigned int & returnedChannelNum) = 0;
			virtual GReturn isStreamPlaying(bool & _returnedBool) = 0;
			//! Return the total number of active references to this object.
			/*!
			*	\param [out] _outCount The total number of active references of this object.
			*
			*	\retval SUCCESS Successfully ran.
			*	\retval FAILURE Either class does not exist or the internal reference count is corrupt.
			*/
			virtual GReturn GetCount(unsigned int& _outCount) = 0;

			//! Increase the total number of active references to this object.
			/*!
			*	End users should only call this operation if they are familiar with reference counting behavior.
			*
			*	\retval SUCCESS Successfully incremented the internal reference count.
			*	\retval FAILURE Incrementation of internal reference count would overflow the value.
			*/
			virtual GReturn IncrementCount() = 0;

			//! Decrease the total number of active references to this object.
			/*!
			*	Once the internal count reaches zero this object will be deallocated and your pointer will become invalid.
			*
			*	\retval SUCCESS Successfully decremented the internal reference count.
			*	\retval FAILURE Decrementing of internal reference count would underflow the value.
			*/
			virtual GReturn DecrementCount() = 0;

			//! Requests an interface that may or may not be supported by this object.
			/*!
			*	 Can be used by the end-user to query for a new interface using the
			*	 unique ID of the interface they want and implement an interface update.
			*
			*	\param [in] _interfaceID The GUUIID of the interface you are requesting.
			*	\param [out] _outputInterface Where the interface will be stored if function is successful.
			*
			*	\retval SUCCESS The interface is supported and function succeded.
			*	\retval INTERFACE_UNSUPPORTED The requested interface is not supported.
			*/
			virtual GReturn RequestInterface(const GUUIID& _interfaceID, void** _outputInterface) = 0;

		}; // end GMusic class


	} // end SYSTEM namespace
} // end GW namespace
#endif