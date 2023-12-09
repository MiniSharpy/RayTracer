// Main code
#include<iostream>
import Tuple;

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
	Projectile projectile = { RayTracer::Tuple::Point(0,1,0), RayTracer::Tuple::Vector(1,1,0).Normalised() };
	Environment environment = { RayTracer::Tuple::Vector(0, -0.1, 0), RayTracer::Tuple::Vector(-0.01, 0, 0) };

	bool hasHitGround = false;
	while (!hasHitGround)
	{
		projectile = Tick(environment, projectile);
		hasHitGround = projectile.Position.Y <= 0 ? true : false;
		std::cout << projectile.Position << std::endl;
	}

	return 0;
}