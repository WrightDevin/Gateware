// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"
#include "../../Interface/G_Math/GMatrix.h"
#include "../Source/G_System/GUtility.h"

#include <atomic> //Thread safety

//The using statements for specifically what we are using.
using namespace GW;
using namespace MATH;

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

	GReturn MatrixXVectorF(GMATRIXF _matrix, GVECTORF _vector, GVECTORF& _outVector) override;

	GReturn ConvertQuaternionF(GQUATERNIONF _quaternion, GMATRIXF& _outMatrix) override;

	GReturn MultiplyNumF(GMATRIXF _matrix, float _scalar, GMATRIXF& _outMatrix) override;

	GReturn DeterminantF(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn TransposeF(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn InverseF(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn IdentityF(GMATRIXF& _outMatrix) override;

	GReturn GetRotationF(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn GetTranslationF(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

	GReturn GetScaleF(GMATRIXF _matrix, GMATRIXF& _outMatrix) override;

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

	GReturn MatrixXVectorD(GMATRIXD _matrix, GVECTORD _vector, GVECTORD& _outVector) override;

	GReturn ConvertQuaternionD(GQUATERNIOND _quaternion, GMATRIXD& _outMatrix) override;

	GReturn MultiplyNumD(GMATRIXD _matrix, double _scalar, GMATRIXD& _outMatrix) override;

	GReturn DeterminantD(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn TransposeD(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn InverseD(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn IdentityD(GMATRIXD& _outMatrix) override;

	GReturn GetRotationD(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn GetTranslationD(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

	GReturn GetScaleD(GMATRIXD _matrix, GMATRIXD& _outMatrix) override;

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
	return FAILURE;
}

GReturn GMatirxCpp::SubtractMatrixF(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MultiplyMatrixF(GMATRIXF _matrix1, GMATRIXF _matrix2, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MatrixXVectorF(GMATRIXF _matrix, GVECTORF _vector, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GMatirxCpp::ConvertQuaternionF(GQUATERNIONF _quaternion, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MultiplyNumF(GMATRIXF _matrix, float _scalar, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::DeterminantF(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::TransposeF(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::InverseF(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::IdentityF(GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetRotationF(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetTranslationF(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetScaleF(GMATRIXF _matrix, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationXF(GMATRIXF _matrix, float _radian, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationYF(GMATRIXF _matrix, float _radian, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationZF(GMATRIXF _matrix, float _radian, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::TranslatelocalF(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::ScalingF(GMATRIXF _matrix, GVECTORF _vector, GMATRIXF & _outMatirx)
{
	return FAILURE;
}

GReturn GMatirxCpp::LerpF(GMATRIXF _matrix1, GMATRIXF _matrix2, float _ratio, GMATRIXF & _outMatrix)
{
	return FAILURE;
}


//double Matrix

GReturn GMatirxCpp::AddMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::SubtractMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MultiplyMatrixD(GMATRIXD _matrix1, GMATRIXD _matrix2, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MatrixXVectorD(GMATRIXD _matrix, GVECTORD _vector, GVECTORD & _outVector)
{
	return FAILURE;
}

GReturn GMatirxCpp::ConvertQuaternionD(GQUATERNIOND _quaternion, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::MultiplyNumD(GMATRIXD _matrix, double _scalar, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::DeterminantD(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::TransposeD(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::InverseD(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::IdentityD(GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetRotationD(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetTranslationD(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::GetScaleD(GMATRIXD _matrix, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationXD(GMATRIXD _matrix, double _radian, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationYD(GMATRIXD _matrix, double _radian, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::RotationZD(GMATRIXD _matrix, double _radian, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::TranslatelocalD(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::ScalingD(GMATRIXD _matrix, GVECTORD _vector, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GMatirxCpp::LerpD(GMATRIXD _matrix1, GMATRIXD _matrix2, double _ratio, GMATRIXD & _outMatrix)
{
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

