// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/controls.h
//	Desc: GUI Control class definitions
// 
//	Modified: 2026/02/23 9:48 AM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <string>
#include <unordered_map>

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
		Control();
		~Control() = default;

		template <typename T>
		T* CreateControl(const std::wstring& text, const Vec2i& size, const Vec2i& position)
		{
			return static_cast<T*>(m_Controls.emplace_back(new T(text, size, position, m_Handle)));
		}

		inline Vec2i GetSize() const { return m_Size; }
		inline Vec2i GetPosition() const { return m_Position; }
		void SetSize(const Vec2i& size);
		void SetPosition(const Vec2i& position);
		void Resize(const Vec2<float> delta);
		void Reposition(const Vec2<float> delta);
		void Close();
		void ClearControls();

	protected:
		std::vector<Control*> m_Controls = { };
		HWND m_Handle, m_Parent;
		std::wstring m_Text;
		Vec2i m_Size, m_Position;
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

		static WNDCLASSEXW s_ButtonClass;
		static LRESULT s_WindowProcedure(HWND, UINT, WPARAM, LPARAM);
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