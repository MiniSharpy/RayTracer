import RayTracer;
#include "gtest/gtest.h"

namespace RayTracer
{
	TEST(CanvasTest, CanvasConstruction)
	{
		auto canvas = Canvas(10, 20);
		ASSERT_EQ(canvas.GetWidth(), 10);
		ASSERT_EQ(canvas.GetHeight(), 20);
		auto expectedColour = Tuple::Colour(0, 0, 0);
		for (const Tuple& pixel : canvas.GetPixels())
		{
			ASSERT_EQ(pixel, expectedColour);
		}
	}

	TEST(CanvasTest, SetPixel)
	{
		auto canvas = Canvas(10, 20);
		auto red = Tuple::Colour( 1,0,0 );
		canvas.SetPixel(2, 3, red);
		ASSERT_EQ(canvas.GetPixel(2, 3), red);
	}
}
