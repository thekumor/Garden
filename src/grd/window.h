// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/window.h
//	Desc: Window class definition.
// 
//	Modified: 2026/01/18 4:37 PM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <string>
#include <vector>

// WinAPI
#include <windows.h>

// Garden
#include <grd/base_class.h>
#include <grd/controls.h>
#include <grd/util.h>
#include <grd/events.h>

namespace grd
{

	// ---------------------------------------------------
	//	Handles displaying elements.
	// ---------------------------------------------------
	class Window : public BaseClass
	{
	public:
		Window(const std::wstring& title, const Vec2<std::int32_t>& size);
		Window() = default;
		~Window() = default;

		template <typename T>
		T* CreateControl(const std::wstring& text, const Vec2<std::int32_t>& size, const Vec2<std::int32_t>& position)
		{
			return static_cast<T*>(m_Controls.emplace_back(new T(text, size, position, m_Handle)));
		}

		static LRESULT s_WindowProcedure(HWND, UINT, WPARAM, LPARAM);

	private:
		WNDCLASSEXW m_WindowClass;
		HWND m_Handle;
		std::wstring m_Title;
		Vec2<std::int32_t> m_Size;
		std::vector<Control*> m_Controls = { };
	};

}