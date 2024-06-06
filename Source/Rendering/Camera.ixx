module;
#include<cmath>
export module RayTracer:Camera;
import :Matrix;
import :Ray;
import :Canvas;
import :World;

namespace RayTracer
{
	export class Camera
	{
	public:
		// TODO: Make private and require getters?
		int RenderWidth;

		int RenderHeight;

		float FieldOfView;

		Matrix<4> Transform;

		float HalfWidth;

		float HalfHeight;

		// The size of the pixels on the canvas in world-space units.
		float PixelSize;

		Camera(int width, int height, float fieldOfView, const Matrix<4>& transform) : RenderWidth(width),
			RenderHeight(height), FieldOfView(fieldOfView), Transform(transform)
		{
			float halfView = tanf(FieldOfView / 2.f);
			float aspectRatio = static_cast<float>(RenderWidth) / static_cast<float>(RenderHeight);

			if (aspectRatio >= 1)
			{
				HalfWidth = halfView;
				HalfHeight = halfView / aspectRatio;
			}
			else
			{
				HalfWidth = halfView * aspectRatio;
				HalfHeight = halfView;
			}

			PixelSize = (HalfWidth * 2) / RenderWidth;
		}

		Camera(int width, int height, float fieldOfView) : Camera(width, height, fieldOfView,
		                                                          Matrix<4>::IdentityMatrix()) {}

		Ray RayForPixel(int x, int y) const
		{
			// Offset from edge of canvas to pixel's centre.
			float xOffset = x + 0.5;
			float yOffset = y + 0.5;

			// Pixels in world space.
			float worldX = HalfWidth - (xOffset * PixelSize);
			float worldY = HalfHeight - (yOffset * PixelSize);

			// Compute the ray's origin and direction using the camera's transform, treating the canvas as
			// at Z=-1.
			Tuple pixel = Transform.Inverted() * Tuple::Point(worldX, worldY, -1);
			Tuple origin = Transform.Inverted() * Tuple::Point(0, 0, 0);
			Tuple direction = (pixel - origin).Normalised();

			return {origin, direction};
		}

		Canvas Render(const World& world) const
		{
			Canvas image(RenderWidth, RenderHeight);
			for (int x = 0; x < RenderWidth; ++x)
			{
				for (int y = 0; y < RenderHeight; ++y)
				{
					Ray ray = RayForPixel(x, y);
					Tuple colour = world.ColourAt(ray);
					image.SetPixel(x, y, colour);
				}
			}

			return image;
		}
	};
}
