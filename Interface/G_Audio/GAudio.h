#ifndef GAUDIO_H
#define GAUDIO_H
/*!
File: GAudio.h
Purpose: A Gateware interface that handles sounds and music.
Author: TJay Cargle
Contributors: N/A
Last Modified: 8/7/2017
Interface Status: Early Stage Development
Copyright: 7thGate Software LLC.
License: MIT
*/

#include "../G_Core/GDefines.h"


//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all Gateware library interfaces must belong.
	namespace SYSTEM
	{

		//! Ensure identical binary padding for structures on all platforms.
#pragma pack(push, 1)

#pragma pack(pop)



		//! Unique Identifier for this interface. {A5D7746F-FAAE-42BF-AC16-5C25551CA7B6}.
		static const GUUIID GWindowUUIID =
		{
			0xa5d7746f, 0xfaae, 0x42bf,{ 0xac, 0x16, 0x5c, 0x25, 0x55, 0x1c, 0xa7, 0xb6 }
		};
		class G_Sound
		{

		public:
			
			virtual GReturn PlaySound(const char* soundName) = 0;
			virtual GReturn SetVolume(unsigned int newVolume, const char* soundName) = 0;
			virtual GReturn Pause() = 0;
			virtual GReturn Resume() = 0;
			virtual GReturn SetVolumes(float *values, int numChannels) = 0;



		}; // end GSound class
		class G_Music
		{

		public:
			virtual GReturn PlayMusic(const char* soundName) = 0;
			virtual GReturn SetVolume(unsigned int newVolume, const char* soundName) = 0;
			virtual GReturn Pause() = 0;
			virtual GReturn Resume() = 0;
			virtual GReturn SetChannelVolumes(float *values, int numChannels) = 0;


		}; // end GMusic class
		class G_Audio
		{

		public:
			virtual GReturn Init() = 0;
			virtual GReturn CreateSound(const char* path, G_Sound** outSound) = 0;
			virtual GReturn CreateMusicStream(const char* path, G_Music** outMusic) = 0;
			virtual GReturn SetMasterVolume(float value) = 0;
			virtual GReturn SetMasterChannelVolumes(float *values, int numChannels) = 0;
			virtual GReturn PauseAll() = 0;
			virtual GReturn ResumeAll() = 0;
	

		}; // end GAudio class

	} // end SYSTEM namespace
} // end GW namespace