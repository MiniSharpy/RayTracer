import RayTracer;
#include "gtest/gtest.h"

namespace RayTracer
{
	TEST(MaterialTest, DefaultMaterial)
	{
		Material material;
		ASSERT_EQ(material.Colour, Tuple::Colour(1, 1, 1));
		ASSERT_FLOAT_EQ(material.Ambient, 0.1f);
		ASSERT_FLOAT_EQ(material.Diffuse, 0.9f);
		ASSERT_FLOAT_EQ(material.Specular, 0.9f);
		ASSERT_FLOAT_EQ(material.Shininess, 200.0f);
	}

	TEST(MaterialTest, ViewerAt0Degrees)
	{
		Material material;
		Tuple pointIlluminated = Tuple::Point(0, 0, 0);
		Tuple viewVector = Tuple::Vector(0, 0, -1);
		Tuple normal = Tuple::Vector(0, 0, -1);
		PointLight light
		{
			Tuple::Point(0, 0, -10),
			Tuple::Colour(1, 1, 1)
		};

		Tuple result = material.Lighting(light, pointIlluminated, viewVector, normal);
		// Ambient, diffuse, and specular should be at full strength.
		// E.G. Total intensity = 0.1 (the ambient value) + 0.9 (the diffuse value) +
		// 0.9 (the specular value).
		ASSERT_EQ(result, Tuple::Colour(1.9, 1.9, 1.9));
	}

	TEST(MaterialTest, ViewerAt45Degrees)
	{
		Material material;
		Tuple pointIlluminated = Tuple::Point(0, 0, 0);
		Tuple viewVector = Tuple::Vector(0, sqrtf(2) / 2, -sqrtf(2) / 2);
		Tuple normal = Tuple::Vector(0, 0, -1);
		PointLight light
		{
			Tuple::Point(0, 0, -10),
			Tuple::Colour(1, 1, 1)
		};

		Tuple result = material.Lighting(light, pointIlluminated, viewVector, normal);
		// Ambient, diffuse should be at full strength, but the specular effectively 0.
		ASSERT_EQ(result, Tuple::Colour(1.0f, 1.0f, 1.0f));
	}

	TEST(MaterialTest, ViewerAt0DegreesLightAt45Degrees)
	{
		Material material;
		Tuple pointIlluminated = Tuple::Point(0, 0, 0);
		Tuple viewVector = Tuple::Vector(0, 0, -1);
		Tuple normal = Tuple::Vector(0, 0, -1);
		PointLight light
		{
			Tuple::Point(0, 10, -10),
			Tuple::Colour(1, 1, 1)
		};

		Tuple result = material.Lighting(light, pointIlluminated, viewVector, normal);
		// Ambient at full. Diffuse component falls off, specular effectively 0. 
		ASSERT_EQ(result, Tuple::Colour(0.7364, 0.7364, 0.7364));
	}

	TEST(MaterialTest, ViewerAtLightReflection)
	{
		Material material;
		Tuple pointIlluminated = Tuple::Point(0, 0, 0);
		Tuple viewVector = Tuple::Vector(0, -sqrtf(2) / 2.f, -sqrtf(2) / 2.f);
		Tuple normal = Tuple::Vector(0, 0, -1);
		PointLight light
		{
			Tuple::Point(0, 10, -10),
			Tuple::Colour(1, 1, 1)
		};

		Tuple result = material.Lighting(light, pointIlluminated, viewVector, normal);
		// Specular at fall strength, ambient at full, and diffuse falls off.
		ASSERT_EQ(result, Tuple::Colour(1.6364, 1.6364, 1.6364));
	}

	TEST(MaterialTest, LightBehindSurface)
	{
		Material material;
		Tuple pointIlluminated = Tuple::Point(0, 0, 0);
		Tuple viewVector = Tuple::Vector(0, 0, -1);
		Tuple normal = Tuple::Vector(0, 0, -1);
		PointLight light
		{
			Tuple::Point(0, 0, 10),
			Tuple::Colour(1, 1, 1)
		};

		Tuple result = material.Lighting(light, pointIlluminated, viewVector, normal);
		// Only the ambient has an effect when the light source is unavailable.
		ASSERT_EQ(result, Tuple::Colour(0.1, 0.1, 0.1));
	}

	TEST(MaterialTest, SurfaceInShadow)
	{
		Material material;
		Tuple pointIlluminated = Tuple::Point(0, 0, 0);
		Tuple viewVector = Tuple::Vector(0, 0, -1);
		Tuple normal = Tuple::Vector(0, 0, -1);
		PointLight light
		{
			Tuple::Point(0, 0, -10),
			Tuple::Colour(1, 1, 1)
		};

		Tuple result = material.Lighting(light, pointIlluminated, viewVector, normal, true);
		// Ambient, diffuse should be at full strength, but the specular effectively 0.
		ASSERT_EQ(result, Tuple::Colour(.1f, .1f, .1f));
	}

	TEST(MaterialTest, LightingWithPattern)
	{
		Material material;
		material.Pattern_ = std::make_shared<Stripe>(Colour::White, Colour::Black);
		material.Ambient = 1;
		material.Diffuse = 0;
		material.Specular = 0;

		Tuple viewVector = Tuple::Vector(0, 0, -1);
		Tuple normal = Tuple::Vector(0, 0, -1);
		PointLight light
		{
			Tuple::Point(0, 0, -10),
			Tuple::Colour(1, 1, 1)
		};

		Tuple point1 = Tuple::Point(0.9f, 0, 0);
		Tuple point2 = Tuple::Point(1.1f, 0, 0);

		Tuple colour1 = material.Lighting(light, point1, viewVector, normal, false,
		                                  material.Pattern_->ColourAt(point1));
		Tuple colour2 = material.Lighting(light, point2, viewVector, normal, false,
		                                  material.Pattern_->ColourAt(point2));

		ASSERT_EQ(colour1, Tuple::Colour(1, 1, 1));
		ASSERT_EQ(colour2, Tuple::Colour(0, 0, 0));
	}
}
