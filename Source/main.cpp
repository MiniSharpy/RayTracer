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
		RayTracer::Tuple::Point(-width/2, -height/2, distance),
		RayTracer::Tuple::Colour(1, 1, 1)
	};

	// World Position:  X=256, Y=256, Z=0.
	RayTracer::Sphere sphere
	{ RayTracer::Matrix<4>::Scaling(128, 128, 128).Translate(width / 2, height / 2, 0)
	};
	sphere.MaterialInstance.Colour = RayTracer::Tuple::Colour(1, 0.2, 1);

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
				RayTracer::Tuple eye = -ray.Direction;
				RayTracer::Tuple surfaceColour = hitObject.MaterialInstance.Lighting
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

void DrawSpheres()
{
	std::shared_ptr<RayTracer::Sphere> floor = std::make_shared<RayTracer::Sphere>();
	floor->Transform.Scale(10, 0.01, 10);
	floor->MaterialInstance.Colour = RayTracer::Tuple::Colour(1, 0.9, 0.9);
	floor->MaterialInstance.Specular = 0;

	std::shared_ptr<RayTracer::Sphere> leftWall = std::make_shared<RayTracer::Sphere>();
	leftWall->Transform.Scale(10, 0.01, 10)
		.RotateX(std::numbers::pi / 2).RotateY(-std::numbers::pi / 4)
		.Translate(0, 0, 5);
	leftWall->MaterialInstance = floor->MaterialInstance;

	std::shared_ptr<RayTracer::Sphere> rightWall = std::make_shared<RayTracer::Sphere>();
	rightWall->Transform.Scale(10, 0.01, 10)
		.RotateX(std::numbers::pi / 2).RotateY(std::numbers::pi / 4)
		.Translate(0, 0, 5);
	rightWall->MaterialInstance = floor->MaterialInstance;

	std::shared_ptr<RayTracer::Sphere> middle = std::make_shared<RayTracer::Sphere>();
	middle->Transform.Translate(-0.5, 1, 0.5);
	middle->MaterialInstance.Colour = RayTracer::Tuple::Colour(0.5, 1, 0.1);
	middle->MaterialInstance.Diffuse = 0.7;
	middle->MaterialInstance.Specular = 0.3;

	std::shared_ptr<RayTracer::Sphere> right = std::make_shared<RayTracer::Sphere>();
	right->Transform.Scale(0.5, 0.5, 0.5).Translate(1.5, 0.5, 0.1);
	right->MaterialInstance.Colour = RayTracer::Tuple::Colour(0.5, 1, 0.1);
	right->MaterialInstance.Diffuse = 0.7;
	right->MaterialInstance.Specular = 0.3;

	std::shared_ptr<RayTracer::Sphere> left = std::make_shared<RayTracer::Sphere>();
	left->Transform.Scale(0.33, 0.33, 0.33).Translate(-1.5, 0.33, -0.75);
	left->MaterialInstance.Colour = RayTracer::Tuple::Colour(1, 0.8, 0.1);
	left->MaterialInstance.Diffuse = 0.7;
	left->MaterialInstance.Specular = 0.3;

	RayTracer::World world
	{
	{ floor, leftWall, rightWall, left, middle, right },
		RayTracer::PointLight
		{
			RayTracer::Tuple::Point(-10, 10, -10),
			RayTracer::Tuple::Colour(1, 1, 1)
		}
	};

	// TODO: Does it even make sense to have a camera not attached to a world?
	RayTracer::Camera camera(100, 50, std::numbers::pi / 3);
	camera.Transform = RayTracer::Matrix<4>::ViewTransform
	(
		RayTracer::Tuple::Point(0, 1.5, -5),
		RayTracer::Tuple::Point(0, 1, 0),
		RayTracer::Tuple::Vector(0, 1, 0)
	);

	RayTracer::Canvas canvas = camera.Render(world);
	canvas.WritePPM();
}

int main(int, char**)
{
	DrawSpheres();
	return 0;
}