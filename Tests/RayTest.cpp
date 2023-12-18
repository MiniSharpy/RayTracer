#include "gtest/gtest.h"
#include <optional>

import RayTracer;

namespace RayTracer
{
	TEST(RayTest, RayConstruction)
	{
		Ray ray = { Tuple::Point(2, 3, 4), Tuple::Vector(1, 0, 0) };
		ASSERT_EQ(ray.Origin, Tuple::Point(2, 3, 4));
		ASSERT_EQ(ray.Direction, Tuple::Vector(1, 0, 0));
	}

	TEST(RayTest, ComputePointFromDistance)
	{
		Ray ray = { Tuple::Point(2, 3, 4), Tuple::Vector(1, 0, 0) };
		ASSERT_EQ(ray.Position(0), Tuple::Point(2, 3, 4));
		ASSERT_EQ(ray.Position(1), Tuple::Point(3, 3, 4));
		ASSERT_EQ(ray.Position(-1), Tuple::Point(1, 3, 4));
		ASSERT_EQ(ray.Position(2.5), Tuple::Point(4.5, 3, 4));
	}

	TEST(RayTest, RayTranslation)
	{
		Ray ray = { Tuple::Point(1, 2, 3), Tuple::Vector(0, 1, 0) };
		Matrix<4> transform = Matrix<4>::Translation(3, 4, 5);
		Ray transformedRay = ray.Transformed(transform);
		ASSERT_EQ(transformedRay.Origin, Tuple::Point(4, 6, 8));
		ASSERT_EQ(transformedRay.Direction, Tuple::Vector(0, 1, 0));
	}

	TEST(RayTest, RayScaling)
	{
		Ray ray = { Tuple::Point(1, 2, 3), Tuple::Vector(0, 1, 0) };
		Matrix<4> transform = Matrix<4>::Scaling(2, 3, 4);
		Ray transformedRay = ray.Transformed(transform);
		ASSERT_EQ(transformedRay.Origin, Tuple::Point(2, 6, 12));
		ASSERT_EQ(transformedRay.Direction, Tuple::Vector(0, 3, 0));
	}
}