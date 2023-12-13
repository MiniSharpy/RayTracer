#include "gtest/gtest.h"

import Tuple;
import Ray;
import Sphere;

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

	TEST(RayTest, SphereIntersectAtTwoPoints)
	{
		Ray ray = { Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere{};
		std::vector<float> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0], 4);
		ASSERT_FLOAT_EQ(intersections[1], 6.0);
	}

	TEST(RayTest, SphereIntersectAtTangent)
	{
		Ray ray = { Tuple::Point(0, 1, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere{};
		std::vector<float> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0], 5);
		ASSERT_FLOAT_EQ(intersections[1], 5);
	}

	TEST(RayTest, SphereIntersectMiss)
	{
		Ray ray = { Tuple::Point(0, 2, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere{};
		std::vector<float> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 0);
	}

	TEST(RayTest, SphereIntersectOriginatesInsideSphere)
	{
		Ray ray = { Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1) };
		Sphere sphere{};
		std::vector<float> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0], -1);
		ASSERT_FLOAT_EQ(intersections[1], 1);
	}

	TEST(RayTest, SphereIntersectOriginatesInfrontOfSphere)
	{
		Ray ray = { Tuple::Point(0, 0, 5), Tuple::Vector(0, 0, 1) };
		Sphere sphere{};
		std::vector<float> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0], -6);
		ASSERT_FLOAT_EQ(intersections[1], -4);
	}
}