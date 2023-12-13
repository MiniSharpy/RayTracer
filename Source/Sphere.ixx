module;
#include <vector>

export module RayTracer:Sphere;
import :Ray;
import :Tuple;
import :Intersection;

namespace RayTracer
{
	export class Sphere : public Object
	{
	public:
		Matrix<4> Transform;

		Sphere() : Transform(Matrix<4>::IdentityMatrix()) {}
		Sphere(const Matrix<4>& transform) : Transform(transform) {}

		std::vector<Intersection> Intersect(Ray& ray)
		{
			// Rather than contend with transforming spheres, making calculations difficult,
			// instead transform the ray by the inverse transform allowing the sphere to be treated as a
			// unit sphere with its origin as 0,0,0. World-Space vs Object-Space.
			const Ray transformedRay = ray.Transformed(Transform.Inverted());
			const Tuple sphereToRay = transformedRay.Origin - Tuple::Point(0, 0, 0); // The RHS is the centre of the sphere, assumed to be world origin.
			const float a = Tuple::Dot(transformedRay.Direction, transformedRay.Direction); // Surely this is always 1?
			const float b = 2 * Tuple::Dot(transformedRay.Direction, sphereToRay);
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
	};
}
