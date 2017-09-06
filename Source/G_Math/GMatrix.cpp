// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"


#include "../../Interface/G_Math/GMatrix.h"

//The using statements for specifically what we are using.
using namespace GW;

class GMatirxCpp :public::GW::MATH::GMatrix
{
public:
	GMatirxCpp();
	~GMatirxCpp();


	//float Matrix

	GReturn AddMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) override;

	GReturn SubtractMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) override;

	GReturn MultiplyMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF& _outMatrix) override;

	GReturn MatrixXVector(GMATRIXF _matrix, GVECTORF _vector, GVECTORF& _outVector) override;

	GReturn ConvertQuaternion(GQUATERNIONF _quaternion, GMATRIXF& _outMatrix) override;

	GReturn MultiplyNum(GMATRIXF _matrix, float _scalar, GMATRIXF& _outMatrix) override;

	GReturn Determinant(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn Transpose(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn Inverse(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn Identity(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn GetRotation(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn GetTranslation(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn GetScale(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn RotationX(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) override;

	GReturn RotationY(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) override;

	GReturn RotationZ(GMATRIXF _matrix, float _radian, GMATRIXF& _outMatrix) override;

	GReturn Translate(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatrix) override;

	GReturn  Scaling(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF& _outMatirx) override;



	//double Matrix

	GReturn AddMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) override;

	GReturn SubtractMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) override;

	GReturn MultiplyMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD& _outMatrix) override;

	GReturn MatrixXVector(GMATRIXD _matrix, GMATRIXD _vector, GMATRIXD& _outVector) override;

	GReturn ConvertQuaternion(GQUATERNIOND _quaternion, GMATRIXD& _outMatrix) override;

	GReturn MultiplyNum(GMATRIXD _matrix, double _scalar, GMATRIXD& _outMatrix) override;

	GReturn Determinant(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn Transpose(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn Inverse(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn Identity(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn GetRotation(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn GetTranslation(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn GetScale(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn RotationX(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) override;

	GReturn RotationY(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) override;

	GReturn RotationZ(GMATRIXD _matrix, double _radian, GMATRIXD& _outMatrix) override;

	GReturn Translate(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatrix) override;

	GReturn  Scaling(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD& _outMatirx) override;
private:

};

GMatirxCpp::GMatirxCpp()
{
}

GMatirxCpp::~GMatirxCpp()
{
}

GReturn GMatirxCpp::AddMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::SubtractMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MultiplyMatrix(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MatrixXVector(GMATRIXF _matrix, GVECTORF _vector, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GMatirxCpp::ConvertQuaternion(GQUATERNIONF _quaternion, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MultiplyNum(GMATRIXF _matrix, float _scalar, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Determinant(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Transpose(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Inverse(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Identity(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetRotation(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetTranslation(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetScale(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationX(GMATRIXF _matrix, float _radian, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationY(GMATRIXF _matrix, float _radian, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationZ(GMATRIXF _matrix, float _radian, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Translate(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Scaling(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF & _outMatirx)
{
	return FAILURE;
}

//double Matrix

GReturn GMatirxCpp::AddMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::SubtractMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MultiplyMatrix(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MatrixXVector(GMATRIXD _matrix, GMATRIXD _vector, GMATRIXD & _outVector)
{
	return FAILURE;
}

GReturn GMatirxCpp::ConvertQuaternion(GQUATERNIOND _quaternion, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MultiplyNum(GMATRIXD _matrix, double _scalar, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Determinant(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Transpose(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Inverse(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Identity(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetRotation(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetTranslation(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetScale(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationX(GMATRIXD _matrix, double _radian, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationY(GMATRIXD _matrix, double _radian, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationZ(GMATRIXD _matrix, double _radian, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Translate(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::Scaling(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD & _outMatirx)
{
	return FAILURE;
}
