#ifndef GAUDIO_H
#define GAUDIO_H

/*!
File: GAudio.h
Purpose: A Gateware interface that handles sounds and music.
Author: TJay Cargle
Contributors: N/A
Last Modified: 10/19/2017
Interface Status: Complete
Copyright: 7thGate Software LLC.
License: MIT
*/

#include "GSound.h"
#include "GMusic.h"


//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all Gateware library interfaces must belong.
	namespace AUDIO
	{

		//! Ensure identical binary padding for structures on all platforms.
#pragma pack(push, 1)

#pragma pack(pop)



		//! Unique Identifier for this interface. {AA479919-631C-488D-B278-DBF6D139988C}.
		static const GUUIID GAudioUUIID =
		{

		 0xaa479919, 0x631c, 0x488d,{ 0xb2, 0x78, 0xdb, 0xf6, 0xd1, 0x39, 0x98, 0x8c } 

		};

		class GAudio
		{

		public:
			//! Initializes all neccassary data for GAudio based on platform.
			/*!
			*	On Windows, initilaizes XAudio2 pointers IXAudio2 and IXAudio2MasteringVoice.\
			*	\retval SUCCESS on Windows if xAudio2 is able to setup correctly.
			*	\retval FAILURE on Windows if it cannot coinitilaize.
			*	\retval FAILURE on Windows if it xAudio2Create fails.
			*	\retval FAILURE on Windows if it xAudio fails to create mastering voice.
			*	On Mac, initilaizes AVAudioEngine and starts the engine.
			*	\retval SUCCESS on Mac if AVAudioEngine is able to setup correctly.
			*	\retval FAILURE on Mac if AVAudioEngine is able to setup correctly.
			*   \retval REDUNDANT_OPERATION tbd
			*/
			virtual GReturn Init(int _numOfOutputs = 2) = 0;
			//! Fills out a GSound with data from provided .wav file.
			/*!
			*	tbd
			*	\retval SUCCESS tbd
			*   \retval REDUNDANT_OPERATION tbd
			*/
			virtual GReturn CreateSound(const char* _path, GSound** _outSound) = 0;
			//! Fills out a GMusic with data from provided .wav file.
			/*!
			*	tbd
			*	\retval SUCCESS tbd
			*   \retval REDUNDANT_OPERATION tbd
			*/
			virtual GReturn CreateMusicStream(const char* _path, GMusic** _outMusic) = 0;
			//! Sets Master Volume for all sounds and music.
			/*!
			*	tbd
			*	\retval SUCCESS tbd
			*   \retval REDUNDANT_OPERATION tbd
			*/
			virtual GReturn SetMasterVolume(float _value) = 0;
			//! Sets Master Volume for all sounds and music for specifc speakers.
			/*!
			*	tbd
			*	\retval SUCCESS tbd
			*   \retval REDUNDANT_OPERATION tbd
			*/
			virtual GReturn SetMasterChannelVolumes(const float * _values, int _numChannels) = 0;
			//! Sets Pauses all sounds and music.
			/*!
			*	tbd
			*	\retval SUCCESS tbd
			*   \retval REDUNDANT_OPERATION tbd
			*/
			virtual GReturn PauseAll() = 0;
			//!  Resumes all paused/stoped sounds and music.
			/*!
			*	Stoped Sounds/Music will play from the start
			*	\retval SUCCESS tbd
			*   \retval REDUNDANT_OPERATION tbd
			*/
			virtual GReturn ResumeAll() = 0;
			//! Stops all paused/stoped sounds and music.
			/*!
			*	Stoped Sounds/Music will play from the start
			*	\retval SUCCESS tbd
			*   \retval REDUNDANT_OPERATION tbd
			*/
			virtual GReturn StopAll() = 0;
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
			

		}; // end GAudio class
		GATEWARE_EXPORT_IMPLICIT GReturn CreateGAudio(GAudio** _outAudio);

	

	} // end SYSTEM namespace
} // end GW namespace
#endif