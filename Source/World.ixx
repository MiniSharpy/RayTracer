module;
#include <optional>
#include <vector>

export module RayTracer:World;

import :Object;
import :PointLight;

namespace RayTracer
{
	export class World
	{
	public:
		std::vector<Object*> Objects;
		std::optional<PointLight> Light;
	};
}
