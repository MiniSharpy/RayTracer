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
	};

	export class Pattern
	{
	public:
		virtual ~Pattern() = default;

		virtual Tuple ColourAt(Tuple point) = 0;

		Matrix<4> Transform;
	};

	export class Stripe : public Pattern
	{
	public:
		Tuple ColourA;

		Tuple ColourB;

		Stripe(Tuple colourA, Tuple colourB) : ColourA(colourA), ColourB(colourB) {}

		Tuple ColourAt(Tuple point) override
		{
			// We need to cast to an integer so that we can check if odd.
			// But, we can't rely on integer truncating as it'll 
			if ((static_cast<int>(std::floor(point.X)) & 1) == 0) { return ColourA; }

			return ColourB;
		}
	};
}
