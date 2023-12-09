module;
#include <cmath>
#include <limits>
#include <iostream>

export module Tuple;

// Requires MSVC boilerplate, https://github.com/GabrielDosReis/cmake-for-modules/tree/main
// import std; // Multiple definition errors with normal includes of std headers, including through third party libraries like GTest.

namespace RayTracer
{
	/// <summary>
	/// A struct representing a point (W=1) and a vector (W=0), with the W component determining which.
	/// </summary>
	export struct Tuple
	{
		/*STATIC*/
		// METHODS
		static constexpr Tuple Point(float x, float y, float z) { return { x, y, z, 1.0f }; }
		static constexpr Tuple Vector(float x, float y, float z) { return { x, y, z, 0.0f }; }
		static constexpr Tuple ZeroVector() { return Vector(0, 0, 0); }
		static constexpr Tuple UnitXVector() { return Vector(1, 0, 0); }
		static constexpr Tuple UnitYVector() { return Vector(0, 1, 0); }
		static constexpr Tuple UnitZVector() { return Vector(0, 1, 0); }

		/// <summary>
		/// The larger the dot product, the larger the angle between vectors.
		///	With two unit vectors:
		///	- A dot product of 1 means they are identical.
		///	- A dot product of -1 means they point in opposite directions.
		///	The dot product is the cosine of the angle between the two vectors.
		/// </summary>
		static constexpr float Dot(Tuple lhs, Tuple rhs)
		{
			return
				lhs.X * rhs.X +
				lhs.Y * rhs.Y +
				lhs.Z * rhs.Z +
				lhs.W * rhs.W;
		}

		/// <summary>
		/// Cross product of vectors.
		///	Non-commutative. Order matters.
		///	Results in a new vector perpendicular (the normal) to the original vectors.
		/// </summary>
		static constexpr Tuple Cross(Tuple lhs, Tuple rhs)
		{
			return Vector
			(
				lhs.Y * rhs.Z - lhs.Z * rhs.Y,
				lhs.Z * rhs.X - lhs.X * rhs.Z,
				lhs.X * rhs.Y - lhs.Y * rhs.X
			);
		}

		/*INSTANCE*/
		float X, Y, Z, W;

		/// <summary>
		/// Add a point (W=1) and a vector (W=0), and you get another point (W=1). Essentially moving in the direction of the vector.
		///	Add a vector (W=0) and a vector (W=0), and you get another vector (W=0). Essentially accumulating growth.
		///	Add a point (W=1) and a point (W=1), and you get nonsense (W=2).
		/// </summary>
		constexpr Tuple operator+ (const Tuple& rhs) const { return { X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W }; }

		/// <summary>
		/// Subtract a point (W=1) from another point (W=1), and you get a vector (W=0). Essentially getting a direction and magnitude from one point to the other.
		///	Subtract a vector (W=0) from a point (W=1), and you get a point (W=1). Essentially moving away by the vector.
		///	Subtract a vector (W=0) from a vector (W=0), and you get a vector(W=0). Essentially getting the change in direction between two vectors.
		///	Subtract a point (W=1) from a vector (W=0), and you get nonsense (W=-1).
		/// </summary>
		constexpr Tuple operator- (const Tuple& rhs) const { return { X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W }; }

		constexpr Tuple operator-() const { return { -X, -Y, -Z, -W }; };

		constexpr Tuple operator* (const float right) const { return { X * right, Y * right, Z * right, W * right }; };
		constexpr Tuple operator/ (const float right) const { return { X / right, Y / right, Z / right, W / right }; };

		bool operator==(const Tuple& rhs) const
		{
			// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
			auto almostEquals = [](float lhs, float rhs)
			{
				constexpr float epsilon = std::numeric_limits<float>::epsilon();
				const float difference = std::abs(lhs - rhs);
				lhs = std::abs(lhs);
				rhs = std::abs(rhs);
				const float largest = (rhs > lhs) ? rhs : lhs;

				return difference <= largest * epsilon ? true : false;
			};

			const Tuple& lhs = *this;

			return almostEquals(lhs.X, rhs.X) && almostEquals(lhs.Y, rhs.Y) && almostEquals(lhs.Z, rhs.Z) && almostEquals(lhs.W, rhs.W);
		}
		bool operator!=(const Tuple& rhs) const { const Tuple& lhs = *this; return !(lhs == rhs); }

		// METHODS
		Tuple Normalised() const
		{
			if (MagnitudeSquared() == 0) { return {}; }
			float scale = 1.0f / Magnitude();
			return Vector(X * scale, Y * scale, Z * scale);
		}

		float Magnitude() const
		{
			return sqrt(MagnitudeSquared());
		}

		float MagnitudeSquared() const
		{
			return X * X + Y * Y + Z * Z;
		}

		bool IsAPoint() const
		{
			return W == 1.0f;
		}

		bool IsAVector() const
		{
			return W == 0.0f;
		}

		friend std::ostream& operator<<(std::ostream& os, const Tuple& tuple)
		{
			return os << "X:" << tuple.X << " Y:" << tuple.Y << " Z:" << tuple.Z << " W:" << tuple.W;
		}
	};
}
