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

		Tuple tuple{ 1, 2, 3, 1 };

		Tuple resultingTuple = matrix * tuple;

		Tuple expectedTuple = { 18, 24, 33, 1 };

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
		Matrix<3> matrixA =
		{
			3, 5, 0,
			2, -1, -7,
			6, -1, 5
		};

		ASSERT_FLOAT_EQ(matrixA.Minor(0, 0), -12);
		ASSERT_FLOAT_EQ(matrixA.Cofactor(0, 0), -12);
		ASSERT_FLOAT_EQ(matrixA.Minor(1, 0), 25);
		ASSERT_FLOAT_EQ(matrixA.Cofactor(1, 0), -25);
	}
}
