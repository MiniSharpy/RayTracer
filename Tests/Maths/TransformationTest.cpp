#include "gtest/gtest.h"
import RayTracer;

namespace RayTracer
{
	TEST(TransformationTest, DefaultOrientation)
	{
		Tuple from = Tuple::Point(0, 0, 0);
		Tuple to = Tuple::Point(0, 0, -1);
		Tuple up = Tuple::Vector(0, 1, 0);
		Matrix<4> transform = Matrix<4>::ViewTransform(from, to, up);
		ASSERT_EQ(transform, Matrix<4>::IdentityMatrix());
	}

	TEST(TransformationTest, LookingInPositiveZDirection)
	{
		Tuple from = Tuple::Point(0, 0, 0);
		Tuple to = Tuple::Point(0, 0, 1);
		Tuple up = Tuple::Vector(0, 1, 0);
		Matrix<4> transform = Matrix<4>::ViewTransform(from, to, up);
		ASSERT_EQ(transform, Matrix<4>::Scaling(-1, 1, -1));
	}

	TEST(TransformationTest, TranslateTheWorld)
	{
		Tuple from = Tuple::Point(0, 0, 8);
		Tuple to = Tuple::Point(0, 0, 0);
		Tuple up = Tuple::Vector(0, 1, 0);
		Matrix<4> transform = Matrix<4>::ViewTransform(from, to, up);
		Matrix<4> expected = Matrix<4>::Translation(0, 0, -8);
		ASSERT_EQ(transform, expected);
	}

	TEST(TransformationTest, ArbitraryView)
	{
		Tuple from = Tuple::Point(1, 3, 2);
		Tuple to = Tuple::Point(4, -2, 8);
		Tuple up = Tuple::Vector(1, 1, 0);
		Matrix<4> transform = Matrix<4>::ViewTransform(from, to, up);
		Matrix<4> expected
		{
			-0.50709, 0.50709, 0.67612, -2.36643,
			0.76772, 0.60609, 0.12122, -2.82843,
			-0.35857, 0.59761, -0.71714, 0.00000,
			0.00000, 0.00000, 0.00000, 1.00000
		};

		ASSERT_EQ(transform, expected);
	}
}
