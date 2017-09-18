#include "../G_System/Common.h"


//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES.

using namespace GW;
using namespace MATH;

//Globals used for all test cases.
GMatrix* MatrixC;

GMATRIXF matrixTest_MatF1;
GMATRIXF matrixTest_MatF2;
GMATRIXF matrixTest_OutMatrixF;

GMATRIXD matrixTest_MatD1;
GMATRIXD matrixTest_MatD2;
GMATRIXD matrixTest_OutMatrixD;

GVECTORF matrixTest_VecF;
GVECTORF matrixTest_OutVectorF;

GVECTORD matrixTest_VecD;
GVECTORD matrixTest_OutVectorD;

GQUATERNIONF matrixTest_QuaF;
GQUATERNIOND matrixTest_QuaD;

float matrixTest_NumF = 0.5f;
double matrixTest_NumD = 0.4;



TEST_CASE("Create GMatrix.", "[CreateGMatrix]")
{
	//Fail cases
	CHECK(G_FAIL(CreateGMatrix(nullptr)));

	//Pass Cases
	REQUIRE(G_SUCCESS(CreateGMatrix(&MatrixC)));
}

TEST_CASE("Add two matrices.", "[AddMatrixF], [AddMatrixD]")
{

	//Fail cases
	SECTION("Float matrix addition.", "[AddMatrixF]")
	{
		CHECK(G_FAIL(MatrixC->AddMatrixF(matrixTest_MatF1, matrixTest_MatF2, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix addition.", "[AddMatrixD]")
	{
		CHECK(G_FAIL(MatrixC->AddMatrixD(matrixTest_MatD1, matrixTest_MatD2, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Subtract two matrices.", "[SubtractMatrixF], [SubtractMatrixD]")
{

	//Fail cases
	SECTION("Float matrix subtraction.", "[SubtractMatrixF]")
	{
		CHECK(G_FAIL(MatrixC->SubtractMatrixF(matrixTest_MatF1, matrixTest_MatF2, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix subtraction.", "[SubtractMatrixD]")
	{
		CHECK(G_FAIL(MatrixC->SubtractMatrixD(matrixTest_MatD1, matrixTest_MatD2, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Multiply a matrix by a matrix.", "[MultiplyMatrixF], [MultiplyMatrixD]")
{

	//Fail cases
	SECTION("Float matrix multiplication.", "[MultiplyMatrixF]")
	{
		CHECK(G_FAIL(MatrixC->MultiplyMatrixF(matrixTest_MatF1, matrixTest_MatF2, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix multiplication.", "[MultiplyMatrixD]")
	{
		CHECK(G_FAIL(MatrixC->MultiplyMatrixD(matrixTest_MatD1, matrixTest_MatD2, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Multiply a matrix by a vector.", "[MatrixXVectorF], [MatrixXVectorD]")
{

	//Fail cases
	SECTION("Float matrix multiplication.", "[MatrixXVectorF]")
	{
		CHECK(G_FAIL(MatrixC->MatrixXVectorF(matrixTest_MatF1, matrixTest_VecF, matrixTest_OutVectorF)));
	}
	SECTION("Double matrix multiplication.", "[MatrixXVectorD]")
	{
		CHECK(G_FAIL(MatrixC->MatrixXVectorD(matrixTest_MatD1, matrixTest_VecD, matrixTest_OutVectorD)));
	}

}

TEST_CASE("Convert a quaternion to a rotation matrix.", "[ConvertQuaternionF], [ConvertQuaternionD]")
{

	//Fail cases
	SECTION("Float matrix convert.", "[ConvertQuaternionF]")
	{
		CHECK(G_FAIL(MatrixC->ConvertQuaternionF(matrixTest_QuaF, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix Multiplication.", "[ConvertQuaternionD]")
	{
		CHECK(G_FAIL(MatrixC->ConvertQuaternionD(matrixTest_QuaD, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Multiply a matrix by a number.", "[MultiplyNumF], [MultiplyNumD]")
{

	//Fail cases
	SECTION("Float matrix multiplication.", "[MultiplyNumF]")
	{
		CHECK(G_FAIL(MatrixC->MultiplyNumF(matrixTest_MatF1, matrixTest_NumF, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix multiplication.", "[MultiplyNumD]")
	{
		CHECK(G_FAIL(MatrixC->MultiplyNumD(matrixTest_MatD1, matrixTest_NumD, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Calculate a determinant of a matrix.", "[DeterminantF], [DeterminantD]")
{

	//Fail cases
	SECTION("Float matrix determinant.", "[DeterminantF]")
	{
		CHECK(G_FAIL(MatrixC->DeterminantF(matrixTest_MatF1, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix determinant.", "[DeterminantD]")
	{
		CHECK(G_FAIL(MatrixC->DeterminantD(matrixTest_MatD1, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Transpose a matrix.", "[TransposeF], [TransposeD]")
{

	//Fail cases
	SECTION("Float matrix transpose.", "[TransposeF]")
	{
		CHECK(G_FAIL(MatrixC->TransposeF(matrixTest_MatF1, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix transpose.", "[TransposeD]")
	{
		CHECK(G_FAIL(MatrixC->TransposeD(matrixTest_MatD1, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Inverse a matrix.", "[InverseF], [InverseD]")
{

	//Fail cases
	SECTION("Float matrix inverse.", "[InverseF]")
	{
		CHECK(G_FAIL(MatrixC->InverseF(matrixTest_MatF1, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix inverse.", "[InverseD]")
	{
		CHECK(G_FAIL(MatrixC->InverseD(matrixTest_MatD1, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Set a matrix to an identity matrix.", "[IdentityF], [IdentityD]")
{

	//Fail cases
	SECTION("Float identity matrix.", "[IdentityF]")
	{
		CHECK(G_FAIL(MatrixC->IdentityF(matrixTest_OutMatrixF)));
	}
	SECTION("Double identity matrix.", "[IdentityD]")
	{
		CHECK(G_FAIL(MatrixC->IdentityD(matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Get a roatation matrix form a transform matrix.", "[GetRotationF], [GetRotationD]")
{

	//Fail cases
	SECTION("Float matrix.", "[GetRotationF]")
	{
		CHECK(G_FAIL(MatrixC->GetRotationF(matrixTest_MatF1, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix.", "[GetRotationD]")
	{
		CHECK(G_FAIL(MatrixC->GetRotationD(matrixTest_MatD1, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Get a translation matrix form a transform matrix.", "[GetTranslationF], [GetTranslationD]")
{

	//Fail cases
	SECTION("Float matrix.", "[GetTranslationF]")
	{
		CHECK(G_FAIL(MatrixC->GetTranslationF(matrixTest_MatF1, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix.", "[GetTranslationD]")
	{
		CHECK(G_FAIL(MatrixC->GetTranslationD(matrixTest_MatD1, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Get a scale matrix form a transform matrix.", "[GetScaleF], [GetScaleD]")
{

	//Fail cases
	SECTION("Float matrix.", "[GetScaleF]")
	{
		CHECK(G_FAIL(MatrixC->GetScaleF(matrixTest_MatF1, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix.", "[GetScaleD]")
	{
		CHECK(G_FAIL(MatrixC->GetScaleD(matrixTest_MatD1, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Rotate a specified matrix around the x-axis.", "[RotationXF], [RotationXD]")
{

	//Fail cases
	SECTION("Float matrix rotation.", "[RotationXF]")
	{
		CHECK(G_FAIL(MatrixC->RotationXF(matrixTest_MatF1, matrixTest_NumF, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix rotation.", "[RotationXD]")
	{
		CHECK(G_FAIL(MatrixC->RotationXD(matrixTest_MatD1, matrixTest_NumD, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Rotate a specified matrix around the y-axis.", "[RotationYF], [RotationYD]")
{

	//Fail cases
	SECTION("Float matrix rotation.", "[RotationYF]")
	{
		CHECK(G_FAIL(MatrixC->RotationYF(matrixTest_MatF1, matrixTest_NumF, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix rotation.", "[RotationYD]")
	{
		CHECK(G_FAIL(MatrixC->RotationYD(matrixTest_MatD1, matrixTest_NumD, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Rotate a specified matrix around the z-axis.", "[RotationZF], [RotationZD]")
{

	//Fail cases
	SECTION("Float matrix rotation.", "[RotationZF]")
	{
		CHECK(G_FAIL(MatrixC->RotationZF(matrixTest_MatF1, matrixTest_NumF, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix rotation.", "[RotationZD]")
	{
		CHECK(G_FAIL(MatrixC->RotationZD(matrixTest_MatD1, matrixTest_NumD, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Translate a specified matrix by the vector.", "[TranslatelocalF], [TranslatelocalD]")
{

	//Fail cases
	SECTION("Float matrix trasnlation.", "[TranslatelocalF]")
	{
		CHECK(G_FAIL(MatrixC->TranslatelocalF(matrixTest_MatF1, matrixTest_VecF, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix trasnlation.", "[TranslatelocalD]")
	{
		CHECK(G_FAIL(MatrixC->TranslatelocalD(matrixTest_MatD1, matrixTest_VecD, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Scale a specified matrix by the vector.", "[ScalingF], [ScalingD]")
{

	//Fail cases
	SECTION("Float matrix Scaling.", "[ScalingF]")
	{
		CHECK(G_FAIL(MatrixC->ScalingF(matrixTest_MatF1, matrixTest_VecF, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix Scaling.", "[ScalingD]")
	{
		CHECK(G_FAIL(MatrixC->ScalingD(matrixTest_MatD1, matrixTest_VecD, matrixTest_OutMatrixD)));
	}

}

TEST_CASE("Lerp between two matrices.", "[LerpF], [LerpD]")
{

	//Fail cases
	SECTION("Float matrix Scaling.", "[LerpF]")
	{
		CHECK(G_FAIL(MatrixC->LerpF(matrixTest_MatF1, matrixTest_MatF2, matrixTest_NumF, matrixTest_OutMatrixF)));
	}
	SECTION("Double matrix Scaling.", "[LerpD]")
	{
		CHECK(G_FAIL(MatrixC->LerpD(matrixTest_MatD1, matrixTest_MatD1, matrixTest_NumD, matrixTest_OutMatrixD)));
	}

	MatrixC->DecrementCount();
}

