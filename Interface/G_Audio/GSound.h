#pragma once
#ifndef GSound_H
#define GSound_H
#endif
/*!
File: GAudio.h
Purpose: A Gateware interface that handles sounds.
Author: TJay Cargle
Contributors: N/A
Last Modified: 8/12/2017
Interface Status: Early Stage Development
Copyright: 7thGate Software LLC.
License: MIT
*/

#include "../G_Core/GDefines.h"


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
		class GSound
		{

		public:
		
			//SetPCMShader
			virtual GReturn SetPCMShader(const char* _data) = 0;
			virtual GReturn SetChannelVolumes(float *_values, int _numChannels) = 0;
			virtual GReturn SetVolume(float _newVolume) = 0;
			virtual GReturn Play() = 0;
			virtual GReturn Pause() = 0;
			virtual GReturn Resume() = 0;
			virtual GReturn StopSound() = 0;
			//virtual ~GSound();


		}; // end GSound class

	} // end SYSTEM namespace
} // end GW namespace
