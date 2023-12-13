module;
#include <cstdlib>

export module FloatHelper;

namespace RayTracer
{
	export constexpr auto AlmostEquals = [](float lhs, float rhs)
	{
		constexpr float epsilon = 0.00001;
		return std::abs(lhs - rhs) < epsilon ? true : false;
	};
}

