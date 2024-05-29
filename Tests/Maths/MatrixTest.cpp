#include "gtest/gtest.h"
#include <algorithm>
#include <numbers>

import RayTracer;

namespace RayTracer
{
	TEST(MatrixTest, Constructon4x4)
	{
		Matrix<4> matrix
		{
			1, 2, 3, 4,
			5.5, 6.5, 7.5, 8.5,
			9, 10, 11, 12,
			13.5, 14.5, 15.5, 16.5
		};

		ASSERT_FLOAT_EQ(matrix(0, 0), 1);
		ASSERT_FLOAT_EQ(matrix(0, 3), 4);
		ASSERT_FLOAT_EQ(matrix(1, 0), 5.5);
		ASSERT_FLOAT_EQ(matrix(1, 2), 7.5);
		ASSERT_FLOAT_EQ(matrix(2, 2), 11);
		ASSERT_FLOAT_EQ(matrix(3, 0), 13.5);
		ASSERT_FLOAT_EQ(matrix(3, 2), 15.5);
	}

	TEST(MatrixTest, Constructon3x3)
	{
		Matrix<3> matrix
		{
			-3, 5, 0,
			1, -2, -7,
			0, 1, 1
		};

		ASSERT_FLOAT_EQ(matrix(0, 0), -3);
		ASSERT_FLOAT_EQ(matrix(1, 1), -2);
		ASSERT_FLOAT_EQ(matrix(2, 2), 1);
	}

	TEST(MatrixTest, Constructon2x2)
	{
		Matrix<2> matrix
		{
			-3, 5,
			1, -2
		};

		ASSERT_FLOAT_EQ(matrix(0, 0), -3);
		ASSERT_FLOAT_EQ(matrix(0, 1), 5);
		ASSERT_FLOAT_EQ(matrix(1, 0), 1);
		ASSERT_FLOAT_EQ(matrix(1, 1), -2);
	}

	TEST(MatrixTest, EqualityIdentical)
	{
		Matrix<4> matrixA
		{
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		};

		Matrix<4> matrixB
		{
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		};

		ASSERT_EQ(matrixA, matrixB);
	}

	TEST(MatrixTest, EqualityDifferent)
	{
		Matrix<4> matrixA
		{
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		};

		Matrix<4> matrixB
		{
			2, 3, 4, 5,
			6, 7, 8, 9,
			8, 7, 6, 5,
			4, 3, 2, 1
		};

		ASSERT_NE(matrixA, matrixB);
	}

	TEST(MatrixTest, Multiplication)
	{
		Matrix<4> matrixA
		{
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		};

		Matrix<4> matrixB
		{
			-2, 1, 2, 3,
			3, 2, 1, -1,
			4, 3, 6, 5,
			1, 2, 7, 8
		};

		Matrix<4> resultingMatrix = matrixA * matrixB;

		Matrix<4> expectedMatrix =
		{
			20, 22, 50, 48,
			44, 54, 114, 108,
			40, 58, 110, 102,
			16, 26, 46, 42
		};

		ASSERT_EQ(resultingMatrix, expectedMatrix);
	}

	TEST(MatrixTest, MultiplicationByTuple)
	{
		Matrix<4> matrix
		{
			1, 2, 3, 4,
			2, 4, 4, 2,
			8, 6, 4, 1,
			0, 0, 0, 1
		};

		Tuple tuple{1, 2, 3, 1};

		Tuple resultingTuple = matrix * tuple;

		Tuple expectedTuple = {18, 24, 33, 1};

		ASSERT_EQ(resultingTuple, expectedTuple);
	}

	TEST(MatrixTest, MultiplicationByIdentityMatrix)
	{
		Matrix<4> matrix
		{
			1, 2, 3, 4,
			2, 4, 4, 2,
			8, 6, 4, 1,
			0, 0, 0, 1
		};

		auto test = Matrix<4>::IdentityMatrix();

		ASSERT_EQ(matrix * Matrix<4>::IdentityMatrix(), matrix);
	}

	TEST(MatrixTest, MultiplicationIdentityMatrixByTuple)
	{
		Tuple tuple{1, 2, 3, 4};

		ASSERT_EQ(Matrix<4>::IdentityMatrix() * tuple, tuple);
	}

	TEST(MatrixTest, Transposition)
	{
		Matrix<4> matrix
		{
			0, 9, 3, 0,
			9, 8, 0, 8,
			1, 8, 5, 3,
			0, 0, 5, 8
		};

		Matrix<4> expected =
		{
			0, 9, 1, 0,
			9, 8, 8, 0,
			3, 0, 5, 5,
			0, 8, 3, 8
		};

		ASSERT_EQ(matrix.Transposed(), expected);
	}

	TEST(MatrixTest, TranspositionIdentityMatrix)
	{
		ASSERT_EQ(Matrix<4>::IdentityMatrix().Transposed(), Matrix<4>::IdentityMatrix());
	}

	TEST(MatrixTest, Determinant2x2)
	{
		Matrix<2> matrix =
		{
			1, 5,
			-3, 2
		};

		ASSERT_FLOAT_EQ(matrix.Determinant(), 17);
	}

	TEST(MatrixTest, Determinant3x3)
	{
		Matrix<3> matrix =
		{
			1, 2, 6,
			-5, 8, -4,
			2, 6, 4
		};

		ASSERT_FLOAT_EQ(matrix.Cofactor(0, 0), 56);
		ASSERT_FLOAT_EQ(matrix.Cofactor(0, 1), 12);
		ASSERT_FLOAT_EQ(matrix.Cofactor(0, 2), -46);
		ASSERT_FLOAT_EQ(matrix.Determinant(), -196);
	}

	TEST(MatrixTest, Determinant4x4)
	{
		Matrix<4> matrix =
		{
			-2, -8, 3, 5,
			-3, 1, 7, 3,
			1, 2, -9, 6,
			-6, 7, 7, -9
		};

		ASSERT_FLOAT_EQ(matrix.Cofactor(0, 0), 690);
		ASSERT_FLOAT_EQ(matrix.Cofactor(0, 1), 447);
		ASSERT_FLOAT_EQ(matrix.Cofactor(0, 2), 210);
		ASSERT_FLOAT_EQ(matrix.Cofactor(0, 3), 51);
		ASSERT_FLOAT_EQ(matrix.Determinant(), -4071);
	}

	TEST(MatrixTest, Submatrix3x3)
	{
		Matrix<3> matrix =
		{
			1, 5, 0,
			-3, 2, 7,
			0, 6, -3
		};

		Matrix<2> expectedSubmatrix =
		{
			-3, 2,
			0, 6
		};

		ASSERT_EQ(matrix.Submatrix(0, 2), expectedSubmatrix);
	}

	TEST(MatrixTest, Submatrix4x4)
	{
		Matrix<4> matrix =
		{
			-6, 1, 1, 6,
			-8, 5, 8, 6,
			-1, 0, 8, 2,
			-7, 1, -1, 1
		};

		Matrix<3> expectedSubmatrix =
		{
			-6, 1, 6,
			-8, 8, 6,
			-7, -1, 1
		};

		ASSERT_EQ(matrix.Submatrix(2, 1), expectedSubmatrix);
	}

	TEST(MatrixTest, Minor3x3)
	{
		Matrix<3> matrixA =
		{
			3, 5, 0,
			2, -1, -7,
			6, -1, 5
		};

		Matrix<2> matrixB = matrixA.Submatrix(1, 0);

		ASSERT_FLOAT_EQ(matrixB.Determinant(), 25);
		ASSERT_FLOAT_EQ(matrixA.Minor(1, 0), 25);
	}

	TEST(MatrixTest, Cafactor3x3)
	{
		Matrix<3> matrix =
		{
			3, 5, 0,
			2, -1, -7,
			6, -1, 5
		};

		ASSERT_FLOAT_EQ(matrix.Minor(0, 0), -12);
		ASSERT_FLOAT_EQ(matrix.Cofactor(0, 0), -12);
		ASSERT_FLOAT_EQ(matrix.Minor(1, 0), 25);
		ASSERT_FLOAT_EQ(matrix.Cofactor(1, 0), -25);
	}

	TEST(MatrixTest, Invertibility)
	{
		Matrix<4> matrix =
		{
			6, 4, 4, 4,
			5, 5, 7, 6,
			4, -9, 3, -7,
			9, 1, 7, -6
		};

		ASSERT_FLOAT_EQ(matrix.Determinant(), -2120); // Is invertible.
	}

	TEST(MatrixTest, InvertibilityNonInvertible)
	{
		Matrix<4> matrix =
		{
			-4, 2, -2, -3,
			9, 6, 2, 6,
			0, -5, 1, -5,
			0, 0, 0, 0
		};

		ASSERT_FLOAT_EQ(matrix.Determinant(), 0); // Is not invertible.
	}

	TEST(MatrixTest, Invert)
	{
		Matrix<4> matrix =
		{
			-5, 2, 6, -8,
			1, -5, 1, 8,
			7, 7, -6, -7,
			1, -3, 7, 4
		};

		Matrix<4> inverted = matrix.Inverted();

		ASSERT_FLOAT_EQ(matrix.Determinant(), 532);
		ASSERT_FLOAT_EQ(matrix.Cofactor(2, 3), -160);
		ASSERT_FLOAT_EQ(inverted(3, 2), -160.f / 532.f);
		ASSERT_FLOAT_EQ(matrix.Cofactor(3, 2), 105);
		ASSERT_FLOAT_EQ(inverted(2, 3), 105.f / 532.f);

		Matrix<4> expected =
		{
			0.21805, 0.45113, 0.24060, -0.04511,
			-0.80827, -1.45677, -0.44361, 0.52068,
			-0.07895, -0.22368, -0.05263, 0.19737,
			-0.52256, -0.81391, -0.30075, 0.30639
		};

		ASSERT_EQ(inverted, expected);
	}

	TEST(MatrixTest, InvertSecond)
	{
		Matrix<4> matrix =
		{
			8, -5, 9, 2,
			7, 5, 6, 1,
			-6, 0, 9, 6,
			-3, 0, -9, -4
		};

		Matrix<4> expected =
		{
			-0.15385, -0.15385, -0.28205, -0.53846,
			-0.07692, 0.12308, 0.02564, 0.03077,
			0.35897, 0.35897, 0.43590, 0.92308,
			-0.69231, -0.69231, -0.76923, -1.92308
		};

		ASSERT_EQ(matrix.Inverted(), expected);
	}

	TEST(MatrixTest, InvertThird)
	{
		Matrix<4> matrix =
		{
			9, 3, 0, 9,
			-5, -2, -6, -3,
			-4, 9, 6, 4,
			-7, 6, 6, 2
		};

		Matrix<4> expected =
		{
			-0.04074, -0.07778, 0.14444, -0.22222,
			-0.07778, 0.03333, 0.36667, -0.33333,
			-0.02901, -0.14630, -0.10926, 0.12963,
			0.17778, 0.06667, -0.26667, 0.33333
		};

		ASSERT_EQ(matrix.Inverted(), expected);
	}

	TEST(MatrixTest, InvertMultiply)
	{
		Matrix<4> matrixA =
		{
			3, -9, 7, 3,
			3, -8, 2, -9,
			-4, 4, 4, 1,
			-6, 5, -1, 1
		};

		Matrix<4> matrixB =
		{
			8, 2, 2, 2,
			3, -1, 7, 0,
			7, 0, 5, 4,
			6, -2, 0, 5
		};

		Matrix<4> matrixAB = matrixA * matrixB;
		Matrix<4> matrixAT = matrixAB * matrixB.Inverted();

		ASSERT_EQ(matrixAB * matrixB.Inverted(), matrixA);
	}

	TEST(MatrixTest, TranslationMultiplication)
	{
		Matrix<4> transform = Matrix<4>::Translation(5, -3, 2);
		Tuple point = Tuple::Point(-3, 4, 5);

		ASSERT_EQ(transform * point, Tuple::Point(2, 1, 7));
	}

	TEST(MatrixTest, TranslationMultiplicationByInverse)
	{
		Matrix<4> transform = Matrix<4>::Translation(5, -3, 2);
		Matrix<4> inverse = transform.Inverted();
		Tuple point = Tuple::Point(-3, 4, 5);

		ASSERT_EQ(inverse * point, Tuple::Point(-8, 7, 3));
	}

	TEST(MatrixTest, TranslationDoesNotAffectVectors)
	{
		Matrix<4> transform = Matrix<4>::Translation(5, -3, 2);
		Tuple vector = Tuple::Vector(-3, 4, 5);

		ASSERT_EQ(transform * vector, vector);
	}

	TEST(MatrixTest, ScaleMultiplication)
	{
		Matrix<4> transform = Matrix<4>::Scaling(2, 3, 4);
		Tuple point = Tuple::Point(-4, 6, 8);

		ASSERT_EQ(transform * point, Tuple::Point(-8 , 18, 32));
	}

	TEST(MatrixTest, ScaleMultiplicationAffectsVectors)
	{
		Matrix<4> transform = Matrix<4>::Scaling(2, 3, 4);
		Tuple vector = Tuple::Vector(-4, 6, 8);

		ASSERT_EQ(transform * vector, Tuple::Vector(-8, 18, 32));
	}

	TEST(MatrixTest, ScaleMultiplicationByInverse)
	{
		Matrix<4> transform = Matrix<4>::Scaling(2, 3, 4);
		Matrix<4> inverse = transform.Inverted();
		Tuple vector = Tuple::Vector(-4, 6, 8);

		ASSERT_EQ(inverse * vector, Tuple::Vector(-2, 2, 2));
	}

	TEST(MatrixTest, ScaleReflection)
	{
		Matrix<4> transform = Matrix<4>::Scaling(-1, 1, 1);
		Tuple point = Tuple::Point(2, 3, 4);

		ASSERT_EQ(transform * point, Tuple::Point(-2, 3, 4));
	}

	TEST(MatrixTest, RotateX)
	{
		Matrix<4> half_quarter = Matrix<4>::RotationX(std::numbers::pi / 4);
		Matrix<4> full_quarter = Matrix<4>::RotationX(std::numbers::pi / 2);
		Tuple point = Tuple::Point(0, 1, 0);

		ASSERT_EQ(half_quarter * point, Tuple::Point(0, sqrtf(2)/2.f, sqrtf(2) / 2.f));
		ASSERT_EQ(full_quarter * point, Tuple::Point(0, 0, 1));
	}

	TEST(MatrixTest, RotateXInverse)
	{
		Tuple point = Tuple::Point(0, 1, 0);
		Matrix<4> half_quarter = Matrix<4>::RotationX(std::numbers::pi / 4);

		ASSERT_EQ(half_quarter.Inverted() * point, Tuple::Point(0, sqrtf(2) / 2.f, -sqrtf(2) / 2.f));
	}

	TEST(MatrixTest, RotateY)
	{
		Tuple point = Tuple::Point(0, 0, 1);
		Matrix<4> half_quarter = Matrix<4>::RotationY(std::numbers::pi / 4);
		Matrix<4> full_quarter = Matrix<4>::RotationY(std::numbers::pi / 2);

		ASSERT_EQ(half_quarter * point, Tuple::Point(sqrtf(2) / 2.f, 0, sqrtf(2) / 2.f));
		ASSERT_EQ(full_quarter * point, Tuple::Point(1, 0, 0));
	}

	TEST(MatrixTest, RotateZ)
	{
		Tuple point = Tuple::Point(0, 1, 0);
		Matrix<4> half_quarter = Matrix<4>::RotationZ(std::numbers::pi / 4);
		Matrix<4> full_quarter = Matrix<4>::RotationZ(std::numbers::pi / 2);

		ASSERT_EQ(half_quarter * point, Tuple::Point(-sqrtf(2) / 2.f, sqrtf(2) / 2.f, 0));
		ASSERT_EQ(full_quarter * point, Tuple::Point(-1, 0, 0));
	}

	TEST(MatrixTest, ShearXInProportionToY)
	{
		Matrix<4> transform = Matrix<4>::Shearing(1, 0, 0, 0, 0, 0);
		Tuple point = Tuple::Point(2, 3, 4);
		ASSERT_EQ(transform * point, Tuple::Point(5, 3, 4));
	}

	TEST(MatrixTest, ShearXInProportionToZ)
	{
		Matrix<4> transform = Matrix<4>::Shearing(0, 1, 0, 0, 0, 0);
		Tuple point = Tuple::Point(2, 3, 4);
		ASSERT_EQ(transform * point, Tuple::Point(6, 3, 4));
	}

	TEST(MatrixTest, ShearYInProportionToX)
	{
		Matrix<4> transform = Matrix<4>::Shearing(0, 0, 1, 0, 0, 0);
		Tuple point = Tuple::Point(2, 3, 4);
		ASSERT_EQ(transform * point, Tuple::Point(2, 5, 4));
	}

	TEST(MatrixTest, ShearYInProportionToZ)
	{
		Matrix<4> transform = Matrix<4>::Shearing(0, 0, 0, 1, 0, 0);
		Tuple point = Tuple::Point(2, 3, 4);
		ASSERT_EQ(transform * point, Tuple::Point(2, 7, 4));
	}

	TEST(MatrixTest, ShearZInProportionToX)
	{
		Matrix<4> transform = Matrix<4>::Shearing(0, 0, 0, 0, 1, 0);
		Tuple point = Tuple::Point(2, 3, 4);
		ASSERT_EQ(transform * point, Tuple::Point(2, 3, 6));
	}

	TEST(MatrixTest, ShearZInProportionToY)
	{
		Matrix<4> transform = Matrix<4>::Shearing(0, 0, 0, 0, 0, 1);
		Tuple point = Tuple::Point(2, 3, 4);
		ASSERT_EQ(transform * point, Tuple::Point(2, 3, 7));
	}

	TEST(MatrixTest, MultipleTransformations)
	{
		Tuple point = Tuple::Point(1, 0, 1);
		Matrix<4> rotation = Matrix<4>::RotationX(std::numbers::pi / 2);
		Matrix<4> scaling = Matrix<4>::Scaling(5, 5, 5);
		Matrix<4> translation = Matrix<4>::Translation(10, 5, 7);

		Tuple rotatedPoint = rotation * point;
		ASSERT_EQ(rotatedPoint, Tuple::Point(1, -1, 0));

		Tuple scaledPoint = scaling * rotatedPoint;
		ASSERT_EQ(scaledPoint, Tuple::Point(5, -5, 0));

		Tuple translatedPoint = translation * scaledPoint;
		ASSERT_EQ(translatedPoint, Tuple::Point(15, 0, 7));
	}

	TEST(MatrixTest, ChainedTransformations)
	{
		Tuple point = Tuple::Point(1, 0, 1);
		Matrix<4> rotation = Matrix<4>::RotationX(std::numbers::pi / 2);
		Matrix<4> scaling = Matrix<4>::Scaling(5, 5, 5);
		Matrix<4> translation = Matrix<4>::Translation(10, 5, 7);

		ASSERT_EQ(translation * scaling * rotation * point, Tuple::Point(15, 0, 7));
	}

	TEST(MatrixTest, MethodTransformations)
	{
		// There will be three moves, and a copy.
		Tuple point = Tuple::Point(1, 0, 1);
		Matrix<4> transform = Matrix<4>::IdentityMatrix(); // This value should change by the end.

		Matrix<4> rotation = Matrix<4>::RotationX(std::numbers::pi / 2);
		Matrix<4> scaling = Matrix<4>::Scaling(5, 5, 5);
		Matrix<4> translation = Matrix<4>::Translation(10, 5, 7);

		ASSERT_EQ(
			transform.RotateX(std::numbers::pi / 2)
			.Scale(5, 5, 5)
			.Translate(10, 5, 7) * point, Tuple::Point(15, 0, 7));
		ASSERT_EQ(transform, translation * scaling * rotation);
	}

	TEST(MatrixTest, MethodCopies)
	{
		// This will be four copies.
		Tuple point = Tuple::Point(1, 0, 1);

		Matrix<4> transform = Matrix<4>::IdentityMatrix(); // This value should be the same by the end.

		Matrix<4> rotation = Matrix<4>::RotationX(std::numbers::pi / 2);
		Matrix<4> scaling = Matrix<4>::Scaling(5, 5, 5);
		Matrix<4> translation = Matrix<4>::Translation(10, 5, 7);

		ASSERT_EQ(
			transform.RotatedX(std::numbers::pi / 2)
			.Scaled(5, 5, 5)
			.Translated(10, 5, 7) * point, Tuple::Point(15, 0, 7));
		ASSERT_NE(transform, translation * scaling * rotation);
	}
}
