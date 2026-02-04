// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/controls.h
//	Desc: GUI Control class definitions
// 
//	Modified: 2026/02/02 4:10 PM
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
		Control(const std::wstring& text, const Vec2i& size, const Vec2i& position);
		Control() = default;
		~Control() = default;

		inline Vec2i GetSize() const { return m_Size; }
		inline Vec2i GetPosition() const { return m_Position; }
		void SetSize(const Vec2i& size);
		void SetPosition(const Vec2i& position);
		void Resize(const Vec2<float> delta);
		void Reposition(const Vec2<float> delta);

	protected:
		HWND m_Handle, m_Parent;
		std::wstring m_Text;
		Vec2i m_Size, m_Position;
		EventListener m_Listener;
	};

	// ---------------------------------------------------
	//	Can be clicked to perform an action.
	// ---------------------------------------------------
	class Button : public Control
	{
	public:
		Button(const std::wstring& text, const Vec2i& size, const Vec2i& position, HWND parent);
		Button() = default;
		~Button() = default;
	};

	// ---------------------------------------------------
	//	On-screen text element.
	// ---------------------------------------------------
	class Text : public Control
	{
	public:
		Text(const std::wstring& text, const Vec2i& size, const Vec2i& position, HWND parent);
		Text() = default;
		~Text() = default;
	};

}