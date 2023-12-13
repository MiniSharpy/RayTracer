export module RayTracer:Object;

namespace RayTracer
{
	export class Object
	{
		static size_t GetID()
		{
			static size_t ID = 0;
			return ID++;
		}

		size_t ID = GetID();
	public:
		bool operator==(const Object& rhs) const
		{
			return ID == rhs.ID;
		}
	};
}