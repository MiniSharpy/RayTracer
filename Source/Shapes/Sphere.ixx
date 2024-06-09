module;
#include <vector>

export module RayTracer:Sphere;
import :Ray;
import :Tuple;
import :Shape;

namespace RayTracer
{
	export class Sphere : public Shape
	{
	public:
		using Shape::Shape;

		std::vector<Intersection> IntersectLocal(const Ray& ray) override
		{
			const Tuple sphereToRay = ray.Origin - Tuple::Point(0, 0, 0);
			// The RHS is the centre of the sphere, assumed to be world origin.
			const float a = Tuple::Dot(ray.Direction, ray.Direction); // Surely this is always 1?
			const float b = 2 * Tuple::Dot(ray.Direction, sphereToRay);
			const float c = Tuple::Dot(sphereToRay, sphereToRay) - 1; // Surely this always 0?
			const float discriminant = b * b - 4 * a * c;

			if (discriminant < 0) { return {}; }

			// TODO: Return "in increasing order, to make it easier to determine which intersections
			// are significant later."
			return
			{
				{(-b - sqrtf(discriminant)) / (2 * a), this},
				{(-b + sqrtf(discriminant)) / (2 * a), this}
			};
		}

	protected:
		/// <summary>
		/// Calculates the normals at the point of contact on the sphere.
		/// </summary>
		Tuple NormalLocal(const Tuple& objectSpacePoint) const override
		{
			return objectSpacePoint - Tuple::Point(0, 0, 0);
		}
	};
}
