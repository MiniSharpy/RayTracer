export module Ray;

import Tuple;

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
	};
}