// ================================================
// 
//	Project: Garden
// 
//	File: util.h
//	Desc: Utility functions and structures.
// 
//	Modified: 2025/01/08 2:26 PM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <cstdint>
#include <string>

// WinAPI
#include <windows.h>

#define GRD_WINAPI_DEBUG_INFO 0

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

	DWORD CheckErrors(const std::wstring& info);

}