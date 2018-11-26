#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <array>
#include <math.h>
#include <random>
#include <string>

namespace EOUL {

	namespace Math {

		/* return the given value as a binary string */
		std::string toBinaryString(unsigned long long value, bool keepTrailingZeros = false, unsigned long long groupSize = -1);

		/* generates a random number between 0.0 and 1.0 */
		double random();
		/* generates a random number between 0.0 and the given max */
		double random(double max);
		/* generates a random number between the given min and the given max */
		double random(double min, double max);

		/* returns the 3d distance of 2 points */
		double dist(double x1, double y1, double z1, double x2, double y2, double z2);
		/* returns the 2d distance of 2 points */
		double dist(double x1, double y1, double x2, double y2);
		/* retuns a constrained value of the given number */
		double constrain(double val, double min, double max);
		/* lerps between a start and a stop, based on the given amt */
		double lerp(double start, double stop, double amt);

		/* maps tow ranges to eachother */
		double map(double value, double min1, double max1, double min2, double max2, bool constrainValue = false);
		/* aps a range to 0.0 - 1.0 */
		double norm(double value, double min, double max);

		/* transforms degrees into radians */
		double radians(double degrees);
		/* transforms radians into degrees */
		double degrees(double radians);

		/* squares the given number */
		double sq(double num);

	}

}

namespace EOUL {

	namespace Math {

		template <typename T>
		inline T& random(std::vector<T>& arr) {

			return arr[(unsigned int) random(0, arr.size())];

		}

		template <typename T, unsigned long long size>
		inline T& random(std::array<T, size>& arr) {

			return arr[(unsigned int) random(0, size)];

		}

	}

}