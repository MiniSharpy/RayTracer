import RayTracer;
#include "gtest/gtest.h"

namespace RayTracer
{
	TEST(PlaneTest, ConstantNormal)
	{
		Plane plane;
		Tuple n1 = plane.Normal(Tuple::Point(0, 0, 0));
		Tuple n2 = plane.Normal(Tuple::Point(10, 0, -10));
		Tuple n3 = plane.Normal(Tuple::Point(-5, 0, 150));

		ASSERT_EQ(n1, Tuple::Vector(0, 1,0));
		ASSERT_EQ(n2, Tuple::Vector(0, 1, 0));
		ASSERT_EQ(n3, Tuple::Vector(0, 1, 0));
	}

	TEST(PlaneTest, RayParralelToPlane)
	{
		Plane plane;
		Ray ray{Tuple::Point(0, 10, 0), Tuple::Vector(0, 0, 1)};
		std::vector<Shape::Intersection> intersections = plane.Intersect(ray);
		ASSERT_TRUE(intersections.empty());
	}

	TEST(PlaneTest, CoplanarRay)
	{
		Plane plane;
		Ray ray{Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1)};
		std::vector<Shape::Intersection> intersections = plane.Intersect(ray);
		ASSERT_TRUE(intersections.empty());
	}

	TEST(PlaneTest, IntersectAbove)
	{
		Plane plane;
		Ray ray{Tuple::Point(0, 1, 0), Tuple::Vector(0, -1, 0)};
		std::vector<Shape::Intersection> intersections = plane.Intersect(ray);
		ASSERT_EQ(intersections.size(), 1);
		ASSERT_EQ(intersections[0].Time, 1);
		ASSERT_EQ(*intersections[0].Object, plane);
	}

	TEST(PlaneTest, IntersectBelow)
	{
		Plane plane;
		Ray ray{Tuple::Point(0, -1, 0), Tuple::Vector(0, 1, 0)};
		std::vector<Shape::Intersection> intersections = plane.Intersect(ray);
		ASSERT_EQ(intersections.size(), 1);
		ASSERT_EQ(intersections[0].Time, 1);
		ASSERT_EQ(*intersections[0].Object, plane);
	}
}
