#pragma once

// STL
#include <cstdint>

namespace grd
{

	template <typename T>
	struct Vec2
	{
		Vec2(T x, T y)
			: X(x), Y(y)
		{
		}
		Vec2() = default;
		~Vec2() = default;

		union
		{
			T x, X;
		};
		union
		{
			T y, Y;
		};
	};

}