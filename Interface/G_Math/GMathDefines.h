#ifndef GMATHDEFINES_H
#define GMATHDEFINES_H

/*!
File: GMathDefine.h
Purpose: A Gateware interface that handles math sturcts, such as vector, quaternion and matrix.
Author: Shuo-Yi Chang
Contributors: N/A
Last Modified: 9/29/2016
Interface Status: Beta
Copyright: 7thGate Software LLC.
License: MIT
*/

//! GMathDefines inherits directly from GMultiThreaded.
#include "../G_Core/GMultiThreaded.h"

#define G_PI						3.14159265358979323846
#define G_PI_R						0.318309886183790671538

#define G_EPSILON_F					1.192092896e-07F 
#define G_EPSILON_D					2.2204460492503131e-016

#define G_ABS_F(num)					( ( (num) > 0 ) ?  (num) : std::fabs(num) )		//RETURN THE ABSOLUTE VALUE OF THE INPUT NUMBER
#define G_ABS_D(num)					( ( (num) > 0 ) ?  (num) : std::abs(num) )		//RETURN THE ABSOLUTE VALUE OF THE INPUT NUMBER
#define G_LARGER(A, B)				( ( (A) > (B) ) ?  (A) : (B) )			//RETURN THE LARGER INPUT NUMBER
#define G_SMALLER(A, B)				( ( (A) < (B) ) ?  (A) : (B) )			//RETURN THE SMALLER INPUT NUMBER

#define G_ABS_LARGER_F(A, B)		( ( G_ABS_F(A) > G_ABS_F(B) ) ?  G_ABS_F(A) : G_ABS_F(B) )	
#define G_ABS_LARGER_D(A, B)		( ( G_ABS_D(A) > G_ABS_D(B) ) ?  G_ABS_D(A) : G_ABS_D(B) )

#define G_DEVIATION_EXACT 0
#define G_DEVIATION_PRECISE_F G_EPSILON_F
#define G_DEVIATION_STANDARD_F G_EPSILON_F * 10
#define G_DEVIATION_LOOSE_F G_EPSILON_F * 100

#define G_DEVIATION_PRECISE_D G_EPSILON_D
#define G_DEVIATION_STANDARD_D G_EPSILON_D * 10
#define G_DEVIATION_LOOSE_D G_EPSILON_D * 100

#define G_FIRST_COMPARISON_F(num1 , num2)   ( G_ABS_F( (num1) - (num2) ) <= ( G_EPSILON_F ) )	//FIRST CHECK IF TWO INPUT FLOATS' DIFF ARE LESS THAN EPSILON 
#define G_SECOND_COMPARISON_F(num1 , num2)   ( G_ABS_F( (num1) - (num2) ) <= ( G_DEVIATION_STANDARD_F * G_ABS_LARGER_F(num1, num2)) ) 	//SECOND CHECK IF TWO INPUT FLOATS' DIFF ARE LESS THAN EPSILON MULTIPLY THE LARGER INPUT FLOAT
#define G_COMPARISON_STANDARD_F(num1 , num2)   ( G_FIRST_COMPARISON_F( (num1), (num2) ) ? true : G_SECOND_COMPARISON_F( (num1) , (num2) ) )
#define G_COMPARISON_F(num1, num2, deviation) ( G_FIRST_COMPARISON_F( (num1), (num2) )	? true :  ( G_ABS_F( (num1) - (num2) ) <=  ( deviation * G_ABS_LARGER_F(num1, num2)) )  ) 

#define G_FIRST_COMPARISON_D(num1 , num2)   ( G_ABS_D( (num1) - (num2) ) <= ( G_EPSILON_D ) )	//FIRST CHECK IF TWO INPUT FLOATS' DIFF ARE LESS THAN EPSILON 
#define G_SECOND_COMPARISON_D(num1 , num2)   ( G_ABS_D( (num1) - (num2) ) <= ( G_DEVIATION_STANDARD_D * G_ABS_LARGER_F(num1, num2)) ) //SECOND CHECK IF TWO INPUT FLOATS' DIFF ARE LESS THAN EPSILON MULTIPLY THE LARGER INPUT FLOAT
#define G_COMPARISON_STANDARD_D(num1 , num2)   ( G_FIRST_COMPARISON_D( (num1), (num2) ) ? true : G_SECOND_COMPARISON_D( (num1) , (num2) ) )	
#define G_COMPARISON_D(num1 , num2, deviation)   ( G_FIRST_COMPARISON_D( (num1), (num2) ) ? true :( G_ABS_D( (num1) - (num2) ) <= ( deviation * (G_ABS_LARGER_F(num1, num2))) )  )	

#define G_LERP(start , end, ratio)  ( start + ratio * (end - start) )		//LINEAR INTERPOLATE TWO POINT WITH THE RATIO
#define G_CLAMP(num , top, bottom)  ((((num) > (top)) ? (top) : (num)) < (bottom)) ? (bottom) : (num)		//CLAMP THE NUMBER BETWEEN THE TOP NUMBER AND THE BOTTOM NUMBER



//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{

	//! The namespace to which all math library interface must belong.
	namespace MATH
	{

		//! Unique Identifier for this interface. {733D6B86-7DE3-4190-86AB-36348A958652}
		static const GUUIID GMathDefinesUUIID =
		{
			0x733d6b86, 0x7de3, 0x4190,{ 0x86, 0xab, 0x36, 0x34, 0x8a, 0x95, 0x86, 0x52 }
		};

		// Ensure identical binary padding for structures on all platforms.
#pragma pack(push, 1)

		//! To hold all math structs and variables.
		/*!
		*   For letting classes can use each others variables and structs, here collect all
		*	strcuts and variables.
		*/
		//! Vector with 4 float elements
		struct GVECTORF
		{
			union
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
		};

		//! Vector with 4 double elements
		struct GVECTORD
		{
			union
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
		};
		//! Matrix with 4 float vectors which represent for each row.
		struct GMATRIXF
		{
			union
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
		};

		//! Matrix with 4 double vectors which represent for each row.
		struct GMATRIXD
		{
			union
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
		};

		//! Quaternion with 4 float elements
		struct GQUATERNIONF
		{
			union
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
		};

		//! Quaternion with 4 double elements
		struct GQUATERNIOND
		{
			union
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
		};

#pragma pack(pop)

		static const GVECTORF GZeroVectorF = { 0,0,0,0 };
		static const GVECTORD GZeroVectorD = { 0,0,0,0 };

		static const GMATRIXF GIdentityMatrixF{ 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		static const GMATRIXD GIdentityMatrixD{ 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		static const GMATRIXF GZeroMatrixF{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		static const GMATRIXD GZeroMatrixD{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

		static const GQUATERNIONF GIdentityQuaternionF{ 0,0,0,1 };
		static const GQUATERNIOND GIdentityQuaternionD{ 0,0,0,1 };
		static const GQUATERNIONF GZeroQuaternionF{ 0,0,0,0 };
		static const GQUATERNIOND GZeroQuaternionD{ 0,0,0,0 };

	} // end MATH namespace
} // end GW namespace




#endif