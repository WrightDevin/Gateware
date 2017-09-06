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
	//! The namespace to which all math library interface must belong.
	namespace MATH
	{
		//! Unique Identifier for this interface. {21108DB6-BE6C-4AA6-955C-F673B9EE3EDA}
		static const GUUIID GMathDefinesUUIID =
		{ 
			0x21108db6, 0xbe6c, 0x4aa6,{ 0x95, 0x5c, 0xf6, 0x73, 0xb9, 0xee, 0x3e, 0xda }
		};

		//! To hold all math structs and variables.
		/*! 
		*   For letting classes can use each others variables and structs, here collect all
		*	strcuts and variables.
		*/
		class GMathDefines
		{
		public:

			//! Vector with 4 float elements
			struct GVECTORF
			{
				float x;
				float y;
				float z;
				float w;
			};
			
			//! Vector with 4 double elements
			struct GVECTORD
			{
				double x;
				double y;
				double z;
				double w;
			};

			//! Matrix with 4 float vectors which represent for each row.
			struct GMATRIXF
			{
				GVECTORF row1;
				GVECTORF row2;
				GVECTORF row3;
				GVECTORF row4;
			};

			//! Matrix with 4 double vectors which represent for each row.
			struct GMATRIXD
			{
				GVECTORD row1;
				GVECTORD row2;
				GVECTORD row3;
				GVECTORD row4;
			};

			//! Quaternion with 4 float elements
			struct GQUATERNIONF
			{
				float x;
				float y;
				float z;
				float w;
			};

			//! Quaternion with 4 double elements
			struct GQUATERNIOND
			{
				double x;
				double y;
				double z;
				double w;
			};

		};// end GMathDefines class
	} // end SYSTEM namespace
} // end GW namespace


#endif