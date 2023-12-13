// Main code
#include<iostream>
#include <numbers>
import Tuple;
import Canvas;
import Matrix;

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
	return {projectile.Position + projectile.Velocity, projectile.Velocity + environment.Gravity + environment.Wind};
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
	RayTracer::Matrix<4> translation = RayTracer::Matrix<4>::TransformTranslate(256, 256, 0);
	RayTracer::Matrix<4> rotation = RayTracer::Matrix<4>::TransformRotateZ((2 * std::numbers::pi) 
		/ numberOfDots);

	for (int i = 0; i < numberOfDots; ++i)
	{
		// TODO: Implement Tuple::Translate()? Would chaining still work alright?
		RayTracer::Tuple centred = translation * point;
		canvas.SetPixel(centred.X, centred.Y, {1, 1, 1});
		point = rotation * point;
	}

	canvas.WritePPM();
}

int main(int, char**)
{
	DrawDistributedPoints();
	return 0;
}