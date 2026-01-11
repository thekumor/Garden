// ================================================
// 
//	Project: Garden
// 
//	File: src/window.cpp
//	Desc: Window class definition.
// 
//	Modified: 2025/01/08 2:26 PM
//	Authors: The Kumor
// 
// ================================================

#include "window.h"

namespace grd
{

	Window::Window(const std::wstring& title, const Vec2<std::int32_t>& size)
		: m_Title(title), m_Size(size)
	{
		static const wchar_t* className = L"Garden Window";

		HINSTANCE instance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

		m_WindowClass = { 0 };
		m_WindowClass.cbClsExtra = 0;
		m_WindowClass.cbSize = sizeof(WNDCLASSEXW);
		m_WindowClass.hInstance = instance;
		m_WindowClass.lpszClassName = className;
		m_WindowClass.lpszMenuName = nullptr;
		m_WindowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
		m_WindowClass.lpfnWndProc = Window::s_WindowProcedure;

		RegisterClassEx(&m_WindowClass);
		CheckErrors(L"Window.Window.RegisterClassEx");

		m_Handle = CreateWindowEx(
			0,
			className,
			title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			size.x,
			size.y,
			nullptr,
			nullptr,
			instance,
			nullptr
		);
		CheckErrors(L"Window.Window.CreateWindowEx");

		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);
	}

	LRESULT Window::s_WindowProcedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_CLOSE:
			{
				PostQuitMessage(0);
			} break;

			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(handle, &ps);
				
				FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW + 3));
				//RECT rc;
				//GetWindowRect(handle, &rc);
				//DrawText(hdc, L"Hello, I'm a text :)\0", -1, &rc, DT_CENTER);

				EndPaint(handle, &ps);
			} break;
		}

		return DefWindowProc(handle, msg, wp, lp);
	}

}