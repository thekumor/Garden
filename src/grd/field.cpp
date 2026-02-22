// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/field.h
//	Desc: Field and the way it behaves.
// 
//	Modified: 2026/02/22 10:44 AM
//	Created: 2026/02/20 10:42 AM
//	Authors: The Kumor
// 
// ================================================

#include "field.h"

namespace grd
{

	static std::vector<POINT> s_Points = {};

	static void PaintField(HWND handle, HDC hdc)
	{
		static HBRUSH s_FieldBgr = CreateSolidBrush(RGB(128, 128, 128));
		static HBRUSH s_Black = CreateSolidBrush(RGB(0, 0, 0));

		for (auto& point : s_Points)
		{
			RECT subrc;
			subrc.left = point.x;
			subrc.top = point.y;
			subrc.right = subrc.left + 64;
			subrc.bottom = subrc.top + 64;

			FillRect(hdc, &subrc, s_FieldBgr);
			FrameRect(hdc, &subrc, s_Black);
		}
	}

	WNDCLASSEXW Field::s_FieldClass = { 0 };

	LRESULT Field::s_WindowProcedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_PAINT:
			{
				static HBRUSH s_Background = CreateSolidBrush(RGB(0, 100, 0));
				PAINTSTRUCT ps;
				RECT rc;
				GetClientRect(handle, &rc);

				HDC hdc = BeginPaint(handle, &ps);
				FillRect(hdc, &rc, s_Background);
				g_EventDispatcher.CallEventQ(Event(EventType::Draw, &hdc), handle);
				EndPaint(handle, &ps);
			} break;

			case WM_LBUTTONDOWN:
			{
				RECT rc;
				POINT cursorPos;
				GetCursorPos(&cursorPos);
				GetWindowRect(handle, &rc);

				cursorPos.x -= rc.left;
				cursorPos.y -= rc.top;

				RECT paintRegion;
				paintRegion.left = cursorPos.x;
				paintRegion.top = cursorPos.y;
				paintRegion.right = paintRegion.left + 64;
				paintRegion.bottom = paintRegion.top + 64;

				s_Points.push_back(cursorPos);
				InvalidateRect(handle, &paintRegion, TRUE);
			} break;
		}

		return DefWindowProcW(handle, msg, wp, lp);
	}

	HBITMAP Field::ms_Bitmap = nullptr;

	Field::Field(const Vec2i& size, const Vec2i& position, HWND parent)
		: Control(L"", size, position)
	{
		const wchar_t* className = L"Garden Field";
		HINSTANCE instance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

		if (!s_FieldClass.hInstance)
		{
			s_FieldClass.cbSize = sizeof(WNDCLASSEXW);
			s_FieldClass.hInstance = instance;
			s_FieldClass.lpszClassName = className;
			s_FieldClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
			s_FieldClass.lpfnWndProc = Field::s_WindowProcedure;

			RegisterClassExW(&s_FieldClass);
			CheckErrors(L"Field.Field.RegisterClassExW");
		}

		// TODO: Change this path!!
		m_ImageData = stbi_load("D:\\Dev\\Garden\\img\\vegetables\\transparent.png", &m_ImageWidth, &m_ImageHeight, &m_ImageChannels, 4);
		if (!m_ImageData)
		{
			MessageBoxW(nullptr, L"Failed to load field image", L"File load error", IDOK);
			return;
		}

		// Switch to BGRA
		for (std::int32_t i = 0; i < m_ImageWidth * m_ImageHeight; i++)
		{
			unsigned char* pixel = m_ImageData + i * 4;

			unsigned char r = pixel[0];
			unsigned char g = pixel[1];
			unsigned char b = pixel[2];
			unsigned char a = pixel[3];

			pixel[0] = (b * a) / 255;
			pixel[1] = (g * a) / 255;
			pixel[2] = (r * a) / 255;
		}

		m_Handle = CreateWindowW(
			className,
			L"",
			WS_VISIBLE | (parent ? WS_CHILD : 0),
			position.x,
			position.y,
			size.x,
			size.y,
			parent,
			nullptr,
			instance,
			0
		);
		CheckErrors(L"Field.Field.CreateWindowW");

		ShowWindow(m_Handle, SW_SHOW);

		m_Listener->AddCallback(EventType::WindowResize, [this](EventData ev)
			{
				Vec2<float> delta = GRD_EVDATA_CAST(ev, Vec2<float>);

				Resize(delta);
				Reposition(delta);
			}
		);

		m_Listener->AddCallback(EventType::Draw, [this](EventData ev)
			{
				HDC hdc = GRD_EVDATA_CAST(ev, HDC);
				PaintField(nullptr, hdc);
			});

		m_Listener->SetQualifier(m_Handle);
	}

}