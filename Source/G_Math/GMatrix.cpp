// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"
#include "../../Interface/G_Math/GMatrix.h"
#include "../Source/G_System/GUtility.h"

#include <atomic> //Thread safety

//The using statements for specifically what we are using.
using namespace GW;
using namespace MATH;
using namespace std;

class GMatirxCpp :public GMatrix
{
	//Reference counter.
	atomic<unsigned int> refCount;

public:
	GMatirxCpp();
	~GMatirxCpp();


	//float Matrix

	GReturn AddMatrixF(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) override;

	GReturn SubtractMatrixF(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) override;

	GReturn MultiplyMatrixF(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) override;

	GReturn VectorXMatrixF(GMATRIXF _matrix, GVECTORF _vector, GVECTORF& _outVector) override;

	GReturn ConvertQuaternionF(GQUATERNIONF _quaternion, GMATRIXF& _outMatrix) override;

	GReturn MultiplyNumF(GMATRIXF _matrix, float _scalar, GMATRIXF& _outMatrix) override;

	GReturn DeterminantF(GMATRIXF _matrix, float& _outValue) override;

	GReturn TransposeF(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn InverseF(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn IdentityF(GMATRIXF& _outMatrix) override;

	GReturn GetRotationF(GMATRIXF _matrix, GQUATERNIONF& _outQuaternion) override;

	GReturn GetTranslationF(GMATRIXF _matrix, GVECTORF& _outMatrix) override;

	GReturn GetScaleF(GMATRIXF _matrix, GVECTORF& _outMatrix) override;

	GReturn RotationXF(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) override;

	GReturn RotationYF(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) override;

	GReturn RotationZF(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) override;

	GReturn TranslatelocalF(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatrix) override;

	GReturn ScalingF(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatirx) override;

	GReturn LerpF(GMATRIXF _matrix1, GMATRIXF _matrix2, float _ratio, GMATRIXF& _outMatrix) override;

	//double Matrix

	GReturn AddMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) override;

	GReturn SubtractMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) override;

	GReturn MultiplyMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) override;

	GReturn VectorXMatrixD(GMATRIXD _matrix, GVECTORD _vector, GVECTORD& _outVector) override;

	GReturn ConvertQuaternionD(GQUATERNIOND _quaternion, GMATRIXD& _outMatrix) override;

	GReturn MultiplyNumD(GMATRIXD _matrix, double _scalar, GMATRIXD& _outMatrix) override;

	GReturn DeterminantD(GMATRIXD _matrix, double& _outValue) override;

	GReturn TransposeD(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn InverseD(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn IdentityD(GMATRIXD& _outMatrix) override;

	GReturn GetRotationD(GMATRIXD _matrix, GQUATERNIOND& _outQuaternion) override;

	GReturn GetTranslationD(GMATRIXD _matrix, GVECTORD& _outMatrix) override;

	GReturn GetScaleD(GMATRIXD _matrix, GVECTORD& _outMatrix) override;

	GReturn RotationXD(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) override;

	GReturn RotationYD(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) override;

	GReturn RotationZD(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) override;

	GReturn TranslatelocalD(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatrix) override;

	GReturn ScalingD(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatirx) override;

	GReturn LerpD(GMATRIXD _matrix1, GMATRIXD _matrix2, double _ratio, GMATRIXD& _outMatrix) override;

	GReturn GetCount(unsigned int& _outCount) override;

	GReturn IncrementCount() override;

	GReturn DecrementCount() override;

	GReturn RequestInterface(const GW::GUUIID& _interfaceID, void** _outputInterface) override;


};

GMatirxCpp::GMatirxCpp() : refCount(1)
{
}

GMatirxCpp::~GMatirxCpp()
{
}

//float Matrix

GReturn GMatirxCpp::AddMatrixF(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF & _outMatrix)
{
	for (int i = 0; i < 16; i++)
	{
		_outMatrix.data[i] = _matrix1.data[i] + _matrix2.data[i];
	}
	return FAILURE;
}

GReturn GMatirxCpp::SubtractMatrixF(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF & _outMatrix)
{
	for (int i = 0; i < 16; i++)
	{
		_outMatrix.data[i] = _matrix1.data[i] - _matrix2.data[i];
	}
	return FAILURE;
}

GReturn GMatirxCpp::MultiplyMatrixF(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF & _outMatrix)
{
	_outMatrix.data[0] = _matrix1.data[0] * _matrix2.data[0] + _matrix1.data[1] * _matrix2.data[4] + _matrix1.data[2] * _matrix2.data[8] + _matrix1.data[3] * _matrix2.data[12];
	_outMatrix.data[1] = _matrix1.data[0] * _matrix2.data[1] + _matrix1.data[1] * _matrix2.data[5] + _matrix1.data[2] * _matrix2.data[9] + _matrix1.data[3] * _matrix2.data[13];
	_outMatrix.data[2] = _matrix1.data[0] * _matrix2.data[2] + _matrix1.data[1] * _matrix2.data[6] + _matrix1.data[2] * _matrix2.data[10] + _matrix1.data[3] * _matrix2.data[14];
	_outMatrix.data[3] = _matrix1.data[0] * _matrix2.data[3] + _matrix1.data[1] * _matrix2.data[7] + _matrix1.data[2] * _matrix2.data[11] + _matrix1.data[3] * _matrix2.data[15];

	_outMatrix.data[4] = _matrix1.data[4] * _matrix2.data[0] + _matrix1.data[5] * _matrix2.data[4] + _matrix1.data[6] * _matrix2.data[8] + _matrix1.data[7] * _matrix2.data[12];
	_outMatrix.data[5] = _matrix1.data[4] * _matrix2.data[1] + _matrix1.data[5] * _matrix2.data[5] + _matrix1.data[6] * _matrix2.data[9] + _matrix1.data[7] * _matrix2.data[13];
	_outMatrix.data[6] = _matrix1.data[4] * _matrix2.data[2] + _matrix1.data[5] * _matrix2.data[6] + _matrix1.data[6] * _matrix2.data[10] + _matrix1.data[7] * _matrix2.data[14];
	_outMatrix.data[7] = _matrix1.data[4] * _matrix2.data[3] + _matrix1.data[5] * _matrix2.data[7] + _matrix1.data[6] * _matrix2.data[11] + _matrix1.data[7] * _matrix2.data[15];

	_outMatrix.data[8] = _matrix1.data[8] * _matrix2.data[0] + _matrix1.data[9] * _matrix2.data[4] + _matrix1.data[10] * _matrix2.data[8] + _matrix1.data[11] * _matrix2.data[12];
	_outMatrix.data[9] = _matrix1.data[8] * _matrix2.data[1] + _matrix1.data[9] * _matrix2.data[5] + _matrix1.data[10] * _matrix2.data[9] + _matrix1.data[11] * _matrix2.data[13];
	_outMatrix.data[10] = _matrix1.data[8] * _matrix2.data[2] + _matrix1.data[9] * _matrix2.data[6] + _matrix1.data[10] * _matrix2.data[10] + _matrix1.data[11] * _matrix2.data[14];
	_outMatrix.data[11] = _matrix1.data[8] * _matrix2.data[3] + _matrix1.data[9] * _matrix2.data[7] + _matrix1.data[10] * _matrix2.data[11] + _matrix1.data[11] * _matrix2.data[15];

	_outMatrix.data[12] = _matrix1.data[12] * _matrix2.data[0] + _matrix1.data[13] * _matrix2.data[4] + _matrix1.data[14] * _matrix2.data[8] + _matrix1.data[15] * _matrix2.data[12];
	_outMatrix.data[13] = _matrix1.data[12] * _matrix2.data[1] + _matrix1.data[13] * _matrix2.data[5] + _matrix1.data[14] * _matrix2.data[9] + _matrix1.data[15] * _matrix2.data[13];
	_outMatrix.data[14] = _matrix1.data[12] * _matrix2.data[2] + _matrix1.data[13] * _matrix2.data[6] + _matrix1.data[14] * _matrix2.data[10] + _matrix1.data[15] * _matrix2.data[14];
	_outMatrix.data[15] = _matrix1.data[12] * _matrix2.data[3] + _matrix1.data[13] * _matrix2.data[7] + _matrix1.data[14] * _matrix2.data[11] + _matrix1.data[15] * _matrix2.data[15];

	return FAILURE;
}
 
GReturn GMatirxCpp::VectorXMatrixF(GMATRIXF _matrix, GVECTORF _vector, GVECTORF & _outVector)
{
	_outVector.x = _vector.data[0] * _matrix.data[0] + _vector.data[1] * _matrix.data[4] + _vector.data[2] * _matrix.data[8] + _vector.data[3] * _matrix.data[12];
	_outVector.y = _vector.data[0] * _matrix.data[1] + _vector.data[1] * _matrix.data[5] + _vector.data[2] * _matrix.data[9] + _vector.data[3] * _matrix.data[13];
	_outVector.z = _vector.data[0] * _matrix.data[2] + _vector.data[1] * _matrix.data[6] + _vector.data[2] * _matrix.data[10] + _vector.data[3] * _matrix.data[14];
	_outVector.w = _vector.data[0] * _matrix.data[3] + _vector.data[1] * _matrix.data[7] + _vector.data[2] * _matrix.data[11] + _vector.data[3] * _matrix.data[15];

	return FAILURE;
}

GReturn GMatirxCpp::ConvertQuaternionF(GQUATERNIONF _quaternion, GMATRIXF & _outMatrix)
{
	float xx2 = 2 * _quaternion.x * _quaternion.x;
	float yy2 = 2 * _quaternion.y * _quaternion.y;
	float zz2 = 2 * _quaternion.z * _quaternion.z;

	float xy2 = 2 * _quaternion.x * _quaternion.y;
	float xz2 = 2 * _quaternion.x * _quaternion.z;
	float yz2 = 2 * _quaternion.y * _quaternion.z;

	float wx2 = 2 * _quaternion.w * _quaternion.x;
	float wy2 = 2 * _quaternion.w * _quaternion.y;
	float wz2 = 2 * _quaternion.w * _quaternion.z;

	_outMatrix.data[0] = 1.0f - yy2 - zz2;
	_outMatrix.data[1] = xy2 - wz2;
	_outMatrix.data[2] = xz2 + wy2;
	_outMatrix.data[3] = 0.0f;
	_outMatrix.data[4] = xy2 + wz2;
	_outMatrix.data[5] = 1.0f - xx2 - zz2;
	_outMatrix.data[6] = yz2 - wx2;
	_outMatrix.data[7] = 0.0f;
	_outMatrix.data[8] = xz2 - wy2;
	_outMatrix.data[9] = yz2 + wx2;
	_outMatrix.data[10] = 1.0f - xx2 - yy2;
	_outMatrix.data[11] = 0.0f;
	_outMatrix.data[12] = 0.0f;
	_outMatrix.data[13] = 0.0f;
	_outMatrix.data[14] = 0.0f;
	_outMatrix.data[15] = 1.0f;

	return FAILURE;
} 

GReturn GMatirxCpp::MultiplyNumF(GMATRIXF _matrix, float _scalar, GMATRIXF & _outMatrix)
{
	for (int i = 0; i < 16; i++)
	{
		_outMatrix.data[i] = _matrix.data[i] * _scalar;
	}
	return FAILURE;
}

GReturn GMatirxCpp::DeterminantF(GMATRIXF _matrix, float & _outValue)
{
	float a0 = _matrix.data[0] * _matrix.data[5] - _matrix.data[1] * _matrix.data[4];
	float a1 = _matrix.data[0] * _matrix.data[6] - _matrix.data[2] * _matrix.data[4];
	float a2 = _matrix.data[0] * _matrix.data[7] - _matrix.data[3] * _matrix.data[4];
	float a3 = _matrix.data[1] * _matrix.data[6] - _matrix.data[2] * _matrix.data[5];
	float a4 = _matrix.data[1] * _matrix.data[7] - _matrix.data[3] * _matrix.data[5];
	float a5 = _matrix.data[2] * _matrix.data[7] - _matrix.data[3] * _matrix.data[6];
	float b0 = _matrix.data[8] * _matrix.data[13] - _matrix.data[9] * _matrix.data[12];
	float b1 = _matrix.data[8] * _matrix.data[14] - _matrix.data[10] * _matrix.data[12];
	float b2 = _matrix.data[8] * _matrix.data[15] - _matrix.data[11] * _matrix.data[12];
	float b3 = _matrix.data[9] * _matrix.data[14] - _matrix.data[10] * _matrix.data[13];
	float b4 = _matrix.data[9] * _matrix.data[15] - _matrix.data[11] * _matrix.data[13];
	float b5 = _matrix.data[10] * _matrix.data[15] - _matrix.data[11] * _matrix.data[14];

	_outValue = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

	return SUCCESS;
}

GReturn GMatirxCpp::TransposeF(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	_outMatrix.data[0] = _matrix.data[0];
	_outMatrix.data[1] = _matrix.data[4];
	_outMatrix.data[2] = _matrix.data[8];
	_outMatrix.data[3] = _matrix.data[12];
	_outMatrix.data[4] = _matrix.data[1];
	_outMatrix.data[5] = _matrix.data[5];
	_outMatrix.data[6] = _matrix.data[9];
	_outMatrix.data[7] = _matrix.data[13];
	_outMatrix.data[8] = _matrix.data[2];
	_outMatrix.data[9] = _matrix.data[6];
	_outMatrix.data[10] = _matrix.data[10];
	_outMatrix.data[11] = _matrix.data[14];
	_outMatrix.data[12] = _matrix.data[3];
	_outMatrix.data[13] = _matrix.data[7];
	_outMatrix.data[14] = _matrix.data[11];
	_outMatrix.data[15] = _matrix.data[15];
	return FAILURE;
}

GReturn GMatirxCpp::InverseF(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	float det;
	float a0 = _matrix.data[0] * _matrix.data[5] - _matrix.data[1] * _matrix.data[4];
	float a1 = _matrix.data[0] * _matrix.data[6] - _matrix.data[2] * _matrix.data[4];
	float a2 = _matrix.data[0] * _matrix.data[7] - _matrix.data[3] * _matrix.data[4];
	float a3 = _matrix.data[1] * _matrix.data[6] - _matrix.data[2] * _matrix.data[5];
	float a4 = _matrix.data[1] * _matrix.data[7] - _matrix.data[3] * _matrix.data[5];
	float a5 = _matrix.data[2] * _matrix.data[7] - _matrix.data[3] * _matrix.data[6];
	float b0 = _matrix.data[8] * _matrix.data[13] - _matrix.data[9] * _matrix.data[12];
	float b1 = _matrix.data[8] * _matrix.data[14] - _matrix.data[10] * _matrix.data[12];
	float b2 = _matrix.data[8] * _matrix.data[15] - _matrix.data[11] * _matrix.data[12];
	float b3 = _matrix.data[9] * _matrix.data[14] - _matrix.data[10] * _matrix.data[13];
	float b4 = _matrix.data[9] * _matrix.data[15] - _matrix.data[11] * _matrix.data[13];
	float b5 = _matrix.data[10] * _matrix.data[15] - _matrix.data[11] * _matrix.data[14];

	det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

	_outMatrix.data[0] = _matrix.data[5] * b5 - _matrix.data[6] * b4 + _matrix.data[7] * b3;
	_outMatrix.data[1] = -_matrix.data[1] * b5 + _matrix.data[2] * b4 - _matrix.data[3] * b3;
	_outMatrix.data[2] = _matrix.data[13] * a5 - _matrix.data[14] * a4 + _matrix.data[15] * a3;
	_outMatrix.data[3] = -_matrix.data[9] * a5 + _matrix.data[10] * a4 - _matrix.data[11] * a3;

	_outMatrix.data[4] = -_matrix.data[4] * b5 + _matrix.data[6] * b2 - _matrix.data[7] * b1;
	_outMatrix.data[5] = _matrix.data[0] * b5 - _matrix.data[2] * b2 + _matrix.data[3] * b1;
	_outMatrix.data[6] = -_matrix.data[12] * a5 + _matrix.data[14] * a2 - _matrix.data[15] * a1;
	_outMatrix.data[7] = _matrix.data[8] * a5 - _matrix.data[10] * a2 + _matrix.data[11] * a1;

	_outMatrix.data[8] = _matrix.data[4] * b4 - _matrix.data[5] * b2 + _matrix.data[7] * b0;
	_outMatrix.data[9] = -_matrix.data[0] * b4 + _matrix.data[1] * b2 - _matrix.data[3] * b0;
	_outMatrix.data[10] = _matrix.data[12] * a4 - _matrix.data[13] * a2 + _matrix.data[15] * a0;
	_outMatrix.data[11] = -_matrix.data[8] * a4 + _matrix.data[9] * a2 - _matrix.data[11] * a0;

	_outMatrix.data[12] = -_matrix.data[4] * b3 + _matrix.data[5] * b1 - _matrix.data[6] * b0;
	_outMatrix.data[13] = _matrix.data[0] * b3 - _matrix.data[1] * b1 + _matrix.data[2] * b0;
	_outMatrix.data[14] = -_matrix.data[12] * a3 + _matrix.data[13] * a1 - _matrix.data[14] * a0;
	_outMatrix.data[15] = _matrix.data[8] * a3 - _matrix.data[9] * a1 + _matrix.data[10] * a0;

	MultiplyNumF(_outMatrix, 1.0f / det, _outMatrix);

	return FAILURE;
}

GReturn GMatirxCpp::IdentityF(GMATRIXF & _outMatrix) 
{
	_outMatrix = GIdentityMatrixF;
	return FAILURE;
}

GReturn GMatirxCpp::GetRotationF(GMATRIXF _matrix, GQUATERNIONF & _outQuaternion)
{
	float det;
	float sx = sqrtf(_matrix.data[0] * _matrix.data[0] + _matrix.data[4] * _matrix.data[4] + _matrix.data[8] * _matrix.data[8]);
	float sy = sqrtf(_matrix.data[1] * _matrix.data[1] + _matrix.data[5] * _matrix.data[5] + _matrix.data[9] * _matrix.data[9]);
	float sz = sqrtf(_matrix.data[2] * _matrix.data[2] + _matrix.data[6] * _matrix.data[6] + _matrix.data[10] * _matrix.data[10]);
	DeterminantF(_matrix, det);
	if (det < 0)
	{
		sz = -sz;
	}
	GMATRIXF Rotation = _matrix;
	Rotation.data[0] /= sx;
	Rotation.data[1] /= sy;
	Rotation.data[2] /= sz;
	Rotation.data[4] /= sx;
	Rotation.data[5] /= sy;
	Rotation.data[6] /= sz;
	Rotation.data[8] /= sx;
	Rotation.data[9] /= sy;
	Rotation.data[10] /= sz;


	float trace = Rotation.data[0] + Rotation.data[5] + Rotation.data[10] + 1;

	if (trace > G_EPSILON_F)
	{
		float s = 0.5f / sqrtf(trace);
		_outQuaternion.x = (Rotation.row3.y - Rotation.row2.z) * s;
		_outQuaternion.y = (Rotation.row1.z - Rotation.row3.x) * s;
		_outQuaternion.z = (Rotation.row2.x - Rotation.row1.y) * s;
		_outQuaternion.w = 0.25f / s;
	}
	else
	{
		if (Rotation.row1.x > Rotation.row2.y && Rotation.row1.x > Rotation.row3.z)
		{
			float s = 0.5f / sqrtf(1.0f + Rotation.row1.x - Rotation.row2.y - Rotation.row3.z);
			_outQuaternion.x = 0.25f / s;
			_outQuaternion.y = (Rotation.row1.y + Rotation.row2.x) * s;
			_outQuaternion.z = (Rotation.row1.z + Rotation.row3.x) * s;
			_outQuaternion.w = (Rotation.row3.y - Rotation.row2.z) * s;
		}
		else if (Rotation.row2.y > Rotation.row3.z)
		{
			float s = 0.5f / sqrtf(1.0f + Rotation.row2.y - Rotation.row1.x - Rotation.row3.z);
			_outQuaternion.x = (Rotation.row1.y + Rotation.row2.x) * s;
			_outQuaternion.y = 0.25f / s;
			_outQuaternion.z = (Rotation.row2.z + Rotation.row3.y) * s;
			_outQuaternion.w = (Rotation.row1.z - Rotation.row3.x) * s;
		}
		else
		{
			float s = 0.5f / sqrtf(1.0f + Rotation.row3.z - Rotation.row1.x - Rotation.row2.y);
			_outQuaternion.x = (Rotation.row1.z + Rotation.row3.x) * s;
			_outQuaternion.y = (Rotation.row2.z + Rotation.row3.y) * s;
			_outQuaternion.z = 0.25f / s;
			_outQuaternion.w = (Rotation.row2.x - Rotation.row1.y) * s;
		}
	}

	return FAILURE;
}

GReturn GMatirxCpp::GetTranslationF(GMATRIXF _matrix, GVECTORF& _outVector)
{
	_outVector.x = _matrix.data[3];
	_outVector.y = _matrix.data[7];
	_outVector.z = _matrix.data[11];
	_outVector.w = 0;
	return FAILURE;
}
 
GReturn GMatirxCpp::GetScaleF(GMATRIXF _matrix, GVECTORF& _outVector)
{
	float det;

	_outVector.x = sqrtf(_matrix.data[0] * _matrix.data[0] + _matrix.data[4] * _matrix.data[4] + _matrix.data[8] * _matrix.data[8]);
	_outVector.y = sqrtf(_matrix.data[1] * _matrix.data[1] + _matrix.data[5] * _matrix.data[5] + _matrix.data[9] * _matrix.data[9]);
	_outVector.z = sqrtf(_matrix.data[2] * _matrix.data[2] + _matrix.data[6] * _matrix.data[6] + _matrix.data[10] * _matrix.data[10]);
	_outVector.w = 0;

	DeterminantF(_matrix, det);
	if (det < 0)
	{
		_outVector.z = -_outVector.z;
	}

	return FAILURE;
}
 
GReturn GMatirxCpp::RotationXF(GMATRIXF _matrix, float _radian, GMATRIXF & _outMatrix)
{
	float c = cosf(_radian);
	float s = sinf(_radian);
	GMATRIXF Rotation = GIdentityMatrixF;
	Rotation.data[5] = c;
	Rotation.data[6] = -s;
	Rotation.data[9] = s;
	Rotation.data[10] = c;

	MultiplyMatrixF(_matrix, Rotation, _outMatrix);

	return FAILURE;
}

GReturn GMatirxCpp::RotationYF(GMATRIXF _matrix, float _radian, GMATRIXF & _outMatrix)
{
	float c = cosf(_radian);
	float s = sinf(_radian);
	GMATRIXF Rotation = GIdentityMatrixF;
	Rotation.data[0] = c;
	Rotation.data[2] = s;
	Rotation.data[8] = -s;
	Rotation.data[10] = c;

	MultiplyMatrixF(_matrix, Rotation, _outMatrix);
	return FAILURE;
}

GReturn GMatirxCpp::RotationZF(GMATRIXF _matrix, float _radian, GMATRIXF & _outMatrix)
{
	float c = cosf(_radian);
	float s = sinf(_radian);
	GMATRIXF Rotation = GIdentityMatrixF;
	Rotation.data[0] = c;
	Rotation.data[1] = -s;
	Rotation.data[4] = s;
	Rotation.data[5] = c;

	MultiplyMatrixF(_matrix, Rotation, _outMatrix);
	return FAILURE;
}

GReturn GMatirxCpp::TranslatelocalF(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF & _outMatrix)
{
	GMATRIXF Translation = GIdentityMatrixF;
	Translation.data[3] = _vector.x;
	Translation.data[7] = _vector.y;
	Translation.data[11] = _vector.z;

	MultiplyMatrixF(_matrix, Translation, _outMatrix);

	return FAILURE;
}

GReturn GMatirxCpp::ScalingF(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF & _outMatrix)
{
	GMATRIXF Scale = GIdentityMatrixF;
	Scale.data[0] = _vector.x;
	Scale.data[5] = _vector.y;
	Scale.data[10] = _vector.z;

	MultiplyMatrixF(_matrix, Scale, _outMatrix);

	return FAILURE;
}

GReturn GMatirxCpp::LerpF(GMATRIXF _matrix1, GMATRIXF _matrix2, float _ratio, GMATRIXF & _outMatrix)
{
	for (int i = 0; i < 16; i++)
	{
		_outMatrix.data[i] = G_LERP(_matrix1.data[i], _matrix2.data[i], _ratio);
	}
	return FAILURE;
}
 

//double Matrix

GReturn GMatirxCpp::AddMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD & _outMatrix)
{
	for (int i = 0; i < 16; i++)
	{
		_outMatrix.data[i] = _matrix1.data[i] + _matrix2.data[i];
	}
	return FAILURE;
}

GReturn GMatirxCpp::SubtractMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD & _outMatrix)
{
	for (int i = 0; i < 16; i++)
	{
		_outMatrix.data[i] = _matrix1.data[i] - _matrix2.data[i];
	}
	return FAILURE;
}

GReturn GMatirxCpp::MultiplyMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD & _outMatrix)
{
	_outMatrix.data[0] = _matrix1.data[0] * _matrix2.data[0] + _matrix1.data[1] * _matrix2.data[4] + _matrix1.data[2] * _matrix2.data[8] + _matrix1.data[3] * _matrix2.data[12];
	_outMatrix.data[1] = _matrix1.data[0] * _matrix2.data[1] + _matrix1.data[1] * _matrix2.data[5] + _matrix1.data[2] * _matrix2.data[9] + _matrix1.data[3] * _matrix2.data[13];
	_outMatrix.data[2] = _matrix1.data[0] * _matrix2.data[2] + _matrix1.data[1] * _matrix2.data[6] + _matrix1.data[2] * _matrix2.data[10] + _matrix1.data[3] * _matrix2.data[14];
	_outMatrix.data[3] = _matrix1.data[0] * _matrix2.data[3] + _matrix1.data[1] * _matrix2.data[7] + _matrix1.data[2] * _matrix2.data[11] + _matrix1.data[3] * _matrix2.data[15];

	_outMatrix.data[4] = _matrix1.data[4] * _matrix2.data[0] + _matrix1.data[5] * _matrix2.data[4] + _matrix1.data[6] * _matrix2.data[8] + _matrix1.data[7] * _matrix2.data[12];
	_outMatrix.data[5] = _matrix1.data[4] * _matrix2.data[1] + _matrix1.data[5] * _matrix2.data[5] + _matrix1.data[6] * _matrix2.data[9] + _matrix1.data[7] * _matrix2.data[13];
	_outMatrix.data[6] = _matrix1.data[4] * _matrix2.data[2] + _matrix1.data[5] * _matrix2.data[6] + _matrix1.data[6] * _matrix2.data[10] + _matrix1.data[7] * _matrix2.data[14];
	_outMatrix.data[7] = _matrix1.data[4] * _matrix2.data[3] + _matrix1.data[5] * _matrix2.data[7] + _matrix1.data[6] * _matrix2.data[11] + _matrix1.data[7] * _matrix2.data[15];

	_outMatrix.data[8] = _matrix1.data[8] * _matrix2.data[0] + _matrix1.data[9] * _matrix2.data[4] + _matrix1.data[10] * _matrix2.data[8] + _matrix1.data[11] * _matrix2.data[12];
	_outMatrix.data[9] = _matrix1.data[8] * _matrix2.data[1] + _matrix1.data[9] * _matrix2.data[5] + _matrix1.data[10] * _matrix2.data[9] + _matrix1.data[11] * _matrix2.data[13];
	_outMatrix.data[10] = _matrix1.data[8] * _matrix2.data[2] + _matrix1.data[9] * _matrix2.data[6] + _matrix1.data[10] * _matrix2.data[10] + _matrix1.data[11] * _matrix2.data[14];
	_outMatrix.data[11] = _matrix1.data[8] * _matrix2.data[3] + _matrix1.data[9] * _matrix2.data[7] + _matrix1.data[10] * _matrix2.data[11] + _matrix1.data[11] * _matrix2.data[15];

	_outMatrix.data[12] = _matrix1.data[12] * _matrix2.data[0] + _matrix1.data[13] * _matrix2.data[4] + _matrix1.data[14] * _matrix2.data[8] + _matrix1.data[15] * _matrix2.data[12];
	_outMatrix.data[13] = _matrix1.data[12] * _matrix2.data[1] + _matrix1.data[13] * _matrix2.data[5] + _matrix1.data[14] * _matrix2.data[9] + _matrix1.data[15] * _matrix2.data[13];
	_outMatrix.data[14] = _matrix1.data[12] * _matrix2.data[2] + _matrix1.data[13] * _matrix2.data[6] + _matrix1.data[14] * _matrix2.data[10] + _matrix1.data[15] * _matrix2.data[14];
	_outMatrix.data[15] = _matrix1.data[12] * _matrix2.data[3] + _matrix1.data[13] * _matrix2.data[7] + _matrix1.data[14] * _matrix2.data[11] + _matrix1.data[15] * _matrix2.data[15];

	return FAILURE;
}

GReturn GMatirxCpp::VectorXMatrixD(GMATRIXD _matrix, GVECTORD _vector, GVECTORD & _outVector)
{
	_outVector.x = _vector.data[0] * _matrix.data[0] + _vector.data[1] * _matrix.data[4] + _vector.data[2] * _matrix.data[8] + _vector.data[3] * _matrix.data[12];
	_outVector.y = _vector.data[0] * _matrix.data[1] + _vector.data[1] * _matrix.data[5] + _vector.data[2] * _matrix.data[9] + _vector.data[3] * _matrix.data[13];
	_outVector.z = _vector.data[0] * _matrix.data[2] + _vector.data[1] * _matrix.data[6] + _vector.data[2] * _matrix.data[10] + _vector.data[3] * _matrix.data[14];
	_outVector.w = _vector.data[0] * _matrix.data[3] + _vector.data[1] * _matrix.data[7] + _vector.data[2] * _matrix.data[11] + _vector.data[3] * _matrix.data[15];

	return FAILURE;
}

GReturn GMatirxCpp::ConvertQuaternionD(GQUATERNIOND _quaternion, GMATRIXD & _outMatrix)
{
	double xx2 = 2 * _quaternion.x * _quaternion.x;
	double yy2 = 2 * _quaternion.y * _quaternion.y;
	double zz2 = 2 * _quaternion.z * _quaternion.z;

	double xy2 = 2 * _quaternion.x * _quaternion.y;
	double xz2 = 2 * _quaternion.x * _quaternion.z;
	double yz2 = 2 * _quaternion.y * _quaternion.z;

	double wx2 = 2 * _quaternion.w * _quaternion.x;
	double wy2 = 2 * _quaternion.w * _quaternion.y;
	double wz2 = 2 * _quaternion.w * _quaternion.z;

	_outMatrix.data[0] = 1.0f - yy2 - zz2;
	_outMatrix.data[1] = xy2 - wz2;
	_outMatrix.data[2] = xz2 + wy2;
	_outMatrix.data[3] = 0.0f;
	_outMatrix.data[4] = xy2 + wz2;
	_outMatrix.data[5] = 1.0f - xx2 - zz2;
	_outMatrix.data[6] = yz2 - wx2;
	_outMatrix.data[7] = 0.0f;
	_outMatrix.data[8] = xz2 - wy2;
	_outMatrix.data[9] = yz2 + wx2;
	_outMatrix.data[10] = 1.0f - xx2 - yy2;
	_outMatrix.data[11] = 0.0f;
	_outMatrix.data[12] = 0.0f;
	_outMatrix.data[13] = 0.0f;
	_outMatrix.data[14] = 0.0f;
	_outMatrix.data[15] = 1.0f;

	return FAILURE;
}

GReturn GMatirxCpp::MultiplyNumD(GMATRIXD _matrix, double _scalar, GMATRIXD & _outMatrix)
{
	for (int i = 0; i < 16; i++)
	{
		_outMatrix.data[i] = _matrix.data[i] * _scalar;
	}
	return FAILURE;
}

GReturn GMatirxCpp::DeterminantD(GMATRIXD _matrix, double & _outValue)
{
	double a0 = _matrix.data[0] * _matrix.data[5] - _matrix.data[1] * _matrix.data[4];
	double a1 = _matrix.data[0] * _matrix.data[6] - _matrix.data[2] * _matrix.data[4];
	double a2 = _matrix.data[0] * _matrix.data[7] - _matrix.data[3] * _matrix.data[4];
	double a3 = _matrix.data[1] * _matrix.data[6] - _matrix.data[2] * _matrix.data[5];
	double a4 = _matrix.data[1] * _matrix.data[7] - _matrix.data[3] * _matrix.data[5];
	double a5 = _matrix.data[2] * _matrix.data[7] - _matrix.data[3] * _matrix.data[6];
	double b0 = _matrix.data[8] * _matrix.data[13] - _matrix.data[9] * _matrix.data[12];
	double b1 = _matrix.data[8] * _matrix.data[14] - _matrix.data[10] * _matrix.data[12];
	double b2 = _matrix.data[8] * _matrix.data[15] - _matrix.data[11] * _matrix.data[12];
	double b3 = _matrix.data[9] * _matrix.data[14] - _matrix.data[10] * _matrix.data[13];
	double b4 = _matrix.data[9] * _matrix.data[15] - _matrix.data[11] * _matrix.data[13];
	double b5 = _matrix.data[10] * _matrix.data[15] - _matrix.data[11] * _matrix.data[14];

	_outValue = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

	return SUCCESS;
}

GReturn GMatirxCpp::TransposeD(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	_outMatrix.data[0] = _matrix.data[0];
	_outMatrix.data[1] = _matrix.data[4];
	_outMatrix.data[2] = _matrix.data[8];
	_outMatrix.data[3] = _matrix.data[12];
	_outMatrix.data[4] = _matrix.data[1];
	_outMatrix.data[5] = _matrix.data[5];
	_outMatrix.data[6] = _matrix.data[9];
	_outMatrix.data[7] = _matrix.data[13];
	_outMatrix.data[8] = _matrix.data[2];
	_outMatrix.data[9] = _matrix.data[6];
	_outMatrix.data[10] = _matrix.data[10];
	_outMatrix.data[11] = _matrix.data[14];
	_outMatrix.data[12] = _matrix.data[3];
	_outMatrix.data[13] = _matrix.data[7];
	_outMatrix.data[14] = _matrix.data[11];
	_outMatrix.data[15] = _matrix.data[15];
	return FAILURE;
}

GReturn GMatirxCpp::InverseD(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	double det;
	double a0 = _matrix.data[0] * _matrix.data[5] - _matrix.data[1] * _matrix.data[4];
	double a1 = _matrix.data[0] * _matrix.data[6] - _matrix.data[2] * _matrix.data[4];
	double a2 = _matrix.data[0] * _matrix.data[7] - _matrix.data[3] * _matrix.data[4];
	double a3 = _matrix.data[1] * _matrix.data[6] - _matrix.data[2] * _matrix.data[5];
	double a4 = _matrix.data[1] * _matrix.data[7] - _matrix.data[3] * _matrix.data[5];
	double a5 = _matrix.data[2] * _matrix.data[7] - _matrix.data[3] * _matrix.data[6];
	double b0 = _matrix.data[8] * _matrix.data[13] - _matrix.data[9] * _matrix.data[12];
	double b1 = _matrix.data[8] * _matrix.data[14] - _matrix.data[10] * _matrix.data[12];
	double b2 = _matrix.data[8] * _matrix.data[15] - _matrix.data[11] * _matrix.data[12];
	double b3 = _matrix.data[9] * _matrix.data[14] - _matrix.data[10] * _matrix.data[13];
	double b4 = _matrix.data[9] * _matrix.data[15] - _matrix.data[11] * _matrix.data[13];
	double b5 = _matrix.data[10] * _matrix.data[15] - _matrix.data[11] * _matrix.data[14];

	det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

	_outMatrix.data[0] = _matrix.data[5] * b5 - _matrix.data[6] * b4 + _matrix.data[7] * b3;
	_outMatrix.data[1] = -_matrix.data[1] * b5 + _matrix.data[2] * b4 - _matrix.data[3] * b3;
	_outMatrix.data[2] = _matrix.data[13] * a5 - _matrix.data[14] * a4 + _matrix.data[15] * a3;
	_outMatrix.data[3] = -_matrix.data[9] * a5 + _matrix.data[10] * a4 - _matrix.data[11] * a3;

	_outMatrix.data[4] = -_matrix.data[4] * b5 + _matrix.data[6] * b2 - _matrix.data[7] * b1;
	_outMatrix.data[5] = _matrix.data[0] * b5 - _matrix.data[2] * b2 + _matrix.data[3] * b1;
	_outMatrix.data[6] = -_matrix.data[12] * a5 + _matrix.data[14] * a2 - _matrix.data[15] * a1;
	_outMatrix.data[7] = _matrix.data[8] * a5 - _matrix.data[10] * a2 + _matrix.data[11] * a1;

	_outMatrix.data[8] = _matrix.data[4] * b4 - _matrix.data[5] * b2 + _matrix.data[7] * b0;
	_outMatrix.data[9] = -_matrix.data[0] * b4 + _matrix.data[1] * b2 - _matrix.data[3] * b0;
	_outMatrix.data[10] = _matrix.data[12] * a4 - _matrix.data[13] * a2 + _matrix.data[15] * a0;
	_outMatrix.data[11] = -_matrix.data[8] * a4 + _matrix.data[9] * a2 - _matrix.data[11] * a0;

	_outMatrix.data[12] = -_matrix.data[4] * b3 + _matrix.data[5] * b1 - _matrix.data[6] * b0;
	_outMatrix.data[13] = _matrix.data[0] * b3 - _matrix.data[1] * b1 + _matrix.data[2] * b0;
	_outMatrix.data[14] = -_matrix.data[12] * a3 + _matrix.data[13] * a1 - _matrix.data[14] * a0;
	_outMatrix.data[15] = _matrix.data[8] * a3 - _matrix.data[9] * a1 + _matrix.data[10] * a0;

	MultiplyNumD(_outMatrix, 1.0f / det, _outMatrix);

	return FAILURE;
}

GReturn GMatirxCpp::IdentityD(GMATRIXD & _outMatrix)
{
	_outMatrix = GIdentityMatrixD;
	return FAILURE;
}

GReturn GMatirxCpp::GetRotationD(GMATRIXD _matrix, GQUATERNIOND& _outQuaternion)
{
	double det;
	double sx = sqrt(_matrix.data[0] * _matrix.data[0] + _matrix.data[4] * _matrix.data[4] + _matrix.data[8] * _matrix.data[8]);
	double sy = sqrt(_matrix.data[1] * _matrix.data[1] + _matrix.data[5] * _matrix.data[5] + _matrix.data[9] * _matrix.data[9]);
	double sz = sqrt(_matrix.data[2] * _matrix.data[2] + _matrix.data[6] * _matrix.data[6] + _matrix.data[10] * _matrix.data[10]);
	DeterminantD(_matrix, det);
	if (det < 0)
	{
		sz = -sz;
	}
	GMATRIXD Rotation = _matrix;
	Rotation.data[0] /= sx;
	Rotation.data[1] /= sy;
	Rotation.data[2] /= sz;
	Rotation.data[4] /= sx;
	Rotation.data[5] /= sy;
	Rotation.data[6] /= sz;
	Rotation.data[8] /= sx;
	Rotation.data[9] /= sy;
	Rotation.data[10] /= sz;

	double trace = Rotation.data[0] + Rotation.data[5] + Rotation.data[10] + 1;

	if (trace > G_EPSILON_D)
	{
		double s = 0.5 / sqrt(trace);
		_outQuaternion.x = (Rotation.row3.y - Rotation.row2.z) * s;
		_outQuaternion.y = (Rotation.row1.z - Rotation.row3.x) * s;
		_outQuaternion.z = (Rotation.row2.x - Rotation.row1.y) * s;
		_outQuaternion.w = 0.25 / s;
	}
	else
	{
		if (Rotation.row1.x > Rotation.row2.y && Rotation.row1.x > Rotation.row3.z)
		{
			double s = 0.5f / sqrt(1.0 + Rotation.row1.x - Rotation.row2.y - Rotation.row3.z);
			_outQuaternion.x = 0.25 / s;
			_outQuaternion.y = (Rotation.row1.y + Rotation.row2.x) * s;
			_outQuaternion.z = (Rotation.row1.z + Rotation.row3.x) * s;
			_outQuaternion.w = (Rotation.row3.y - Rotation.row2.z) * s;
		}
		else if (Rotation.row2.y > Rotation.row3.z)
		{
			double s = 0.5 / sqrt(1.0 + Rotation.row2.y - Rotation.row1.x - Rotation.row3.z);
			_outQuaternion.x = (Rotation.row1.y + Rotation.row2.x) * s;
			_outQuaternion.y = 0.25 / s;
			_outQuaternion.z = (Rotation.row2.z + Rotation.row3.y) * s;
			_outQuaternion.w = (Rotation.row1.z - Rotation.row3.x) * s;
		}
		else
		{
			double s = 0.5 / sqrt(1.0 + Rotation.row3.z - Rotation.row1.x - Rotation.row2.y);
			_outQuaternion.x = (Rotation.row1.z + Rotation.row3.x) * s;
			_outQuaternion.y = (Rotation.row2.z + Rotation.row3.y) * s;
			_outQuaternion.z = 0.25 / s;
			_outQuaternion.w = (Rotation.row2.x - Rotation.row1.y) * s;
		}
	}

	return FAILURE;
}

GReturn GMatirxCpp::GetTranslationD(GMATRIXD _matrix, GVECTORD& _outVector)
{
	_outVector.x = _matrix.data[3];
	_outVector.y = _matrix.data[7];
	_outVector.z = _matrix.data[11];
	_outVector.w = 0 ;
	return FAILURE;
}

GReturn GMatirxCpp::GetScaleD(GMATRIXD _matrix, GVECTORD& _outVector)
{
	double det;

	_outVector.x = sqrt(_matrix.data[0] * _matrix.data[0] + _matrix.data[4] * _matrix.data[4] + _matrix.data[8] * _matrix.data[8]);
	_outVector.y = sqrt(_matrix.data[1] * _matrix.data[1] + _matrix.data[5] * _matrix.data[5] + _matrix.data[9] * _matrix.data[9]);
	_outVector.z = sqrt(_matrix.data[2] * _matrix.data[2] + _matrix.data[6] * _matrix.data[6] + _matrix.data[10] * _matrix.data[10]);
	_outVector.w = 0;

	DeterminantD(_matrix, det);
	if (det < 0)
	{
		_outVector.z = -_outVector.z;
	}

	return FAILURE;
}

GReturn GMatirxCpp::RotationXD(GMATRIXD _matrix, double _radian, GMATRIXD & _outMatrix)
{
	double c = cos(_radian);
	double s = sin(_radian);
	GMATRIXD Rotation = GIdentityMatrixD;
	Rotation.data[5] = c;
	Rotation.data[6] = -s;
	Rotation.data[9] = s;
	Rotation.data[10] = c;

	MultiplyMatrixD(_matrix, Rotation, _outMatrix);

	return FAILURE;
}

GReturn GMatirxCpp::RotationYD(GMATRIXD _matrix, double _radian, GMATRIXD & _outMatrix)
{
	double c = cos(_radian);
	double s = sin(_radian);
	GMATRIXD Rotation = GIdentityMatrixD;
	Rotation.data[0] = c;
	Rotation.data[2] = s;
	Rotation.data[8] = -s;
	Rotation.data[10] = c;

	MultiplyMatrixD(_matrix, Rotation, _outMatrix);
	return FAILURE;
}

GReturn GMatirxCpp::RotationZD(GMATRIXD _matrix, double _radian, GMATRIXD & _outMatrix)
{
	double c = cos(_radian);
	double s = sin(_radian);
	GMATRIXD Rotation = GIdentityMatrixD;
	Rotation.data[0] = c;
	Rotation.data[1] = -s;
	Rotation.data[4] = s;
	Rotation.data[5] = c;

	MultiplyMatrixD(_matrix, Rotation, _outMatrix);
	return FAILURE;
}

GReturn GMatirxCpp::TranslatelocalD(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD & _outMatrix)
{
	GMATRIXD Translation = GIdentityMatrixD;
	Translation.data[3] = _vector.x;
	Translation.data[7] = _vector.y;
	Translation.data[11] = _vector.z;

	MultiplyMatrixD(_matrix, Translation, _outMatrix);

	return FAILURE;
}

GReturn GMatirxCpp::ScalingD(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD & _outMatrix)
{
	GMATRIXD Scale = GIdentityMatrixD;
	Scale.data[0] = _vector.x;
	Scale.data[5] = _vector.y;
	Scale.data[10] = _vector.z;

	MultiplyMatrixD(_matrix, Scale, _outMatrix);

	return FAILURE;
}

GReturn GMatirxCpp::LerpD(GMATRIXD _matrix1, GMATRIXD _matrix2, double _ratio, GMATRIXD & _outMatrix)
{
	for (int i = 0; i < 16; i++)
	{
		_outMatrix.data[i] = G_LERP(_matrix1.data[i], _matrix2.data[i], _ratio);
	}
	return FAILURE;
}

GReturn GMatirxCpp::GetCount(unsigned int & _outCount)
{
	//Store reference count.
	_outCount = refCount;

	return GW::SUCCESS;
}

GReturn GMatirxCpp::IncrementCount()
{
	//Check to make sure overflow will not occur.
	if (refCount == G_UINT_MAX)
		return GW::FAILURE;

	//Increment reference count.
	++refCount;

	return GW::SUCCESS;
}

GReturn GMatirxCpp::DecrementCount()
{
	//Check to make sure underflow will not occur.
	if (refCount == 0)
		return GW::FAILURE;

	//Decrement reference count.
	--refCount;

	return GW::SUCCESS;
}

GReturn GMatirxCpp::RequestInterface(const GW::GUUIID & _interfaceID, void ** _outputInterface)
{
	if (_outputInterface == nullptr)
		return GW::INVALID_ARGUMENT;

	//If passed in interface is equivalent to current interface (this).
	if (_interfaceID == GW::MATH::GMatrixUUIID)
	{
		//Temporary GFile* to ensure proper functions are called.
		GMatrix* convert = reinterpret_cast<GMatrix*>(this);

		//Increment the count of the GFile.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//If requested interface is multithreaded.
	else if (_interfaceID == GW::CORE::GSingleThreadedUUIID)
	{
		//Temporary GSingleThreaded* to ensure proper functions are called.
		GSingleThreaded* convert = reinterpret_cast<GSingleThreaded*>(this);

		//Increment the count of the GMultithreaded.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//If requested interface is the primary interface.
	else if (_interfaceID == GW::CORE::GInterfaceUUIID)
	{
		//Temporary GInterface* to ensure proper functions are called.
		GInterface* convert = reinterpret_cast<GInterface*>(this);

		//Increment the count of the GInterface.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//Interface is not supported.
	else
		return GW::INTERFACE_UNSUPPORTED;

	return GW::SUCCESS;
}

GATEWARE_EXPORT_EXPLICIT GReturn CreateGMatrix(GMatrix** _outMatrix)
{
	return GW::MATH::CreateGMatrix(_outMatrix);
}

GReturn GW::MATH::CreateGMatrix(GMatrix** _outMatrix)
{
	if (_outMatrix == nullptr)
	{
		return INVALID_ARGUMENT;
	}
	GMatirxCpp* mat = new GMatirxCpp();

	if (mat == nullptr)
	{
		return FAILURE;
	}

	(*_outMatrix) = mat;

	return SUCCESS;
}

