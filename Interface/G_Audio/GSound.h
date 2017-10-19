#pragma once
#ifndef GSound_H
#define GSound_H
#endif
/*!
File: GAudio.h
Purpose: A Gateware internal interface that handles sounds.
Author: TJay Cargle
Contributors: N/A
Last Modified: 8/12/2017
Interface Status: Early Stage Development
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



		//! Unique Identifier for this interface. {0004A714-6E71-4A9D-B1F9-23E2468D2817}.
		static const GUUIID GSoundUUIID =
		{

		 0x4a714, 0x6e71, 0x4a9d,{ 0xb1, 0xf9, 0x23, 0xe2, 0x46, 0x8d, 0x28, 0x17 }

		};
		class GSound : public GW::CORE::GMultiThreaded
		{

		public:
		
			//SetPCMShader
			virtual GReturn SetPCMShader(const char* _data) = 0;
			virtual GReturn SetChannelVolumes(float *_values, int _numChannels) = 0;
			virtual GReturn SetVolume(float _newVolume) = 0;
			virtual GReturn Play(bool _loop = false) = 0;
			virtual GReturn Pause() = 0;
			virtual GReturn Resume() = 0;
			virtual GReturn StopSound() = 0;
			virtual GReturn GetSoundSourceChannels(unsigned int & returnedChannelNum) = 0;
			virtual GReturn GetSoundOutputChannels(unsigned int & returnedChannelNum) = 0;
			virtual GReturn isSoundPlaying(bool & _returnedBool) = 0;
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


		}; // end GSound class

	} // end SYSTEM namespace
} // end GW namespace
