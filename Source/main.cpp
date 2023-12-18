// Main code
#include<iostream>
#include<numbers>
#include<optional>
import RayTracer;

struct Projectile
{
	RayTracer::Tuple Position;
	RayTracer::Tuple Velocity;
};

struct Environment
{
	RayTracer::Tuple Gravity;
	RayTracer::Tuple Wind;
};

Projectile Tick(Environment& environment, Projectile& projectile)
{
	return { projectile.Position + projectile.Velocity, projectile.Velocity + environment.Gravity + environment.Wind };
}

void DrawProjectile()
{
	Projectile projectile =
	{
		RayTracer::Tuple::Point(0,1,0),
		RayTracer::Tuple::Vector(1,1.8,0).Normalised() * 11
	};
	Environment environment = {
		RayTracer::Tuple::Vector(0, -0.1, 0),
		RayTracer::Tuple::Vector(-0.01, 0, 0)
	};
	RayTracer::Canvas canvas(900, 550);

	bool hasHitGround = false;
	while (!hasHitGround)
	{
		projectile = Tick(environment, projectile);
		hasHitGround = projectile.Position.Y <= 0 ? true : false;
		canvas.SetPixel(
			std::max<int>(0, projectile.Position.X),
			std::max<int>(0, projectile.Position.Y),
			{ 1, 0,0 });
		std::cout << projectile.Position << std::endl;
	}

	canvas.WritePPM();
}

void DrawDistributedPoints()
{
	constexpr int numberOfDots = 8192;
	constexpr int width = 512;
	constexpr int height = 512;
	constexpr int radius = 200;
	RayTracer::Canvas canvas(width, height);
	RayTracer::Tuple point = RayTracer::Tuple::Point(0, radius, 0);
	RayTracer::Matrix<4> translation = RayTracer::Matrix<4>::Translation(256, 256, 0);
	RayTracer::Matrix<4> rotation = RayTracer::Matrix<4>::RotationZ((2 * std::numbers::pi)
		/ numberOfDots);

	for (int i = 0; i < numberOfDots; ++i)
	{
		// TODO: Implement Tuple::Translate()? Would chaining still work alright?
		RayTracer::Tuple centred = translation * point;
		canvas.SetPixel(centred.X, centred.Y, { 1, 1, 1 });
		point = rotation * point;
	}

	canvas.WritePPM();
}

void DrawFilledCircled()
{
	constexpr int distance = 512;
	constexpr int width = 512;
	constexpr int height = 512;
	RayTracer::Canvas canvas(width, height);

	// World Position:  X=256, Y=256, Z=0.
	RayTracer::Sphere sphere
	{ RayTracer::Matrix<4>::Scaling(15, 30, 1).Translate(width / 2, height / 2, 0)
	};

	// World Position: X=256, Y=256, Z=512.
	RayTracer::Ray ray
	{
		RayTracer::Tuple::Point(width / 2, height / 2, distance),
		RayTracer::Tuple::Vector(0, 0, 0)
	};

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			ray.Direction = RayTracer::Tuple::Point(x, y, 0) - ray.Origin;

			std::optional<RayTracer::Intersection> hit = 
				RayTracer::Intersection::Hit(sphere.Intersect(ray));
			if (hit)
			{
				canvas.SetPixel(x, y, RayTracer::Tuple::Colour(1, 0, 0));
			}
		}
	}

	canvas.WritePPM();
}

void DrawSphere()
{
	constexpr int width = 512;
	constexpr int height = 512;
	constexpr int distance = 512;

	RayTracer::Canvas canvas(width, height);

	RayTracer::PointLight light
	{
		RayTracer::Tuple::Point(-width/2, -height/2, -distance),
		RayTracer::Tuple::Colour(1, 1, 1)
	};

	// World Position:  X=256, Y=256, Z=0.
	RayTracer::Sphere sphere
	{ RayTracer::Matrix<4>::Scaling(128, 128, 128).Translate(width / 2, height / 2, 0)
	};
	sphere.MaterialData.Colour = RayTracer::Tuple::Colour(1, 0.2, 1);

	// World Position: X=256, Y=256, Z=512.
	RayTracer::Ray ray
	{
		RayTracer::Tuple::Point(width / 2, height / 2, distance),
		RayTracer::Tuple::Vector(0, 0, 0)
	};

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			ray.Direction = (RayTracer::Tuple::Point(x, y, 0) - ray.Origin).Normalised();

			std::optional<RayTracer::Intersection> hit =
				RayTracer::Intersection::Hit(sphere.Intersect(ray));

			if (hit)
			{
				RayTracer::Sphere& hitObject = sphere;
				RayTracer::Tuple position = ray.Position(hit->Time);
				RayTracer::Tuple normal = hitObject.Normal(position);
				RayTracer::Tuple eye = ray.Direction;
				RayTracer::Tuple surfaceColour = hitObject.MaterialData.Lighting
				(
					light,
					position,
					eye,
					normal
				);
				canvas.SetPixel(x, y, surfaceColour);
			}
		}
	}

	canvas.WritePPM();
}

int main(int, char**)
{
	DrawSphere();
	return 0;
}