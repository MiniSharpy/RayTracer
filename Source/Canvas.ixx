module;
#include "vector"
#include "format"
#include <algorithm>
#include <fstream>

export module RayTracer:Canvas;
import :Tuple;

namespace RayTracer
{
	export class Canvas
	{
		// FIELDS
	private:
		int Width, Height;
		std::vector<Tuple> Pixels;

	public:
		// CONSTRUCTORS
		Canvas(int width, int height) : Width{ width }, Height{ height }, Pixels(width * height) {  }

		// METHODS
		// GETTERS
		int GetWidth() const { return Width; }
		int GetHeight() const { return Height; }
		const std::vector<Tuple>& GetPixels() const { return Pixels; }

		Tuple GetPixel(int x, int y) const
		{
			return Pixels[Width * y + x];
		}

		void SetPixel(int x, int y, const Tuple& colour)
		{
			Pixels[Width * y + x] = colour;
		}

		void WritePPM() const
		{
			std::ofstream image("render.ppm");
			image << std::format("P3\n{} {}\n255\n", Width, Height);

			for (const Tuple& pixel : Pixels)
			{
				int red = std::clamp<float>(round(pixel.X * 255), 0, 255);
				int green = std::clamp<float>(round(pixel.Y * 255), 0, 255);
				int blue = std::clamp<float>(round(pixel.Z * 255), 0, 255);
				image << std::format("{} {} {} ", red, green, blue);
			}
		}
	};
}
