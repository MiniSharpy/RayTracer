module;
#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

export module RayTracer:World;

import :Shape;
import :Sphere;
import :PointLight;
import :Ray;

namespace RayTracer
{
	export class World
	{
	public:
		static World ExampleWorld()
		{
			PointLight light{Tuple::Point(-10, 10, -10), Tuple::Colour(1, 1, 1)};

			std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Material{Tuple::Colour(0.8, 1.0, 0.6)});
			sphere1->Material_.Diffuse = 0.7;
			sphere1->Material_.Specular = 0.2;
			std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Matrix<4>::Scaling(0.5, 0.5, 0.5));

			return {{sphere1, sphere2}, light};
		}

		std::vector<std::shared_ptr<Shape>> Objects;

		std::optional<PointLight> Light;

		std::vector<Shape::Intersection> Intersect(const Ray& ray) const
		{
			std::vector<Shape::Intersection> intersections;
			for (const std::shared_ptr<Shape>& object : Objects)
			{
				std::vector<Shape::Intersection> objectIntersections = object->Intersect(ray);
				intersections.insert(intersections.end(), objectIntersections.begin(), objectIntersections.end());
			}

			auto sortAscendingWithNegativesAtEnd = [](const Shape::Intersection& lhs, const Shape::Intersection& rhs)
			{
				return (lhs.Time > 0 && rhs.Time > 0) ? rhs.Time > lhs.Time : lhs.Time > rhs.Time;
			};
			std::ranges::sort(intersections, sortAscendingWithNegativesAtEnd);

			return intersections;
		}

		Tuple ShadeIntersection(const Shape::Computation& computation) const
		{
			bool isShadowed = IsPointInShadow(computation.HitOffset);

			// To support multiple lights iterate over all sources and add together resulting values.
			// But how does that handle values > 1? Do they just get clipped at some point?
			return computation.Object->Lighting(*Light, computation.Hit, computation.EyeVector, computation.Normal,
			                                    isShadowed);
		}

		Tuple ColourAt(Ray& ray) const
		{
			std::vector<Shape::Intersection> intersections = Intersect(ray);
			std::optional<Shape::Intersection> intersection = Shape::Intersection::Hit(intersections);

			if (!intersection) { return {}; }

			return ShadeIntersection(intersection->PrepareComputations(ray));
		}

		bool IsPointInShadow(Tuple point) const
		{
			Tuple lightDirectionNonNormalised = Light->Position - point;
			float lightDistance = (lightDirectionNonNormalised).Magnitude();
			Tuple lightDirection = lightDirectionNonNormalised.Normalised();

			Ray ray{point, lightDirection};

			std::vector<Shape::Intersection> intersections = Intersect(ray);
			std::optional<Shape::Intersection> hit = Shape::Intersection::Hit(intersections);

			if (hit && hit->Time < lightDistance) { return true; }

			return false;
		}
	};
}
