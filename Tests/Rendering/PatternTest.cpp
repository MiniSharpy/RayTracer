#include "gtest/gtest.h"

import RayTracer;

namespace RayTracer
{
	TEST(PatternTest, Black) { ASSERT_EQ(Colour::Black, Tuple::Colour(0,0,0)); }

	TEST(PatternTest, White) { ASSERT_EQ(Colour::White, Tuple::Colour(1, 1, 1)); }

	TEST(PatternTest, Stripe)
	{
		StripePattern pattern(Colour::White, Colour::Black);
		ASSERT_EQ(pattern.ColourA, Colour::White);
		ASSERT_EQ(pattern.ColourB, Colour::Black);
	}

	TEST(PatternTest, StripeAtConstantY)
	{
		StripePattern pattern(Colour::White, Colour::Black);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0,0,0)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 1, 0)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 2, 0)), Colour::White);
	}

	TEST(PatternTest, StripeAtConstantZ)
	{
		StripePattern pattern(Colour::White, Colour::Black);

		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0, 0)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0, 1)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0, 2)), Colour::White);
	}

	TEST(PatternTest, StripeAtAlternatingX)
	{
		StripePattern pattern(Colour::White, Colour::Black);

		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0, 0)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0.9, 0, 0)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(1, 0, 0)), Colour::Black);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(-0.1, 0, 0)), Colour::Black);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(-1, 0, 0)), Colour::Black);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(-1.1, 0, 0)), Colour::White);
	}

	TEST(PatternTest, StripesWithObjectTransform)
	{
		Sphere sphere;
		sphere.Transform_.Scale(2, 2, 2);
		sphere.Material_.Pattern_ = std::make_shared<StripePattern>(Colour::White, Colour::Black);
		ASSERT_EQ(sphere.StripeAt(Tuple::Point(1.5, 0, 0)), Colour::White);
	}

	TEST(PatternTest, StripesWithPatternTransform)
	{
		Sphere sphere;
		sphere.Material_.Pattern_ = std::make_shared<StripePattern>(Colour::White, Colour::Black);
		sphere.Material_.Pattern_->Transform.Scale(2, 2, 2);
		ASSERT_EQ(sphere.StripeAt(Tuple::Point(1.5, 0, 0)), Colour::White);
	}

	TEST(PatternTest, StripesWithObjectAndPatternTransform)
	{
		Sphere sphere;
		sphere.Transform_.Scale(2, 2, 2);
		sphere.Material_.Pattern_ = std::make_shared<StripePattern>(Colour::White, Colour::Black);
		sphere.Material_.Pattern_->Transform.Scale(0.5, 0, 0);

		ASSERT_EQ(sphere.StripeAt(Tuple::Point(2.5, 0, 0)), Colour::White);
	}

	TEST(PatternTest, Gradient)
	{
		GradientPattern pattern(Colour::White, Colour::Black);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0.25, 0, 0)), Tuple::Colour(0.75, 0.75, 0.75));
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0.5, 0, 0)), Tuple::Colour(0.5, 0.5, 0.5));
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0.75, 0, 0)), Tuple::Colour(0.25, 0.25, 0.25));
	}

	TEST(PatternTest, Ring)
	{
		RingPattern pattern(Colour::White, Colour::Black);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0, 0)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(1, 0, 0)), Colour::Black);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0, 1)), Colour::Black);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0.708, 0, 0.708)), Colour::Black);
	}

	TEST(PatternTest, CheckerX)
	{
		CheckerPattern pattern(Colour::White, Colour::Black);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0, 0)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0.99, 0, 0)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(1.01, 0, 0)), Colour::Black);
	}

	TEST(PatternTest, CheckerY)
	{
		CheckerPattern pattern(Colour::White, Colour::Black);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0, 0)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0.99, 0)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 1.01, 0)), Colour::Black);
	}

	TEST(PatternTest, CheckerZ)
	{
		CheckerPattern pattern(Colour::White, Colour::Black);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0, 0)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0, 0.99)), Colour::White);
		ASSERT_EQ(pattern.ColourAt(Tuple::Point(0, 0, 1.01)), Colour::Black);
	}
}