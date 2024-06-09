import RayTracer;
#include "gtest/gtest.h"

namespace RayTracer
{
	TEST(IntersectionTest, PrecomputeState)
	{
		Ray ray{Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1)};
		Sphere sphere{};
		Shape::Intersection intersection{4, &sphere};
		Shape::Computation computation = intersection.PrepareComputations(ray);
		ASSERT_EQ(computation.Object, intersection.Object);
		ASSERT_EQ(computation.Hit, Tuple::Point(0, 0, -1));
		ASSERT_EQ(computation.EyeVector, Tuple::Vector(0, 0, -1));
		ASSERT_EQ(computation.Normal, Tuple::Vector(0, 0, -1));
	}

	TEST(IntersectionTest, IntersectionOutside)
	{
		Ray ray{Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1)};
		Sphere sphere{};
		Shape::Intersection intersection{4, &sphere};
		Shape::Computation computation = intersection.PrepareComputations(ray);
		ASSERT_EQ(computation.Inside, false);
	}

	TEST(IntersectionTest, IntersectionInside)
	{
		Ray ray{Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1)};
		Sphere sphere{};
		Shape::Intersection intersection{1, &sphere};
		Shape::Computation computation = intersection.PrepareComputations(ray);
		ASSERT_EQ(computation.Inside, true);
		ASSERT_EQ(computation.Object, intersection.Object);
		ASSERT_EQ(computation.Hit, Tuple::Point(0, 0, 1));
		ASSERT_EQ(computation.EyeVector, Tuple::Vector(0, 0, -1));
		ASSERT_EQ(computation.Normal, Tuple::Vector(0, 0, -1));
	}

	TEST(IntersectionTest, SelfShadow)
	{
		Ray ray{Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1)};

		Sphere sphere{};
		sphere.Transform_ = Matrix<4>::IdentityMatrix().Translated(0, 0, 1);

		Shape::Intersection intersection{5, &sphere};

		Shape::Computation computation = intersection.PrepareComputations(ray);

		float expected = -Epsilon / 2.f;
		ASSERT_LT(computation.HitOffset.Z, expected);
		ASSERT_GT(computation.Hit.Z, computation.HitOffset.Z);
	}

	TEST(IntersectionTest, PrecomputeReflectionVector)
	{
		Plane plane;
		Ray ray{Tuple::Point(0, 1, -1), Tuple::Vector(0, -std::sqrtf(2) / 2.f, std::sqrtf(2) / 2)};
		Shape::Intersection intersection{std::sqrtf(2), &plane};
		Shape::Computation computation = intersection.PrepareComputations(ray);
		ASSERT_EQ(computation.Reflection, Tuple::Vector(0, std::sqrtf(2) / 2, std::sqrtf(2) / 2));
	}
}
