// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"


#include "../../Interface/G_Math/GVector.h"

//The using statements for specifically what we are using.
using namespace GW;

class GVecoterCpp :public::GW::MATH::GVector
{
public:
	GVecoterCpp();
	~GVecoterCpp();

	//float vector

	GReturn AddVector(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) override;

	GReturn SubtractVector(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) override;

	GReturn Scale(GVECTORF _vector, float _scalar, GVECTORF& _outVector) override;

	GReturn Dot(GVECTORF _vector1, GVECTORF _vector2, float& _outValue) override;

	GReturn CrossVector2(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) override;
																					 
	GReturn CrossVector3(GVECTORF _vector1, GVECTORF _vector2, GVECTORF& _outVector) override;

	GReturn VectorXMatrix(GVECTORF _vector, GMATRIXF _matrix, GVECTORF& _outVector) override;

	GReturn TransformMatrix(GVECTORF _vector, GMATRIXF _matrix, GVECTORF& _outVector) override;

	GReturn Magnitude(GVECTORF _vector, float& _outMagnitude) override;
															  
	GReturn Normalize(GVECTORF _vector, GVECTORF& _outVector) override;

	//double vector

	GReturn AddVector(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) override;

	GReturn SubtractVector(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) override;

	GReturn Scale(GVECTORD _vector, double _scalar, GMATRIXD& _outMatrix) override;

	GReturn Dot(GVECTORD _vector1, GVECTORD _vector2, double& _outValue) override;

	GReturn CrossVec2(GVECTORD _vector1, GVECTORD _vector2, double& _outValue) override;

	GReturn CrossVec3(GVECTORD _vector1, GVECTORD _vector2, GVECTORD& _outVector) override;

	GReturn VectorXMatrix(GVECTORD _vector, GMATRIXD _matrix, GVECTORD& _outVector) override;

	GReturn TransformMatrix(GVECTORD _vector, GMATRIXD _matrix, GVECTORD& _outVector) override;

	GReturn Magnitude(GVECTORD _vector, float& _outMagnitude) override;

	GReturn Normalize(GVECTORD _vector, GVECTORD& _outVector) override;
};

GVecoterCpp::MyClass()
{
}

GVecoterCpp::~MyClass()
{
}

GReturn GVecoterCpp::AddVector(GVECTORF _vector1, GVECTORF _vector2, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::SubtractVector(GVECTORF _vector1, GVECTORF _vector2, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::Scale(GVECTORF _vector, float _scalar, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::Dot(GVECTORF _vector1, GVECTORF _vector2, float & _outValue)
{
	return FAILURE;
}

GReturn GVecoterCpp::CrossVector2(GVECTORF _vector1, GVECTORF _vector2, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::CrossVector3(GVECTORF _vector1, GVECTORF _vector2, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::VectorXMatrix(GVECTORF _vector, GMATRIXF _matrix, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::TransformMatrix(GVECTORF _vector, GMATRIXF _matrix, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::Magnitude(GVECTORF _vector, float & _outMagnitude)
{
	return FAILURE;
}

GReturn GVecoterCpp::Normalize(GVECTORF _vector, GVECTORF & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::AddVector(GVECTORD _vector1, GVECTORD _vector2, GVECTORD & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::SubtractVector(GVECTORD _vector1, GVECTORD _vector2, GVECTORD & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::Scale(GVECTORD _vector, double _scalar, GMATRIXD & _outMatrix)
{
	return FAILURE;
}

GReturn GVecoterCpp::Dot(GVECTORD _vector1, GVECTORD _vector2, double & _outValue)
{
	return FAILURE;
}

GReturn GVecoterCpp::CrossVec2(GVECTORD _vector1, GVECTORD _vector2, double & _outValue)
{
	return FAILURE;
}

GReturn GVecoterCpp::CrossVec3(GVECTORD _vector1, GVECTORD _vector2, GVECTORD & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::VectorXMatrix(GVECTORD _vector, GMATRIXD _matrix, GVECTORD & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::TransformMatrix(GVECTORD _vector, GMATRIXD _matrix, GVECTORD & _outVector)
{
	return FAILURE;
}

GReturn GVecoterCpp::Magnitude(GVECTORD _vector, float & _outMagnitude)
{
	return FAILURE;
}

GReturn GVecoterCpp::Normalize(GVECTORD _vector, GVECTORD & _outVector)
{
	return FAILURE;
}
