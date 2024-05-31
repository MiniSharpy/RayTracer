module;
#include <cstdlib>
#include <float.h>

export module RayTracer:FloatHelper;

namespace RayTracer
{
	export constexpr float Epsilon = 0.00001;
	export constexpr auto AlmostEquals = [](float lhs, float rhs)
	{
		
		return std::abs(lhs - rhs) < Epsilon ? true : false;
	};
}

