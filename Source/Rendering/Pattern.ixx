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
		// TODO: Depending on how this chapter plays out, methods might be better.
		// Or even using a standard structure like an array to store the colours.
		static Pattern Stripe(Tuple colourA, Tuple colourB) { return {colourA, colourB}; }

		static Tuple StripeAt(Pattern pattern, Tuple point)
		{
			// We need to cast to an integer so that we can check if odd.
			// But, we can't rely on integer truncating as it'll 
			if ((static_cast<int>(std::floor(point.X)) & 1) == 0) { return pattern.ColourA; }

			return pattern.ColourB;
		}

		Tuple ColourA;

		Tuple ColourB;

		Matrix<4> Transform;
	};
}
