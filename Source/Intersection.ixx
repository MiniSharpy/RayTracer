module;
#include <optional>
#include <vector>

export module RayTracer:Intersection;
import :Object;

namespace RayTracer
{
	export struct Intersection
	{
		static std::optional<Intersection> Hit(const std::vector<Intersection>& intersections)
		{
			// TODO: Ideally intersections would be kept ordered, but I don't have enough
			// knowledge of how these objects will be used yet and so don't feel comfortable
			// implementing a comprehensive solution.
			// Might be worth storing a shared pointer of intersection as well so there's less passing by value.
			std::optional<Intersection> lowestNonNegativeIntersection = {};
			for (const Intersection& intersection : intersections)
			{
				if (intersection.Time < 0) { continue; }
				if (lowestNonNegativeIntersection && 
					(*lowestNonNegativeIntersection).Time > intersection.Time)
				{
					lowestNonNegativeIntersection = intersection;
				}
				else
				{
					lowestNonNegativeIntersection = intersection;
				}
			}
			return lowestNonNegativeIntersection;
		}

		float Time;
		Object* Object; // Maybe shared_ptr? Guess if the object doesn't exist any more that's less calculations really.

		bool operator==(const Intersection& rhs) const
		{
			return Time == rhs.Time && Object == rhs.Object;
		}
	};
}