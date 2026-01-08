// ================================================
// 
//	Project: Garden
// 
//	File: controls.h
//	Desc: GUI Control class definitions
// 
//	Modified: 2025/01/08 2:26 PM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <string>

// WinAPI
#include <windows.h>

// Garden
#include <grd/base_class.h>
#include <grd/util.h>

namespace grd
{

	class Control : public BaseClass
	{
	public:
		Control(const std::wstring& text, const Vec2<std::int32_t>& size, const Vec2<std::int32_t>& position);
		Control() = default;
		~Control() = default;

	protected:
		HWND m_Handle, m_Parent;
		std::wstring m_Text;
		Vec2<std::int32_t> m_Size, m_Position;
	};

	class Button : public Control
	{
	public:
		Button(const std::wstring& text, const Vec2<std::int32_t>& size, const Vec2<std::int32_t>& position, HWND parent);
		Button() = default;
		~Button() = default;
	};

	class Text : public Control
	{
	public:
		Text(const std::wstring& text, const Vec2<std::int32_t>& size, const Vec2<std::int32_t>& position, HWND parent);
		Text() = default;
		~Text() = default;
	};

}