// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/field.h
//	Desc: Field and the way it behaves.
// 
//	Modified: 2026/02/21 10:11 AM
//	Created: 2026/02/20 10:42 AM
//	Authors: The Kumor
// 
// ================================================

#include "field.h"

namespace grd
{

	WNDCLASSEXW Field::s_FieldClass = { 0 };

	LRESULT Field::s_WindowProcedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				RECT rc;
				GetClientRect(handle, &rc);
				static HBRUSH background = CreateSolidBrush(RGB(0, 100, 0));
				HDC hdc = BeginPaint(handle, &ps);

				FillRect(hdc, &rc, background);

				EndPaint(handle, &ps);
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
	}

}