#pragma once
#include <compare>

namespace RayTracer
{
	struct Tuple
	{
		static Tuple Point(float x, float y, float z);
		static Tuple Vector(float x, float y, float z);

		float X, Y, Z, W;
		auto operator<=>(const Tuple&) const = default;

		bool IsAPoint() const;
		bool IsAVector() const;
	};
}
