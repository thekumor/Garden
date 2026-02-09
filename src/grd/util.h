// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/util.h
//	Desc: Utility functions and structures.
// 
//	Modified: 2026/02/09 11:44 AM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <cstdint>
#include <string>
#include <unordered_map>

// WinAPI
#include <windows.h>

#define GRD_WINDOW_HEIGHT 900
#define GRD_WINDOW_WIDTH 1280

#define GRD_WINAPI_DEBUG_INFO 0

namespace grd
{

	// ---------------------------------------------------
	//	Contains 2D vector data.
	// ---------------------------------------------------
	template <typename T>
	struct Vec2
	{
		Vec2(T x, T y)
			: X(x), Y(y)
		{}
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

		Vec2<T> operator+(const Vec2<T>& other) const
		{
			return Vec2<T>(X + other.X, Y + other.Y);
		}

		Vec2<T> operator-(const Vec2<T>& other) const
		{
			return Vec2<T>(X - other.X, Y - other.Y);
		}

		Vec2<T> operator*(const Vec2<T>& other) const
		{
			return Vec2<T>(X * other.X, Y * other.Y);
		}

		Vec2<T> operator*(const T& scalar) const
		{
			return Vec2<T>(X * scalar, Y * scalar);
		}

		Vec2<T> operator/(const Vec2<T>& other) const
		{
			return Vec2<T>(X / other.X, Y / other.Y);
		}

		Vec2<T> operator/(const T& scalar) const
		{
			return Vec2<T>(X / scalar, Y / scalar);
		}
	};

	template <typename T>
	class Handle
	{
	public:
		Handle(T& val)
			: m_Value(val), m_Valid(true)
		{}

		Handle() :
			m_Valid(true)
		{}
		~Handle() = default;
		
		T& operator*()
		{
			return m_Value;
		}

		inline bool IsValid()
		{
			return m_Valid;
		}

		inline void SetInvalid()
		{
			m_Valid = false;
		}

	private:
		T m_Value;
		bool m_Valid;
	};

	typedef Vec2<std::int32_t> Vec2i;

	DWORD CheckErrors(const std::wstring& info);

	extern std::unordered_map<HWND, Vec2i> g_WindowSizes;

}