// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/field.h
//	Desc: Field and the way it behaves.
// 
//	Modified: 2026/02/21 8:11 AM
//	Created: 2026/02/20 10:35 AM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// Garden
#include <grd/controls.h>
#include <grd/util.h>

// stb
#include <stb/stb_image.h>

// WinAPI
#include <windows.h>

namespace grd
{

	class Field : public Control
	{
	public:
		Field(const Vec2i& size, const Vec2i& position, HWND parent = nullptr);
		Field() = default;
		~Field() = default;

		static WNDCLASSEXW s_FieldClass;

		static LRESULT s_WindowProcedure(HWND, UINT, WPARAM, LPARAM);

	private:
		static HBITMAP ms_Bitmap;

		unsigned char* m_ImageData;
		int m_ImageWidth, m_ImageHeight, m_ImageChannels;
	};

}