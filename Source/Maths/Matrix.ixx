module;
#include<array>
#include <cassert>
#include<limits>

export module Matrix;

import Tuple;

namespace RayTracer
{
	export template<size_t Dimensions>
	struct Matrix
	{
		/// <summary>
		/// Any matrix multiplied by the identity matrix returns the same value.
		/// </summary>
		/// <returns>A zeroed matrix, except for its diagonals which have the value 1.</returns>
		constexpr static Matrix IdentityMatrix()
		{
			Matrix identityMatrix{};
			for (int i = 0; i < Dimensions; ++i)
			{
				identityMatrix[(Dimensions + 1) * i] = 1;
			}

			return identityMatrix;
		}

		std::array<float, Dimensions* Dimensions> Values;

		/// <summary>
		///	For every row in left hand side matrix:
		/// Multiply each element in a left hand side column
		/// by the corresponding element in a right hand side row,
		/// adding the products together to form a single element in the new matrix
		/// corresponding to the respective row and column. \n
		/// Each element of the final matrix is a dot product of a row-column
		/// combination.
		/// </summary>
		constexpr Matrix operator* (const Matrix& rhs) const
		{
			Matrix result{};

			for (int row = 0; row < Dimensions; ++row)
			{
				for (int column = 0; column < Dimensions; ++column)
				{
					for (int i = 0; i < Dimensions; ++i)
					{
						result(row, column) += (*this)(row, i) * rhs(i, column);
					}
				}
			}

			return result;
		}

		constexpr Tuple operator* (const Tuple& rhs) const requires(Dimensions == 4)
		{
			Tuple result{};
			for (int row = 0; row < 4; ++row)
			{
				for (int i = 0; i < 4; ++i)
				{
					result[row] += (*this)(row, i) * rhs[i];
				}
			}

			return result;
		}

		bool operator==(const Matrix& rhs) const
		{
			// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
			auto almostEquals = [](float lhs, float rhs)
			{
				// Need a pretty high epsilon for some of the unit tests to pass.
				// Maybe I should instead just use the cofactor / determinant (E.G. 5 / -755)
				// rather than the hardcoded provided in the book?
				constexpr float epsilon = std::numeric_limits<float>::epsilon() * 1000;
				const float difference = std::abs(lhs - rhs);
				lhs = std::abs(lhs);
				rhs = std::abs(rhs);
				const float largest = (rhs > lhs) ? rhs : lhs;

				return difference <= largest * epsilon ? true : false;
			};

			bool isAlmostEqual = true;
			for (int i = 0; i < Dimensions * Dimensions; ++i)
			{
				isAlmostEqual &= almostEquals((*this)[i], rhs[i]);
			}

			return isAlmostEqual;
		}
		bool operator!=(const Matrix& rhs) const { return !(*this == rhs); }

		// TODO: Not supported by MSVC yet.
		// Multidimensional subscript operator:
		// https://en.cppreference.com/w/cpp/23
		//constexpr float& operator[](std::size_t row, std::size_t column)
		//{
		//	return Values[Dimensions * column + row];
		//}

		float& operator() (size_t row, size_t column)
		{
			return Values[Dimensions * row + column];
		}

		const float& operator() (size_t row, size_t column) const
		{
			return Values[Dimensions * row + column];
		}

		float& operator[](std::size_t index)
		{
			return Values[index];
		}

		const float& operator[](std::size_t index) const
		{
			return Values[index];
		}

		Matrix Transposed()
		{
			Matrix transposed;
			for (int row = 0; row < Dimensions; ++row)
			{
				for (int column = 0; column < Dimensions; ++column)
				{
					transposed(row, column) = (*this)(column, row);
				}
			}

			return transposed;
		}

		// TODO: Specialise With modules, a specialised version isn't called.
		float Determinant()  requires(Dimensions == 2)
		{
			return (Values[0] * Values[3]) - (Values[1] * Values[2]);
		}

		float Determinant() requires(Dimensions > 2)
		{
			// Doesn't matter which row or column is picked.
			float determinant = 0;
			for (int column = 0; column < Dimensions; ++column)
			{
				determinant += Values[column] * Cofactor(0, column);
			}

			return determinant;
		}

		Matrix<Dimensions - 1> Submatrix(size_t rowToRemove, size_t columnToRemove)
		{
			Matrix<Dimensions - 1> submatrix;

			for (int row = 0; row < Dimensions - 1; ++row)
			{
				for (int column = 0; column < Dimensions - 1; ++column)
				{
					size_t rowOffset = row >= rowToRemove ? 1 : 0;
					size_t columnOffset = column >= columnToRemove ? 1 : 0;
					submatrix(row, column) = (*this)
						(
							row + rowOffset,
							column + columnOffset
							);
				}
			}

			return submatrix;
		}

		float Minor(size_t rowToRemove, size_t columnToRemove)
		{
			return Submatrix(rowToRemove, columnToRemove).Determinant();
		}

		float Cofactor(size_t row, size_t column)
		{
			float minor = Minor(row, column);
			bool isOdd = (row + column) % 2;
			return isOdd ? -minor : minor;
		}

		Matrix Inverted()
		{
			// TODO: Move to own file to reduce repetition.
			auto almostEquals = [](float lhs, float rhs)
			{
				constexpr float epsilon = std::numeric_limits<float>::epsilon() * 1000;
				const float difference = std::abs(lhs - rhs);
				lhs = std::abs(lhs);
				rhs = std::abs(rhs);
				const float largest = (rhs > lhs) ? rhs : lhs;

				return difference <= largest * epsilon ? true : false;
			};

			float determinant = Determinant();
			assert(!almostEquals(determinant, 0));

			Matrix inverted;

			for (int row = 0; row < Dimensions; ++row)
			{
				for (int column = 0; column < Dimensions; ++column)
				{
					float cofactor = Cofactor(row, column);
					// Flipped row, column to also handle transposing.
					inverted(column, row) = cofactor / determinant;
				}
			}

			return inverted;
		}
	};
}