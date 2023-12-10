// Main code
#include<iostream>
import Tuple;
import Canvas;

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

int main(int, char**)
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
	return 0;
}