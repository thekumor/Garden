// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/controls.cpp
//	Desc: GUI Control class definitions
// 
//	Modified: 2026/02/09 2:41 PM
//	Authors: The Kumor
// 
// ================================================

#include "controls.h"

namespace grd
{

	Control::Control(const std::wstring& text, const Vec2i& size, const Vec2i& position)
		: m_Text(text), m_Size(size), m_Position(position), m_Parent(nullptr)
	{
		m_Listener = new EventListener;
		g_EventDispatcher.PinListener(m_Listener);
	}

	Control::~Control()
	{
		auto* listener = g_EventDispatcher.GetListenerHandle(m_Listener);
		
		if(listener)
			listener->SetInvalid();

		delete m_Listener;
	}

	void Control::SetSize(const Vec2i& size)
	{
		m_Size = size;
		if (m_Handle)
			SetWindowPos(m_Handle, nullptr, 0, 0, size.x, size.y, SWP_NOMOVE | SWP_NOZORDER);
	}

	void Control::SetPosition(const Vec2i& position)
	{
		m_Position = position;
		if (m_Handle)
			SetWindowPos(m_Handle, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	void Control::Resize(const Vec2<float> delta)
	{
		if (m_Handle)
			SetWindowPos(m_Handle, nullptr, 0, 0, m_Size.x * delta.x, m_Size.y * delta.y, SWP_NOMOVE | SWP_NOZORDER);
	}

	void Control::Reposition(const Vec2<float> delta)
	{
		if (m_Handle)
			SetWindowPos(m_Handle, nullptr, m_Position.x * delta.x, m_Position.y * delta.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	void Control::Close()
	{
		DestroyWindow(m_Handle);
	}

	Button::Button(const std::wstring& text, const Vec2i& size, const Vec2i& position, HWND parent)
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
		
		m_Listener->AddCallback(EventType::WindowResize, [this](EventData ev)
			{
				std::vector<Vec2i> sizes = GRD_EVDATA_CAST(ev, std::vector<Vec2i>);
				
				Vec2i& newSize = sizes[0];
				Vec2i& originalSize = sizes[1];
				Vec2<float> delta(static_cast<float>(newSize.x) / originalSize.x, static_cast<float>(newSize.y) / originalSize.y);

				Resize(delta);
				Reposition(delta);
			}
		);
	}

	Text::Text(const std::wstring& text, const Vec2i& size, const Vec2i& position, HWND parent)
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