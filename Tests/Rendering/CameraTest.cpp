
#include "gtest/gtest.h"
#include <numbers>
import RayTracer;

namespace RayTracer
{
	TEST(CameraTest, Construction)
	{
		Camera camera{ 160, 120, std::numbers::pi / 2.f };
		ASSERT_EQ(camera.RenderWidth, 160);
		ASSERT_EQ(camera.RenderHeight, 120);
		ASSERT_FLOAT_EQ(camera.FieldOfView, std::numbers::pi / 2.f);
		ASSERT_EQ(camera.Transform, Matrix<4>::IdentityMatrix());
	}

	TEST(CameraTest, HorizontalCanvasPixelSize)
	{
		Camera camera{ 200, 125, std::numbers::pi / 2.f };
		ASSERT_FLOAT_EQ(camera.PixelSize, 0.01);
	}

	TEST(CameraTest, VerticalCanvasPixelSize)
	{
		Camera camera{ 125, 200, std::numbers::pi / 2.f };
		ASSERT_FLOAT_EQ(camera.PixelSize, 0.01);
	}

	TEST(CameraTest, RayAtCentre)
	{
		Camera camera{ 201, 101, std::numbers::pi / 2.f };
		Ray ray = camera.RayForPixel(100, 50);
		ASSERT_EQ(ray.Origin, Tuple::Point(0, 0, 0));
		ASSERT_EQ(ray.Direction, Tuple::Vector(0, 0, -1));
	}

	TEST(CameraTest, RayAtCorner)
	{
		Camera camera{ 201, 101, std::numbers::pi / 2.f };
		Ray ray = camera.RayForPixel(0, 0);
		ASSERT_EQ(ray.Origin, Tuple::Point(0, 0, 0));
		ASSERT_EQ(ray.Direction, Tuple::Vector(0.66519, 0.33259, -0.66851));
	}

	TEST(CameraTest, RayWithTransformedCamera)
	{
		Camera camera{ 201, 101, std::numbers::pi / 2.f };
		camera.Transform.Translate(0, -2, 5).RotateY(std::numbers::pi / 4.f);
		Ray ray = camera.RayForPixel(100, 50);
		// Flipped when compared to camera's transform because the world has moved relative to the camera.
		ASSERT_EQ(ray.Origin, Tuple::Point(0, 2, -5));
		ASSERT_EQ(ray.Direction, Tuple::Vector(sqrtf(2) / 2.f, 0, -sqrtf(2) / 2.f));
	}

	TEST(CameraTest, Render)
	{
		World world = World::ExampleWorld();

		Camera camera{ 11, 11, std::numbers::pi / 2 };
		Tuple from = Tuple::Point(0, 0, -5);
		Tuple to = Tuple::Point(0, 0, 0);
		Tuple up = Tuple::Point(0, 1, 0);
		camera.Transform = Matrix<4>::ViewTransform(from, to, up);

		Canvas image = camera.Render(world);
		ASSERT_EQ(image.GetPixel(5, 5), Tuple::Colour(0.38066, 0.47583, 0.2855));
	}
}
