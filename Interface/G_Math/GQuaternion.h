#ifndef GQUATERNION_H
#define GQUATERNION_H
/*!
File: GQuaternion.h
Purpose: A Gateware interface that handles quaternion functions.
Author: Shuo-Yi Chang
Contributors: N/A
Last Modified: 8/30/2016
Interface Status: Beta
Copyright: 7thGate Software LLC.
License: MIT
*/

//! GMathDefines inherits directly from GMultiThreaded.
#include "../G_Core/GSingleThreaded.h"
#include "GMathDefines.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong.
namespace GW
{
	//! The namespace to which all math library interface must belong.
	namespace MATH
	{
		//! Unique Identifier for this interface. {1B42F04F-5A3F-40C5-A506-479768629014}
		static const GUUIID GQuaternionUUIID =
		{
			0x1b42f04f, 0x5a3f, 0x40c5,{ 0xa5, 0x6, 0x47, 0x97, 0x68, 0x62, 0x90, 0x14 }
		};

		//! Quaternion functions
		/*!
		*	Include float vector and double quaternion's functions
		*/
		class GQuaternion : public CORE::GSingleThreaded 
		{
			// All Gateware API interfaces contain no variables & are pure virtual.
		public:
			//float quaternion

			//! Add two quaternions
			/*!
			*	Adds the two specified quaternions and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The second quaternion
			*	\param [out] _outQuaternion		The result of the addition
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn AddQuaternionF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) = 0;

			//! Subtract two quaternions
			/*!
			*	Subtracts the two specified quaternions and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The second quaternion
			*	\param [out] _outQuaternion		The result of the subtraction
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn SubtractQuaternionF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) = 0;

			//! Multiply two quaternions
			/*!
			*	Multiplies the two specified quaternions and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The second quaternion
			*	\param [out] _outQuaternion		The result of the multiplication
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn MultiplyQuaternionF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GQUATERNIONF& _outQuaternion) = 0;

			//! Scale the quaternion
			/*!
			*	Scales the specified quaternion with a number and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion		The quaternion
			*	\param [in]  _scalar			The specified value to scale
			*	\param [out] _outQuaternion		The result of the scaling
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn ScaleF(GQUATERNIONF _quaternion, float _scalar, GQUATERNIONF& _outQuaternion) = 0;
			
			//! Set the quaternion by the specified vector and the specified angle
			/*!
			*	Sets the quaternion with a number and stores the result in the output quaternion.
			*
			*	\param [in]  _vector			The specified vector
			*	\param [in]  _radian			The specified value of angle
			*	\param [out] _outQuaternion		The result of the rotation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn SetByVectorAngleF(GVECTORF _vector, float _radian, GQUATERNIONF& _outQuaternion) = 0;
			
			//! Set the quaternion by the specified matrix
			/*!
			*	Sets the quaternion by the rotation part of the specifed matrix 
			*	and stores the result in the output quaternion.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _outQuaternion		The result of the rotation of matrix
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn SetByMatrixF(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion) = 0;

			//! Calculates the dot product of the two specified quaternions
			/*!
			*	Calculates the dot product of two specified quaternions and stores the result in the output Value.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The second quaternion
			*	\param [out] _outValue			The value of the dot product
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid vector was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn DotF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float& _outValue) = 0;
			
			//! Calculates the cross product of the two specified quaternions
			/*!
			*	Corsses two specified quaternions and stores the result in the output Value.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The second quaternion
			*	\param [out] _outVector			The vector of the corss product
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid vector was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn CrossF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, GVECTORF& _outVector) = 0;
			
			//! Conjugate the specified quaternion
			/*!
			*	Conjugates the specified quaternion and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion		The quaternion
			*	\param [out] _outQuaternion		The result of the conjugate
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn ConjugateF(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) = 0;

			//! Inverse the specified quaternion
			/*!
			*	Inverses the specified quaternion and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion		The specified quaternion
			*	\param [out] _outQuaternion		The result of the inverse
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn InverseF(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) = 0;

			//! Calculate the magnitude of quaternion
			/*!
			*	Calculate the magnitude of the specified quaternion and stores the result in the output value.
			*
			*	\param [in]  _quaternion		The quaternion
			*	\param [out] _outMagnitude		The result of the Calculation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn MagnitudeF(GQUATERNIONF _quaternion, float& _outMagnitude) = 0;

			//! Normalize the specified quaternion
			/*!
			*	Normalizes the specified quaternion and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion		The quaternion
			*	\param [out] _outMagnitude		The result of the normalization
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn NormalizeF(GQUATERNIONF _quaternion, GQUATERNIONF& _outQuaternion) = 0;

			//! Identity the specified quaternion
			/*!
			*	Set the output quaternion as an identity quaternion
			*
			*	\param [out] _outQuaternion		The result of the identity
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn IdentityF(GQUATERNIONF& _outQuaternion) = 0;

			//! Linear interpolate between two specified quaternions
			/*!
			*	Linear interpolates between two specified quaternions
			*	and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The seconds quaternion
			*	\param [in]  _ratio				The interpolation coefficient
			*	\param [out] _outQuaternion		The result of the lerp
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn LerpF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float _ratio, GQUATERNIONF& _outQuaternion) = 0;
			
			//! Spherical linear interpolates between two specified quaternions
			/*!
			*	Spherical linear interpolates between two specified quaternions 
			*	and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The seconds quaternion
			*	\param [in]  _ratio				The interpolation coefficient
			*	\param [out] _outQuaternion		The result of the lerp
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn SlerpF(GQUATERNIONF _quaternion1, GQUATERNIONF _quaternion2, float _ratio, GQUATERNIONF& _outQuaternion) = 0;



			//double quaternion

			//! Add two quaternions
			/*!
			*	Adds the two specified quaternions and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The second quaternion
			*	\param [out] _outQuaternion		The result of the addition
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn AddQuaternionD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) = 0;

			//! Subtract two quaternions
			/*!
			*	Subtracts the two specified quaternions and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The second quaternion
			*	\param [out] _outQuaternion		The result of the subtraction
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn SubtractQuaternionD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) = 0;

			//! Multiply two quaternions
			/*!
			*	Multiplies the two specified quaternions and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The second quaternion
			*	\param [out] _outQuaternion		The result of the multiplication
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn MultiplyQuaternionD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GQUATERNIOND& _outQuaternion) = 0;

			//! Scale the quaternion
			/*!
			*	Scales the specified quaternion with a number and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion		The quaternion
			*	\param [in]  _scalar			The specified value to scale
			*	\param [out] _outQuaternion		The result of the scaling
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn ScaleD(GQUATERNIOND _quaternion, double _scalar, GQUATERNIOND& _outQuaternion) = 0;

			//! Set the quaternion by the specified vector and the specified angle
			/*!
			*	Sets the quaternion with a number and stores the result in the output quaternion.
			*
			*	\param [in]  _vector			The specified vector
			*	\param [in]  _radain			The specified value of angle
			*	\param [out] _outQuaternion		The result of the rotation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn SetByVectorAngleD(GVECTORD _vector, double _radain, GQUATERNIOND& _outQuaternion) = 0;

			//! Set the quaternion by the specified matrix
			/*!
			*	Sets the quaternion by the rotation part of the specifed matrix 
			*	and stores the result in the output quaternion.
			*
			*	\param [in]  _matrix			The specified matrix
			*	\param [out] _outQuaternion		The result of the rotation of matrix
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn SetByMatrixD(GMATRIXD _matrix, GQUATERNIOND& _outQuaternion) = 0;
		
			//! Calculates the dot product of the two specified quaternions
			/*!
			*	Calculates the dot product of two specified quaternions and stores the result in the output Value.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The second quaternion
			*	\param [out] _outValue			The value of the dot product
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid vector was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn DotD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, double& _outQuaternion) = 0;

			//! Calculates the cross product of the two specified quaternions
			/*!
			*	Corsses two specified quaternions and stores the result in the output Value.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The second quaternion
			*	\param [out] _outVector			The vector of the corss product
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid vector was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn CrossD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, GVECTORD& _outVector) = 0;

			//! Conjugate the specified quaternion
			/*!
			*	Conjugates the specified quaternion and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion		The quaternion
			*	\param [out] _outQuaternion		The result of the conjugate
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn ConjugateD(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) = 0;

			//! Inverse the specified quaternion
			/*!
			*	Inverses the specified quaternion and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion		The specified quaternion
			*	\param [out] _outQuaternion		The result of the inverse
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn InverseD(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) = 0;

			//! Calculate the magnitude of quaternion
			/*!
			*	Calculate the magnitude of the specified quaternion and stores the result in the output value.
			*
			*	\param [in]  _quaternion		The quaternion
			*	\param [out] _outMagnitude		The result of the Calculation
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn MagnitudeD(GQUATERNIOND _quaternion, double& _outMagnitude) = 0;

			//! Normalize the specified quaternion
			/*!
			*	Normalizes the specified quaternion and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion		The quaternion
			*	\param [out] _outMagnitude		The result of the normalization
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn NormalizeD(GQUATERNIOND _quaternion, GQUATERNIOND& _outQuaternion) = 0;

			//! Identity the specified quaternion
			/*!
			*	Set the output quaternion as an identity quaternion
			*
			*	\param [out] _outQuaternion		The result of the identity
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn IdentityD(GQUATERNIOND& _outQuaternion) = 0;

			//! Linear interpolate between two specified quaternions
			/*!
			*	Linear interpolates between two specified quaternions
			*	and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The seconds quaternion
			*	\param [in]  _ratio				The interpolation coefficient
			*	\param [out] _outQuaternion		The result of the lerp
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn LerpD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, float _ratio, GQUATERNIOND& _outQuaternion) = 0;

			//! Spherical linear interpolates between two specified quaternions
			/*!
			*	Spherical linear interpolates between two specified quaternions
			*	and stores the result in the output quaternion.
			*
			*	\param [in]  _quaternion1		The first quaternion
			*	\param [in]  _quaternion2		The seconds quaternion
			*	\param [in]  _ratio				The interpolation coefficient
			*	\param [out] _outQuaternion		The result of the lerp
			*
			*	\retval SUCCESS					The calculation succeed
			*	\retval INVALID_ARGUMENT		An invalid quaternion was passed in
			*	\retval FAILURE					The calculation failed
			*/
			virtual GReturn SlerpD(GQUATERNIOND _quaternion1, GQUATERNIOND _quaternion2, double _ratio, GQUATERNIOND& _outQuaternion) = 0;




		}; //! end GQuaternion class
		GATEWARE_EXPORT_IMPLICIT GReturn CreateGQuaternion(GQuaternion** _outQuaternion);

	};//! end SYSTEM namespace
} //! end GW namespace


#endif