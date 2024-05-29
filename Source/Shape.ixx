module;
#include <algorithm>
#include <vector>
#include <optional>

export module RayTracer:Shape;
import :Matrix;
import :Material;
import :Ray;
import :Tuple;

namespace RayTracer
{
	export class Shape
	{
	public:
		struct Computation
		{
			float Time;
			Shape *ObjectInstance;
			Tuple Hit;
			Tuple EyeVector;
			Tuple Normal;
			bool Inside;

			Computation(const Ray &ray, float time, Shape *object) :
				Time(time),
				ObjectInstance(object),
				Hit(ray.Position(time)),
				EyeVector(-ray.Direction),
				Normal(object->Normal(Hit)),
				Inside(false)
			{
				if (Tuple::Dot(Normal, EyeVector) < 0)
				{
					Inside = true;
					Normal = -Normal;
				}
			}

		};

		struct Intersection
		{
			static std::optional<Intersection> Hit(const std::vector<Intersection> &intersections)
			{
				auto copy = intersections;
				auto sortAscendingWithNegativesAtEnd = [](const Intersection &lhs, const Intersection &rhs)
				{ return (lhs.Time > 0 && rhs.Time > 0) ? rhs.Time > lhs.Time : lhs.Time > rhs.Time; };
				std::ranges::sort(copy, sortAscendingWithNegativesAtEnd);

				if (copy.empty() || copy[0].Time < 0) { return{}; }
				return copy[0];
			}

			float Time;
			Shape *Object; // Maybe shared_ptr? Guess if the object doesn't exist any more that's less calculations really.

			bool operator==(const Intersection &rhs) const
			{
				return Time == rhs.Time && Object == rhs.Object;
			}

			// Why even have a separate object? Why not just use the intersection? Surely the extra memory
			// won't make that much of a difference. Hell, why not just calculate it in a function before it's used?
			Computation PrepareComputations(const Ray &ray) const
			{
				return { ray, Time, Object };
			}
		};

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