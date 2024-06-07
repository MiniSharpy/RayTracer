module;
#include <cmath>
export module RayTracer:Pattern;

import :Tuple;
import :Matrix;

namespace RayTracer
{
	export namespace Colour
	{
		constexpr Tuple Black = Tuple::Colour(0, 0, 0);

		constexpr Tuple White = Tuple::Colour(1, 1, 1);

		constexpr Tuple Red = Tuple::Colour(1, 0, 0);

		constexpr Tuple Green = Tuple::Colour(0, 1, 0);

		constexpr Tuple Blue = Tuple::Colour(0, 0, 1);
	};

	export class Pattern
	{
	public:
		virtual ~Pattern() = default;

		virtual Tuple ColourAt(Tuple point) = 0;

		Matrix<4> Transform = Matrix<4>::IdentityMatrix();
	};

	export class StripePattern : public Pattern
	{
	public:
		Tuple ColourA;

		Tuple ColourB;

		StripePattern(Tuple colourA, Tuple colourB) : ColourA(colourA), ColourB(colourB) {}

		Tuple ColourAt(Tuple point) override
		{
			// We need to cast to an integer so that we can check if odd.
			// But, we can't rely on integer truncating as it'll 
			if ((static_cast<int>(std::floor(point.X)) & 1) == 0) { return ColourA; }

			return ColourB;
		}
	};

	export class GradientPattern : public Pattern
	{
	public:
		Tuple ColourA;

		Tuple ColourB;

		GradientPattern(Tuple colourA, Tuple colourB) : ColourA(colourA), ColourB(colourB) {}

		Tuple ColourAt(Tuple point) override
		{
			// Offset to get from ColourA to ColourB.
			Tuple distanceAB = ColourB - ColourA;

			// How far into the gradient the point is,
			// taking only the fractional part so that it the pattern effectively loops.
			float fraction = point.X - std::floor(point.X);

			// Offset from ColourA to the point,
			Tuple distanceAP = distanceAB * fraction;

			// Colour at the specified point.
			return ColourA + distanceAP;
		}
	};

	export class RingPattern : public Pattern
	{
	public:
		Tuple ColourA;

		Tuple ColourB;

		RingPattern(Tuple colourA, Tuple colourB) : ColourA(colourA), ColourB(colourB) {}

		Tuple ColourAt(Tuple point) override
		{
			if ((static_cast<int>(std::floor(std::sqrtf(std::pow(point.X, 2.f) + std::pow(point.Z, 2.f)))) & 1)
				== 0) { return ColourA; }
			return ColourB;
		}
	};

	export class CheckerPattern : public Pattern
	{
	public:
		Tuple ColourA;

		Tuple ColourB;

		CheckerPattern(Tuple colourA, Tuple colourB) : ColourA(colourA), ColourB(colourB) {}

		Tuple ColourAt(Tuple point) override
		{
			// We need to cast to an integer so that we can check if odd.
			// But, we can't rely on integer truncating as it'll 
			if ((static_cast<int>(std::floor(point.X)) +
				static_cast<int>(std::floor(point.Y)) +
				static_cast<int>(std::floor(point.Z))
				& 1) == 0) { return ColourA; }

			return ColourB;
		}
	};
}
