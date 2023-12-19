import RayTracer;
#include "gtest/gtest.h"

namespace RayTracer
{
	TEST(IntersectionTest, PrecomputeState)
	{
		Ray ray{ Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere{};
		Intersection intersection{ 4, &sphere };
		Computation computation = intersection.PrepareComputations(ray);
		ASSERT_EQ(computation.ObjectInstance, intersection.Object);
		ASSERT_EQ(computation.Hit, Tuple::Point(0, 0, -1));
		ASSERT_EQ(computation.EyeVector, Tuple::Vector(0, 0, -1));
		ASSERT_EQ(computation.Normal, Tuple::Vector(0, 0, -1));
	}

	TEST(IntersectionTest, IntersectionOutside)
	{
		Ray ray{ Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere{};
		Intersection intersection{ 4, &sphere };
		Computation computation = intersection.PrepareComputations(ray);
		ASSERT_EQ(computation.Inside, false);
	}

	TEST(IntersectionTest, IntersectionInside)
	{
		Ray ray{ Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1) };
		Sphere sphere{};
		Intersection intersection{ 1, &sphere };
		Computation computation = intersection.PrepareComputations(ray);
		ASSERT_EQ(computation.Inside, true);
		ASSERT_EQ(computation.ObjectInstance, intersection.Object);
		ASSERT_EQ(computation.Hit, Tuple::Point(0, 0, 1));
		ASSERT_EQ(computation.EyeVector, Tuple::Vector(0, 0, -1));
		ASSERT_EQ(computation.Normal, Tuple::Vector(0, 0, -1));
	}
}
