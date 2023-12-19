#include "gtest/gtest.h"

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
		PointLight light{ Tuple::Point(-10, 10, -10), Tuple::Colour(1, 1, 1) };

		Sphere& sphere0 = static_cast<Sphere&>(*world.Objects[0].get());
		Sphere& sphere1 = static_cast<Sphere&>(*world.Objects[1].get());

		Material material{ Tuple::Colour(0.8, 1.0, 0.6) };
		material.Diffuse = 0.7;
		material.Specular = 0.2;

		ASSERT_EQ(world.Light, light);
		ASSERT_EQ(sphere0.Transform, Matrix<4>::IdentityMatrix());
		ASSERT_EQ(sphere0.MaterialInstance, material);
		ASSERT_EQ(sphere1.Transform, Matrix<4>::Scaling(0.5, 0.5, 0.5));
	}

	TEST(WorldTest, WorldIntersect)
	{
		World world = World::ExampleWorld();
		Ray ray{ Tuple::Point(0,0,-5), Tuple::Vector(0,0,1) };
		std::vector<Intersection> intersections = world.Intersect(ray);

		ASSERT_EQ(intersections.size(), 4);
		ASSERT_EQ(intersections[0].Time, 4);
		ASSERT_EQ(intersections[1].Time, 4.5);
		ASSERT_EQ(intersections[2].Time, 5.5);
		ASSERT_EQ(intersections[3].Time, 6);
	}

	TEST(WorldTest, ShadeIntersection)
	{
		World world = World::ExampleWorld();
		world.Light = PointLight{ Tuple::Point(0, 0.25, 0), Tuple::Colour(1, 1, 1) };
		Ray ray{Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1)};
		auto& object = world.Objects[1];
		Intersection intersection{ 0.5, object.get() };
		auto computation = intersection.PrepareComputations(ray);
		Tuple resultingColour = world.ShadeIntersection(computation);
		ASSERT_EQ(resultingColour, Tuple::Colour(0.90498, 0.90498, 0.90498));
	}

	TEST(WorldTest, RayMiss)
	{
		World world = World::ExampleWorld();
		Ray ray{ Tuple::Point(0, 0, -5), Tuple::Vector(0, 1, 0)};
		ASSERT_EQ(world.ColourAt(ray), Tuple::Colour(0, 0, 0));
	}

	TEST(WorldTest, RayHit)
	{
		World world = World::ExampleWorld();
		Ray ray{ Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1) };
		ASSERT_EQ(world.ColourAt(ray), Tuple::Colour(0.38066, 0.47583, 0.2855));
	}

	TEST(WorldTest, IntersectionBehindRay)
	{
		World world = World::ExampleWorld();
		auto& outer = world.Objects[0];
		auto& inner = world.Objects[1];

		outer->MaterialInstance.Ambient = 1;
		inner->MaterialInstance.Ambient = 1;
		Ray ray{ Tuple::Point(0, 0, 0.75), Tuple::Vector(0, 0, -1) };
		Tuple colour = world.ColourAt(ray);
		ASSERT_EQ(colour, inner->MaterialInstance.Colour);
	}
}