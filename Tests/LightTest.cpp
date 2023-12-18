import RayTracer;
#include "gtest/gtest.h"

namespace RayTracer
{
	TEST(LightTest, PointLightConstruction)
	{
		Tuple position = Tuple::Point(0, 0, 0);
		Tuple colour = Tuple::Colour(1, 1, 1);
		PointLight light = { position, colour };
		ASSERT_EQ(light.Position, position);
		ASSERT_EQ(light.Intensity, colour);
	}
}