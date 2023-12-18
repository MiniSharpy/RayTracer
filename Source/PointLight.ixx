export module RayTracer:PointLight;
import :Tuple;

namespace RayTracer
{
	export struct PointLight
	{
		Tuple Position;
		Tuple Intensity;
	};

}