module;
#include <vector>

export module RayTracer:Sphere;
import :Ray;
import :Tuple;
import :Shape;
import :Material;

namespace RayTracer
{
	export class Sphere : public Shape
	{
	public:
		Sphere() : Shape(Matrix<4>::IdentityMatrix()) {}
		Sphere(const Matrix<4>& transform) : Shape(transform) {}
		Sphere(const Matrix<4>& transform, const Material& material) : Shape(transform, material) {}
		Sphere(const Material& material) : Shape(Matrix<4>::IdentityMatrix(), material) {}
		Sphere(const Sphere& object) : Shape(object) {}

		std::vector<Intersection> Intersect(const Ray& ray) override
		{
			// Rather than contend with transforming spheres, making calculations difficult,
			// instead transform the ray by the inverse transform allowing the sphere to be treated as a
			// unit sphere with its origin as 0,0,0. World-Space vs Object-Space.
			// TODO: What do the calculations look like if you're not dealing with a unit sphere at 0,0,0?
			const Ray transformedRay = ray.Transformed(Transform_.Inverted());
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

		/// <summary>
		/// Calculates the normals at the point of contact on the sphere.
		/// </summary>
		Tuple Normal(const Tuple& worldSpacePoint) const override
		{
			// To handle a transformed sphere, transform the world space point
			// to object space so that the sphere can be treated as though it
			// were a unit sphere. This gets the normal in object space.
			Tuple objectSpacePoint = Transform_.Inverted() * worldSpacePoint;
			Tuple objectNormal = objectSpacePoint - Tuple::Point(0, 0, 0);

			// To convert from object space to normal space multiply the
			// the object normal by the inverse transpose transform.
			// Multiplying just by the transform matrix would get something almost
			// right, but because the normals will no longer be perpendicular to
			// the surface it'll appear as though the image was transformed,
			// rather than the object.
			Tuple worldNormal = Transform_.Inverted().Transposed() * objectNormal;
			worldNormal.W = 0; // Hack to fix any wonky w coordinate caused by a translation transform.

			return worldNormal.Normalised();
		}
	};
}
