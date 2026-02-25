// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/side_panel.cpp
//	Desc: Place where buttons to place vegs live.
// 
//	Modified: 2026/02/24 9:03 AM
//	Created: 2026/02/22 11:30 AM
//	Authors: The Kumor
// 
// ================================================

#include "side_panel.h"

namespace grd
{

	WNDCLASSEX SidePanel::s_SidePanelClass = { 0 };

	SidePanel::SidePanel(const Vec2i& size, const Vec2i& position, HWND parent)
		: Control(L"", size, position)
	{
		static const wchar_t* className = L"Garden Side Panel";
		HINSTANCE instance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

		if (!s_SidePanelClass.hInstance)
		{
			s_SidePanelClass = { 0 };
			s_SidePanelClass.cbClsExtra = 0;
			s_SidePanelClass.cbSize = sizeof(WNDCLASSEXW);
			s_SidePanelClass.hInstance = instance;
			s_SidePanelClass.lpszClassName = className;
			s_SidePanelClass.lpszMenuName = nullptr;
			s_SidePanelClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
			s_SidePanelClass.lpfnWndProc = SidePanel::s_WindowProcedure;

			RegisterClassEx(&s_SidePanelClass);
			CheckErrors(L"SidePanel.SidePanel.RegisterClassEx");
		}

		m_Handle = CreateWindow(
			className,
			L"",
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
		CheckErrors(L"SidePanel.SidePanel.CreateWindow");

		m_Listener->AddCallback(EventType::WindowResize, [this](EventData ev)
			{
				Vec2<float> delta = GRD_EVDATA_CAST(ev, Vec2<float>);

				Resize(delta);
				Reposition(delta);
			}
		);

		m_Listener->SetQualifier(m_Handle);
	}

	LRESULT SidePanel::s_WindowProcedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_PAINT:
			{
				static HBRUSH red = CreateSolidBrush(RGB(100, 0, 0));
				PAINTSTRUCT ps;
				RECT rc;
				GetClientRect(handle, &rc);
				HDC hdc = BeginPaint(handle, &ps);

				FillRect(hdc, &rc, red);

				EndPaint(handle, &ps);
			} break;
		}

		return Control::s_WindowProcedure(handle, msg, wp, lp);
	}

}