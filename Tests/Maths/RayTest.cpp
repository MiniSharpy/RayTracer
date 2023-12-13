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

	TEST(RayTest, SphereIntersectAtTwoPoints)
	{
		Ray ray = { Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, 4);
		ASSERT_FLOAT_EQ(intersections[1].Time, 6.0);
		ASSERT_EQ(sphere, *intersections[0].Object);
	}

	TEST(RayTest, SphereIntersectAtTangent)
	{
		Ray ray = { Tuple::Point(0, 1, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, 5);
		ASSERT_FLOAT_EQ(intersections[1].Time, 5);
		ASSERT_EQ(sphere, *intersections[0].Object);
	}

	TEST(RayTest, SphereIntersectMiss)
	{
		Ray ray = { Tuple::Point(0, 2, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 0);
	}

	TEST(RayTest, SphereIntersectOriginatesInsideSphere)
	{
		Ray ray = { Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, -1);
		ASSERT_FLOAT_EQ(intersections[1].Time, 1);
		ASSERT_EQ(sphere, *intersections[0].Object);
	}

	TEST(RayTest, SphereIntersectOriginatesInfrontOfSphere)
	{
		Ray ray = { Tuple::Point(0, 0, 5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, -6);
		ASSERT_FLOAT_EQ(intersections[1].Time, -4);
		ASSERT_EQ(sphere, *intersections[0].Object);
	}

	TEST(RayTest, AggregatingIntersection)
	{
		Ray ray = { Tuple::Point(0, 0, 5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, -6);
		ASSERT_FLOAT_EQ(intersections[1].Time, -4);
	}

	TEST(RayTest, HitWhenPositiveT)
	{
		Sphere sphere;
		Intersection intersectionA = Intersection{ 1, &sphere };
		Intersection intersectionB = Intersection{ 2, &sphere };
		std::vector<Intersection> intersections = { intersectionB, intersectionA };
		std::optional<Intersection> hit = Intersection::Hit(intersections);

		ASSERT_TRUE(hit);
		ASSERT_EQ(*hit, intersectionA);
	}

	TEST(RayTest, HitWhenNegativeT)
	{
		Sphere sphere;
		Intersection intersectionA = Intersection{ -1, &sphere };
		Intersection intersectionB = Intersection{ 2, &sphere };
		std::vector<Intersection> intersections = { intersectionB, intersectionA };
		std::optional<Intersection> hit = Intersection::Hit(intersections);
		ASSERT_TRUE(hit);
		ASSERT_EQ(*hit, intersectionB);
	}

	TEST(RayTest, HitWhenAllNegativeT)
	{
		Sphere sphere;
		Intersection intersectionA = Intersection{ -2, &sphere };
		Intersection intersectionB = Intersection{ -1, &sphere };
		std::vector<Intersection> intersections = { intersectionB, intersectionA };
		std::optional<Intersection> hit = Intersection::Hit(intersections);
		ASSERT_FALSE(hit);
	}

	TEST(RayTest, HitIsLowestNonNegativeIntersection)
	{
		Sphere sphere{};
		Intersection intersectionA = Intersection{ 5, &sphere };
		Intersection intersectionB = Intersection{ 7, &sphere };
		Intersection intersectionC = Intersection{ -3, &sphere };
		Intersection intersectionD = Intersection{ 2, &sphere };

		std::vector<Intersection> intersections = { intersectionA, intersectionB, intersectionC, intersectionD };
		std::optional<Intersection> hit = Intersection::Hit(intersections);
		ASSERT_TRUE(hit);
		ASSERT_EQ(*hit, intersectionD);
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

	TEST(RayTest, SphereDefaultTransform)
	{
		Sphere sphere;
		ASSERT_EQ(sphere.Transform, Matrix<4>::IdentityMatrix());
	}

	TEST(RayTest, SphereSetTransform)
	{
		Sphere sphere;
		Matrix<4> transform = Matrix<4>::Translation(2, 3, 4);
		sphere.Transform = transform; // TODO: Use a setter? Maybe if logic gets more complicated.
		ASSERT_EQ(sphere.Transform, transform);
	}

	TEST(RayTest, SphereScaledIntersectRay)
	{
		Ray ray{ Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		sphere.Transform = Matrix<4>::Scaling(2, 2, 2);
		std::vector<Intersection> intersections = sphere.Intersect(ray);

		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, 3);
		ASSERT_FLOAT_EQ(intersections[1].Time, 7);
	}

	TEST(RayTest, SphereTranslatedIntersectRay)
	{
		Ray ray{ Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		sphere.Transform = Matrix<4>::Translation(5, 0, 0);
		std::vector<Intersection> intersections = sphere.Intersect(ray);

		ASSERT_EQ(intersections.size(), 0);
	}
}