export module RayTracer:PointLight;
import :Tuple;

namespace RayTracer
{
	export struct PointLight
	{
		Tuple Position;
		Tuple Intensity;

		bool operator==(const PointLight& rhs) const
		{
			return Position == rhs.Position && Intensity == rhs.Intensity;
		}
	};

}