#include "../G_System/Common.h"


//THESE TEST CASES ARE SET UP IN A SPECIFIC ORDER. REORDERING TEST CASES COULD CAUSE
//CRASHES, FALSE FAILURES, or FALSE PASSES.

using namespace GW;
using namespace MATH;

//Globals used for all test cases.
GQuaternion* QuaternionC;


TEST_CASE("Create GQuaternion.", "[CreateGQuaternion]")
{
	//Fail cases
	CHECK(G_FAIL(CreateGQuaternion(nullptr)));

	//Pass cases
	REQUIRE(G_SUCCESS(CreateGQuaternion(&QuaternionC)));
}

TEST_CASE("Add two quaternions.", "[AddQuaternionF], [AddQuaternionD]")
{
	GQUATERNIONF qF1 = { 1.1f,2.2f,3.3f,4.4f };
	GQUATERNIONF qF2 = { 0.1f,0.2f,0.3f,0.4f };
	GQUATERNIONF resultF;

	GQUATERNIOND qD1 = { 1.1,2.2,3.3,4.4 };
	GQUATERNIOND qD2 = { 0.1,0.2,0.3,0.4 };
	GQUATERNIOND resultD;

	SECTION("Float quaternion addition.", "[AddQuaternionF]")
	{
		CHECK(G_SUCCESS(QuaternionC->AddQuaternionF(qF1, qF2, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, 1.2f));
		CHECK(G_COMPARISON_F(resultF.y, 2.4f));
		CHECK(G_COMPARISON_F(resultF.z, 3.6f));
		CHECK(G_COMPARISON_F(resultF.w, 4.8f));
	}
	SECTION("Double quaternion addition.", "[AddQuaternionD]")
	{
		CHECK(G_SUCCESS(QuaternionC->AddQuaternionD(qD1, qD2, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, 1.2));
		CHECK(G_COMPARISON_D(resultD.y, 2.4));
		CHECK(G_COMPARISON_D(resultD.z, 3.6L));
		CHECK(G_COMPARISON_D(resultD.w, 4.8));
	}

}

TEST_CASE("Subtract two quaternions.", "[SubtractQuaternionF], [SubtractQuaternionD]")
{
	GQUATERNIONF qF1 = { 1.1f,2.2f,3.3f,4.4f };
	GQUATERNIONF qF2 = { 0.1f,0.2f,0.3f,0.4f };
	GQUATERNIONF resultF;

	GQUATERNIOND qD1 = { 1.1,2.2,3.3,4.4 };
	GQUATERNIOND qD2 = { 0.1,0.2,0.3,0.4 };
	GQUATERNIOND resultD;
	SECTION("Float quaternion subtraction.", "[SubtractQuaternionF]")
	{
		CHECK(G_SUCCESS(QuaternionC->SubtractQuaternionF(qF1, qF2, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, 1.0f));
		CHECK(G_COMPARISON_F(resultF.y, 2.0f));
		CHECK(G_COMPARISON_F(resultF.z, 3.0f));
		CHECK(G_COMPARISON_F(resultF.w, 4.0f));
	}
	SECTION("Double quaternion subtraction.", "[SubtractQuaternionD]")
	{
		CHECK(G_SUCCESS(QuaternionC->SubtractQuaternionD(qD1, qD2, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, 1));
		CHECK(G_COMPARISON_D(resultD.y, 2));
		CHECK(G_COMPARISON_D(resultD.z, 3));
		CHECK(G_COMPARISON_D(resultD.w, 4));

	}

}

TEST_CASE("Multiply two quaternions.", "[MultiplyQuaternionF], [MultiplyQuaternionD]")
{
	GQUATERNIONF qF1 = { 1.1f,2.2f,3.3f,4.4f };
	GQUATERNIONF qF2 = { 0.1f,0.2f,0.3f,0.4f };
	GQUATERNIONF resultF;

	GQUATERNIOND qD1 = { 1.1,2.2,3.3,4.4 };
	GQUATERNIOND qD2 = { 0.1,0.2,0.3,0.4 };
	GQUATERNIOND resultD;

	SECTION("Float quaternion Multiplication.", "[MultiplyQuaternionF]")
	{
		CHECK(G_SUCCESS(QuaternionC->MultiplyQuaternionF(qF1, qF2, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, 0.88f));
		CHECK(G_COMPARISON_F(resultF.y, 1.76f));
		CHECK(G_COMPARISON_F(resultF.z, 2.64f));
		CHECK(G_COMPARISON_F(resultF.w, 0.22f));

	}
	SECTION("Double quaternion Multiplication.", "[MultiplyQuaternionD]")
	{
		CHECK(G_SUCCESS(QuaternionC->MultiplyQuaternionD(qD1, qD2, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, 0.88));
		CHECK(G_COMPARISON_D(resultD.y, 1.76));
		CHECK(G_COMPARISON_D(resultD.z, 2.64));
		CHECK(G_COMPARISON_D(resultD.w, 0.22));
	}
}

TEST_CASE("Scale two quaternions.", "[ScaleF], [ScaleD]")
{
	GQUATERNIONF qF1 = { 1.1f,2.2f,3.3f,4.4f };
	GQUATERNIONF resultF;

	GQUATERNIOND qD1 = { 1.1,2.2,3.3,4.4 };
	GQUATERNIOND resultD;
	SECTION("Float quaternion scaling.", "[ScaleF]")
	{
		CHECK(G_SUCCESS(QuaternionC->ScaleF(qF1, 0.1f, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, 0.11f));
		CHECK(G_COMPARISON_F(resultF.y, 0.22f));
		CHECK(G_COMPARISON_F(resultF.z, 0.33f));
		CHECK(G_COMPARISON_F(resultF.w, 0.44f));
	}
	SECTION("Double quaternion scaling.", "[ScaleD]")
	{
		CHECK(G_SUCCESS(QuaternionC->ScaleD(qD1, 0.1, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, 0.11));
		CHECK(G_COMPARISON_D(resultD.y, 0.22));
		CHECK(G_COMPARISON_D(resultD.z, 0.33));
		CHECK(G_COMPARISON_D(resultD.w, 0.44));
	}

}

TEST_CASE("Set a quaternion by a vector and a angle.", "[SetByVectorAngleF], [SetByVectorAngleD]")
{

	GVECTORF vF = { 1.0f,1.0f,1.0f,1.0f };
	GQUATERNIONF resultF;
	float radianF = (float)G_PI / 2.0f;
	GVECTORD vD = { 2.0,2.0,2.0,2.0 };
	double radianD = G_PI / 2.0;
	GQUATERNIOND resultD;

	SECTION("Float quaternion.", "[SetByVectorAngleF]")
	{
		CHECK(G_SUCCESS(QuaternionC->SetByVectorAngleF(vF, radianF, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, 1.0f * sqrtf(2) / 2.0f));
		CHECK(G_COMPARISON_F(resultF.y, 1.0f * sqrtf(2) / 2.0f));
		CHECK(G_COMPARISON_F(resultF.z, 1.0f * sqrtf(2) / 2.0f));
		CHECK(G_COMPARISON_F(resultF.w, sqrtf(2) / 2.0f));
	}
	SECTION("Double quaternion.", "[SetByVectorAngleD]")
	{
		CHECK(G_SUCCESS(QuaternionC->SetByVectorAngleD(vD, radianD, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, 2.0 * sqrt(2) / 2.0));
		CHECK(G_COMPARISON_D(resultD.y, 2.0 * sqrt(2) / 2.0));
		CHECK(G_COMPARISON_D(resultD.z, 2.0 * sqrt(2) / 2.0));
		CHECK(G_COMPARISON_D(resultD.w, sqrt(2) / 2.0));
	}

}

TEST_CASE("Set a quaternion by a matrix.", "[SetByMatrixF], [SetByMatrixD]")
{
	GMATRIXF mF = { 0,-1,0,0, 1,0,0,0, 0,0,1,0, 0,0,0,1 };
	GQUATERNIONF resultF;
	GMATRIXD mD = { 0,-1,0,0, 1,0,0,0, 0,0,1,0, 0,0,0,1 };
	GQUATERNIOND resultD;

	SECTION("Float quaternion.", "[SetByMatrixF]")
	{
		CHECK(G_SUCCESS(QuaternionC->SetByMatrixF(mF, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, 0.0f));
		CHECK(G_COMPARISON_F(resultF.y, 0.0f));
		CHECK(G_COMPARISON_F(resultF.z, 0.7071067f));
		CHECK(G_COMPARISON_F(resultF.w, 0.7071067f));
	}
	SECTION("Double quaternion.", "[SetByMatrixD]")
	{
		CHECK(G_SUCCESS(QuaternionC->SetByMatrixD(mD, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, 0.0));
		CHECK(G_COMPARISON_D(resultD.y, 0.0));
		CHECK(G_COMPARISON_D(resultD.z, 0.7071067811865475));
		CHECK(G_COMPARISON_D(resultD.w, 0.7071067811865475));

	}

}

TEST_CASE("Calculate the dot product of a quaternion.", "[DotF], [DotD]")
{
	GQUATERNIONF qF1 = { 1.1f,2.2f,3.3f,4.4f };
	GQUATERNIONF qF2 = { 0.1f,0.2f,0.3f,0.4f };
	float resultF;

	GQUATERNIOND qD1 = { 1.1,2.2,3.3,4.4 };
	GQUATERNIOND qD2 = { 0.1,0.2,0.3,0.4 };
	double resultD;

	SECTION("Float quaternion dot product.", "[DotF]")
	{
		CHECK(G_SUCCESS(QuaternionC->DotF(qF1, qF2, resultF)));
		CHECK(G_COMPARISON_F(resultF, 3.3f));
	}
	SECTION("Double quaternion dot product.", "[DotD]")
	{
		CHECK(G_SUCCESS(QuaternionC->DotD(qD1, qD2, resultD)));
		CHECK(G_COMPARISON_D(resultD, 3.3));
	}

}

TEST_CASE("Calculate the cross product of a quaternion.", "[CrossF], [CrossD]")
{
	GQUATERNIONF qF1 = { 5.2f, 3.4f, 2, 6 };
	GQUATERNIONF qF2 = { 0.2f, 1, 2.5f, 0.4f };
	GVECTORF resultF;

	GQUATERNIOND qD1 = { 5.2, 3.4, 2, 6 };
	GQUATERNIOND qD2 = { 0.2, 1, 2.5, 0.4 };
	GVECTORD resultD;

	SECTION("Float quaternion subtraction.", "[CrossF]")
	{
		CHECK(G_SUCCESS(QuaternionC->CrossF(qF1, qF2, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, 6.5f));
		CHECK(G_COMPARISON_F(resultF.y, -12.6f));
		CHECK(G_COMPARISON_F(resultF.z, 4.52f));
		CHECK(G_COMPARISON_F(resultF.w, 0.0f));

	}
	SECTION("Double quaternion subtraction.", "[CrossD]")
	{
		CHECK(G_SUCCESS(QuaternionC->CrossD(qD1, qD2, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, 6.5));
		CHECK(G_COMPARISON_D(resultD.y, -12.6));
		CHECK(G_COMPARISON_D(resultD.z, 4.52));
		CHECK(G_COMPARISON_D(resultD.w, 0.0));
	}

}


TEST_CASE("Set a quaternion to the conjugate of itself.", "[ConjugateF], [ConjugateD]")
{

	GQUATERNIONF qF1 = { 5.2f, 3.4f, 2, 6 };
	GQUATERNIONF resultF;

	GQUATERNIOND qD1 = { 5.2, 3.4, 2, 6 };
	GQUATERNIOND resultD;
	SECTION("Float quaternion.", "[ConjugateF]")
	{
		CHECK(G_SUCCESS(QuaternionC->ConjugateF(qF1, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, -5.2f));
		CHECK(G_COMPARISON_F(resultF.y, -3.4f));
		CHECK(G_COMPARISON_F(resultF.z, -2.0f));
		CHECK(G_COMPARISON_F(resultF.w, 6.0f));
	}
	SECTION("Double quaternion.", "[ConjugateD]")
	{
		CHECK(G_SUCCESS(QuaternionC->ConjugateD(qD1, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, -5.2));
		CHECK(G_COMPARISON_D(resultD.y, -3.4));
		CHECK(G_COMPARISON_D(resultD.z, -2.0));
		CHECK(G_COMPARISON_D(resultD.w, 6.0));
	}

}

TEST_CASE("Set a quaternion to the inverse of itself.", "[InverseF], [InverseD]")
{
	GQUATERNIONF qF0 = { 0.0f, 0.0f, 0.0f, 0.0f };
	GQUATERNIONF qF1 = { 10.0f, 8.0f, 6.0f, 0.0f };
	GQUATERNIONF resultF;

	GQUATERNIOND qD0 = { 0, 0, 0, 0 };
	GQUATERNIOND qD1 = { 10, 8, 6, 0 };
	GQUATERNIOND resultD;
	SECTION("Float quaternion.", "[InverseF]")
	{
		//Fail cases
		CHECK(G_FAIL(QuaternionC->InverseF(qF0, resultF)));

		//Pass cases
		CHECK(G_SUCCESS(QuaternionC->InverseF(qF1, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, -0.05f));
		CHECK(G_COMPARISON_F(resultF.y, -0.04f));
		CHECK(G_COMPARISON_F(resultF.z, -0.03f));
		CHECK(G_COMPARISON_F(resultF.w, 0.0f));
	}
	SECTION("Double quaternion.", "[InverseD]")
	{
		//Fail cases
		CHECK(G_FAIL(QuaternionC->InverseD(qD0, resultD)));

		//Pass cases
		CHECK(G_SUCCESS(QuaternionC->InverseD(qD1, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, -0.05));
		CHECK(G_COMPARISON_D(resultD.y, -0.04));
		CHECK(G_COMPARISON_D(resultD.z, -0.03));
		CHECK(G_COMPARISON_D(resultD.w, 0.0));
	}

}

TEST_CASE("Calcuate the magnitude of the quaternion.", "[MagnitudeF], [MagnitudeD]")
{
	GQUATERNIONF qF0 = { 0.0f, 0.0f, 0.0f, 0.0f };
	GQUATERNIONF qF1 = { 10.0f, 8.0f, 6.0f, 0.0f };
	float resultF;

	GQUATERNIOND qD0 = { 0, 0, 0, 0 };
	GQUATERNIOND qD1 = { 10, 8, 6, 0 };
	double resultD;
	SECTION("Float quaternion.", "[MagnitudeF]")
	{
		//Fail cases
		CHECK(G_FAIL(QuaternionC->MagnitudeF(qF0, resultF)));

		//Pass cases
		CHECK(G_SUCCESS(QuaternionC->MagnitudeF(qF1, resultF)));
		CHECK(G_COMPARISON_F(resultF, sqrtf(200)));
	}
	SECTION("Double quaternion.", "[MagnitudeD]")
	{
		//Fail cases
		CHECK(G_FAIL(QuaternionC->MagnitudeD(qD0, resultD)));

		//Pass cases
		CHECK(G_SUCCESS(QuaternionC->MagnitudeD(qD1, resultD)));
		CHECK(G_COMPARISON_D(resultD, sqrt(200)));
	}

}

TEST_CASE("Normalize the quaternion.", "[NormalizeF], [NormalizeD]")
{
	GQUATERNIONF qF0 = { 0.0f, 0.0f, 0.0f, 0.0f };
	GQUATERNIONF qF1 = { 10.0f, 8.0f, 6.0f, 0.0f };
	GQUATERNIONF resultF;

	GQUATERNIOND qD0 = { 0, 0, 0, 0 };
	GQUATERNIOND qD1 = { 10, 8, 6, 0 };
	GQUATERNIOND resultD;
	SECTION("Float quaternion.", "[NormalizeF]")
	{
		//Fail cases
		CHECK(G_FAIL(QuaternionC->NormalizeF(qF0, resultF)));

		//Pass cases
		CHECK(G_SUCCESS(QuaternionC->NormalizeF(qF1, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, 10.0f / sqrtf(200)));
		CHECK(G_COMPARISON_F(resultF.y,  8.0f / sqrtf(200)));
		CHECK(G_COMPARISON_F(resultF.z,  6.0f / sqrtf(200)));
		CHECK(G_COMPARISON_F(resultF.w,  0.0f / sqrtf(200)));
	}
	SECTION("Double quaternion.", "[NormalizeD]")
	{
		//Fail cases
		CHECK(G_FAIL(QuaternionC->NormalizeD(qD0, resultD)));

		//Pass cases
		CHECK(G_SUCCESS(QuaternionC->NormalizeD(qD1, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, 10 / sqrt(200)));
		CHECK(G_COMPARISON_D(resultD.y,  8 / sqrt(200)));
		CHECK(G_COMPARISON_D(resultD.z,  6 / sqrt(200)));
		CHECK(G_COMPARISON_D(resultD.w,  0));
	}

}

TEST_CASE("Set a identity quaternion.", "[IdentityF], [IdentityD]")
{
	GQUATERNIONF resultF;

	GQUATERNIOND resultD;
	SECTION("Float quaternion.", "[IdentityF]")
	{
		CHECK(G_SUCCESS(QuaternionC->IdentityF(resultF)));
		CHECK(G_COMPARISON_F(resultF.x, 0.0f));
		CHECK(G_COMPARISON_F(resultF.y, 0.0f));
		CHECK(G_COMPARISON_F(resultF.z, 0.0f));
		CHECK(G_COMPARISON_F(resultF.w, 1.0f));
	}
	SECTION("Double quaternion.", "[IdentityD]")
	{
		CHECK(G_SUCCESS(QuaternionC->IdentityD(resultD)));
		CHECK(G_COMPARISON_D(resultD.x, 0));
		CHECK(G_COMPARISON_D(resultD.y, 0));
		CHECK(G_COMPARISON_D(resultD.z, 0));
		CHECK(G_COMPARISON_D(resultD.w, 1));
	}

}

TEST_CASE("Calcuate the lerp of the quaternion.", "[LerpF], [LerpD]")
{
	GQUATERNIONF qF1 = { 0.0f, 0.0f, 0.0f, 0.0f };
	GQUATERNIONF qF2 = { 3, 5, 7, 9 };
	GQUATERNIONF resultF;

	GQUATERNIOND qD1 = { 0, 0, 0, 0 };
	GQUATERNIOND qD2 = { 3, 5, 7, 9 };
	GQUATERNIOND resultD;
	SECTION("Float quaternion.", "[LerpF]")
	{
		CHECK(G_SUCCESS(QuaternionC->LerpF(qF1, qF2, 0.5f, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, 1.5f));
		CHECK(G_COMPARISON_F(resultF.y, 2.5f));
		CHECK(G_COMPARISON_F(resultF.z, 3.5f));
		CHECK(G_COMPARISON_F(resultF.w, 4.5f));
	}
	SECTION("Double quaternion.", "[LerpD]")
	{
		CHECK(G_SUCCESS(QuaternionC->LerpD(qD1, qD2, 0.5, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, 1.5));
		CHECK(G_COMPARISON_D(resultD.y, 2.5));
		CHECK(G_COMPARISON_D(resultD.z, 3.5));
		CHECK(G_COMPARISON_D(resultD.w, 4.5));
	}

}

TEST_CASE("Calcuate the slerp of the quaternion.", "[SlerpF], [SlerpD]")
{
	GQUATERNIONF qF1 = { 0.7071067f, 0.0f, 0.0f, 0.7071067f};
	GQUATERNIONF qF2 = { 0.0f, 0.7071067f, 0.0f, 0.7071067f};
	GQUATERNIONF resultF;

	GQUATERNIOND qD1 = { 0.7071067811865475, 0, 0, 0.7071067811865475 };
	GQUATERNIOND qD2 = { 0, 0.7071067811865475, 0, 0.7071067811865475 };
	GQUATERNIOND resultD;

	SECTION("Float quaternion.", "[SlerpF]")
	{
		CHECK(G_SUCCESS(QuaternionC->SlerpF(qF1, qF2, 0.5f, resultF)));
		CHECK(G_COMPARISON_F(resultF.x, 0.4082482f));
		CHECK(G_COMPARISON_F(resultF.y, 0.4082482f));
		CHECK(G_COMPARISON_F(resultF.z, 0.0f));
		CHECK(G_COMPARISON_F(resultF.w, 0.8164965f));
	}
	SECTION("Double quaternion.", "[SlerpD]")
	{
		CHECK(G_SUCCESS(QuaternionC->SlerpD(qD1, qD2, 0.5, resultD)));
		CHECK(G_COMPARISON_D(resultD.x, 0.40824829046386296));
		CHECK(G_COMPARISON_D(resultD.y, 0.40824829046386296));
		CHECK(G_COMPARISON_D(resultD.z, 0.0));
		CHECK(G_COMPARISON_D(resultD.w, 0.8164965809277259));
	}

	QuaternionC->DecrementCount();
}