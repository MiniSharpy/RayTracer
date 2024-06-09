module;
#include <algorithm>
#include <cassert>
#include <optional>
#include <vector>

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

			Shape* Object;

			Tuple Hit;

			Tuple EyeVector;

			Tuple Normal;

			Tuple HitOffset;

			Tuple Reflection;

			bool Inside;

			Computation(const Ray& ray, float time, Shape* object) :
				Time(time),
				Object(object),
				Hit(ray.Position(time)),
				EyeVector(-ray.Direction),
				Normal(object->Normal(Hit)),
				HitOffset(Hit + Normal * Epsilon * 100),
				//Reflection(ray.Direction.Reflect(Normal)),
				Inside(false)
			{
				if (Tuple::Dot(Normal, EyeVector) < 0)
				{
					Inside = true;
					Normal = -Normal;
				}
				Reflection = ray.Direction.Reflect(Normal);
			}
		};

		struct Intersection
		{
			static std::optional<Intersection> Hit(const std::vector<Intersection>& intersections)
			{
				auto copy = intersections;
				auto sortAscendingWithNegativesAtEnd = [](const Intersection& lhs, const Intersection& rhs)
				{
					return (lhs.Time > 0 && rhs.Time > 0) ? rhs.Time > lhs.Time : lhs.Time > rhs.Time;
				};
				std::ranges::sort(copy, sortAscendingWithNegativesAtEnd);

				if (copy.empty() || copy[0].Time < 0) { return {}; }
				return copy[0];
			}

			float Time;

			Shape* Object;

			// Maybe shared_ptr? Guess if the object doesn't exist any more that's less calculations really.

			bool operator==(const Intersection& rhs) const { return Time == rhs.Time && Object == rhs.Object; }

			// Why even have a separate object? Why not just use the intersection? Surely the extra memory
			// won't make that much of a difference. Hell, why not just calculate it in a function before it's used?
			Computation PrepareComputations(const Ray& ray) const { return {ray, Time, Object}; }
		};

	private:
		static size_t GetFreeID()
		{
			static size_t ID = 0;
			return ID++;
		}

		size_t ID_ = GetFreeID();

	public:
		Matrix<4> Transform_ = Matrix<4>::IdentityMatrix();

		Material Material_; // Maybe this is why pascal case members aren't so popular in C++...

		Shape() {}

		Shape(const Matrix<4>& transform) : Transform_(transform) {}

		Shape(const Matrix<4>& transform, const Material& material) : Transform_(transform), Material_(material) {}

		Shape(const Material& material) : Material_(material) {}

		Shape(const Shape& object) : Transform_(object.Transform_), Material_(object.Material_) {}

		virtual ~Shape() = default;

		virtual std::vector<Intersection> Intersect(const Ray& ray)
		{
			// Rather than contend with transforming objects, making calculations difficult,
			// instead transform the ray by the inverse transform allowing the object to be treated as a
			// unit object with its origin as 0,0,0. World-Space vs Object-Space.
			const Ray transformedRay = ray.Transformed(Transform_.Inverted());

			return IntersectLocal(transformedRay);
		}

		virtual Tuple Normal(const Tuple& worldSpacePoint) const
		{
			// To handle a transformed sphere, transform the world space point
			// to object space so that the sphere can be treated as though it
			// were a unit sphere. This gets the normal in object space.
			Tuple objectSpacePoint = Transform_.Inverted() * worldSpacePoint;
			Tuple localNormal = NormalLocal(objectSpacePoint);

			// To convert from object space to normal space multiply the
			// object normal by the inverse transpose transform.
			// Multiplying just by the transform matrix would get something almost
			// right, but because the normals will no longer be perpendicular to
			// the surface it'll appear as though the image was transformed,
			// rather than the object.
			Tuple worldNormal = Transform_.Inverted().Transposed() * localNormal;
			worldNormal.W = 0; // Hack to fix any wonky w coordinate caused by a translation transform.

			return worldNormal.Normalised();
		}

	protected:
		virtual std::vector<Intersection> IntersectLocal(const Ray& ray) = 0;

		virtual Tuple NormalLocal(const Tuple& objectSpacePoint) const = 0;

	public:
		// Needed to move this here rather than on pattern object to avoid circular dependency. But really, it makes
		// more sense here anyway
		Tuple StripeAt(Tuple worldSpacePoint) const
		{
			assert(Material_.Pattern_);

			Tuple objectSpacePoint = Transform_.Inverted() * worldSpacePoint;
			Tuple patternSpacePoint = Material_.Pattern_->Transform.Inverted() * objectSpacePoint;

			return Material_.Pattern_->ColourAt(patternSpacePoint);
		}

		Tuple Lighting(const PointLight& light, const Tuple& surfacePointViewed,
		               const Tuple& viewVector, const Tuple& surfaceNormal, bool inShadow = false) const
		{
			assert(viewVector == viewVector.Normalised());

			if (Material_.Pattern_)
			{
				return Material_.Lighting(light, surfacePointViewed, viewVector, surfaceNormal, inShadow,
				                          StripeAt(surfacePointViewed));
			}

			return Material_.Lighting(light, surfacePointViewed, viewVector, surfaceNormal, inShadow);
		}

		bool operator==(const Shape& rhs) const { return ID_ == rhs.ID_; }
	};
}
