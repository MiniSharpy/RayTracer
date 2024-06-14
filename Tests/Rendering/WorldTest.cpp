#include "gtest/gtest.h"
#include <numbers>

import RayTracer;

namespace RayTracer
{
	TEST(WorldTest, WorldConstruction)
	{
		World world;
		ASSERT_TRUE(world.Objects.empty());
		ASSERT_TRUE(!world.Light);
	}

	TEST(WorldTest, WorldConstructionExample)
	{
		World world = World::ExampleWorld();
		PointLight light{Tuple::Point(-10, 10, -10), Tuple::Colour(1, 1, 1)};

		Sphere& sphere0 = static_cast<Sphere&>(*world.Objects[0].get());
		Sphere& sphere1 = static_cast<Sphere&>(*world.Objects[1].get());

		Material material{Tuple::Colour(0.8, 1.0, 0.6)};
		material.Diffuse = 0.7;
		material.Specular = 0.2;

		ASSERT_EQ(world.Light, light);
		ASSERT_EQ(sphere0.Transform_, Matrix<4>::IdentityMatrix());
		ASSERT_EQ(sphere0.Material_, material);
		ASSERT_EQ(sphere1.Transform_, Matrix<4>::Scaling(0.5, 0.5, 0.5));
	}

	TEST(WorldTest, WorldIntersect)
	{
		World world = World::ExampleWorld();
		Ray ray{Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1)};
		std::vector<Shape::Intersection> intersections = world.Intersect(ray);

		ASSERT_EQ(intersections.size(), 4);
		ASSERT_EQ(intersections[0].Time, 4);
		ASSERT_EQ(intersections[1].Time, 4.5);
		ASSERT_EQ(intersections[2].Time, 5.5);
		ASSERT_EQ(intersections[3].Time, 6);
	}

	TEST(WorldTest, ShadeIntersection)
	{
		World world = World::ExampleWorld();
		world.Light = PointLight{Tuple::Point(0, 0.25, 0), Tuple::Colour(1, 1, 1)};
		Ray ray{Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1)};
		auto& object = world.Objects[1];
		Shape::Intersection intersection{0.5, object.get()};
		auto computation = intersection.PrepareComputations(ray);
		Tuple resultingColour = world.ShadeIntersection(computation);
		ASSERT_EQ(resultingColour, Tuple::Colour(0.1, 0.1, 0.1));
	}

	TEST(WorldTest, RayMiss)
	{
		World world = World::ExampleWorld();
		Ray ray{Tuple::Point(0, 0, -5), Tuple::Vector(0, 1, 0)};
		ASSERT_EQ(world.ColourAt(ray), Tuple::Colour(0, 0, 0));
	}

	TEST(WorldTest, RayHit)
	{
		World world = World::ExampleWorld();
		Ray ray{Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1)};
		ASSERT_EQ(world.ColourAt(ray), Tuple::Colour(0.38066, 0.47583, 0.2855));
	}

	TEST(WorldTest, IntersectionBehindRay)
	{
		World world = World::ExampleWorld();
		auto& outer = world.Objects[0];
		auto& inner = world.Objects[1];

		outer->Material_.Ambient = 1;
		inner->Material_.Ambient = 1;
		Ray ray{Tuple::Point(0, 0, 0.75), Tuple::Vector(0, 0, -1)};
		Tuple colour = world.ColourAt(ray);
		ASSERT_EQ(colour, inner->Material_.Colour);
	}

	TEST(WorldTest, PointNonOccluded)
	{
		World world = World::ExampleWorld();
		Tuple point = Tuple::Point(0, 10, 0);
		ASSERT_FALSE(world.IsPointInShadow(point));
	}

	TEST(WorldTest, LightBetweenPointAndObject)
	{
		World world = World::ExampleWorld();
		Tuple point = Tuple::Point(-20, 20, -20);
		ASSERT_FALSE(world.IsPointInShadow(point));
	}

	TEST(WorldTest, PointBetweenLightAndObject)
	{
		World world = World::ExampleWorld();
		Tuple point = Tuple::Point(-2, 2, -2);
		ASSERT_FALSE(world.IsPointInShadow(point));
	}

	TEST(WorldTest, PointOccluded)
	{
		World world = World::ExampleWorld();
		Tuple point = Tuple::Point(10, -10, 10);
		ASSERT_TRUE(world.IsPointInShadow(point));
	}

	TEST(WorldTest, ShadeIntersectionShadow)
	{
		World world = World::ExampleWorld();
		world.Light = PointLight{Tuple::Point(0, 0, -10), Tuple::Colour(1, 1, 1)};
		Sphere& sphere0 = static_cast<Sphere&>(*world.Objects[0].get());
		sphere0.Transform_ = Matrix<4>::IdentityMatrix().Translated(0, 0, 10);

		Sphere& sphere1 = static_cast<Sphere&>(*world.Objects[1].get());
		sphere1.Transform_ = Matrix<4>::IdentityMatrix();

		Ray ray{Tuple::Point(0, 0, 5), Tuple::Vector(0, 0, 1)};

		Shape::Intersection intersection{4, &sphere1};
		Shape::Computation computation = intersection.PrepareComputations(ray);

		Tuple colour = world.ShadeIntersection(computation);
		ASSERT_EQ(colour, Tuple::Colour(0.1f, 0.1f, 0.1f));
	}

	TEST(WorldTest, NonReflectiveMaterial)
	{
		World world = World::ExampleWorld();

		Ray ray{Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1)};

		Shape& shape = *world.Objects[1].get();
		shape.Material_.Ambient = 1;

		Shape::Intersection intersection{1, &shape};

		Shape::Computation computation = intersection.PrepareComputations(ray);

		Tuple colour = world.ReflectedColour(computation);

		ASSERT_EQ(colour, Tuple::Colour(0, 0, 0));
	}

	TEST(WorldTest, ReflectiveMaterial)
	{
		World world = World::ExampleWorld();
		world.Objects.emplace_back(std::make_shared<Plane>());

		Shape* plane = world.Objects[2].get();
		plane->Material_.Reflectiveness = 0.5f;
		plane->Transform_.Translate(0, -1, 0);

		Ray ray{Tuple::Point(0, 0, -3), Tuple::Vector(0, -std::sqrtf(2) / 2, std::sqrtf(2) / 2)};

		Shape::Intersection intersection = Shape::Intersection(std::sqrtf(2), plane);

		Shape::Computation computation = intersection.PrepareComputations(ray);

		Tuple colour = world.ReflectedColour(computation);

		ASSERT_EQ(colour, Tuple::Colour(0.190503, 0.238129, 0.142877));
	}

	TEST(WorldTest, ReflectiveMaterialShade)
	{
		World world = World::ExampleWorld();
		world.Objects.emplace_back(std::make_shared<Plane>());

		Shape* plane = world.Objects[2].get();
		plane->Material_.Reflectiveness = 0.5f;
		plane->Transform_.Translate(0, -1, 0);

		Ray ray{Tuple::Point(0, 0, -3), Tuple::Vector(0, -std::sqrtf(2) / 2, std::sqrtf(2) / 2)};

		Shape::Intersection intersection = Shape::Intersection(std::sqrtf(2), plane);

		Shape::Computation computation = intersection.PrepareComputations(ray);

		Tuple colour = world.ShadeIntersection(computation);

		ASSERT_EQ(colour, Tuple::Colour(0.876929, 0.924554, 0.829303));
	}

	TEST(WorldTest, ReflectionRecursion)
	{
		World world;
		world.Light = PointLight{Tuple::Point(0, 0, 0), Colour::White};
		world.Objects.emplace_back(std::make_shared<Plane>());
		world.Objects.emplace_back(std::make_shared<Plane>());

		Shape& lower = *world.Objects[0].get();
		lower.Material_.Reflectiveness = 1;
		lower.Transform_.Translate(0, -1, 0);

		// Why do I need to rotate this?
		Shape& upper = *world.Objects[1].get();
		upper.Material_.Reflectiveness = 1;
		upper.Transform_.RotateX(-std::numbers::pi).Translate(0, 1, 0);

		Ray ray{Tuple::Point(0, 0, 0), Tuple::Vector(0, 1, 0)};

		// This should overflow the stack if recursion isn't handled.
		Tuple colour = world.ColourAt(ray);
		SUCCEED();
	}

	TEST(WorldTest, ReflectionMaximumDepth)
	{
		World world = World::ExampleWorld();
		std::shared_ptr<Shape>& plane = world.Objects.emplace_back(std::make_shared<Plane>());
		plane->Material_.Reflectiveness = 0.5;
		plane->Transform_.Translate(0, -1, 0);

		Ray ray{Tuple::Point(0, 0, -3), Tuple::Vector(0, -std::sqrtf(2) / 2.f, std::sqrtf(2) / 2.f)};
		Shape::Intersection intersection{std::sqrtf(2), plane.get()};

		Shape::Computation computation = intersection.PrepareComputations(ray);
		Tuple colour = world.ReflectedColour(computation, 0);
		ASSERT_EQ(colour, Tuple::Colour(0, 0, 0));
	}
}
