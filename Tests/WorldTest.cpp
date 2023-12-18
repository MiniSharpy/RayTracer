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
}
