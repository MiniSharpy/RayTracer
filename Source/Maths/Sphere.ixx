module;
#include <vector>

export module Sphere;
import Ray;
import Tuple;

namespace RayTracer
{
	export struct Sphere
	{
		std::vector<float> Intersect(Ray& ray)
		{
			Tuple sphereToRay = ray.Origin - Tuple::Point(0, 0, 0); // The RHS is the centre of the sphere, assumed to be world origin here.
			auto a = Tuple::Dot(ray.Direction, ray.Direction); // Surely this is always 1?
			auto b = 2 * Tuple::Dot(ray.Direction, sphereToRay);
			auto c = Tuple::Dot(sphereToRay, sphereToRay) - 1; // Surely this always 0?
			float discriminant = b * b - 4 * a * c;

			if (discriminant < 0) { return {}; }

			return { (-b - sqrtf(discriminant)) / (2 * a), (- b + sqrtf(discriminant)) / (2 * a)};
		}
	};
}
