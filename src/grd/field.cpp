// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/field.h
//	Desc: Field and the way it behaves.
// 
//	Modified: 2026/02/24 10:16 AM
//	Created: 2026/02/20 10:42 AM
//	Authors: The Kumor
// 
// ================================================

#include "field.h"

namespace grd
{

	static std::unordered_map<Vec2i, ImageRect> s_PlantedVegetables = {};

	static void PaintField(HWND handle, HDC hdc)
	{
		static HBRUSH s_Background = CreateSolidBrush(RGB(0, 255, 0));

		for (auto& plantedVeg : s_PlantedVegetables)
		{
			Vec2i position = plantedVeg.first;
			ImageRect imageRect = plantedVeg.second;

			BITMAPINFO bmi = { 0 };
			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth = g_ImageInfo.ImageWidth;
			bmi.bmiHeader.biHeight = -g_ImageInfo.ImageHeight;
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;
			bmi.bmiHeader.biCompression = BI_RGB;

			RECT rc;
			rc.left = position.x;
			rc.top = position.y;
			rc.right = rc.left + 64;
			rc.bottom = rc.top + 64;

			// Some background
			FillRect(hdc, &rc, s_Background);

			HDC memDC = CreateCompatibleDC(hdc);
			void* bits = nullptr;

			HBITMAP dib = CreateDIBSection(
				hdc,
				&bmi,
				DIB_RGB_COLORS,
				&bits,
				nullptr,
				0
			);

			memcpy(bits, g_ImageInfo.ImageData, g_ImageInfo.ImageWidth * g_ImageInfo.ImageHeight * 4);
			HBITMAP old = reinterpret_cast<HBITMAP>(SelectObject(memDC, dib));

			BLENDFUNCTION bf = {
				AC_SRC_OVER,
				0,
				255,
				AC_SRC_ALPHA
			};

			AlphaBlend(
				hdc,
				rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
				memDC,
				imageRect.Pos.x, imageRect.Pos.y, imageRect.Size.x, imageRect.Size.y,
				bf
			);

			SelectObject(memDC, old);
			DeleteObject(dib);
			DeleteDC(memDC);
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
				PaintField(handle, hdc);
				EndPaint(handle, &ps);
			} break;

			case WM_LBUTTONDOWN:
			{
				if (!g_CurrentVegetable) break;

				RECT rc;
				POINT cursorPos;
				GetCursorPos(&cursorPos);
				GetWindowRect(handle, &rc);

				cursorPos.x -= rc.left;
				cursorPos.y -= rc.top;

				cursorPos.x -= cursorPos.x % 64;
				cursorPos.y -= cursorPos.y % 64;

				RECT paintRegion;
				paintRegion.left = cursorPos.x;
				paintRegion.top = cursorPos.y;
				paintRegion.right = paintRegion.left + 64;
				paintRegion.bottom = paintRegion.top + 64;

				ImageRect imgRect = g_CurrentVegetable->GetRect();
				Vec2i cursorVec(cursorPos.x, cursorPos.y);

				s_PlantedVegetables[cursorVec] = imgRect;
				InvalidateRect(handle, &paintRegion, TRUE);
			} break;
		}

		return Control::s_WindowProcedure(handle, msg, wp, lp);
	}

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

		m_Listener->SetQualifier(m_Handle);
	}

}