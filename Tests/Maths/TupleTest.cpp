import RayTracer;
#include "gtest/gtest.h"

namespace RayTracer
{
	TEST(TupleTest, PointConstruction)
	{
		auto point = Tuple{ 4.3f, -4.2f, 3.1f, 1.0f };
		ASSERT_FLOAT_EQ(point.X, 4.3f);
		ASSERT_FLOAT_EQ(point.Y, -4.2f);
		ASSERT_FLOAT_EQ(point.Z, 3.1f);
		ASSERT_FLOAT_EQ(point.W, 1.0f);

		ASSERT_TRUE(point.IsAPoint());
		ASSERT_FALSE(point.IsAVector());
	}

	TEST(TupleTest, VectorConstruction)
	{
		auto vector = Tuple{ 4.3f, -4.2f, 3.1f, 0.0f };
		ASSERT_FLOAT_EQ(vector.X, 4.3f);
		ASSERT_FLOAT_EQ(vector.Y, -4.2f);
		ASSERT_FLOAT_EQ(vector.Z, 3.1f);
		ASSERT_FLOAT_EQ(vector.W, 0.0f);

		ASSERT_FALSE(vector.IsAPoint());
		ASSERT_TRUE(vector.IsAVector());
	}

	TEST(TupleTest, PointMethod)
	{
		auto point = Tuple::Point(4, -4, 3);
		ASSERT_FLOAT_EQ(point.X, 4.f);
		ASSERT_FLOAT_EQ(point.Y, -4.f);
		ASSERT_FLOAT_EQ(point.Z, 3.f);
		ASSERT_FLOAT_EQ(point.W, 1.0f);
	}

	TEST(TupleTest, VectorMethod)
	{
		auto vector = Tuple::Vector(4, -4, 3);
		ASSERT_FLOAT_EQ(vector.X, 4.f);
		ASSERT_FLOAT_EQ(vector.Y, -4.f);
		ASSERT_FLOAT_EQ(vector.Z, 3.f);
		ASSERT_FLOAT_EQ(vector.W, 0.0f);
	}

	TEST(TupleTest, SubscriptOperator)
	{
		auto point = Tuple{ 3, -2, 5, 1 };
		ASSERT_EQ(point[0], point.X);
		ASSERT_EQ(point[1], point.Y);
		ASSERT_EQ(point[2], point.Z);
		ASSERT_EQ(point[3], point.W);
	}

	TEST(TupleTest, AdditionPointVector)
	{
		auto point = Tuple{ 3, -2, 5, 1 };
		auto vector = Tuple{ -2, 3, 1, 0 };
		auto resultingPoint = Tuple{ 1, 1, 6, 1 };
		ASSERT_EQ(point + vector, resultingPoint);
	}


	TEST(TupleTest, SubtractionPoints)
	{
		auto pointA = Tuple::Point(3, 2, 1);
		auto pointB = Tuple::Point(5, 6, 7);
		auto resultingVector = Tuple::Vector(-2, -4, -6);
		ASSERT_EQ(pointA - pointB, resultingVector);
	}

	TEST(TupleTest, SubtractionVectorFromPoint)
	{
		auto point = Tuple::Point(3, 2, 1);
		auto vector = Tuple::Vector(5, 6, 7);
		auto resultingPoint = Tuple::Point(-2, -4, -6);
		ASSERT_EQ(point - vector, resultingPoint);
	}

	TEST(TupleTest, SubtractionVectors)
	{
		auto vectorA = Tuple::Vector(3, 2, 1);
		auto vectorB = Tuple::Vector(5, 6, 7);
		auto resultingVector = Tuple::Vector(-2, -4, -6);
		ASSERT_EQ(vectorA - vectorB, resultingVector);
	}

	TEST(TupleTest, SubtractionVectorFromZeroVector)
	{
		auto vectorA = Tuple::Vector(1, -2, 3);
		auto resultingVector = Tuple::Vector(-1, 2, -3);
		ASSERT_EQ(Tuple::ZeroVector() - vectorA, resultingVector);
	}

	TEST(TupleTest, SubtractionUnary)
	{
		auto tuple = Tuple{ 1, -2, 3, -4 };
		auto resultingTuple = Tuple{ -1, 2, -3, 4 };
		ASSERT_EQ(-tuple, resultingTuple);
	}

	TEST(TupleTest, MultiplicationScalar)
	{
		auto tuple = Tuple{ 1, -2, 3, -4 };
		auto resultingTuple = Tuple{ 3.5, -7, 10.5, -14 };
		ASSERT_EQ(tuple * 3.5, resultingTuple);
	}

	TEST(TupleTest, MultiplicationFraction)
	{
		auto tuple = Tuple{ 1, -2, 3, -4 };
		auto resultingTuple = Tuple{ 0.5, -1, 1.5, -2 };
		ASSERT_EQ(tuple * 0.5, resultingTuple);
	}

	TEST(TupleTest, DivisionScalar)
	{
		auto tuple = Tuple{ 1, -2, 3, -4 };
		auto resultingTuple = Tuple{ 0.5, -1, 1.5, -2 };
		ASSERT_EQ(tuple / 2, resultingTuple);
	}

	TEST(TupleTest, MagnitudeUnitX)
	{
		auto vector = Tuple::UnitXVector();
		ASSERT_FLOAT_EQ(vector.Magnitude(), 1.0f);
	}

	TEST(TupleTest, MagnitudeUnitY)
	{
		auto vector = Tuple::UnitYVector();
		ASSERT_FLOAT_EQ(vector.Magnitude(), 1.0f);
	}

	TEST(TupleTest, MagnitudeUnitZ)
	{
		auto vector = Tuple::UnitZVector();
		ASSERT_FLOAT_EQ(vector.Magnitude(), 1.0f);
	}


	TEST(TupleTest, MagnitudeXYZ)
	{
		auto vector = Tuple::Vector(1, 2, 3);
		ASSERT_FLOAT_EQ(vector.Magnitude(), sqrt(14));
	}

	TEST(TupleTest, MagnitudeNegativeXYZ)
	{
		auto vector = Tuple::Vector(-1, -2, -3);
		ASSERT_FLOAT_EQ(vector.Magnitude(), sqrt(14));
	}

	TEST(TupleTest, NormaliseSingle)
	{
		auto tuple = Tuple::Vector(4, 0, 0);
		auto resultingVector = Tuple::Vector(1, 0, 0);
		ASSERT_EQ(tuple.Normalised(), resultingVector);
	}

	TEST(TupleTest, NormaliseMultiple)
	{
		auto tuple = Tuple::Vector(1, 2, 3);
		auto resultingVector = Tuple::Vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14));
		ASSERT_EQ(tuple.Normalised(), resultingVector);
	}

	TEST(TupleTest, NormaliseMagnitude)
	{
		auto tuple = Tuple::Vector(1, 2, 3);
		ASSERT_FLOAT_EQ(tuple.Normalised().Magnitude(), 1);
	}

	TEST(TupleTest, DotProduct)
	{
		auto lhs = Tuple::Vector(1, 2, 3);
		auto rhs = Tuple::Vector(2, 3, 4);
		ASSERT_FLOAT_EQ(Tuple::Dot(lhs, rhs), 20);
	}

	TEST(TupleTest, CrossProduct)
	{
		auto a = Tuple::Vector(1, 2, 3);
		auto b = Tuple::Vector(2, 3, 4);
		auto resultingVectorAB = Tuple::Vector(-1, 2, -1);
		auto resultingVectorBA = Tuple::Vector(1, -2, 1);
		ASSERT_EQ(Tuple::Cross(a, b), resultingVectorAB);
		ASSERT_EQ(Tuple::Cross(b, a), resultingVectorBA);
	}

	TEST(TupleTest, ColourTuples)
	{
		auto colour = Tuple::Colour(-0.5, 0.4, 1.7);
		auto resultingColour = Tuple::Colour(-0.5, 0.4, 1.7);
		ASSERT_EQ(colour, resultingColour);
	}

	TEST(TupleTest, ColourMultiplication)
	{
		auto colourA = Tuple::Colour(1, 0.2, 0.4);
		auto colourB = Tuple::Colour(0.9, 1, 0.1);

		auto resultingColour = Tuple::Colour(0.9, 0.2, 0.04);
		ASSERT_EQ(Tuple::HadamardProduct(colourA, colourB), resultingColour);
	}

	TEST(TupleTest, ReflectAt45Degree)
	{
		Tuple vector = Tuple::Vector(1, -1, 0);
		Tuple normal = Tuple::Vector(0, 1, 0);
		Tuple reflect = vector.Reflect(normal);
		ASSERT_EQ(reflect, Tuple::Vector(1, 1, 0));
	}

	TEST(TupleTest, ReflectOffSlantedSurface)
	{
		Tuple vector = Tuple::Vector(0, -1, 0);
		Tuple normal = Tuple::Vector(sqrtf(2)/2, sqrtf(2) / 2, 0);
		Tuple reflect = vector.Reflect(normal);
		ASSERT_EQ(reflect, Tuple::Vector(1, 0, 0));
	}
}
