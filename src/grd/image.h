// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/image.h
//	Desc: Defines the way images are stored.
// 
//	Modified: 2026/02/24 11:54 AM
//	Created: 2026/02/23 10:48 AM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <string>
#include <cstdint>
#include <unordered_map>
#include <utility>

// WinAPI
#include <windows.h>

// stb
#include <stb/stb_image.h>

// Garden
#include <grd/controls.h>

namespace grd
{

	struct ImageInfo
	{
		ImageInfo(const std::string& path);
		ImageInfo() = default;
		~ImageInfo();

		bool LoadImage(const std::string& path);

		std::string Path;
		std::uint8_t* ImageData;
		std::int32_t ImageWidth, ImageHeight, ImageChannels;
	};

	extern ImageInfo g_ImageInfo;

	struct ImageRect
	{
		ImageRect(const Vec2i& pos, const Vec2i& size);
		ImageRect() = default;
		
		Vec2i Pos, Size;

		friend bool operator==(const ImageRect&, const ImageRect&) = default;
	};

	class Image : public Control
	{
	public:
		Image(const std::wstring& text, const Vec2i& size, const Vec2i& position, HWND parent);
		Image() = default;
		~Image() = default;

		inline ImageRect GetRect() const { return m_Rect; }
		void SetRect(const ImageRect& rect);
		void SetBgColors(COLORREF background, COLORREF frame);

		static WNDCLASSEXW s_ImageClass;
		static Image* s_SelectedImg;
		static std::unordered_map<HWND, ImageRect> s_ImageRects;
		static std::unordered_map<HWND, std::pair<HBRUSH, HBRUSH>> s_ImageBgColors;
		static LRESULT s_WindowProcedure(HWND, UINT, WPARAM, LPARAM);

	private:
		ImageRect m_Rect;
	};

}

namespace std
{

	template <>
	struct hash<grd::ImageRect>
	{
		std::size_t operator()(const grd::ImageRect& v) const noexcept
		{
			std::size_t h1 = std::hash<grd::Vec2i>{}(v.Pos);
			std::size_t h2 = std::hash<grd::Vec2i>{}(v.Size);

			return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
		}
	};

}