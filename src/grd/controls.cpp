// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/controls.cpp
//	Desc: GUI Control class definitions
// 
//	Modified: 2026/02/22 11:02 AM
//	Authors: The Kumor
// 
// ================================================

#include "controls.h"

namespace grd
{

	Control::Control(const std::wstring& text, const Vec2i& size, const Vec2i& position)
		: m_Text(text), m_Size(size), m_Position(position), m_Parent(nullptr), m_Handle(nullptr)
	{}

	Control::Control()
		: m_Text(L""), m_Size(0, 0), m_Position(0, 0), m_Parent(nullptr), m_Handle(nullptr)
	{}

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
			SetWindowPos(
				m_Handle,
				nullptr,
				0,
				0,
				static_cast<std::int32_t>(m_Size.x * delta.x),
				static_cast<std::int32_t>(m_Size.y * delta.y),
				SWP_NOMOVE | SWP_NOZORDER
			);
	}

	void Control::Reposition(const Vec2<float> delta)
	{
		if (m_Handle)
			SetWindowPos(
				m_Handle,
				nullptr,
				static_cast<std::int32_t>(m_Position.x * delta.x),
				static_cast<std::int32_t>(m_Position.y * delta.y),
				0,
				0,
				SWP_NOSIZE | SWP_NOZORDER
			);
	}

	void Control::Close()
	{
		DestroyWindow(m_Handle);
	}

	WNDCLASSEXW Button::s_ButtonClass;
	Button::Button(const std::wstring& text, const Vec2i& size, const Vec2i& position, HWND parent)
		: Control(text, size, position)
	{
		static const wchar_t* className = L"Garden Field";
		HINSTANCE instance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

		if (!s_ButtonClass.hInstance)
		{
			s_ButtonClass = { 0 };
			s_ButtonClass.cbClsExtra = 0;
			s_ButtonClass.cbSize = sizeof(WNDCLASSEXW);
			s_ButtonClass.hInstance = instance;
			s_ButtonClass.lpszClassName = className;
			s_ButtonClass.lpszMenuName = nullptr;
			s_ButtonClass.hCursor = LoadCursorW(nullptr, IDC_HAND);
			s_ButtonClass.lpfnWndProc = Button::s_WindowProcedure;

			RegisterClassEx(&s_ButtonClass);
			CheckErrors(L"Button.Button.RegisterClassEx");
		}

		m_Handle = CreateWindow(
			className,
			text.c_str(),
			WS_VISIBLE | WS_CHILD,
			position.x,
			position.y,
			size.x,
			size.y,
			parent,
			nullptr,
			instance,
			0
		);
		CheckErrors(L"Button.Button.CreateWindow");

		m_Listener->AddCallback(EventType::WindowResize, [this](EventData ev)
			{
				Vec2<float> delta = GRD_EVDATA_CAST(ev, Vec2<float>);

				Resize(delta);
				Reposition(delta);
			}
		);

		m_Listener->SetQualifier(m_Handle);
	}

	LRESULT Button::s_WindowProcedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		static std::unordered_map<LPCWSTR, HBITMAP> s_Bitmaps = {};
		static LPCWSTR s_ImgPath = L"D:\\Dev\\Garden\\img\\test.bmp";

		switch (msg)
		{
			case WM_PAINT:
			{
				//PAINTSTRUCT ps;
				//HBRUSH border = CreateSolidBrush(RGB(32, 32, 32));
				//HBRUSH background = CreateSolidBrush(RGB(220, 220, 220));
				//RECT rc;
				//GetClientRect(handle, &rc);

				//HDC hdc = BeginPaint(handle, &ps);
				//FillRect(hdc, &rc, background);
				//FrameRect(hdc, &rc, border);
				//EndPaint(handle, &ps);

				//HBITMAP hBitmap = s_Bitmaps[s_ImgPath];

				//PAINTSTRUCT ps;
				//HDC hdc = BeginPaint(handle, &ps);
				//HDC memDC = CreateCompatibleDC(hdc);
				//HGDIOBJ old = SelectObject(memDC, hBitmap);

				//BITMAP bitmap;
				//GetObject(hBitmap, sizeof(bitmap), &bitmap);
				////BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, memDC, 0, 0, SRCCOPY);
				//StretchBlt(hdc, 0, 0, 64, 64, memDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
				//SelectObject(memDC, old);
				//DeleteDC(memDC);

				//EndPaint(handle, &ps);

				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(handle, &ps);
				static HBRUSH background = CreateSolidBrush(RGB(220, 220, 220));
				static HBRUSH frame = CreateSolidBrush(RGB(20, 20, 20));
				RECT rc;
				GetClientRect(handle, &rc);
				FillRect(hdc, &ps.rcPaint, background);
				FrameRect(hdc, &rc, frame);

				// TODO: Make it center vertically
				LPWSTR text = nullptr;
				std::int32_t length = GetWindowTextLengthW(handle);
				if (length != 0)
				{
#pragma warning(disable: 6387)
					GetWindowTextW(handle, text, length);
					DrawTextW(hdc, L"Test", -1, &rc, DT_VCENTER | DT_CENTER);
				}
				EndPaint(handle, &ps);

			} break;

			case WM_CREATE:
			{
				auto it = s_Bitmaps.find(s_ImgPath);
				if (it != s_Bitmaps.end()) break;

				s_Bitmaps[s_ImgPath] = reinterpret_cast<HBITMAP>(LoadImageW(nullptr, s_ImgPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
				CheckErrors(L"Button.s_WindowProcedure.LoadImageW");
			} break;
		}

		return DefWindowProc(handle, msg, wp, lp);
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

		m_Listener->SetQualifier(m_Handle);
	}

}