module;
#include <cassert>
#include<cmath>
export module RayTracer:Material;

import :PointLight;
import :Tuple;
import :FloatHelper;


namespace RayTracer
{
	export struct Material
	{
		Tuple Colour = Tuple::Colour(1, 1, 1);
		float Ambient = 0.1f; // Used to emulate the effects of global illumination.
		float Diffuse = 0.9f; // Used to determine intensity of surfaces aligned to the light source.
		float Specular = 0.9f; // Used to determine the intensity of rays reflecting.
		float Shininess = 200.0f;

		/// <returns>The colour of the surface at the specified point.</returns>
		Tuple Lighting(const PointLight& light, const Tuple& surfacePointViewed, 
			const Tuple& viewVector, const Tuple& surfaceNormal) const
		{
			assert(viewVector == viewVector.Normalised());
			Tuple diffuseColour = Tuple::Colour(0, 0, 0);
			Tuple specularColour = Tuple::Colour(0, 0, 0);

			Tuple effectiveColourOfSurface = Tuple::HadamardProduct(Colour, light.Intensity);
			Tuple ambientColour = effectiveColourOfSurface * Ambient; // Hack to emulate global illumination.

			// When there's a negative dot product the light is on the other side of the surface and diffuse
			// and specular are black.
			Tuple lightVector = (light.Position - surfacePointViewed).Normalised();
			float lightDotNormal = Tuple::Dot(lightVector, surfaceNormal);
			if (lightDotNormal >= 0) 
			{
				// Diffuse colour is determined in large part from angle from the light source to
				// the illuminated point as more light rays would strike the object.
				diffuseColour = effectiveColourOfSurface * Diffuse * lightDotNormal;

				// Negative dot product means light is reflecting away from the eye.
				Tuple reflectVector = (-lightVector).Reflect(surfaceNormal);
				float reflectDotEye = Tuple::Dot(reflectVector, viewVector);
				if (reflectDotEye > 0) // TODO: Why is this not >= ?
				{
					// Light is most concentrated at the reflection of a light ray on shiny objects.
					float factor = std::powf(reflectDotEye, Shininess);
					specularColour = light.Intensity * Specular * factor;
				}
			}

			return ambientColour + diffuseColour + specularColour;
		}

		bool operator==(const Material& rhs) const
		{
			return AlmostEquals(Ambient, rhs.Ambient) &&
				AlmostEquals(Diffuse, rhs.Diffuse) &&
				AlmostEquals(Specular, rhs.Specular) &&
				AlmostEquals(Shininess, rhs.Shininess);
		}
	};
}