module;
#include <cmath>

export module RayTracer:Plane;
import :Shape;

namespace RayTracer
{
	export class Plane : public Shape
	{
	public:
		std::vector<Intersection> Intersect(const Ray& ray) override
		{
			const Ray transformedRay = ray.Transformed(Transform_.Inverted());

			// In object space, the plane is on the XZ plane meaning that if there's no Y value (depth) and it's parallel
			// to the plane and thus always misses.
			if (std::abs(transformedRay.Direction.Y) < Epsilon) { return {}; }

			float t = -transformedRay.Origin.Y / transformedRay.Direction.Y;

			return {{t, this}};
		}

		Tuple Normal(const Tuple& worldSpacePoint) const override { return Tuple::Vector(0, 1, 0); }
	};
}
