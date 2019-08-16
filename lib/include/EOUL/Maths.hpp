#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <array>
#include <cmath>
#include <random>
#include <string>

#include <EOUL/Constants.hpp>

namespace EOUL::Math {

	/* generates a random number between the given min and the given max */
	template <typename RandomEngine = std::mt19937_64>
	inline double random(double min = 0.0, double max = 1.0) {

		static std::random_device device;
		static RandomEngine engine = RandomEngine(device());
		static std::uniform_real_distribution<double> distribution = std::uniform_real_distribution<double>(0.0, 1.0);

		return distribution(engine) * (max - min) + min;

	}

	/*

		returns the 2d distance of 2 points.
		could be inaccurate when used with non-floating types.

	*/
	template <typename T = double>
	inline T dist(T x1, T y1, T x2, T y2) {

		return hypot(x2 - x1, y2 - y1);

	}
	/* 

		returns the 3d distance of 2 points.
		could be inaccurate when used with non-floating types.

	*/
	template <typename T = double>
	inline T dist(T x1, T y1, T z1, T x2, T y2, T z2) {

		T diffX = abs(x1 - x2);
		T diffZ = abs(z1 - z2);

		T gD = hypot(diffX, diffZ);

		return hypot(gD, fabs(y1 - y2));

	}

	/* 

		lerps between a start and a stop, based on the given amt, also known as linear interpolation.
		could be inaccurate when used with non-floating types.

	*/
	template <typename T = double>
	inline T lerp(T start, T stop, T amt) {

		return amt * (stop - start) + start;

	}

	/* 

		maps two ranges to eachother.
		could be inaccurate when used with non-floating types.

	*/
	template <typename T = double>
	inline T map(T value, T min1, T max1, T min2, T max2, bool clampValue = false) {

		T mapped = ((value - min1) / (max1 - min1)) * (max2 - min2) + min2;

		if (clampValue) {

			return std::clamp(mapped, min2, max2);

		}

		return mapped;

	}
	/* 

		maps a range to [0 - 1]
		could be inaccurate when used with non-floating types.

	*/
	template <typename T = double>
	inline T norm(T value, T min, T max) {

		return map(value, min, max, static_cast<T>(0.0), static_cast<T>(1.0));

	}

	/* transforms degrees into radians */
	template <typename T = double>
	inline T radians(T degrees) {

		return degrees * static_cast<T>(PI) / static_cast<T>(180.0);

	}
	/* transforms radians into degrees */
	template <typename T = double>
	inline T degrees(T radians) {

		return radians * static_cast<T>(180.0) / static_cast<T>(PI);

	}

	/* squares the given number */
	template <typename T = double>
	inline T sq(T num) {

		return num * num;

	}

	template <typename T>
	inline T& random(std::vector<T>& arr) {

		return arr[(size_t) random(size_t(0), arr.size())];

	}

	template <typename T, size_t size>
	inline T& random(std::array<T, size>& arr) {

		return arr[(size_t) random(size_t(0), static_cast<size_t>(size))];

	}

	template <typename T>
	inline const T& crandom(const std::vector<T>& arr) {

		return arr[(size_t) random(size_t(0), arr.size())];

	}

	template <typename T, size_t size>
	inline const T& crandom(const std::array<T, size>& arr) {

		return arr[(size_t) random(size_t(0), static_cast<size_t>(size))];

	}

}