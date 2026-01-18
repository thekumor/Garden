// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/controls.h
//	Desc: GUI Control class definitions
// 
//	Modified: 2026/01/18 4:35 PM
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
#include <grd/events.h>

namespace grd
{

	// ---------------------------------------------------
	//	Base class for all controls.
	// ---------------------------------------------------
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
		EventListener m_Listener;
	};

	// ---------------------------------------------------
	//	Can be clicked to perform an action.
	// ---------------------------------------------------
	class Button : public Control
	{
	public:
		Button(const std::wstring& text, const Vec2<std::int32_t>& size, const Vec2<std::int32_t>& position, HWND parent);
		Button() = default;
		~Button() = default;
	};

	// ---------------------------------------------------
	//	On-screen text element.
	// ---------------------------------------------------
	class Text : public Control
	{
	public:
		Text(const std::wstring& text, const Vec2<std::int32_t>& size, const Vec2<std::int32_t>& position, HWND parent);
		Text() = default;
		~Text() = default;
	};

}