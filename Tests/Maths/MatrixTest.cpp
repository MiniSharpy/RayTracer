#include "gtest/gtest.h"

import Matrix;
import Tuple;

namespace RayTracer
{
	TEST(MatrixTest, Constructon4x4)
	{
		Matrix<4> matrix
		{
			1, 2, 3 ,4,
		5.5, 6.5, 7.5, 8.5,
		9, 10, 11 ,12,
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

		Tuple tuple { 1, 2, 3, 1 };

		Tuple resultingTuple = matrix * tuple;

		Tuple expectedTuple = { 18, 24, 33, 1};

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
		Tuple tuple{ 1, 2, 3, 4 };

		ASSERT_EQ(Matrix<4>::IdentityMatrix() * tuple, tuple);
	}
}
