#ifndef GMATHDEFINE_H
#define GMATHDEFINE_H

/*!
File: GMathDefine.h
Purpose: A Gateware interface that handles math sturcts, such as vector, quaternion and matrix.
Author: Shuo-Yi Chang
Contributors: N/A
Last Modified: 8/30/2016
Interface Status: Beta
Copyright: 7thGate Software LLC.
License: MIT
*/

//! GMathDefines inherits directly from GMultiThreaded.
#include "../G_Core/GMultiThreaded.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all Gateware library interfaces must belong.
	namespace MATH
	{
		//! Unique Identifier for this interface. {21108DB6-BE6C-4AA6-955C-F673B9EE3EDA}
		static const GUUIID GMathDefinesUUIID =
		{ 
			0x21108db6, 0xbe6c, 0x4aa6,{ 0x95, 0x5c, 0xf6, 0x73, 0xb9, 0xee, 0x3e, 0xda }
		};

		class GMathDefines : public CORE::GMultiThreaded
		{
		public:
			struct GVECTORF
			{
				float x, y, z, w;
			};
			struct GVECTORD
			{
				double x, y, z, w;
			};

			struct GMATRIXF
			{
				GVECTORF row1, row2, row3, row4;
			};
			struct GMATRIXD
			{
				GVECTORD row1, row2, row3, row4;
			};

			struct GQUATERNIONF
			{
				float x, y, z, w;
			};
			struct GQUATERNIOND
			{
				double x, y, z, w;
			};

		};// end GMathDefines class
	} // end SYSTEM namespace
} // end GW namespace


#endif