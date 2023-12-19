import RayTracer;
#include "gtest/gtest.h"
#include <numbers>

namespace RayTracer
{
	TEST(SphereTest, SphereDefaultTransform)
	{
		Sphere sphere;
		ASSERT_EQ(sphere.Transform, Matrix<4>::IdentityMatrix());
	}

	TEST(SphereTest, SphereSetTransform)
	{
		Sphere sphere;
		Matrix<4> transform = Matrix<4>::Translation(2, 3, 4);
		sphere.Transform = transform; // TODO: Use a setter? Maybe if logic gets more complicated.
		ASSERT_EQ(sphere.Transform, transform);
	}

	TEST(SphereTest, SphereScaledIntersectRay)
	{
		Ray ray{ Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		sphere.Transform = Matrix<4>::Scaling(2, 2, 2);
		std::vector<Intersection> intersections = sphere.Intersect(ray);

		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, 3);
		ASSERT_FLOAT_EQ(intersections[1].Time, 7);
	}

	TEST(SphereTest, SphereTranslatedIntersectRay)
	{
		Ray ray{ Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		sphere.Transform = Matrix<4>::Translation(5, 0, 0);
		std::vector<Intersection> intersections = sphere.Intersect(ray);

		ASSERT_EQ(intersections.size(), 0);
	}

	TEST(SphereTest, SphereIntersectAtTwoPoints)
	{
		Ray ray = { Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, 4);
		ASSERT_FLOAT_EQ(intersections[1].Time, 6.0);
		ASSERT_EQ(sphere, *intersections[0].Object);
	}

	TEST(SphereTest, SphereIntersectAtTangent)
	{
		Ray ray = { Tuple::Point(0, 1, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, 5);
		ASSERT_FLOAT_EQ(intersections[1].Time, 5);
		ASSERT_EQ(sphere, *intersections[0].Object);
	}

	TEST(SphereTest, SphereIntersectMiss)
	{
		Ray ray = { Tuple::Point(0, 2, -5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 0);
	}

	TEST(SphereTest, SphereIntersectOriginatesInsideSphere)
	{
		Ray ray = { Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, -1);
		ASSERT_FLOAT_EQ(intersections[1].Time, 1);
		ASSERT_EQ(sphere, *intersections[0].Object);
	}

	TEST(SphereTest, SphereIntersectOriginatesInfrontOfSphere)
	{
		Ray ray = { Tuple::Point(0, 0, 5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, -6);
		ASSERT_FLOAT_EQ(intersections[1].Time, -4);
		ASSERT_EQ(sphere, *intersections[0].Object);
	}

	TEST(SphereTest, AggregatingIntersection)
	{
		Ray ray = { Tuple::Point(0, 0, 5), Tuple::Vector(0, 0, 1) };
		Sphere sphere;
		std::vector<Intersection> intersections = sphere.Intersect(ray);
		ASSERT_EQ(intersections.size(), 2);
		ASSERT_FLOAT_EQ(intersections[0].Time, -6);
		ASSERT_FLOAT_EQ(intersections[1].Time, -4);
	}

	TEST(SphereTest, HitWhenPositiveT)
	{
		Sphere sphere;
		Intersection intersectionA = Intersection{ 1, &sphere };
		Intersection intersectionB = Intersection{ 2, &sphere };
		std::vector<Intersection> intersections = { intersectionB, intersectionA };
		std::optional<Intersection> hit = Intersection::Hit(intersections);

		ASSERT_TRUE(hit);
		ASSERT_EQ(*hit, intersectionA);
	}

	TEST(SphereTest, HitWhenNegativeT)
	{
		Sphere sphere;
		Intersection intersectionA = Intersection{ -1, &sphere };
		Intersection intersectionB = Intersection{ 2, &sphere };
		std::vector<Intersection> intersections = { intersectionB, intersectionA };
		std::optional<Intersection> hit = Intersection::Hit(intersections);
		ASSERT_TRUE(hit);
		ASSERT_EQ(*hit, intersectionB);
	}

	TEST(SphereTest, HitWhenAllNegativeT)
	{
		Sphere sphere;
		Intersection intersectionA = Intersection{ -2, &sphere };
		Intersection intersectionB = Intersection{ -1, &sphere };
		std::vector<Intersection> intersections = { intersectionB, intersectionA };
		std::optional<Intersection> hit = Intersection::Hit(intersections);
		ASSERT_FALSE(hit);
	}

	TEST(SphereTest, HitIsLowestNonNegativeIntersection)
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

	TEST(SphereTest, NormalX)
	{
		Sphere sphere{};
		Tuple normal = sphere.Normal(Tuple::Point(1, 0, 0));
		ASSERT_EQ(normal, Tuple::Vector(1, 0, 0));
	}

	TEST(SphereTest, NormalY)
	{
		Sphere sphere{};
		Tuple normal = sphere.Normal(Tuple::Point(0, 1, 0));
		ASSERT_EQ(normal, Tuple::Vector(0, 1, 0));
	}

	TEST(SphereTest, NormalZ)
	{
		Sphere sphere{};
		Tuple normal = sphere.Normal(Tuple::Point(0, 0, 1));
		ASSERT_EQ(normal, Tuple::Vector(0, 0, 1));
	}

	TEST(SphereTest, NormalNonAxial)
	{
		Sphere sphere{};
		Tuple normal = sphere.Normal(Tuple::Point(sqrtf(3) / 3.f, sqrtf(3) / 3.f, sqrtf(3) / 3.f));
		ASSERT_EQ(normal, Tuple::Vector(sqrtf(3) / 3.f, sqrtf(3) / 3.f, sqrtf(3) / 3.f));
	}

	TEST(SphereTest, NormalIsNormalised)
	{
		Sphere sphere{};
		Tuple normal = sphere.Normal(Tuple::Point(sqrtf(3) / 3.f, sqrtf(3) / 3.f, sqrtf(3) / 3.f));
		ASSERT_EQ(normal, normal.Normalised());
	}

	TEST(SphereTest, NormalTranslatedSphere)
	{
		Sphere sphere{};
		sphere.Transform = Matrix<4>::Translation(0, 1, 0);
		Tuple normal = sphere.Normal(Tuple::Point(0, 1.70711, -0.70711));
		ASSERT_EQ(normal, Tuple::Vector(0, 0.70711, -0.70711));
	}

	TEST(SphereTest, NormalTransformedSphere)
	{
		Sphere sphere{ Matrix<4>::Scaling(1, 0.5, 1) * Matrix<4>::RotationZ(std::numbers::pi / 5) };
		Tuple normal = sphere.Normal(Tuple::Point(0, sqrtf(2) / 2, -sqrtf(2) / 2));
		ASSERT_EQ(normal, Tuple::Vector(0, 0.97014, -0.24254));
	}

	TEST(SphereTest, HasDefaultMaterial)
	{
		Sphere sphere{};
		Material defaultMaterial;
		ASSERT_EQ(sphere.MaterialInstance, defaultMaterial);
	}
}
