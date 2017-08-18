#pragma once
#ifndef GMUSIC_H
#define GMUSIC_H
#endif
/*!
File: GMusic.h
Purpose: A Gateware interface that handles music.
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
			virtual GReturn StreamStart() = 0;
			virtual GReturn PauseStream() = 0;
			virtual GReturn ResumeStream() = 0;
			virtual GReturn StopStream() = 0;
			//virtual ~GMusic();

		}; // end GMusic class


	} // end SYSTEM namespace
} // end GW namespace
