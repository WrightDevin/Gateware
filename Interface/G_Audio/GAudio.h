#ifndef GAUDIO_H
#define GAUDIO_H
#endif
/*!
File: GAudio.h
Purpose: A Gateware interface that handles sounds and music.
Author: TJay Cargle
Contributors: N/A
Last Modified: 8/15/2017
Interface Status: Early Stage Development
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
			*	On Windows, initilaizes XAudio2 pointers IXAudio2 and IXAudio2MasteringVoice.
			*	\retval SUCCESS tbd
			*   \retval REDUNDANT_OPERATION tbd
			*/
			virtual GReturn Init() = 0;
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

			

		}; // end GAudio class
		GATEWARE_EXPORT_IMPLICIT GReturn CreateGAudio(GAudio** _outAudio);

	

	} // end SYSTEM namespace
} // end GW namespace