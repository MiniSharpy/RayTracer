#include "../../Source/Maths/Tuple.h"
#include "gtest/gtest.h"

namespace RayTracer
{
	TEST(TupleTest, Point)
	{
		auto a = Tuple{ 4.3f, -4.2f, 3.1f, 1.0f };
		ASSERT_FLOAT_EQ(a.X, 4.3f);
		ASSERT_FLOAT_EQ(a.Y, -4.2f);
		ASSERT_FLOAT_EQ(a.Z, 3.1f);
		ASSERT_FLOAT_EQ(a.W, 1.0f);

		ASSERT_TRUE(a.IsAPoint());
		ASSERT_FALSE(a.IsAVector());
	}

	TEST(TupleTest, Vector)
	{
		auto a = Tuple{ 4.3f, -4.2f, 3.1f, 0.0f };
		ASSERT_FLOAT_EQ(a.X, 4.3f);
		ASSERT_FLOAT_EQ(a.Y, -4.2f);
		ASSERT_FLOAT_EQ(a.Z, 3.1f);
		ASSERT_FLOAT_EQ(a.W, 0.0f);

		ASSERT_FALSE(a.IsAPoint());
		ASSERT_TRUE(a.IsAVector());
	}

	TEST(TupleTest, PointMethod)
	{
		auto p = Tuple::Point(4, -4, 3);
		ASSERT_FLOAT_EQ(p.X, 4.f);
		ASSERT_FLOAT_EQ(p.Y, -4.f);
		ASSERT_FLOAT_EQ(p.Z, 3.f);
		ASSERT_FLOAT_EQ(p.W, 1.0f);
	}

	TEST(TupleTest, VectorMethod)
	{
		auto p = Tuple::Vector(4, -4, 3);
		ASSERT_FLOAT_EQ(p.X, 4.f);
		ASSERT_FLOAT_EQ(p.Y, -4.f);
		ASSERT_FLOAT_EQ(p.Z, 3.f);
		ASSERT_FLOAT_EQ(p.W, 0.0f);
	}
}
