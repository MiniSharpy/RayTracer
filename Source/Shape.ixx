module;
#include<vector>

// Forward declaring before the module defintion seems to fix linker errors.
// This is strictly speaking only necessary for intersection.
// However, this does generate some compiler warnings and massively breaks intellisense.
namespace RayTracer {
	struct Intersection;
}

export module RayTracer:Shape;
import :Matrix;
import :Material;
import :Ray;
import :Tuple;

namespace RayTracer
{
	export class Shape
	{
		static size_t GetID()
		{
			static size_t ID = 0;
			return ID++;
		}

		size_t ID = GetID();
	public:
		bool operator==(const Shape& rhs) const
		{
			return ID == rhs.ID;
		}

		Shape() : Transform(Matrix<4>::IdentityMatrix()) {}
		Shape(const Matrix<4>& transform) : Transform(transform) {}
		Shape(const Matrix<4>& transform, const Material& material) : Transform(transform), MaterialInstance(material) {}
		Shape(const Material& material) : Transform(Matrix<4>::IdentityMatrix()), MaterialInstance(material) {}
		Shape(const Shape& object) : Transform(object.Transform), MaterialInstance(object.MaterialInstance) {}

		Matrix<4> Transform;
		Material MaterialInstance; // Maybe this is why pascal case members aren't so popular in C++...

		virtual std::vector<Intersection> Intersect(const Ray& ray) = 0;
		virtual Tuple Normal(const Tuple& worldSpacePoint) const = 0;
		virtual ~Shape() = default;
	};
}