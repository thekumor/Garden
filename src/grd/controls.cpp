// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/grd/controls.cpp
//	Desc: GUI Control class definitions
// 
//	Modified: 2025/01/08 8:22 PM
//	Authors: The Kumor
// 
// ================================================

#include "controls.h"

namespace grd
{

	Control::Control(const std::wstring& text, const Vec2<std::int32_t>& size, const Vec2<std::int32_t>& position)
		: m_Text(text), m_Size(size), m_Position(position), m_Parent(nullptr)
	{
	}

	Button::Button(const std::wstring& text, const Vec2<std::int32_t>& size, const Vec2<std::int32_t>& position, HWND parent)
		: Control(text, size, position)
	{
		m_Handle = CreateWindow(
			L"Button",
			text.c_str(),
			WS_VISIBLE | WS_CHILD,
			position.x,
			position.y,
			size.x,
			size.y,
			parent,
			nullptr,
			reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)),
			0
		);
		CheckErrors(L"Button.Button.CreateWindow");
	}

	Text::Text(const std::wstring& text, const Vec2<std::int32_t>& size, const Vec2<std::int32_t>& position, HWND parent)
	{
		m_Handle = CreateWindow(
			L"Static",
			text.c_str(),
			WS_VISIBLE | WS_CHILD,
			position.x,
			position.y,
			size.x,
			size.y,
			parent,
			nullptr,
			reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)),
			0
		);
		CheckErrors(L"Text.Text.CreateWindow");
	}

}