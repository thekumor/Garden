// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/window.cpp
//	Desc: Window class definition.
// 
//	Modified: 2026/02/06 2:27 PM
//	Authors: The Kumor
// 
// ================================================

#include "window.h"

namespace grd
{

	Window::Window(const std::wstring& title, const Vec2i& size)
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

		HMENU menuHandle = LoadMenuW(instance, MAKEINTRESOURCEW(IDR_MENU1));
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
			menuHandle,
			instance,
			nullptr
		);
		CheckErrors(L"Window.Window.CreateWindowEx");

		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);

		g_WindowSizes[m_Handle] = size;
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

				EndPaint(handle, &ps);
			} break;

			case WM_EXITSIZEMOVE:
			case WM_SIZE:
			{
				if (msg == WM_SIZE && wp != SIZE_MAXIMIZED) break;

				WORD size = static_cast<WORD>(lp);

				RECT rc;
				//GetClientRect(handle, &rc);
				GetWindowRect(handle, &rc);
				Vec2i newSize(rc.right - rc.left, rc.bottom - rc.top);

				Vec2i originalSize = g_WindowSizes[handle];
				std::vector<Vec2i> sizes = { newSize, originalSize };

				g_EventDispatcher.CallEvent(Event(EventType::WindowResize, &sizes));
			} break;

			case WM_COMMAND:
			{
				switch (wp)
				{
					case ID_APPLICATION_CLOSE:
					{
						PostQuitMessage(0);
					} break;

					case ID_ABOUT_WEBSITE:
					{
						ShellExecute(
							nullptr,
							L"open",
							L"https://thekumor.com",
							nullptr,
							nullptr,
							SW_SHOWNORMAL
						);
					} break;

					case ID_SIZE_32X32:
					case ID_SIZE_48X48:
					case ID_SIZE_64X64:
					case ID_SIZE_96X96:
					{
						g_EventDispatcher.CallEvent(Event(EventType::GridSizeChanged, &wp));
					} break;
				}
			} break;
		}

		return DefWindowProc(handle, msg, wp, lp);
	}

	void Camera::Reset()
	{

	}

	void Camera::Zoom(float factor)
	{

	}

	void Camera::Move(const Vec2<float>& delta)
	{

	}

}