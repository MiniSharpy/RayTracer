export module RayTracer:Ray;

import :Tuple;
import :Matrix;

namespace RayTracer
{
	export struct Ray
	{
		Tuple Origin;
		Tuple Direction;

		/// <returns>The position of the ray at the specified time.</returns>
		Tuple Position(float time) const
		{
			return Origin + Direction * time;
		}

		Ray Transformed(Matrix<4> matrix) const
		{
			return { matrix * Origin, matrix * Direction };
		}
	};
}