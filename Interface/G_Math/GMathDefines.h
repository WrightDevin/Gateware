#ifndef GMATHDEFINES_H
#define GMATHDEFINES_H

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
using namespace std;



//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{

	//! The namespace to which all math library interface must belong.
	namespace MATH
	{
		// Ensure identical binary padding for structures on all platforms.
#pragma pack(push, 1)
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

		//! Vector with 4 float elements
		union GVECTORF
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			float data[4];
			//GVECTORF(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {};
		};

		//! Vector with 4 double elements
		union GVECTORD
		{
			struct
			{
				double x;
				double y;
				double z;
				double w;
			};
			double data[4];
		};
		//! Matrix with 4 float vectors which represent for each row.
		union GMATRIXF
		{
			struct
			{
				GVECTORF row1;
				GVECTORF row2;
				GVECTORF row3;
				GVECTORF row4;
			};

			float data[16];
		};

		//! Matrix with 4 double vectors which represent for each row.
		union GMATRIXD
		{
			struct
			{
				GVECTORD row1;
				GVECTORD row2;
				GVECTORD row3;
				GVECTORD row4;
			};
			double data[16];
		};

		//! Quaternion with 4 float elements
		union GQUATERNIONF
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			float data[4];
		};

		//! Quaternion with 4 double elements
		union GQUATERNIOND
		{
			struct
			{
				double x;
				double y;
				double z;
				double w;
			};
			double data[4];
		};

#pragma pack(pop)
	} // end MATH namespace
} // end GW namespace

#define G_PI			3.14159265358979323846
#define G_1_PI			0.318309886183790671538

//static const MATH::GVECTORF GZeroVectorF = { 0.0f,0.0f,0.0f,0.0f };
//static const GVECTORD GZeroVectorD = { 0,0,0,0 };

//static const GMATRIXF GIdentityMatrixF{ 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
//static const GMATRIXD GIdentityMatrixD{ 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
//static const GMATRIXF GZeroMatrixF{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
//static const GMATRIXD GZeroMatrixD{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
//
//static const GQUATERNIONF GIdentityQuaternionF{ 0,0,0,1 };
//static const GQUATERNIOND GIdentityQuaternionD{ 0,0,0,1 };
//static const GQUATERNIONF GZeroQuaternionF{ 0,0,0,0 };
//static const GQUATERNIOND GZeroQuaternionD{ 0,0,0,0 };

#endif