module;
#include <cmath>

export module RayTracer:Plane;
import :Ray;
import :Tuple;
import :Shape;

namespace RayTracer
{
	export class Plane : public Shape
	{
	public:
		using Shape::Shape;

		std::vector<Intersection> IntersectLocal(const Ray& ray) override
		{
			// In object space, the plane is on the XZ plane meaning that if there's no Y value the ray's parallel
			// to the plane and thus always misses.
			if (std::abs(ray.Direction.Y) < Epsilon) { return {}; }

			float t = -ray.Origin.Y / ray.Direction.Y;

			return {{t, this}};
		}

	protected:
		Tuple NormalLocal(const Tuple& objectSpacePoint) const override { return Tuple::Vector(0, 1, 0); }
	};
}
